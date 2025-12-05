# The minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the name of the project
project(HolomineLib CXX)

# Set the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the source files that make up the library/module
add_library(CoreLib
    src/Position.cpp
    src/Signal.cpp
)

target_include_directories(CoreLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# 1. Create a library target (optional, but good practice for modules)
# This compiles SimpleMath.cpp into a library file 
# (e.g., SimpleMath.lib or libSimpleMath.a)
# add_library(SimpleMathLib STATIC ${MODULE_SOURCES})

# 2. Define the executable target
# This compiles main.cpp
add_executable(HolomineApp src/main.cpp)

target_link_libraries(HolomineApp PRIVATE CoreLib)

# 3. Link the executable to the library
# This tells the linker to connect the function calls in main.o 
# with the function definitions in SimpleMathLib.o
# target_link_libraries(simple_app 
#     SimpleMathLib
# )

