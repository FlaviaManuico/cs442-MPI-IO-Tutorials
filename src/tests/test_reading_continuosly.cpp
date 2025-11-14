#include <mpi.h>
#include <stdio.h>
#include "../src.hpp"


int main(int argc, char **argv){
    PMPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const char *filename = "input.bin";

    if (rank == 0)
        printf("Running test_reading_continuosly: \n");

    mpi_io_reading(filename);

    MPI_Barrier(MPI_COMM_WORLD);

    mpi_io_reading(filename);

    if (rank == 0)
        printf("PASS: Consistency test passed (two runs succeeded).\n");

    PMPI_Finalize();
    return 0;
}
