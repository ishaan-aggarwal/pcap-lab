#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    int size, rank, num;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Enter a number: ");
        scanf("%d", &num);
        printf("Process 0: Sending number to all processes\n");
        for (int i=1; i<size; i++) {
            MPI_Send(&num, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(&num, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        printf("Process %d: number received from process 0 is %d\n", rank, num);
    }

    MPI_Finalize();
    return 0;
}
