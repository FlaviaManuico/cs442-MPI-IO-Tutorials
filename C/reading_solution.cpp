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

    // 1. Open file
    if (MPI_File_open(MPI_COMM_WORLD, filename,
                      MPI_MODE_RDONLY, MPI_INFO_NULL, &file) != MPI_SUCCESS) {
        if (rank == 0)
            fprintf(stderr, "Error: could not open file %s\n", filename);
        return;
    }

    // 2. Get file size
    MPI_File_get_size(file, &file_size_bytes);

    // 3. Total doubles
    total_doubles = file_size_bytes / (MPI_Offset)sizeof(double);

    // 4. Divide work
    base = total_doubles / size;
    remainder = total_doubles % size;
    my_count  = base + (rank < remainder ? 1 : 0);

    // 5. Compute offsets
    if (rank < remainder)
        my_offset_doubles = rank * (base + 1);
    else
        my_offset_doubles = remainder * (base + 1)
                          + (rank - remainder) * base;

    my_offset_bytes = my_offset_doubles * sizeof(double);

    // 6. Allocate buffer
    local_data = (double*)malloc((size_t)my_count * sizeof(double));

    // 7. Read
    MPI_File_read_at(file, my_offset_bytes,
                     local_data, (int)my_count,
                     MPI_DOUBLE, &status);

    // 8. Close
    MPI_File_close(&file);

    print_vector(local_data, (int)my_count, rank);

    MPI_Offset start;
    if (rank < remainder)
        start = rank * (base + 1);
    else
        start = remainder * (base + 1)
              + (rank - remainder) * base;

    if (!verify_sequential_data(local_data, (int)my_count, (double)start)) {
        fprintf(stderr, "Rank %d: ERROR: data incorrect\n", rank);
    } else if (rank == 0) {
        printf("All data verified correctly\n");
    }

    free(local_data);
}

// int tutorial_main(int argc, char **argv){
//     int rank;
//     const char *filename = "input.bin";

//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//     if (argc > 1)
//         filename = argv[1];

//     if (rank == 0)
//         printf("MPI I/O Tutorial: Parallel Reading\n\n");

//     double t_start = MPI_Wtime();
//     mpi_io_reading(filename);
//     double t_end = MPI_Wtime();

//     double elapsed = t_end - t_start;
//     double max_elapsed;

//     MPI_Reduce(&elapsed, &max_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
//     if (rank == 0)
//         printf("\nTime: %f seconds\n", max_elapsed);

//     return 0;
// }

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