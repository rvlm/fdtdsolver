cmake_minimum_required(VERSION 2.8)
project(rfdtd)

add_subdirectory(submodules/rvlm-common)

add_executable(fdtdsolver
    include/rvlm/fdtd/BasicFdtdBlock.hh
    include/rvlm/fdtd/Block.hh
    include/rvlm/fdtd/Common.hh
    include/rvlm/fdtd/Domain.hh
    include/rvlm/fdtd/Field.hh
    include/rvlm/fdtd/Lattice.hh
    include/rvlm/fdtd/Medium.hh
    include/rvlm/fdtd/MemoryMedium.hh
    include/rvlm/fdtd/Probe.hh
    include/rvlm/fdtd/ProbeElement.hh
    include/rvlm/fdtd/ResistiveSource.hh
    include/rvlm/fdtd/Source.hh
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
