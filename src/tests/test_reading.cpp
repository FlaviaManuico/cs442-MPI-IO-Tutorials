#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../src.hpp"

int main(int argc, char **argv){
    PMPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const char *filename = "input.bin";

    if (rank == 0)
        printf("Running test_reading on %d ranks...\n", size);

    mpi_io_reading(filename);

    MPI_File file;
    MPI_Offset file_size;
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY,
                   MPI_INFO_NULL, &file);
    MPI_File_get_size(file, &file_size);
    MPI_File_close(&file);

    MPI_Offset total_doubles = file_size / sizeof(double);

    int ok_global = 1;
    if (total_doubles != 1000) {
        if (rank == 0)
            fprintf(stderr,
                "Error: expected 1000 doubles but file has %lld\n",
                (long long)total_doubles);
        ok_global = 0;
    }

    int local_ok = 1;

    MPI_Reduce(&local_ok, &ok_global, 1, MPI_INT, MPI_LAND,
                0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (ok_global)
            printf("PASS: Reading test passed successfully!\n");
        else
            printf("FAIL: Reading verification failed\n");
    }

    PMPI_Finalize();
    return 0;
}
