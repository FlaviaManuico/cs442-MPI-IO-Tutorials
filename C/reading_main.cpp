#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/src.hpp"

void mpi_io_reading(const char *filename){
    int rank, size;
    MPI_File file;
    MPI_Status status;

    MPI_Offset file_size_bytes;
    MPI_Offset total_doubles;
    MPI_Offset base, remainder;
    MPI_Offset my_count;
    MPI_Offset my_offset_doubles;
    MPI_Offset my_offset_bytes;

    double *local_data = NULL;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //---------------------------------------------------
    // TODO 1: Open file
    // file = ...
    //---------------------------------------------------

    //---------------------------------------------------
    // TODO 2: Get file size
    //---------------------------------------------------

    //---------------------------------------------------
    // TODO 3: Compute total_doubles
    //---------------------------------------------------

    //---------------------------------------------------
    // TODO 4: Divide work
    //---------------------------------------------------

    //---------------------------------------------------
    // TODO 5: Compute offsets
    //---------------------------------------------------

    //---------------------------------------------------
    // TODO 6: Allocate buffer
    //---------------------------------------------------

    //---------------------------------------------------
    // TODO 7: Read data
    //---------------------------------------------------

    //---------------------------------------------------
    // TODO 8: Close file
    //---------------------------------------------------

    print_vector(local_data, (int)my_count, rank);

    {
        MPI_Offset start;
        if (rank < remainder)
            start = rank * (base + 1);
        else
            start = remainder * (base + 1) + (rank - remainder) * base;

        if (!verify_sequential_data(local_data, (int)my_count, (double)start)) {
            fprintf(stderr, "Rank %d: ERROR: Data incorrect\n", rank);
        } else if (rank == 0) {
            printf("All data verified correctly\n");
        }
    }

    free(local_data);
}


int tutorial_main(int argc, char **argv){
    int rank;
    const char *filename = "input.bin";

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc > 1)
        filename = argv[1];

    if (rank == 0)
        printf("MPI I/O Tutorial\n\n");

    double t_start = MPI_Wtime();
    mpi_io_reading(filename);
    double t_end = MPI_Wtime();

    double elapsed = t_end - t_start;
    double max_elapsed;

    MPI_Reduce(&elapsed, &max_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("\nTime: %f seconds\n", max_elapsed);

    MPI_Finalize();
    return 0;
}