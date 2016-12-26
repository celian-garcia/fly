// Copyright 2016 <Célian Garcia>

#ifndef INCLUDE_FLY_H_
#define INCLUDE_FLY_H_
#include <string>
#include <opencv2/core.hpp>
#include "./cloud.h"

namespace fly {

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

class CloudPopulate : public FlyRunnable {
 protected:
    cloud cl_result;

 public:
    CloudPopulate();
    void run();
};

class Recontruction3D : public FlyRunnable {
 public:
    Recontruction3D() = default;
    ~Recontruction3D() = default;
};

} /* namespace fly */


#endif  // INCLUDE_FLY_H_
