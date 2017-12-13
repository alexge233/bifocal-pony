#include "realsense/device.hpp"
#include <iostream>

int main()
{
    irs_device camera;
    camera.start();

    for (auto i = 0; i < 25; i++) {
        camera.read_frames();
    }
    camera.stop();
    return 0;
}
