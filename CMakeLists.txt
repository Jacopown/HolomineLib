cmake_minimum_required(VERSION 3.10)

project(HolomineLib CXX)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(CoreLib
  src/PositionLog.cpp
  src/SignalLog.cpp
  src/Hologram.cpp
)

target_include_directories(CoreLib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(CoreLib PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(CoreLib PRIVATE opencv_core opencv_imgproc opencv_imgcodecs)

add_executable(HolomineApp src/main.cpp)

target_link_libraries(HolomineApp PRIVATE CoreLib)

