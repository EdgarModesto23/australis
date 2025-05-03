cmake_minimum_required(VERSION 4.0.1)
project(australis)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Clang as the C and C++ compilers
set(CMAKE_CXX_COMPILER "clang++")

# Enable compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include the 'command' directory for header files
include_directories(${PROJECT_SOURCE_DIR}/command)

# Include the 'command' directory for header files
include_directories(${PROJECT_SOURCE_DIR}/protocol)

find_package(Seastar REQUIRED)

# Add an executable target
add_executable(australis main.cc)

target_link_libraries(australis  Seastar::seastar)
