cmake_minimum_required(VERSION 3.10)

project(HolomineLib CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(CoreLib
    src/Position.cpp
    src/Signal.cpp
)

target_include_directories(CoreLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(HolomineApp src/main.cpp)

target_link_libraries(HolomineApp PRIVATE CoreLib)

