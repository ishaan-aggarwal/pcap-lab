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
        scanf("%[^\n]", string);
        getchar(); // to clear '\n' from input buffer
        length = strlen(string);
        
        while (length % size != 0) {
            printf("String length must be divisible by %d. Enter again: ", size);
            scanf("%[^\n]", string);
            getchar();
            length = strlen(string) ;
        }
    }

    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int local_length = length / size;
    char local_string[local_length];

    MPI_Scatter(&string, local_length, MPI_CHAR, &local_string, local_length, MPI_CHAR, 0, MPI_COMM_WORLD);

    int non_vowel_count = 0;
    for (int i=0; i<local_length; i++) {
        if (!is_vowel(local_string[i]) && isalpha(local_string[i])) {
            non_vowel_count++;
        }
    }

    int all_counts[size];
    MPI_Gather(&non_vowel_count, 1, MPI_INT, &all_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int total_count = 0;
        printf("Non vowels found by each process:\n");
        for (int i=0; i<size; i++) {
            printf("(Process %d) %d non vowels.\n", i, all_counts[i]);
            total_count += all_counts[i];
        }
        printf("Total non vowels in string: %d\n", total_count);
    }

    MPI_Finalize();
    return 0;
}
