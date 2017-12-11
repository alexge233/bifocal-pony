cmake_minimum_required(VERSION 2.8)
project(bifocal_pony)

#TODO: set base path
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(REALSENSE_LIBRARIES ${REALSENSE_LIBRARIES} realsense_image
                                               realsense_projection
                                               realsense)
add_executable(${PROJECT_NAME} src/main.cpp
                               src/realsense/device.cpp
                               src/realsense/pointcloud.cpp
              )

target_link_libraries(${PROJECT_NAME} ${REALSENSE_LIBRARIES})
