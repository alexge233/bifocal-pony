#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "includes.ihh"
#include "parameters.hpp"
#include "pointcloud.hpp"

/**
 * @brief detect and connect an intelrealsense camera zr300
 * @class irs_device
 * @date 7.12.2017
 * @version 0.1.0
 */
class irs_device
{
public:
    ///@brief constructor
    irs_device(const unsigned int number_dev = 0);

    ///@brief start device
    void start();

    ///@brief stop device
    void stop();

    ///@brief read data from camera
    void read_frames();

private:
    //@brief detect device
    void check_device(std::shared_ptr<rs::context> cont,
                      unsigned int number_dev);

    rs::device *device__;
    std::shared_ptr<rs::context> context__;
    frame_param rs_param__;
};

#endif
