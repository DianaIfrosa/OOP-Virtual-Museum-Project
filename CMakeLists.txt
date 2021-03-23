cmake_minimum_required(VERSION 3.17)

project(Laborator-POO)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "D:\\opencv-build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(Laborator-POO main.cpp sala.cpp muzeu.cpp client.cpp sala.h muzeu.h client.h  cvui.h)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(Laborator-POO ${OpenCV_LIBS})