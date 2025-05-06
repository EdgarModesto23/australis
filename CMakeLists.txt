cmake_minimum_required(VERSION 4.0.1)
project(australis)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

FetchContent_MakeAvailable(googletest)

# Include the 'command' directory for header files
include_directories(${PROJECT_SOURCE_DIR}/command)

# Include the 'command' directory for header files
include_directories(${PROJECT_SOURCE_DIR}/protocol)

find_package(Seastar REQUIRED)

find_package(Boost REQUIRED)

# Add an executable target
add_executable(australis main.cc)

target_include_directories(australis PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(australis  Seastar::seastar)

enable_testing()

include(GoogleTest)

add_subdirectory(resp)
add_subdirectory(tests)
