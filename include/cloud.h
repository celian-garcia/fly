// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_CLOUD_H_
#define INCLUDE_CLOUD_H_
#include <string>
#include <vector>
#include <opencv2/core.hpp>

namespace fly {

class cloud {
 protected:
    std::vector<cv::Vec3f> container;

 public:
    cloud() = default;
    ~cloud() = default;
    virtual void add_point(double x, double y, double z);
    virtual void add_point(cv::Vec3f p);
    // cv::Vec3f virtual remove_point(int index);
    // cv::Vec3f virtual remove_point(const cv::Vec3f& p);
};

} /* namespace fly */

#endif  // INCLUDE_CLOUD_H_
