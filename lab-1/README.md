# Lab 1: Introduction to MPI Execution Environment

## **Objective**
This lab introduces the core concepts of MPI (Message Passing Interface) and demonstrates how to write, compile, and execute a basic MPI program. The focus is on understanding the execution environment, process management, and basic MPI routines.

## **Core Concepts**

### **1. MPI Execution Environment**
- MPI programs consist of multiple processes that run in parallel.
- Each process has a unique **rank** (ID) and operates independently.
- Processes communicate by passing messages explicitly.

### **2. Key MPI Routines**
- **`MPI_Init`**: Initializes the MPI environment. Must be called before any other MPI function.
- **`MPI_Comm_size`**: Retrieves the total number of processes in the communicator (e.g., `MPI_COMM_WORLD`).
- **`MPI_Comm_rank`**: Retrieves the rank (ID) of the current process. Each process gets a unique rank, starting from `0` to `size-1`.
- **`MPI_Finalize`**: Cleans up the MPI environment. Must be called at the end of the program.

## **Example Program**

### **Print Process Rank and Total Processes**
This program demonstrates how to retrieve and print the rank of each process and the total number of processes.

```c
#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print the rank and total number of processes
    printf("My rank is %d in total %d processes\n", rank, size);

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
```

## **Steps to Compile and Run the Program**

### **1. Compile the Program**

```bash
mpicc filename.c -o filename.out
```

If you are on macOS and want to prevent the `.dSYM` debug folder from being created, use the `-g0` flag:

```bash
mpicc -g0 filename.c -o filename.out
```

### **2. Run the Program**

```bash
mpirun -n 4 ./filename.out
```

## **Sample Output**

When running the program with 4 processes, the output will look like this:

```bash
My rank is 0 in total 4 processes
My rank is 1 in total 4 processes
My rank is 2 in total 4 processes
My rank is 3 in total 4 processes
```
- Each process prints its rank and the total number of processes.
- The output order may vary depending on the execution order of the processes.

## **Lab Exercises**

1. Write a simple MPI program to find out `pow(x, rank)` for all the processes where `x` is an integer constant and `rank` is the rank of the process.
2. Write a program in MPI where even-ranked processes print "Hello" and odd-ranked processes print "World".
3. Write a program in MPI to simulate a simple calculator. Perform each operation using a different process in parallel.
4. Write a program in MPI to toggle the character of a given string indexed by the rank of the process.  
   **Hint**: Suppose the string is `HELLO` and there are 5 processes, then process 0 toggles `H` to `h`, process 1 toggles `E` to `e`, and so on.
5. Write a program in MPI where even-ranked processes print the factorial of the rank and odd-ranked processes print the Fibonacci number of the rank.

## **Additional Exercises**

1. Write a program in MPI to reverse the digits of the following integer array of size 9 using 9 processes. Initialize the array to the following values:
   - **Input array**: `[18, 523, 301, 1234, 2, 14, 108, 150, 1928]`
   - **Output array**: `[81, 325, 103, 4321, 2, 41, 801, 51, 8291]`
2. Write an MPI program to find the prime numbers between 1 and 100 using two processes.

