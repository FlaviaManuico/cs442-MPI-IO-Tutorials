#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src.hpp"

void mpi_io_reading(const char *filename);

int main(int argc, char **argv) {
    PMPI_Init(&argc, &argv);

    int rank, size;
    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);
    PMPI_Comm_size(MPI_COMM_WORLD, &size);

    const char *filename = "input_remainder.bin";

    if (rank == 0) {
        FILE *f = fopen(filename, "wb");
        if (!f) {
            fprintf(stderr, "Error: could not create %s\n", filename);
            PMPI_Abort(MPI_COMM_WORLD, 1);
        }

        int total = 10;
        double *vals = (double*)malloc(total * sizeof(double));
        for (int i = 0; i < total; i++) {
            vals[i] = (double)i;
        }
        fwrite(vals, sizeof(double), total, f);
        free(vals);
        fclose(f);

        printf("Created %s with %d doubles (remainder test)\n",
               filename, total);
    }

    PMPI_Barrier(MPI_COMM_WORLD);

    mpi_io_reading(filename);

    if (rank == 0) {
        printf("PASS: remainder test completed without errors.\n");
    }

    PMPI_Finalize();
    return 0;
}

