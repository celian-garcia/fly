// Copyright 2016 <Célian Garcia>

#include <gtest/gtest.h>
#include <thread>
#include "fly.hpp"

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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CloudPopulation, Linearly) {
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
    auto *cloud = new fly::CloudLow();
    auto *cp = new fly::CloudFiller<fly::CloudLow>(cloud);
    auto t = std::thread([&] { cp->linear_filling(); });

    // Wait 3 sec to wait for 2 points which takes 2 x 1.1 sec.
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    ASSERT_EQ(cloud_ref_2, *cloud);

    // Wait for the end of thread method (10 points added)
    t.join();
    ASSERT_EQ(cloud_ref_10, *cloud);

    delete (cloud);
    delete (cp);
}

TEST(CloudPopulation, Randomly) {
    // Random filling action of 10 points with coordinates that randomly oscillate from -50 to 50
    auto *cloud = new fly::CloudLow();
    auto *cp = new fly::CloudFiller<fly::CloudLow>(cloud);
    auto t = std::thread([&] { cp->random_filling(10, -50, 50); });

    // Wait 3 sec to wait for 2 points which takes 2 x 1.1 sec.
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    ASSERT_EQ(2, cloud->size());

    // Wait for the end of thread method (10 points added)
    t.join();
    ASSERT_EQ(10, cloud->size());

    bool all_points_are_equal = false;
    cv::Vec3f first_point = cloud->operator[](0);
    for (unsigned int i = 1; i < cloud->size(); ++i) {
        all_points_are_equal = first_point == cloud->operator[](i);
        if (!all_points_are_equal) {
            break;
        }
    }
    ASSERT_EQ(false, all_points_are_equal);

    delete (cloud);
    delete (cp);
}

TEST(CloudPopulation, WithDiamond) {
    auto *cloud = new fly::CloudContainer();
    auto *cp = new fly::CloudFiller<fly::CloudContainer>(cloud);

    int nb_subdivisions = 5;
    double top_radius = 3, mid_radius = 4, top_height = 5, mid_height = 4;
    cv::Vec3f bot_point = {1, 1, 2};
    auto t = std::thread([&] {
        cp->diamond_filling(nb_subdivisions, top_radius, mid_radius, top_height, mid_height, bot_point);
    });

    // Wait for the end of thread method
    t.join();

    // Check the third first points
    cv::Vec3f p_0(1, 1, 2);
    cv::Vec3f p_1(-1.90175f, 1.76147, 7);
    cv::Vec3f p_2(-2.869f, 2.01529, 6);

    double err_0 = cv::norm(p_0 - cloud->operator[](0));
    double err_1 = cv::norm(p_1 - cloud->operator[](1));
    double err_2 = cv::norm(p_2 - cloud->operator[](2));

    ASSERT_LE(0, err_0);
    ASSERT_LE(0, err_1);
    ASSERT_LE(0, err_2);

    delete (cloud);
    delete (cp);
}
