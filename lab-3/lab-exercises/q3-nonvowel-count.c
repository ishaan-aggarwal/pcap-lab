#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) 
{
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main(int argc, char * argv[])
{
    int rank, size, length;
    char string[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (rank == 0) {
        printf("Enter a string: ");
        fgets(string, 100, stdin);
        length = strlen(string) - 1;
        
        while (length % size != 0) {
            printf("String length must be divisible by %d. Enter again: ", size);
            fgets(string, 100, stdin);
            length = strlen(string) - 1;
        }
    }

    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_size = length / size;
    char local_string[local_size];
    
    MPI_Scatter(&string, local_size, MPI_CHAR, &local_string, local_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    int local_count = 0;
    for (int i = 0; i < local_size; i++) {
        if (!is_vowel(local_string[i]) && isalpha(local_string[i])) {
            local_count++;
        }
    }
    
    int all_counts[size];
    MPI_Gather(&local_count, 1, MPI_INT, &all_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int total_nonvowels = 0;
        printf("\nNon-vowels found by each process:\n");
        for (int i = 0; i < size; i++) {
            printf("Process %d: %d\n", i, all_counts[i]);
            total_nonvowels += all_counts[i];
        }
        printf("\nTotal non-vowels: %d\n", total_nonvowels);
    }


    MPI_Finalize();
    return 0;
}
