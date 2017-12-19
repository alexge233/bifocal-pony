#ifndef SLAM_HPP
#define SLAM_HPP

#include "includes.ihh"
#include "../realsense/parameters.hpp" //TODO:create a base path in cmake to avoid relative path

/**
 * @brief orb slam
 * @class slam
 * @date 19.12.2017
 * @version 0.1.0
 */
class slam
{
public:
    ///@brief constructor
    slam(std::string vocabulary_file,
         std::string camera_settings);

    ///@brief do slam
    void do_slam(frame images);

private:
    ORB_SLAM2::System slam_system__;
    std::chrono::steady_clock::time_point start__;
};

#endif
