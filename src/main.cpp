#include "realsense/device.hpp"
#include "orb_slam/slam.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    irs_device camera;
    camera.start();
    slam orb_slam(argv[1], argv[2]);

    for (auto i = 0; i < 120; i++) {
        orb_slam.do_slam(camera.read_frame());
    }
    camera.stop();
    return 0;
}
