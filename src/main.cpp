#include "realsense/device.hpp"
#include "slam/observation.hpp"
#include "slam/icp.hpp"
#include <iostream>

int main()
{
    irs_device camera;
    camera.start();

    icp builder("icp_default.ini"); //TODO:Accept argument 
    for (auto i = 0; i < 120; i++) {
        auto pc = camera.read_frames();
        auto obs = create_3Dobs()(pc);
        if (obs.getScanSize() > 10000) {
            builder.insertObservation(obs);     
        }

    }
    camera.stop();
    return 0;
}
