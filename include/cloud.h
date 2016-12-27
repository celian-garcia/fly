// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_CLOUD_H_
#define INCLUDE_CLOUD_H_
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>

namespace fly {

class cloud {
 protected:
    std::vector<cv::Vec3f> container;

 public:
    friend std::ostream& operator<<(std::ostream&, const cloud&);
    friend bool operator==(const cloud& lhc, const cloud& rhc);
    virtual void add_point(double x, double y, double z);
    virtual void add_point(int x, int y, int z);
    virtual void add_point(cv::Vec3f p);
    // cv::Vec3f virtual remove_point(int index);
    // cv::Vec3f virtual remove_point(const cv::Vec3f& p);
};

} /* namespace fly */

#endif  // INCLUDE_CLOUD_H_
