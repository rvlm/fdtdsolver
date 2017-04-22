cmake_minimum_required(VERSION 2.8)

add_subdirectory(submodules/rvlm-common)

add_executable(fdtdsolver
    src/Block.cc
    src/Domain.cc
    src/Probe.cc
    src/ResistiveSource.cc
    src/main.cc)

target_include_directories(fdtdsolver
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(fdtdsolver PROPERTIES
    CXX_STANDARD_REQUIRED TRUE
    CXX_STANDARD          11)

target_link_libraries(fdtdsolver rvlm-common)