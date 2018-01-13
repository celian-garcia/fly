// Copyright 2016 <Célian Garcia>

#define BOOST_TEST_MODULE "C++ unit tests for Fly Library"

#include <iostream>
#include <thread>
#include "fly.hpp"
#include <boost/thread.hpp>
#include <boost/test/unit_test.hpp>

namespace fly {
class CloudLow : public CloudContainer {
 public:
    using CloudContainer::add_point;

    virtual void add_point(cv::Vec3f v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1100));
        CloudContainer::add_point(v);
    }
};
}  // namespace fly

BOOST_AUTO_TEST_CASE(populate_cloud_linearly) {
    // Fill the test references
    fly::CloudLow cloud_ref_2;
    fly::CloudLow cloud_ref_10;
    for (int i = 0; i < 2; ++i) {
        cloud_ref_2.add_point({i, i, i});
    }
    for (int i = 0; i < 10; ++i) {
        cloud_ref_10.add_point({i, i, i});
    }

    // Linear filling action of 10 points from (0, 0, 0) to (9, 9, 9)
    fly::CloudLow *cloud = new fly::CloudLow();
    fly::CloudFiller<fly::CloudLow> cp(cloud);
    boost::thread t(boost::bind(&fly::CloudFiller<fly::CloudLow>::linear_filling, &cp));

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
    fly::CloudLow *cloud = new fly::CloudLow();
    fly::CloudFiller<fly::CloudLow> cp(cloud);
    boost::thread t(boost::bind(&fly::CloudFiller<fly::CloudLow>::random_filling, &cp, 10, -50, 50));

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

BOOST_AUTO_TEST_CASE(populate_cloud_with_diamond) {
    fly::CloudContainer *cloud = new fly::CloudContainer();
    fly::CloudFiller<fly::CloudContainer> cp(cloud);

    int nb_subdivisions = 5;
    double top_radius = 3, mid_radius = 4, top_height = 5, mid_height = 4;
    cv::Vec3f bot_point = {1, 1, 2};
    boost::thread t(boost::bind(&fly::CloudFiller<fly::CloudContainer>::diamond_filling, &cp,
                                nb_subdivisions, top_radius, mid_radius, top_height, mid_height, bot_point));

    // Wait for the end of thread method
    t.join();

    // Check the third first points
    cv::Vec3f p_0(1, 1, 2);
    cv::Vec3f p_1(-1.90175f, 1.76147, 7);
    cv::Vec3f p_2(-2.869f, 2.01529, 6);

    double err_0 = cv::norm(p_0 - cloud->operator[](0));
    double err_1 = cv::norm(p_1 - cloud->operator[](1));
    double err_2 = cv::norm(p_2 - cloud->operator[](2));

    BOOST_CHECK_LE(0, err_0);
    BOOST_CHECK_LE(0, err_1);
    BOOST_CHECK_LE(0, err_2);

    delete (cloud);
}
