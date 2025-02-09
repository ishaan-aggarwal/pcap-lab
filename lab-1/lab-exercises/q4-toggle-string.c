#include "mpi.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) 
{
    int rank, size;
    char str[] = "HElLo";
    int str_len = strlen(str);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != str_len) {
        if (rank == 0) printf("Run with %d processes.\n", str_len);
        MPI_Finalize();
        exit(0);
    }
    
    if (rank == 0) printf("Original String: %s\n", str);

    if (isupper(str[rank])) {
        str[rank] = tolower(str[rank]);
    }
    else if (islower(str[rank])) {
        str[rank] = toupper(str[rank]);
    }

    printf("Process %d: toggled char is '%c'\n", rank, str[rank]);

    MPI_Finalize();
    return 0;
}