#include "parameters.hpp"

bool frame::check_size()
{
    if (depth_img.rows > 0 && 
        depth_img.cols > 0) {
        if (color_img.rows > 0 && 
            color_img.cols > 0) {
            return true;
        }
    }
    return false;
}
