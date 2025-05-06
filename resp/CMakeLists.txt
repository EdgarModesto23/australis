add_library(resp STATIC resp.cc resp.hh types.cc types.hh)

target_include_directories(resp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
