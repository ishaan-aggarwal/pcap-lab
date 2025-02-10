#include "mpi.h"
#include <stdio.h>

int factorial(int n) 
{
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(int argc, char * argv[])
{
    int rank, size, N, A[20], B[20], c;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (rank == 0) {
        N = size;
        printf("Enter %d elements: ", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
    }

    MPI_Scatter(&A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("(Process %d) Received %d from root.\n", rank, c);
    c = factorial(c);
    MPI_Gather(&c, 1, MPI_INT, &B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered factorials are: ");
        int sum = 0;
        for (int i = 0; i < N; i++) {
            printf("%d ", B[i]);
            sum += B[i];
        }
        printf("\nSum of all factorials is: %d\n", sum);
    }

    MPI_Finalize();
    return 0;
}