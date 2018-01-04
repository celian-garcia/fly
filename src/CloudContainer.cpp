// Copyright 2016 <Célian Garcia>

#include "CloudContainer.hpp"

namespace fly {

std::ostream &
operator<<(std::ostream &os, const CloudContainer &cl) {
    for (auto &v : cl) {
        os << '(' << v[0] << ", " << v[1] << ", " << v[2] << ")\n";
    }
    return os;
}

void
CloudContainer::add_point(cv::Vec3f v) {
    this->push_back(v);
}

}  // namespace fly
