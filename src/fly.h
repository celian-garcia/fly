//
// Created by Célian Garcia on 20/11/2016.
//

#ifndef FLY_FLY_H
#define FLY_FLY_H
#include <string>
#include <opencv2/core.hpp>
using namespace std;

namespace fly {
    string hello (const string& name);
    vector<cv::Vec3f> create_cloud ();
    void progressive_populate_cloud (vector<cv::Vec3f>& cloud_ref);
} /* namespace fly */


#endif //FLY_FLY_H
