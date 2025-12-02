file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")

foreach(src ${TEST_SOURCES})
    get_filename_component(exec_name ${src} NAME_WE)

    add_executable(${exec_name} ${src})

    target_link_libraries(${exec_name} tutorial_utils ${MPI_LIBRARIES})

    add_test(NAME ${exec_name}_Test
             COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4
                     ${MPIEXEC_PREFLAGS}
                     ./${exec_name}
                     ${MPIEXEC_POSTFLAGS})
endforeach()

set_tests_properties(test_reading_Test
                     test_reading_remainder_Test
                     test_reading_continuosly_Test
                     PROPERTIES LABELS "mpi_io_reading")
