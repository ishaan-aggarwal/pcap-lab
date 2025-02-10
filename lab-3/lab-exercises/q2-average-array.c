#include "mpi.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
    int rank, size, M, total_size, A[50];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (rank == 0) {
        printf("Enter M: ");
        scanf("%d", &M);
        while (M % size != 0) {
            printf("M must be divisible by %d. Enter again: ", size);
            scanf("%d", &M);
        }
        total_size = size * M; 
        printf("Enter %d elements: ", total_size);
        for (int i = 0; i < total_size; i++) {
            scanf("%d", &A[i]);
        }
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int local_size = M;
    int C[local_size];
    float B[size];

    MPI_Scatter(&A, local_size, MPI_INT, &C, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    float local_sum = 0.0;
    for (int i = 0; i < local_size; i++) {
        local_sum += C[i];
    }
    float local_avg = local_sum / local_size;
    printf("(Process %d) Local average = %.2f\n", rank, local_avg);

    MPI_Gather(&local_avg, 1, MPI_FLOAT, &B, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        float total_sum = 0.0;
        for (int i = 0; i < size; i++) {
            total_sum += B[i];
        }
        float total_avg = total_sum / size;
        printf("(Process 0) Total average = %.2f\n", total_avg);
    }

    MPI_Finalize();
    return 0;
}