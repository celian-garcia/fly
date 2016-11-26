//
// Created by Célian Garcia on 20/11/2016.
//

#include "fly.h"

using namespace std;
using namespace cv;

namespace fly {
    string hello (const string& name) {
        string result("salut " + name);
        return result;
    }
    vector<Vec3f> create_cloud () {
        vector<Vec3f> result = {
            Vec3f(2.0, 2.0, 2.0),
            Vec3f(2.0, 2.0, 2.0),
            Vec3f(2.0, 2.0, 2.0)
        };
        return result;
    }
} /* namespace fly */
