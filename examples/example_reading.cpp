#include <mpi.h>
#include <stdio.h>
#include "../src/src.hpp"

int main(int argc, char **argv){
    const char *filename = "input.bin";

    PMPI_Init(&argc, &argv);

    int rank;
    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc > 1)
        filename = argv[1];

    if (rank == 0)
        printf("Example (PMPI-enabled): Reading %s\n", filename);

    tutorial_main(argc, argv);

    PMPI_Finalize();
    return 0;
}
