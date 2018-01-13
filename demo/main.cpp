// Copyright 2016 <Célian Garcia>

#include "./fly.hpp"
int main(int argc, char* argv[]) {
    fly::CloudFiller<fly::CloudContainer> cp;
    cp.linear_filling();

    return 0;
}
