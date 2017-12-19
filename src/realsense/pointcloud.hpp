#ifndef POINTCLOUD_HPP
#define POINTCLOUD_HPP

#include "includes.ihh"
#include "parameters.hpp"

#define DEGREES2RADIANS(x) ((x)*M_PI/180.)

/**
 * @brief rotate 90 degrees in X axis 
 * @struct change_coordinates
 * @date 14.12.2017
 * @version 0.1.0
 */
struct change_coordinates
{
    Eigen::Vector3f operator()(rs::float3 point);    
};


/**
 * @brief calculate pointcloud
 * @struct build_pointcloud
 * @date 11.12.2017
 * @version 0.1.0
 */
struct build_pointcloud
{
    ///@return a map with vectors of floats
    /// which contains the coordinates x,y,z
    /// of every point
    std::map<std::string, 
             std::vector<float>> operator()(frame_param fp,
                                            const uint16_t * d_image);
};

#endif
