#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) 
{
    int rank, size;
    float a = 10.5, b = 2.5, result = 0;
    char operator;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != 4) {
        if (rank == 0) printf("Run program with 4 processes.\n");
        MPI_Finalize();
        exit(0);
    }

    switch (rank) {
        case 0:
            result = a + b;
            operator = '+';
            break;
        case 1:
            result = a - b;
            operator = '-';
            break;
        case 2:
            result = a * b;
            operator = '*';
            break;
        case 3:
            if (b == 0)
                printf("Process %d: Division by zero error.\n", rank);
            else
                result = a / b;
            operator = '/';
            break;
    }

    if (!(rank == 3 && b == 0)) {
        printf("Process %d: %.2f %c %.2f = %.2f\n", rank, a, operator, b, result);
    }
    
    MPI_Finalize();
    return 0;
}