#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/src.hpp"
#include <math.h>

#define TOTAL_VALUES 1024

void mpi_io_writing(const char *filename) {
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // For simplicity, we make TOTAL_VALUES divisible by the number of processes. Check this before generating the values.

    const int values_per_process = TOTAL_VALUES / size;

    // Generate the random values. Each process must generate its own chunk.
    double *data_buffer = ...;

    // Calculate the process' offset.
    MPI_Offset file_offset;

    file_offset = ...;

    /* If you need help debugging or if you are curious you can add the following line:
       printf("Process %d will start writing at byte offset: %lld (0x%llX)\n", 
           rank, (long long)file_offset, (long long)file_offset);
    */

    // File handle.
    MPI_File fh;

    // Open the file and perform the parallel write operation.
    // Check the instructions (pdf) for hints.
    MPI_File_open(...);
    MPI_File_write_at(...);

    // Close the file.

    // Free local memory.

}

int writing_main(int argc, char **argv){
    int rank;
    const char *filename = "output.bin";

    // Initialize MPI

    // Get the rank using MPI_Comm_rank

    // (Optional but recommended) Read filename from command line
    //   If argc > 1, set filename = argv[1]
    if (argc > 1)
        filename = argv[1];

    mpi_io_writing(filename);

    // Finalize MPI
    
    return 0;
}
