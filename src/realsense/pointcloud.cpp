#include "pointcloud.hpp"

Eigen::Vector3f change_coordinates::operator()(rs::float3 point)
{
	Eigen::Vector3f new_point(point.x, point.y, point.z);
    Eigen::Matrix3f Rx;
    auto angle = DEGREES2RADIANS(90);
    ////Matrix of rotation in x (due to realsense axis) 
    Rx << 1, 0, 0,
          0, cos(angle), sin(angle),
          0, -sin(angle), cos(angle);
    return Rx * new_point;
}

std::map<std::string, 
         std::vector<float>> build_pointcloud::operator()(frame_param fp,
                                                          const uint16_t * d_image)
{
    std::map<std::string, std::vector<float>> pc;
	for(int dy = 0; dy < fp.depth_intrin.height; dy++)
	{
		for(int dx = 0; dx < fp.depth_intrin.width; dx++)
		{
			// Retrieve the 16-bit depth value and map it into a depth in meters
			uint16_t depth_value = d_image[dy * fp.depth_intrin.width + dx];
			float depth_in_meters = depth_value * fp.scale;

			// Skip over pixels with a depth value of zero, which is used to indicate no data
			if(depth_value == 0) continue;

			// Map from pixel coordinates in the depth image to pixel coordinates in the color image
			rs::float2 depth_pixel = {(float)dx, (float)dy};
			rs::float3 depth_point = fp.depth_intrin.deproject(depth_pixel, depth_in_meters);

			if(depth_point.z > 3.5) continue;
            auto transform = change_coordinates()(depth_point);
            pc["x"].push_back(transform(0));
            pc["y"].push_back(transform(1));
            pc["z"].push_back(transform(2));

            //pc["x"].push_back(depth_point.x);
            //pc["y"].push_back(depth_point.y);
            //pc["z"].push_back(depth_point.z);
		}
	}
    return pc;
} 
