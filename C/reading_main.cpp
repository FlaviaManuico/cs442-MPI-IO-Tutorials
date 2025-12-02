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

    // Get rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    // 1. Open the shared file collectively
    //   Use MPI_File_open on MPI_COMM_WORLD with:
    //   - filename
    //   - MPI_MODE_RDONLY
    //   - MPI_INFO_NULL
    //   Store the result in 'file'.



    // 2. Get the file size in bytes
    //   Use MPI_File_get_size to fill file_size_bytes.



    // 3. Compute total_doubles
    //   Convert file_size_bytes to "how many doubles":
    //   total_doubles = file_size_bytes / sizeof(double);



    // 4. Divide the work across ranks
    //   Compute:
    //      base      = total_doubles / size;
    //      remainder = total_doubles % size;
    //
    //   This will let some ranks get base+1 elements,
    //   and the rest get base.



    // 5. Compute my_count and my_offset_doubles
    //   my_count:
    //      base + (rank < remainder ? 1 : 0)
    //
    //   my_offset_doubles:
    //      - If rank < remainder:
    //          rank * (base + 1)
    //      - Else:
    //          remainder * (base + 1)
    //          + (rank - remainder) * base
    //
    //   Then compute my_offset_bytes =
    //          my_offset_doubles * sizeof(double);



    // 6. Allocate local buffer
    //   - If my_count > 0, allocate:
    //      local_data = (double*) malloc(my_count * sizeof(double));



    // 7. Read your chunk with MPI_File_read_at
    //   - If my_count > 0, call MPI_File_read_at starting at
    //     my_offset_bytes, reading my_count elements of type MPI_DOUBLE into local_data


    // 8. Close the file
    //  - Call MPI_File_close on 'file'.


    // The helper function prints a short preview of the local data
    // and the total number of elements on this rank.

    print_vector(local_data, (int)my_count, rank);

    // This block verifies that the data is sequential and matches
    // the expected pattern (0, 1, 2, ...).
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

    // 1. Initialize MPI
    //   Use MPI_Init(&argc, &argv)
    //   Then get rank using MPI_Comm_rank


    // 2. (Optional) Read filename from command line
    //   If argc > 1, set filename = argv[1]
  


    // 3. Print header from rank 0 (optional)
    //   Example: "MPI I/O Tutorial: Parallel Reading"
    


    // 4. Time your method
    //   - Call MPI_Wtime() before mpi_io_reading
    //   - Call MPI_Wtime() after
    //   - Compute local elapsed = end - start



    // 5. Compute maximum elapsed time across ranks
    //  - Use MPI_Reduce with MPI_MAX



    // 6. Print timing result from rank 0



    // 7. Finalize MPI
    //   Use MPI_Finalize()

    return 0;
}