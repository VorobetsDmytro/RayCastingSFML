cmake_minimum_required(VERSION 3.20)
project(raycast3d)

file(GLOB_RECURSE CPPFILES "src/*.cpp")
file(GLOB_RECURSE LIBFILES "lib/*.a")

add_executable(raycast3d ${CPPFILES})
target_compile_features(raycast3d PRIVATE cxx_std_17)
target_include_directories(raycast3d PRIVATE include)
target_link_libraries(raycast3d PRIVATE ${LIBFILES})