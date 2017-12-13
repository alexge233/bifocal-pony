#include "observation.hpp"

mrpt::obs::CObservation3DRangeScan create_3Dobs::operator()(std::map<std::string,
                                                                      std::vector<float>> points)
{
    mrpt::obs::CObservation3DRangeScan obs;
    obs.points3D_x = points["x"]; 
    obs.points3D_y = points["y"]; 
    obs.points3D_z = points["z"]; 
    obs.hasPoints3D = true;

    return obs;
}
