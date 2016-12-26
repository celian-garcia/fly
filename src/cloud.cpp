// Copyright 2016 <Célian Garcia>

#include "./cloud.h"

namespace fly {

void
cloud::add_point(double x, double y, double z) {
    this->add_point(cv::Vec3f(x, y, z));
}

void
cloud::add_point(cv::Vec3f v) {
    this->container.push_back(v);
}
// cv::Vec3f virtual remove_point(int index);
// cv::Vec3f virtual remove_point(const cv::Vec3f& p);

} /* namespace fly */
