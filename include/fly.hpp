// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_FLY_HPP_
#define INCLUDE_FLY_HPP_
#include <string>
#include <iostream>
#include <opencv2/core.hpp>
#include "./cloud.hpp"

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
    class No {};
    class Yes {
        No no[3];
    };
    static Yes Test(B*);  // not defined
    static No Test(...);  // not defined

    static void Constraints(D* p) { B* pb = p; pb = p; }

 public:
    enum { Is = sizeof(Test(static_cast<D*>(0))) == sizeof(Yes) };
    IsDerivedFrom() { void(*p)(D*) = Constraints; }
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
    explicit Hello(const std::string& name) : mName(name) {}
    std::string get_name();
    void run();
};

template <class T>
class CloudPopulate : public FlyRunnable, private IsDerivedFrom<T, cloud> {
 protected:
    T cloud;

 public:
    CloudPopulate() = default;
    T& get_cloud_reference() {
        return this->cloud;
    }
    void run() {
        for (int i = 0; i < 10; ++i) {
            this->cloud.add_point(cv::Vec3f(i, i, i));
        }
    }
};

class Recontruction3D : public FlyRunnable {
 public:
    Recontruction3D() = default;
    ~Recontruction3D() = default;
};

} /* namespace fly */


#endif  // INCLUDE_FLY_HPP_
