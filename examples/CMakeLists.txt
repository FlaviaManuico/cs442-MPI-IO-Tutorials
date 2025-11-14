file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "*.cpp")

foreach(src ${EXAMPLE_SOURCES})
    get_filename_component(exec_name ${src} NAME_WE)

    add_executable(${exec_name} ${src})
    target_link_libraries(${exec_name} tutorial_utils ${MPI_LIBRARIES})
endforeach()