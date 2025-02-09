#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char * argv[]) 
{
    int rank, size;
    int x = 2;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double result = pow(x, rank);
    printf("Process %d: pow(%d, %d) = %.2lf\n", rank, x, rank, result);

    MPI_Finalize();
    return 0;
}