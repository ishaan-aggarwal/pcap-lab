# Lab 3: Collective Communications in MPI

## **Objective**
This lab focuses on understanding and implementing collective communication in MPI. It covers different collective communication routines such as broadcasting, scattering, gathering, and total exchange.

## **Core Concepts**
### **1. Introduction to Collective Communication**
Collective communication in MPI involves multiple processes participating in a communication operation simultaneously. Unlike point-to-point communication, these operations allow multiple processes to exchange data efficiently in a structured manner.

### **2. Key Collective Communication Routines**

#### **1. MPI\_Bcast (Broadcast)**

- Broadcasts a message from the root process to all other processes in the communicator.
- **Syntax**:
  ```c
  MPI_Bcast(void *Address, int Count, MPI_Datatype Datatype, int Root, MPI_Comm Comm);
  ```
- **Parameters**:
  - `Address`: Pointer to the buffer containing the data to be broadcasted.
  - `Count`: Number of elements in the buffer.
  - `Datatype`: Data type of elements in the buffer (e.g., `MPI_INT`, `MPI_FLOAT`).
  - `Root`: Rank of the root process initiating the broadcast.
  - `Comm`: Communicator handle.

#### **2. MPI\_Scatter (Scatter)**

- Distributes distinct portions of a send buffer from the root process to all processes in the communicator.
- **Syntax**:
  ```c
  MPI_Scatter(void *SendBuff, int Sendcount, MPI_Datatype SendDatatype, void *RecvBuff, int Recvcount, MPI_Datatype RecvDatatype, int Root, MPI_Comm Comm);
  ```

#### **3. MPI\_Gather (Gather)**

- Gathers distinct portions of data from all processes into a receive buffer at the root process.
- **Syntax**:
  ```c
  MPI_Gather(void *SendAddress, int Sendcount, MPI_Datatype SendDatatype, void *RecvAddress, int Recvcount, MPI_Datatype RecvDatatype, int Root, MPI_Comm Comm);
  ```

#### **4. MPI\_Alltoall (Total Exchange)**

- Each process sends a personalized message to every other process, including itself.
- **Syntax**:
  ```c
  MPI_Alltoall(void *SendAddress, int Sendcount, MPI_Datatype SendDatatype, void *RecvAddress, int Recvcount, MPI_Datatype RecvDatatype, MPI_Comm Comm);
  ```

#### **Explanation of Parameters**

- `SendBuff` / `SendAddress`: Pointer to the send buffer.
- `Sendcount`: Number of elements sent to each process.
- `SendDatatype`: Data type of send buffer elements.
- `RecvBuff` / `RecvAddress`: Pointer to the receive buffer.
- `Recvcount`: Number of elements received by each process.
- `RecvDatatype`: Data type of receive buffer elements.
- `Root`: Rank of the root process distributing or gathering data.
- `Comm`: Communicator handle.

## **Example Program: Scatter and Gather**
This MPI program demonstrates scattering an array from the root process to all other processes, computing the square of received values, and gathering the results back to the root.

```c
#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, N, A[10], B[10], c, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        N = size;
        printf("Enter %d values:\n", N);
        for (i = 0; i < N; i++) scanf("%d", &A[i]);
    }

    MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("I have received %d in process %d\n", c, rank);
    c = c * c;
    MPI_Gather(&c, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("The Result gathered in the root:\n");
        for (i = 0; i < N; i++) {
            printf("%d\t", B[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
```

### **Sample Output**
```
Enter 4 values:
2 3 4 5
I have received 2 in process 0
I have received 3 in process 1
I have received 4 in process 2
I have received 5 in process 3
The Result gathered in the root:
4    9    16    25
```

## **Lab Exercises**
1. **Factorial Computation Using MPI**
   - Write an MPI program where the root process reads `N` values and sends one value to each process.
   - Each process calculates the factorial of the received number and returns it to the root.
   - The root process collects the factorial values and finds their sum.
   - Use `MPI_Scatter` and `MPI_Gather`.

2. **Average Calculation Using MPI**
   - Write an MPI program where the root process reads an integer value `M` and `N x M` elements into an array and distributes them evenly among `N` processes.
   - Each process calculates the average of the `M/N` values it receives and sends it to the root.
   - The root process collects all averages and computes the total average.
   - Use `MPI_Scatter` and `MPI_Gather`.

3. **Counting Non-Vowels in a String**
   - Write an MPI program where the root process reads a string and evenly distributes its characters among `N` processes.
   - Each process counts the number of non-vowel characters in its portion and sends the count to the root.
   - The root collects the counts and displays the total number of non-vowels.
   - Use `MPI_Scatter` and `MPI_Gather`.

4. **Merging Two Strings Using MPI**
   - Write an MPI program where the root process reads two strings of the same length and distributes the characters among `N` processes.
   - Each process merges its assigned characters from both strings to form a new sequence.
   - The root process gathers and prints the final merged string.
   - Use `MPI_Scatter` and `MPI_Gather`.