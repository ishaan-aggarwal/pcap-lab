#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char * toggle_case(char * word)
{
    for (int i = 0; word[i] != '\0'; i++) {
        if (islower(word[i])) {
            word[i] = toupper(word[i]);
        } 
        else if (isupper(word[i])) {
            word[i] = tolower(word[i]);
        }
    }
    return word;
}

int main(int argc, char * argv[])
{
    int rank, size, len;
    char word[50];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 2) {
        if (rank == 0) printf("Run with 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        printf("Enter a word: ");
        scanf("%s", word);
        len = strlen(word);
        MPI_Ssend(&len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Ssend(&word, strlen(word), MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        printf("Process 0: Sent word to process 1.\n");
        MPI_Recv(&word, len, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
        printf("Process 0: Received toggled word \"%s\"\n", word);
    }
    else {
        MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&word, len, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        printf("Process 1: Received word \"%s\" from process 0\n", word);
        toggle_case(word);
        MPI_Ssend(&word, len, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
        printf("Process 1: Sent toggled word to process 0\n");
    }

    MPI_Finalize();
    return 0;
}