// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_FLY_HPP_
#define INCLUDE_FLY_HPP_

#include <string>
#include <random>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "CloudContainer.hpp"

namespace fly {

//////////////////////////////////////////////////////////////////
// Code found here:
// http://www.gotw.ca/publications/mxc++-item-4.htm
//
// Permits to check if a template type derive from a given class.
// Example 4-3(c): An IsDerivedFrom constraints base
// with testable value
template<typename D, typename B>
class IsDerivedFrom {
    class No {
    };

    class Yes {
        No no[3];
    };

    static Yes Test(B *);  // not defined
    static No Test(...);  // not defined

    static void Constraints(D *p) {
        B *pb = p;
        pb = p;
    }

 public:
    enum {
        Is = sizeof(Test(static_cast<D *>(0))) == sizeof(Yes)
    };

    IsDerivedFrom() { void (*p)(D *) = Constraints; }
};
// --> end ///////////////////////////////////////////////////////

class FlyRunnable {
    virtual void run() = 0;
};

class Hello : public FlyRunnable {
 protected:
    std::string mName;
 public:
    Hello() : mName("John Doe") {}

    explicit Hello(const std::string &name) : mName(name) {}

    std::string get_name();

    void run();
};

template<class T>
class CloudFiller : private IsDerivedFrom<T, std::vector<cv::Vec3f>> {
 protected:
    T *cloud;

 public:
    CloudFiller() = default;

    explicit CloudFiller(T *cloud) : cloud(cloud) {}

    void linear_filling() {
        linear_filling(10);
    }

    void linear_filling(int size) {
        for (int i = 0; i < size; ++i) {
            this->cloud->add_point(cv::Vec3f(i, i, i));
        }
    }

    void random_filling(int size, int min, int max) {
        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937 generator(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> distrib(min, max);  // guaranteed unbiased

        for (int i = 0; i < size; ++i) {
            auto random_x = distrib(generator);
            auto random_y = distrib(generator);
            auto random_z = distrib(generator);
            this->cloud->add_point({random_x, random_y, random_z});
        }
    }
};

class Recontruction3D : public FlyRunnable {
 public:
    Recontruction3D() = default;

    ~Recontruction3D() = default;
};

}  // namespace fly

#endif  // INCLUDE_FLY_HPP_
