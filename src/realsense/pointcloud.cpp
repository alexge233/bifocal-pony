#include "pointcloud.hpp"

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

            //pc["x"].push_back(depth_point.x);
            //pc["y"].push_back(depth_point.y);
            //pc["z"].push_back(depth_point.z);
            std::cout << depth_point.x << " " << depth_point.y << " " << depth_point.z << std::endl;
		}
	}
    return pc;
}
