#include "observation.hpp"

std::shared_ptr<mrpt::obs::CObservation3DRangeScan> create_3Dobs::operator()(std::map<std::string,
                                                                             std::vector<float>> points)
{
    auto obs = std::make_shared<mrpt::obs::CObservation3DRangeScan>();
    obs->points3D_x = points["x"]; 
    obs->points3D_y = points["y"]; 
    obs->points3D_z = points["z"]; 
    obs->hasPoints3D = true;

    return obs;
}
