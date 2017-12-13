cmake_minimum_required(VERSION 2.8)
project(bifocal_pony)

find_library(LIBREALSENSE realsense)
if(!${LIBREALSENSE})
    message(FATAL "failed to find librealsense")
endif()
include_directories(/usr/local/include)

find_package(MRPT REQUIRED COMPONENTS base slam maps)
include_directories(${MRPT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
add_executable(${PROJECT_NAME} src/main.cpp
                               src/realsense/device.cpp
                               src/realsense/pointcloud.cpp
                               src/slam/icp.cpp
                               src/slam/observation.cpp
              )

target_link_libraries(${PROJECT_NAME} ${LIBREALSENSE}
                                      ${MRPT_LIBS})
