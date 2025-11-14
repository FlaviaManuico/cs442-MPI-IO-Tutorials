#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src.hpp"

int main(int argc, char **argv){
    PMPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const char *filename = "input.bin";

    if (rank == 0)
        printf("Running test reading offsets on %d ranks...\n", size);

    mpi_io_reading(filename);

    MPI_File file;
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY,
                  MPI_INFO_NULL, &file);

    MPI_Offset file_size;
    MPI_File_get_size(file, &file_size);
    MPI_File_close(&file);

    MPI_Offset total_doubles = file_size / sizeof(double);

    MPI_Offset base = total_doubles / size;
    MPI_Offset remainder = total_doubles % size;

    MPI_Offset expected_count =
        base + (rank < remainder ? 1 : 0);

    MPI_Offset expected_offset;
    if (rank < remainder)
        expected_offset = rank * (base + 1);
    else
        expected_offset = remainder * (base + 1)
                        + (rank - remainder) * base;

    double *buf = (double*)malloc(expected_count * sizeof(double));

    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY,
                  MPI_INFO_NULL, &file);

    MPI_File_read_at(file, expected_offset * sizeof(double), buf,
                     (int)expected_count, MPI_DOUBLE, MPI_STATUS_IGNORE);

    MPI_File_close(&file);

    int local_ok = 1;
    for (int i = 0; i < expected_count; i++){
        double expected = (double)(expected_offset + i);
        if (buf[i] != expected){
            fprintf(stderr,
                "Rank %d ERROR: offset mismatch: buf[%d]=%.1f expected %.1f\n",
                rank, i, buf[i], expected);
            local_ok = 0;
            break;
        }
    }

    int global_ok;
    MPI_Reduce(&local_ok, &global_ok, 1, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);

    if (rank == 0){
        if (global_ok)
            printf("PASS: Correct offsets test passed\n");
        else
            printf("FAIL\n");
    }

    free(buf);
    PMPI_Finalize();
    return 0;
}
