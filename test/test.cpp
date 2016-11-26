//
// Created by Célian Garcia on 20/11/2016.
//

#define BOOST_TEST_MODULE "C++ unit tests for Fly Library"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "fly.h"

using namespace std;
using namespace cv;
BOOST_AUTO_TEST_CASE( hello )
{
    string reference("salut célian");
    string name("célian");
    string actual = fly::hello(name);

    BOOST_CHECK_MESSAGE( reference == actual, "result: " << actual << " is not equal to " << reference );
}

BOOST_AUTO_TEST_CASE( create_cloud )
{
    vector<Vec3f> reference = {
        Vec3f(2.0, 2.0, 2.0),
        Vec3f(2.0, 2.0, 2.0),
        Vec3f(2.0, 2.0, 2.0)
    };
    vector<Vec3f> actual = fly::create_cloud();

    BOOST_CHECK( actual == reference );
}