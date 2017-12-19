#ifndef OBSERVATION_HPP
#define OBSERVATION_HPP

#include "includes.ihh"

/**
 * @brief create mrpt::obs::CObservation3DRangeScan 
 * @struct create_3Dobs
 * @date 13.12.2017
 * @version 0.1.0
 */
struct create_3Dobs
{
    ///@return CObservation3DRangeScan
    std::shared_ptr<mrpt::obs::CObservation3DRangeScan> operator()(std::map<std::string,
                                                                   std::vector<float>> points);
};

#endif
