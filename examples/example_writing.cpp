#include <mpi.h>
#include <stdio.h>
#include "../src/src.hpp"

int main(int argc, char **argv){
    const char *filename = "output.bin";

    PMPI_Init(&argc, &argv);

    int rank;
    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc > 1)
        filename = argv[1];

    if (rank == 0)
        printf("Example (PMPI-enabled): Writing %s\n", filename);

    mpi_io_writing(filename);

    PMPI_Finalize();
    return 0;
}
