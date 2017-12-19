#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include "includes.ihh"

/**
 * @brief basic parameters of the camera
 * @struct camera_param
 * @date 8.12.2017
 * @version 0.1.0
 */
struct camera_param
{
    int width;
    int height;
    int fps;
    int pixel_size;
    rs::format format;
};

/**
 * @brief extrinsic, intrinsic & frames
 * @struct frame_param
 * @date 11.12.2017
 * @version 0.1.0
 */
struct frame_param
{
    rs::intrinsics depth_intrin;
    rs::extrinsics depth_to_color;
    rs::intrinsics color_intrin;
    float scale;
};

/**
 * @brief color and depth images
 * @struct frame
 * @date 19.12.2017
 * @version 0.1.0
 */
struct frame
{
    cv::Mat color_img;
    cv::Mat depth_img;

    template <class data_type>
    cv::Mat raw_to_mat(data_type image,
                       camera_param param,
                       int type_mat);
};

/*
 * Implementation
 */
template <class data_type>
cv::Mat frame::raw_to_mat(data_type image,
                          camera_param param,
                          int type_mat)
{
    return cv::Mat(cv::Size(param.width, param.height), 
                   type_mat,
                   (void*)image,
                   cv::Mat::AUTO_STEP);
}

#endif
