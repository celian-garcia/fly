// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_CLOUD_HPP_
#define INCLUDE_CLOUD_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace fly {

class CloudContainer {
 protected:
    std::vector<cv::Vec3f> container;

 public:
    CloudContainer() = default;

    friend std::ostream &operator<<(std::ostream &, const CloudContainer &);

    friend bool operator==(const CloudContainer &lhc, const CloudContainer &rhc);

    virtual void add_point(float x, float y, float z);

    virtual void add_point(int x, int y, int z);

    virtual void add_point(cv::Vec3f v);
};

} /* namespace fly */

#endif  // INCLUDE_CLOUD_HPP_
