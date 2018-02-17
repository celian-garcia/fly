// Copyright 2018 <Célian Garcia>

#include <functional>
#include <fly/CloudFiller.hpp>

namespace fly {

void CloudFiller::register_observer(std::function<void(float, float, float)> o) {
    this->observers.push_back(o);
}

void CloudFiller::add_point(cv::Vec3f v) {
    this->points.push_back(v);
    notify_add(v);
}

void CloudFiller::notify_add(cv::Vec3f v) {
    for (auto observer : this->observers) {
        observer(v[0], v[1], v[2]);
    }
}

void CloudFiller::linear_filling() {
    linear_filling(10);
}

void CloudFiller::linear_filling(int size) {
    for (float i = 0; i < size; ++i) {
        this->add_point({i, i, i});
    }
}

void CloudFiller::random_filling(int size, int min, int max) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 generator(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> distrib(min, max);  // guaranteed unbiased

    for (int i = 0; i < size; ++i) {
        float random_x = distrib(generator);
        float random_y = distrib(generator);
        float random_z = distrib(generator);
        this->add_point({random_x, random_y, random_z});
    }
}

void CloudFiller::diamond_filling(int nb_subdivisions, double top_radius, double mid_radius, double top_height,
                                  double mid_height, cv::Vec3d bot_point) {
    // Add the bottom point
    this->add_point(bot_point);

    for (int curr_subdiv = 1; curr_subdiv <= nb_subdivisions; curr_subdiv++) {
        // Add the top circle point
        cv::Vec2d top_pt_pol(top_radius, (360 * curr_subdiv) / nb_subdivisions);
        cv::Vec3d top_pt_cart(top_pt_pol[0] * cos(top_pt_pol[1]), top_pt_pol[0] * sin(top_pt_pol[1]), top_height);
        this->add_point(top_pt_cart + bot_point);

        // Add the middle circle point
        cv::Vec2d mid_pt_pol(mid_radius, (360 * curr_subdiv) / nb_subdivisions);
        cv::Vec3d mid_pt_cart(mid_pt_pol[0] * cos(mid_pt_pol[1]), mid_pt_pol[0] * sin(mid_pt_pol[1]), mid_height);
        this->add_point(mid_pt_cart + bot_point);
    }
}

}  // namespace fly
