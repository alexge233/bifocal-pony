cmake_minimum_required(VERSION 2.8)
project(bifocal_pony)

#TODO: set base path
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

find_library(REALSENSE_LIB NAMES realsense)
set(REALSENSE_INCLUDE_DIRS "/usr/local/include/librealsense")
find_package(OpenCV REQUIRED)
find_package(octomap REQUIRED)
find_package(OpenGL REQUIRED)
find_package(MRPT REQUIRED COMPONENTS base slam maps gui)
include_directories(${OCTOMAP_INCLUDE_DIRS}
                    ${OpenCV_INCLUDE_DIRS}
                    ${OPENGL_INCLUDE_DIRS}
                    ${MRPT_INCLUDE_DIRS}
                    ${REALSENSE_INCLUDE_DIRS}
                    )

add_executable(${PROJECT_NAME} src/main.cpp
                               src/realsense/device.cpp
                               src/realsense/pointcloud.cpp
              )

target_link_libraries(${PROJECT_NAME} ${REALSENSE_LIB}
                                      ${OCTOMAP_LIBRARIES} 
                                      ${OpenCV_LIBS}
                                      ${OPENGL_LIBRARY}
                                      ${MRPT_LIBS}
                                      )
