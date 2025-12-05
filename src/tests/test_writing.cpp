#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../src.hpp"

#define TOTAL_VALUES 1024
#define FILE_NAME "output.bin"

int main(int argc, char **argv){
  PMPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Rank 0 will read the file to verify the content.
  if (rank == 0)
    printf("\nVerifying the file\n");

  MPI_File file;
  MPI_Offset file_size;
  MPI_File_open(MPI_COMM_WORLD, FILE_NAME, MPI_MODE_RDONLY,
		MPI_INFO_NULL, &file);
  MPI_File_get_size(file, &file_size);
  MPI_File_close(&file);

  MPI_Offset total_doubles = file_size / sizeof(double);

  if (rank == 0) {
    if (total_doubles == 1000)
      printf("PASS: Reading test passed successfully!\n");
    else
      printf("FAIL: Reading verification failed. Expected 1000 doubles but file has %lld\n",(long long)total_doubles);
  }

  PMPI_Finalize();
  return 0;
}
