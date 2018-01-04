// Copyright 2016 <Célian Garcia>

#define BOOST_TEST_MODULE "C++ unit tests for Fly Library"
#include <iostream>
#include <thread>
#include "fly.hpp"
#include <boost/thread.hpp>
#include <boost/test/unit_test.hpp>

namespace fly {
class CloudThread : public cloud {
 protected:
    boost::mutex mtx_;
 public:
    using cloud::add_point;
    virtual void add_point(cv::Vec3f v) {
        boost::lock_guard<boost::mutex> guard(this->mtx_);
        std::this_thread::sleep_for(std::chrono::milliseconds(1100));
        cloud::add_point(v);
    }
};
}  // namespace fly

BOOST_AUTO_TEST_CASE(hello) {
    std::string reference = "célian";
    fly::Hello h = fly::Hello(reference);
    h.run();
    std::string actual = h.get_name();
    BOOST_CHECK_MESSAGE(reference == actual, "result: " << actual << " is not equal to " << reference);
}

BOOST_AUTO_TEST_CASE(populate_cloud) {
    // Fill the references
    fly::CloudThread cloud_ref_2;
    fly::CloudThread cloud_ref_10;
    for (int i = 0; i < 2; ++i) {
        cloud_ref_2.add_point(i, i, i);
    }
    for (int i = 0; i < 10; ++i) {
        cloud_ref_10.add_point(i, i, i);
    }

    fly::CloudPopulate<fly::CloudThread> cp;
    fly::CloudThread& cloud = cp.get_cloud_reference();
    boost::thread t(boost::bind(&fly::CloudPopulate<fly::CloudThread>::run, &cp));

    // Wait 3 sec to wait for 2 points which takes 2 x 1.1 sec.
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    BOOST_CHECK_EQUAL(cloud_ref_2, cloud);

    // Wait for the end of thread method (10 points added)
    t.join();
    BOOST_CHECK_EQUAL(cloud_ref_10, cloud);
}
