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
            if (depth_point.z > 3.5) continue;

            pc["x"].push_back(depth_point.x);
            pc["y"].push_back(depth_point.y);
            pc["z"].push_back(depth_point.z);
            //std::cout << depth_point.x << " " << depth_point.y << " " << depth_point.z << std::endl;
		}
	}
    return pc;
}

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

void see_octomap::operator()(mrpt::maps::COctoMap & map)
{
	//copy of the mrpt test for octomap
	mrpt::gui::CDisplayWindow3D win("OctoMap demo", 640, 480);

    mrpt::opengl::COctoMapVoxels::Ptr gl_map =
        mrpt::make_aligned_shared<mrpt::opengl::COctoMapVoxels>();

    mrpt::opengl::COpenGLScene::Ptr& scene = win.get3DSceneAndLock();

    {
        mrpt::opengl::CGridPlaneXY::Ptr gl_grid =
            mrpt::make_aligned_shared<mrpt::opengl::CGridPlaneXY>(
                -20, 20, -20, 20, 0, 1);
        gl_grid->setColor_u8(mrpt::utils::TColor(0x50, 0x80, 0x20));
        scene->insert(gl_grid);
    }

    map.renderingOptions.generateGridLines = true;
    map.getAsOctoMapVoxels(*gl_map);

    unsigned int VOXEL_SET_OCCUPIED = 0;
    unsigned int VOXEL_SET_FREESPACE = 1;
    gl_map->showGridLines(false);
    gl_map->showVoxels(VOXEL_SET_OCCUPIED, true);
    gl_map->showVoxels(VOXEL_SET_FREESPACE, true);
    scene->insert(gl_map);

    win.unlockAccess3DScene();

// Go through voxels:
    {
        const octomap::OcTree& om = map.getOctomap<octomap::OcTree>();
        for (auto it = om.begin_leafs(); it != om.end_leafs(); ++it)
        {
            const octomap::point3d pt = it.getCoordinate();
            //std::cout << "pt: " << pt << " -> occupancy = " << it->getOccupancy()
            //     << std::endl;
        }
    }
    std::cout << "Close the window to exit" << std::endl;

    bool update_msg = true;

    while (win.isOpen())
    {
        if (win.keyHit())
        {
            const unsigned int k = win.getPushedKey();

            switch (k)
            {
                case 'g':
                case 'G':
                    gl_map->showGridLines(!gl_map->areGridLinesVisible());
                    break;
                case 'f':
                case 'F':
                    gl_map->showVoxels(
                        VOXEL_SET_FREESPACE,
                        !gl_map->areVoxelsVisible(VOXEL_SET_FREESPACE));
                    break;
                case 'o':
                case 'O':
                    gl_map->showVoxels(
                        VOXEL_SET_OCCUPIED,
                        !gl_map->areVoxelsVisible(VOXEL_SET_OCCUPIED));
                    break;
                case 'l':
                case 'L':
                    gl_map->enableLights(!gl_map->areLightsEnabled());
                    break;
            };
            update_msg = true;
        }

        if (update_msg)
        {
            update_msg = false;

            win.addTextMessage(
                5, 5,
                mrpt::format(
                    "Commands: 'g' (grids=%s) | 'f' (freespace=%s) | 'o' "
                    "(occupied=%s) | 'l' (lights=%s)",
                    gl_map->areGridLinesVisible() ? "YES" : "NO",
                    gl_map->areVoxelsVisible(VOXEL_SET_FREESPACE) ? "YES"
                                                                  : "NO",
                    gl_map->areVoxelsVisible(VOXEL_SET_OCCUPIED) ? "YES" : "NO",
                    gl_map->areLightsEnabled() ? "YES" : "NO"),
                mrpt::utils::TColorf(1, 1, 1), "sans", 15);

            win.repaint();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    };
}

//mrpt::maps::CPointsMap operator()(std::map<std::string,
//                                  std::vector<float>> points)
//{
//    mrpt::maps::CPointsMap point_map;
//    point_map.setAllPoints(points["x"],
//                           points["y"],
//                           points["z"]);
//
//    return point_map;
//}
