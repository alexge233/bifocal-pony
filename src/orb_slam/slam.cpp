#include "slam.hpp"

slam::slam(std::string vocabulary_file,
           std::string camera_settings)
:slam_system__(vocabulary_file, 
               camera_settings, 
               ORB_SLAM2::System::RGBD, 
               true)
{}

void slam::do_slam(frame images)
{
    if (images.check_size()) {
        auto now = std::chrono::steady_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>
                                                (now - start__).count(); 
        slam_system__.TrackRGBD(images.color_img,
                                images.depth_img,
                                timestamp); 
    }
    else {
        std::cout << "Error size image" << std::endl;
    }
}
