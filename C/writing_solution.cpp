#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/src.hpp"
#include <math.h>

#define TOTAL_VALUES 1024

int writing_main(char *filename) {
    
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // For simplicity, we make TOTAL_VALUES divisible by the number of processes.
    if (TOTAL_VALUES % size != 0) {
        if (rank == 0) {
            fprintf(stderr, "The number of values must be divisible by the number of processes.\n");
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int values_per_process = TOTAL_VALUES / size;

    // Generate the random values. Each process must generate its own chunk.
    double *data_buffer = (double*)malloc(values_per_process * sizeof(double));
    if (data_buffer == NULL) {
        fprintf(stderr, "Process %d: Failed to allocate memory.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    srand(time(NULL) + rank); 

    for (int i = 0; i < values_per_process; i++) {
        data_buffer[i] = (double)rand();
    }

    // Calculate the process' offset.
    MPI_Offset file_offset;
    
    file_offset = (MPI_Offset)rank * values_per_process * sizeof(double);

    /* If you need help debugging or if you are curious you can add the following line:
       printf("Process %d will start writing at byte offset: %lld (0x%llX)\n", 
           rank, (long long)file_offset, (long long)file_offset);
    */

    // File handle.
    MPI_File fh;

    // Open the file for writing.
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

    // Perform the parallel write operation
    MPI_File_write_at(fh, file_offset, data_buffer, values_per_process, MPI_DOUBLE, MPI_STATUS_IGNORE);

    // Close the file handle
    MPI_File_close(&fh);

    // Free local memory.
    free(data_buffer);
    
    MPI_Finalize();

    return 0;
}
