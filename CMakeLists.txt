cmake_minimum_required(VERSION 3.12)

project(mpi_io_tutorial LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

find_package(MPI REQUIRED)
if (MPI_COMPILER_FLAGS)
  add_compile_options(${MPI_COMPILER_FLAGS})
endif()
include_directories(${MPI_INCLUDE_PATH})

option(USE_C "C/C++" ON)

set(SOURCE_NAME "src")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)

if (USE_C)
    add_library(tutorial_utils STATIC ${src_SOURCES} C/reading_solution.cpp C/writing_solution.cpp)
    target_link_libraries(tutorial_utils ${MPI_LIBRARIES})

    add_executable(create_input C/create_input.cpp)
    
endif()

enable_testing()
add_subdirectory(src/tests)

add_subdirectory(examples)
