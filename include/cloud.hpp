// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_CLOUD_HPP_
#define INCLUDE_CLOUD_HPP_
#include <string>
#include <unordered_map>
#include <iostream>
#include <opencv2/core.hpp>

namespace fly {

class cloud {
 private:
    /// Functor used to perform a hash on cv::Vec3f object
    struct hashFunc {
        size_t operator()(const cv::Vec3f &v) const {
            size_t h1 = std::hash<double>()(v[0]);
            size_t h2 = std::hash<double>()(v[1]);
            size_t h3 = std::hash<double>()(v[2]);
            return (h1 ^ (h2 << 1)) ^ h3;
        }
    };

    /// Functor used to perform a equality on cv::Vec3f object
    struct equalsFunc {
        bool operator()(const cv::Vec3f& lhs, const cv::Vec3f& rhs) const {
            return lhs == rhs;
        }
    };

 protected:
    std::unordered_map<cv::Vec3f, std::string, hashFunc, equalsFunc> map;

 public:
    friend std::ostream& operator<<(std::ostream&, const cloud&);
    friend bool operator==(const cloud& lhc, const cloud& rhc);
    virtual void add_point(double x, double y, double z);
    virtual void add_point(int x, int y, int z);
    virtual void add_point(cv::Vec3f v);
    cv::Vec3f virtual remove_point(const size_t& hashcode);
    cv::Vec3f virtual remove_point(const cv::Vec3f& v);
};

} /* namespace fly */

#endif  // INCLUDE_CLOUD_HPP_
