// Copyright 2016 <Célian Garcia>

#define BOOST_TEST_MODULE "C++ unit tests for Fly Library"
#include <iostream>
#include "./fly.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(hello) {
    std::string reference = "célian";
    fly::Hello h = fly::Hello(reference);
    h.run();
    std::string actual = h.get_name();
    BOOST_CHECK_MESSAGE(reference == actual, "result: " << actual << " is not equal to " << reference);
}

// BOOST_AUTO_TEST_CASE(create_cloud) {
//     std::vector<cv::Vec3f> reference = {
//         cv::Vec3f(2.0, 2.0, 2.0),
//         cv::Vec3f(2.0, 2.0, 2.0),
//         cv::Vec3f(2.0, 2.0, 2.0)
//     };
//     std::vector<cv::Vec3f> actual = fly::create_cloud();

//     BOOST_CHECK(actual == reference);
// }
