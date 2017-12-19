#include "realsense/device.hpp"
#include "slam/observation.hpp"
#include "slam/icp.hpp"
#include <iostream>
#include <chrono>

int main()
{
    irs_device camera;
    camera.start();

    icp builder("icp_default.ini"); //TODO:Accept argument 
    for (auto i = 0; i < 50; i++) {
        auto start_time__ = std::chrono::system_clock::now();
        auto obs = create_3Dobs()(camera.read_frames());
        if (obs->getScanSize() > 10000) {
            auto pose = builder.insert_observation(obs);     
            auto time_finish = std::chrono::system_clock::now();
            std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>
                                        (time_finish - start_time__).count() << std::endl;
            std::cout << pose.x() << " " << pose.y() << " " <<
                         pose.z() << " " << pose.yaw() << std::endl;
        }
    }
    builder.save();
    camera.stop();
    return 0;
}
