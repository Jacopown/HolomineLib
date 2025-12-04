# The minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the name of the project
project(HolomineLib CXX)

# Set the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source files that make up the library/module
set(MODULE_SOURCES
    Position.cpp
    Signal.cpp
)

# 1. Create a library target (optional, but good practice for modules)
# This compiles SimpleMath.cpp into a library file 
# (e.g., SimpleMath.lib or libSimpleMath.a)
# add_library(SimpleMathLib STATIC ${MODULE_SOURCES})

# 2. Define the executable target
# This compiles main.cpp
add_executable(HolomineLib main.cpp Position.cpp Signal.cpp)

# 3. Link the executable to the library
# This tells the linker to connect the function calls in main.o 
# with the function definitions in SimpleMathLib.o
# target_link_libraries(simple_app 
#     SimpleMathLib
# )

