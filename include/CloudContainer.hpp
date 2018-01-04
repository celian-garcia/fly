// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_CLOUDCONTAINER_HPP_
#define INCLUDE_CLOUDCONTAINER_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace fly {

class CloudContainer : public std::vector<cv::Vec3f> {

 public:

    friend std::ostream &operator<<(std::ostream &, const CloudContainer &);

    virtual void add_point(cv::Vec3f v);
};

}  // namespace fly

#endif  // INCLUDE_CLOUDCONTAINER_HPP_
