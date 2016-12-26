// Copyright 2016 <Célian Garcia>

#include "./fly.h"
int main(int argc, char* argv[]) {
    fly::CloudPopulate cp = fly::CloudPopulate();
    cp.run();

    fly::Hello h = fly::Hello("Célian");
    h.run();
    return 0;
}
