// Copyright 2016 <Célian Garcia>

#include "./fly.h"

namespace fly {
    void
    Hello::run() {
        std::cout << this->mName << std::endl;
    }

    std::string
    Hello::get_name() {
        return this->mName;
    }


    // string
    // hello(const string& name) {
    //     string result("salut " + name);
    //     return result;
    // }
    // vector<Vec3f>
    // create_cloud() {
    //     vector<Vec3f> result = {
    //         Vec3f(2.0, 2.0, 2.0),
    //         Vec3f(2.0, 2.0, 2.0),
    //         Vec3f(2.0, 2.0, 2.0)
    //     };
    //     return result;
    // }
    // void
    // progressive_populate_cloud(vector<cv::Vec3f>& cloud_ref) {
    //     for (int i = 0; i < 100; ++i) {
    //         Sleep(1000);
    //         cloud_ref.push_back(Vec3f(i, i, i));
    //     }
    // }

} /* namespace fly */
