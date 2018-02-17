// Copyright 2016 <Célian Garcia>

#include <gtest/gtest.h>
#include <thread>
#include "fly/CloudFiller.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CloudPopulation, Linearly) {
    // Fill the test references
    std::vector<cv::Vec3f> cloud_ref_2;
    std::vector<cv::Vec3f> cloud_ref_10;
    for (int i = 0; i < 2; ++i) {
        cloud_ref_2.push_back({i, i, i});
    }
    for (int i = 0; i < 10; ++i) {
        cloud_ref_10.push_back({i, i, i});
    }

    std::vector<cv::Vec3f> cloud;
    fly::CloudFiller filler;

    // Linear filling action of 10 points from (0, 0, 0) to (9, 9, 9)
    filler.register_observer([&cloud](float x, float y, float z){
        std::this_thread::sleep_for(std::chrono::milliseconds(110));
        cloud.push_back({x, y, z});
    });

    auto t = std::thread([&] { filler.linear_filling(); });

    // Wait 0.3 sec to wait for 2 points which takes 2 x 0,11 sec.
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    ASSERT_EQ(cloud_ref_2, cloud);

    // Wait for the end of thread method (10 points added)
    t.join();
    ASSERT_EQ(cloud_ref_10, cloud);
}

TEST(CloudPopulation, Randomly) {
    std::vector<cv::Vec3f> cloud;
    fly::CloudFiller filler;

    // Random filling action of 10 points with coordinates that randomly oscillate from -50 to 50
    filler.register_observer([&cloud](float x, float y, float z){
        std::this_thread::sleep_for(std::chrono::milliseconds(110));
        cloud.push_back({x, y, z});
    });

    auto t = std::thread([&] { filler.random_filling(10, -50, 50); });

    // Wait 0.3 sec to wait for 2 points which takes 2 x 0.11 sec.
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    ASSERT_EQ(2, cloud.size());

    // Wait for the end of thread method (10 points added)
    t.join();
    ASSERT_EQ(10, cloud.size());

    bool all_points_are_equal = false;
    cv::Vec3f first_point = cloud[0];
    for (unsigned int i = 1; i < cloud.size(); ++i) {
        all_points_are_equal = first_point == cloud[i];
        if (!all_points_are_equal) {
            break;
        }
    }
    ASSERT_EQ(false, all_points_are_equal);
}

TEST(CloudPopulation, WithDiamond) {
    std::vector<cv::Vec3f> cloud;
    fly::CloudFiller filler;

    filler.register_observer([&cloud](float x, float y, float z){
        cloud.push_back({x, y, z});
    });

    int nb_subdivisions = 5;
    double top_radius = 3, mid_radius = 4, top_height = 5, mid_height = 4;
    cv::Vec3f bot_point = {1, 1, 2};
    auto t = std::thread([&] {
        filler.diamond_filling(nb_subdivisions, top_radius, mid_radius, top_height, mid_height, bot_point);
    });

    // Wait for the end of thread method
    t.join();

    // Check the third first points
    cv::Vec3f p_0(1, 1, 2);
    cv::Vec3f p_1(-1.90175f, 1.76147, 7);
    cv::Vec3f p_2(-2.869f, 2.01529, 6);

    double err_0 = cv::norm(p_0 - cloud[0]);
    double err_1 = cv::norm(p_1 - cloud[1]);
    double err_2 = cv::norm(p_2 - cloud[2]);

    ASSERT_LE(0, err_0);
    ASSERT_LE(0, err_1);
    ASSERT_LE(0, err_2);
}
