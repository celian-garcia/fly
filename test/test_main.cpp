// Copyright 2016 <Célian Garcia>

#define BOOST_TEST_MODULE "C++ unit tests for Fly Library"

#include <iostream>
#include <thread>
#include "fly.hpp"
#include <boost/thread.hpp>
#include <boost/test/unit_test.hpp>

namespace fly {
class CloudTestImpl : public CloudContainer {
 public:
    using CloudContainer::add_point;

    virtual void add_point(cv::Vec3f v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1100));
        CloudContainer::add_point(v);
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

BOOST_AUTO_TEST_CASE(populate_cloud_linearly) {
    // Fill the test references
    fly::CloudTestImpl cloud_ref_2;
    fly::CloudTestImpl cloud_ref_10;
    for (int i = 0; i < 2; ++i) {
        cloud_ref_2.add_point({i, i, i});
    }
    for (int i = 0; i < 10; ++i) {
        cloud_ref_10.add_point({i, i, i});
    }

    // Linear filling action of 10 points from (0, 0, 0) to (9, 9, 9)
    fly::CloudTestImpl *cloud = new fly::CloudTestImpl();
    fly::CloudFiller<fly::CloudTestImpl> cp(cloud);
    boost::thread t(boost::bind(&fly::CloudFiller<fly::CloudTestImpl>::linear_filling, &cp));

    // Wait 3 sec to wait for 2 points which takes 2 x 1.1 sec.
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    BOOST_CHECK_EQUAL(cloud_ref_2, *cloud);

    // Wait for the end of thread method (10 points added)
    t.join();
    BOOST_CHECK_EQUAL(cloud_ref_10, *cloud);

    delete (cloud);
}

BOOST_AUTO_TEST_CASE(populate_cloud_randomly) {
    // Random filling action of 10 points with coordinates that randomly oscillate from -50 to 50
    fly::CloudTestImpl *cloud = new fly::CloudTestImpl();
    fly::CloudFiller<fly::CloudTestImpl> cp(cloud);
    boost::thread t(boost::bind(&fly::CloudFiller<fly::CloudTestImpl>::random_filling, &cp, 10, -50, 50));

    // Wait 3 sec to wait for 2 points which takes 2 x 1.1 sec.
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    BOOST_CHECK_EQUAL(2, cloud->size());

    // Wait for the end of thread method (10 points added)
    t.join();
    BOOST_CHECK_EQUAL(10, cloud->size());

    bool all_points_are_equal = false;
    cv::Vec3f first_point = cloud->operator[](0);
    for (unsigned int i = 1; i < cloud->size(); ++i) {
        all_points_are_equal = first_point == cloud->operator[](i);
        if (!all_points_are_equal) {
            break;
        }
    }
    BOOST_CHECK_EQUAL(false, all_points_are_equal);

    delete (cloud);
}
