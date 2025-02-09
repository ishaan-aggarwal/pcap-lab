#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) 
{
    int size, rank;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int buffer_size = size * sizeof(int) + MPI_BSEND_OVERHEAD;
    void * buffer = (void *) malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);
    int array[size];

    if (rank == 0) {
        printf("Enter array of %d elements: ", size);
        for (int i=0; i<size; i++) {
            scanf("%d", &array[i]);
        }

        for (int i=0; i<size; i++) {
            MPI_Bsend(&array[i], 1, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
    }

    MPI_Recv(&array[rank], 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

    if (rank % 2 == 0) {
        int square = array[rank] * array[rank];
        printf("Process %d: square(%d) = %d\n", rank, array[rank], square);
    }
    else {
        int cube = array[rank] * array[rank] * array[rank]; 
        printf("Process %d: cube(%d) = %d\n", rank, array[rank], cube);
    }

    MPI_Buffer_detach(buffer, &size);
    MPI_Finalize();
    return 0;
}
