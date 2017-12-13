#ifndef ICP_HPP
#define ICP_HPP

#include "includes.ihh"

/**
 * @brief create a map of the environment
 * @class icp
 * @date 13.12.2017
 * @version 0.1.0
 */
class icp
{
public:

	///@brief constructor
	icp(std::string config_path);

    ///@brief observation
    template <class observation_type>
    mrpt::poses::CPose3D insert_observation
							(observation_type observation);

    ///@brief save octomap
    void save();

private: 
    //ICP builder
    mrpt::slam::CMetricMapBuilderICP builder__;
	//Config file
	mrpt::utils::CConfigFile config__;
};


/*
 * Implementation
 */
template<class observation_type>
mrpt::poses::CPose3D icp::insert_observation
							(observation_type observation)
{
    builder__.processObservation(observation);
    return builder__.getCurrentPoseEstimation()->getMeanVal();
}

#endif
