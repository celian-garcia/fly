// Copyright 2016 <Célian Garcia>

#include "CloudContainer.hpp"

namespace fly {

std::ostream&
operator<<(std::ostream& os, const CloudContainer& cl) {
    for (auto& v : cl.container) {
        os << '(' << v[0] << ", " << v[1] << ", " << v[2] << ")\n";
    }
    return os;
}

bool
operator==(const CloudContainer& lhc, const CloudContainer& rhc) {
    return lhc.container == rhc.container;
}

void
CloudContainer::add_point(float x, float y, float z) {
    this->add_point(cv::Vec3f(x, y, z));
}

void
CloudContainer::add_point(int x, int y, int z) {
    this->add_point(cv::Vec3f(x, y, z));
}

void
CloudContainer::add_point(cv::Vec3f v) {
    this->container.push_back(v);
}

// cv::Vec3f virtual remove_point(int index);
// cv::Vec3f virtual remove_point(const cv::Vec3f& p);

} /* namespace fly */
