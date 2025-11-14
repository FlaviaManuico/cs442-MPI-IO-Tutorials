#ifndef TUTORIAL_SRC_HPP
#define TUTORIAL_SRC_HPP

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern bool mpi_initialized;
extern bool mpi_finalized;
extern int mpi_num_procs;

int MPI_Init(int *argc, char ***argv);
int MPI_Finalize();

int tutorial_main(int argc, char **argv);
void print_vector(const double *data, int count, int rank);
int verify_sequential_data(const double *data, int count, double expected_start);
void mpi_io_reading(const char *filename);

#ifdef __cplusplus
}
#endif

#endif
