#include "src.hpp"
#include <stdio.h>

void print_vector(const double *vec, int n, int rank){
    int i;
    printf("Rank %d data: [", rank);
    for (i = 0; i < n && i < 5; ++i) {
        printf("%.1f", vec[i]);
        if (i < n - 1 && i < 4) {
            printf(", ");
        }
    }
    if (n > 5) {
        printf(", ...");
    }
    printf("] (total: %d elements)\n", n);
}

int verify_sequential_data(const double *vec, int n, double expected_start){
    int i;
    for (i = 0; i < n; ++i) {
        double expected = expected_start + (double)i;
        if (vec[i] != expected) {
            return 0;
        }
    }
    return 1;
}

bool mpi_initialized = false;
bool mpi_finalized = false;
int num_procs = 0;

int MPI_Init(int* argc, char*** argv)
{
    mpi_initialized = true;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    return MPI_SUCCESS;
}


int MPI_Finalize()
{
    mpi_finalized = true;
    return MPI_SUCCESS;
}


