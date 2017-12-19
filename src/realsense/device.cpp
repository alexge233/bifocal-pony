#include "device.hpp"

irs_device::irs_device(const unsigned int number_dev)
{
    context__ = std::make_shared<rs::context>();
    check_device(context__, number_dev);
    device__ = context__->get_device(number_dev);
}

void irs_device::check_device(std::shared_ptr<rs::context> cont,
                             unsigned int dev_number)
{
    if (cont->get_device_count() == 0 ||
        cont->get_device_count() < (dev_number + 1)) {
        throw std::runtime_error("No intelrealsense device detected");
    }
}

void irs_device::start()
{
    if (!device__) {
        throw std::runtime_error("Impossible to start device");
    }
    camera_param color__ = {640, 480, 30, 3, rs::format::rgb8};
    //camera_param depth = {628, 468, 60, 2, rs::format::z16};
    camera_param depth__ = {640, 480, 30, 2, rs::format::z16};
    device__->enable_stream(rs::stream::color, color__.width, color__.height, color__.format, color__.fps);
    device__->enable_stream(rs::stream::depth, depth__.width, depth__.height, depth__.format, depth__.fps);
    device__->start();    
}

void irs_device::stop()
{
    //device__->stop(rs::source::all_sources);
    context__.reset();
}

frame irs_device::read_frame()
{
    device__->wait_for_frames();  
    //Read frames from camera
    const uint16_t * depth_image = (const uint16_t *)device__->get_frame_data(rs::stream::depth);
    const uint8_t * color_image = (const uint8_t *)device__->get_frame_data(rs::stream::color);

    frame images;
    images.color_img = images.raw_to_mat(color_image, color__, CV_8UC3);
    images.depth_img = images.raw_to_mat(depth_image, depth__, CV_8UC1);

    return images;
}

std::map<std::string,
         std::vector<float>> irs_device::obtain_pointcloud()
{
    device__->wait_for_frames();  
    //Read frames from camera
    const uint16_t * depth_image = (const uint16_t *)device__->get_frame_data(rs::stream::depth);
    const uint8_t * color_image = (const uint8_t *)device__->get_frame_data(rs::stream::color);

    //Read camera parameters
    rs_param__.depth_intrin = device__->get_stream_intrinsics(rs::stream::depth);
    rs_param__.depth_to_color = device__->get_extrinsics(rs::stream::depth, rs::stream::color);
    rs_param__.color_intrin = device__->get_stream_intrinsics(rs::stream::color);
    rs_param__.scale = device__->get_depth_scale();
	return build_pointcloud()(rs_param__, depth_image);
}
