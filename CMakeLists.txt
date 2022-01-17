cmake_minimum_required(VERSION 3.20)
project(CV)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(CV main.cpp ZxLib/ZxCV.h ZxLib/ZxCV.cpp ZxLib/ZxConst.h ZxLib/ZxImageTool.h ZxLib/ZxImageTool.cpp ZxLib/ZxAPI.h ZxLib/ZxAPI.cpp)
target_link_libraries(CV ${OpenCV_LIBS})