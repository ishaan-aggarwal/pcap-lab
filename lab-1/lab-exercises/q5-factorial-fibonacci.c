// Write a program in MPI where even-ranked processes print the factorial of the rank and odd-ranked processes print the Fibonacci number of the rank.
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int num) 
{
    if (num <= 1) {
        return num;
    }
    return fibonacci(num - 1) + fibonacci(num - 2);
}

int factorial(int num) 
{
    if (num == 0 || num == 1) {
        return 1;
    }
    return factorial(num - 1) * num;
} 


int main(int argc, char * argv[])
{
   int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank % 2 == 0) {
        printf("Process %d: factorial(%d) = %d\n", rank, rank, factorial(rank));
    }
    else {
        printf("Process %d: fibonacci(%d) = %d\n", rank, rank, fibonacci(rank));
    }

    MPI_Finalize();
    return 0;
}