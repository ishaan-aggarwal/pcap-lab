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
        fgets(str1, 100, stdin);
        printf("Enter second string: ");
        fgets(str2, 100, stdin);
        
        str1[strcspn(str1, "\n")] = 0;
        str2[strcspn(str2, "\n")] = 0;
        
        length = strlen(str1);
        
        while (length != strlen(str2) || length % size != 0) {
            printf("Strings must be of equal length and length must be divisible by %d\n", size);
            printf("Enter first string: ");
            fgets(str1, 100, stdin);
            printf("Enter second string: ");
            fgets(str2, 100, stdin);
            
            str1[strcspn(str1, "\n")] = 0;
            str2[strcspn(str2, "\n")] = 0;
            length = strlen(str1);
        }
    }
    
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    int local_size = length / size;
    
    char local_str1[local_size];
    char local_str2[local_size];
    char local_merged[local_size * 2];
    
    // Scatter both strings
    MPI_Scatter(str1, local_size, MPI_CHAR, 
                local_str1, local_size, MPI_CHAR, 
                0, MPI_COMM_WORLD);
                
    MPI_Scatter(str2, local_size, MPI_CHAR, 
                local_str2, local_size, MPI_CHAR, 
                0, MPI_COMM_WORLD);
    
    // Merge local portions
    for (int i = 0; i < local_size; i++) {
        local_merged[i * 2] = local_str1[i];
        local_merged[i * 2 + 1] = local_str2[i];
    }
    
    // Array for final merged string
    char final_merged[length * 2 + 1];  // +1 for null terminator
    
    // Gather merged portions
    MPI_Gather(local_merged, local_size * 2, MPI_CHAR,
               final_merged, local_size * 2, MPI_CHAR,
               0, MPI_COMM_WORLD);
    
    // Root process prints result
    if (rank == 0) {
        final_merged[length * 2] = '\0';  // Add null terminator
        printf("\nInput strings: \"%s\" and \"%s\"\n", str1, str2);
        printf("Merged string: \"%s\"\n", final_merged);
    }
    
    MPI_Finalize();
    return 0;
}