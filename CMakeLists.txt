cmake_minimum_required(VERSION 2.8)
project(bifocal_pony)

find_library(LIBREALSENSE realsense)
if(!${LIBREALSENSE})
    message(FATAL "failed to find librealsense")
endif()
find_package(OpenCV REQUIRED)

#ORB SLAM 2
find_package(Eigen3 REQUIRED)
find_package(Pangolin REQUIRED)
find_library(ORB_SLAM2 ORB_SLAM2 PATHS "/home/maria/projects/ORB_SLAM2/lib/")
if(!${ORB_SLAM2})
    message(FATAL "failed to find ORB_SLAM2")
endif()

include_directories(/usr/local/include
                    /home/maria/projects/ORB_SLAM2/include #TODO: create a cmake for orb_slam
                    /home/maria/projects/ORB_SLAM2/
                    ${OpenCV_INCLUDE_DIRS}
                    ${EIGEN3_INCLUDE_DIR}
                    ${Pangolin_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
add_executable(${PROJECT_NAME} src/main.cpp
                               src/realsense/device.cpp
                               src/realsense/pointcloud.cpp
                               src/orb_slam/slam.cpp
              )

target_link_libraries(${PROJECT_NAME} ${LIBREALSENSE}
                                      ${ORB_SLAM2}
                                      ${OpenCV_LIBS}
                                      ${EIGEN3_LIBS}
                                      ${Pangolin_LIBRARIES})
