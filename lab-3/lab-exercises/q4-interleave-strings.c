#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]) 
{
    int rank, size;
    char str1[100], str2[100];
    int length;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) {
        printf("Enter first string: ");
        scanf("%[^\n]", str1);
        getchar();
        printf("Enter second string: ");
        scanf("%[^\n]", str2);
        length = strlen(str1);
        getchar();
        
        while (length != strlen(str2) || length % size != 0) {
            printf("Strings must be of equal length and length must be divisible by %d\n", size);
            printf("Enter first string: ");
            scanf("%[^\n]", str1);
            getchar();
            printf("Enter second string: ");
            scanf("%[^\n]", str2);
            getchar();
            length = strlen(str1);
        }
    }

    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_length = length / size;
    char temp1[local_length], temp2[local_length], temp_result[local_length * 2];
    int j=0;

    MPI_Scatter(&str1, local_length, MPI_CHAR, &temp1, local_length, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(&str2, local_length, MPI_CHAR, &temp2, local_length, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i=0; i<local_length * 2; i++) {
        temp_result[j++] = temp1[i];
        temp_result[j++] = temp2[i];
    }

    char final_result[length * 2];
    MPI_Gather(&temp_result, local_length * 2, MPI_CHAR, &final_result, local_length * 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nInput strings: \"%s\" and \"%s\"\n", str1, str2);
        final_result[length*2] = '\0';
        printf("Merged string: \"%s\"\n", final_result);
    }
    
    
    
    // // Merge local portions
    // for (int i = 0; i < local_size; i++) {
    //     local_merged[i * 2] = local_str1[i];
    //     local_merged[i * 2 + 1] = local_str2[i];
    // }
    
    // // Array for final merged string
    // char final_merged[length * 2 + 1];  // +1 for null terminator
    
    // // Gather merged portions
    // MPI_Gather(local_merged, local_size * 2, MPI_CHAR,
    //            final_merged, local_size * 2, MPI_CHAR,
    //            0, MPI_COMM_WORLD);
    
    // // Root process prints result
    // if (rank == 0) {
    //     final_merged[length * 2] = '\0';  // Add null terminator
    //     printf("\nInput strings: \"%s\" and \"%s\"\n", str1, str2);
    //     printf("Merged string: \"%s\"\n", final_merged);
    // }
    
    MPI_Finalize();
    return 0;
}