# Lab 4: Collective Communications and Error Handling in MPI

## **Objective**
This lab focuses on understanding and implementing collective communication in MPI. It covers aggregation functions, synchronization, and error handling in MPI programs.

## **Core Concepts**

### **1. Aggregation Functions in MPI**
MPI provides two main aggregation functions:
- **Reduction (`MPI_Reduce`)**: Combines partial values from all processes into a single result at the root process.
- **Scan (`MPI_Scan`)**: Combines partial values into intermediate results for each process.
#### **1.1 MPI_Reduce (Reduction)**
Combines partial values from all processes into a single result at the root process.

**Syntax:**
```c
MPI_Reduce(void *SendAddress, void *RecvAddress, int Count, MPI_Datatype Datatype, MPI_Op Op, int Root, MPI_Comm Comm);
```

#### **1.2 MPI_Scan (Scan)**
Combines partial values into intermediate results for each process.

**Syntax:**
```c
MPI_Scan(void *SendAddress, void *RecvAddress, int Count, MPI_Datatype Datatype, MPI_Op Op, MPI_Comm Comm);
```

#### **Explanation of Parameters**
- **SendAddress**: Pointer to the buffer containing the data to be sent.
- **RecvAddress**: Pointer to the buffer where the result will be stored.
- **Count**: Number of elements in the buffer.
- **Datatype**: Data type of elements in the buffer (e.g., `MPI_INT`, `MPI_FLOAT`).
- **Op**: Operation applied during reduction or scan (e.g., `MPI_SUM`, `MPI_MAX`, `MPI_MIN`, `MPI_PROD`).
- **Root**: Rank of the root process collecting the result.
- **Comm**: Communicator handle.

### **2. Synchronization in MPI**

#### **2.1 MPI_Barrier (Synchronization)**
Synchronizes all processes in the communicator. All processes must reach this point before any can proceed.

**Syntax:**
```c
MPI_Barrier(MPI_Comm Comm);
```

### **3. Error Handling in MPI**
MPI provides mechanisms to handle errors during program execution.

#### **3.1 Error Handlers**
- **`MPI_ERRORS_ARE_FATAL`**: Default error handler. Aborts the program if an error is detected.
- **`MPI_ERRORS_RETURN`**: Returns an error code instead of aborting the program.

#### **3.2 Setting Error Handlers**
**Syntax:**
```c
MPI_Errhandler_set(MPI_Comm Comm, MPI_Errhandler ErrHandler);
```

#### **3.3 Error Codes and Classes**
- **`MPI_SUCCESS`**: Indicates no error.
- **`MPI_Error_string`**: Converts an error code to a human-readable message.
- **`MPI_Error_class`**: Retrieves the error class for a given error code.

## **Example Program: Sum of Factorials Using MPI_Reduce**
This MPI program calculates the sum of factorials from `1!` to `N!` using collective communication.

```c
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size, fact = 1, factsum, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Compute factorial for (rank + 1)
    for (i = 1; i <= rank + 1; i++) {
        fact = fact * i;
    }

    // Reduce partial factorials to the root process
    MPI_Reduce(&fact, &factsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process prints the result
    if (rank == 0) {
        printf("Sum of all the factorials = %d\n", factsum);
    }

    MPI_Finalize();
    return 0;
}
```

### **Sample Output**
```
Sum of all the factorials = 33
```
- **Explanation**:
  - Process 0 computes `1! = 1`.
  - Process 1 computes `2! = 2`.
  - Process 2 computes `3! = 6`.
  - Process 3 computes `4! = 24`.
  - The sum of these factorials is `1 + 2 + 6 + 24 = 33`.

## **Lab Exercises**
1. Write an MPI program using N processes to find `1! + 2! + ... + N!` using `MPI_Scan`. Also, handle different errors using error handling routines.
2. Write an MPI program to read a `3 x 3` matrix. Enter an element to be searched in the root process. Find the number of occurrences of this element in the matrix using three processes.
3. Write an MPI program to read a `4 x 4` matrix and display the following output using four processes.

    Input Matrix:
    ```
    1  2  3  4
    1  2  3  1
    1  1  1  1
    2  1  2  1
    ```
    Output Matrix:
    ```
    1  2  3  4
    2  4  6  5
    3  5  7  6
    5  6  9  7
    ```
4. Write an MPI program to read a word of length N. Using N processes, including the root, get an output word with the pattern as shown in the example. Display the resultant output word in the root.

    Example:

    - Input: `PCAP`

    - Output: `PCCAAAPPPP`