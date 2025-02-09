#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    int size, rank;
    MPI_Status status;
    int x;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Enter a number: ");
        scanf("%d", &x);
        MPI_Send(&x, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, size-1, 1, MPI_COMM_WORLD, &status);
        printf("Process 0: Received %d from final process %d\n", x, size-1);
    }
    else if (rank == size-1){
        MPI_Recv(&x, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
        printf("Process %d: Received %d from process %d\n", rank, x, rank-1);
        x++;
        MPI_Send(&x, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(&x, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, &status);
        printf("Process %d: Received %d from process %d\n", rank, x, rank-1);
        x++;
        MPI_Send(&x, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);
    }


    MPI_Finalize();
    return 0;
}
