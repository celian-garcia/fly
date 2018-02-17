// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_FLY_CLOUDFILLER_HPP_
#define INCLUDE_FLY_CLOUDFILLER_HPP_

#include <string>
#include <random>
#include <vector>
#include <iostream>
#include <functional>
#include <opencv2/opencv.hpp>

namespace fly {

class CloudFiller {
 protected:
    std::vector<cv::Vec3f> points;
    std::vector<std::function<void(float, float, float)>> observers;

 public:
    CloudFiller() = default;

    void register_observer(std::function<void(float, float, float)> o);

    void add_point(cv::Vec3f v);

    void notify_add(cv::Vec3f v);

    void linear_filling();

    void linear_filling(int size);

    void random_filling(int size, int min, int max);

    void diamond_filling(int nb_subdivisions, double top_radius, double mid_radius, double top_height,
                         double mid_height, cv::Vec3d bot_point);
};

}  // namespace fly

#endif  // INCLUDE_FLY_CLOUDFILLER_HPP_
