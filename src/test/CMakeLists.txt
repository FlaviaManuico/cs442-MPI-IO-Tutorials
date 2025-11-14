add_executable(test_reading test_reading.cpp)
target_link_libraries(test_reading tutorial_utils ${MPI_LIBRARIES})

add_test(NAME test_reading_Test
         COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4 
                 ${MPIEXEC_PREFLAGS}
                 ${CMAKE_CURRENT_BINARY_DIR}/test_reading
                 ${MPIEXEC_POSTFLAGS}
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set_tests_properties(test_reading_Test PROPERTIES 
    LABELS "mpi_io_reading"
    TIMEOUT 30
)