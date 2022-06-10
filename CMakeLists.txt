cmake_minimum_required(VERSION 3.22)
project(PP)

set(CMAKE_CXX_STANDARD 14)

add_executable(PP main.cpp Tree.cpp Utils.cpp Tree.h Utils.h)
# Add MPI Package to Project
find_package(MPI REQUIRED)
find_package( OpenMP REQUIRED)
if(OPENMP_FOUNG)
    message("OPENMP_FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

    # Add libraries for code completion and compiling
target_link_libraries(PP PUBLIC MPI::MPI_CXX)
