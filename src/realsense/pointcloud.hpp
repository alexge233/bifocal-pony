#ifndef POINTCLOUD_HPP
#define POINTCLOUD_HPP

#include "includes.ihh"
#include "parameters.hpp"

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

/**
 * @brief create mrpt::obs::CObservation3DRangeScan 
 * @struct create_3Dobs
 * @date 13.12.2017
 * @version 0.1.0
 */
struct create_3Dobs
{
    ///@return CObservation3DRangeScan
    mrpt::obs::CObservation3DRangeScan operator()(std::map<std::string,
                                                           std::vector<float>> points);
};

/**
 *
 */
struct see_octomap
{
    void operator()(mrpt::maps::COctoMap & map);
};

#endif
