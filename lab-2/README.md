# Lab 2: Point-to-Point Communications in MPI

## **Objective**
This lab focuses on understanding and implementing point-to-point communication in MPI. It covers different blocking send modes and demonstrates how processes communicate using message passing.

## **Core Concepts**
### **1. Introduction to Point-to-Point Communication**
- Point-to-point communication in MPI involves message passing between two specific MPI tasks:
  - One task performs a **send operation**.
  - The other task performs a **matching receive operation**.
- MPI provides both **blocking** and **non-blocking** send and receive operations.

### **2. Blocking vs. Non-Blocking Operations**
- **Blocking Send**: The sender waits until the receiver has received the message before continuing. Also called **synchronous send**.
- **Non-Blocking Send**: The sender continues execution without waiting for the receiver. Also called **asynchronous send**.

## **Modes of Blocking Send Operations**
MPI provides three modes for blocking send operations:

### **1. Standard Mode**
- The send operation blocks until the message is buffered.
- **Syntax:**
  ```c
  MPI_Send(void *Msg, int Count, MPI_Datatype Datatype, int Destination, int Tag, MPI_Comm Comm);
  ```

### **2. Synchronous Mode**
- The send operation blocks until the corresponding receive operation has started.
- **Syntax:**
  ```c
  MPI_Ssend(void *Msg, int Count, MPI_Datatype Datatype, int Destination, int Tag, MPI_Comm Comm);
  ```

### **3. Buffered Mode**
- The send operation assumes the availability of a user-specified buffer.
- **Syntax:**
  ```c
  MPI_Bsend(void *Msg, int Count, MPI_Datatype Datatype, int Destination, int Tag, MPI_Comm Comm);
  ```
- **Buffer Allocation:**
  ```c
  MPI_Buffer_attach(void *buffer, int size);
  ```
- **Buffer Release:**
  ```c
  MPI_Buffer_detach(void *buffer, int *size);
  ```

## **Receiving Messages in MPI**
The receive operation blocks until the requested data is available in the receiver's buffer.

### **Syntax:**
```c
MPI_Recv(void *Msg, int Count, MPI_Datatype Datatype, int Source, int Tag, MPI_Comm Comm, MPI_Status *status);
```

### **Explanation of Parameters**
- `Msg`: Pointer to the data buffer.
- `Count`: Number of elements in the message.
- `Datatype`: Data type of the message (e.g., `MPI_INT`, `MPI_FLOAT`).
- `Destination`: Rank of the destination process (for send functions).
- `Source`: Rank of the source process (for receive functions).
- `Tag`: Message tag for identification.
  > **Note:** Tags are unique only between a pair of communicating processes. Different process pairs can use the same tag without conflict.
- `Comm`: MPI communicator (usually `MPI_COMM_WORLD`).
- `status`: Pointer to an `MPI_Status` structure that contains information about the received message.

## **Finding Execution Time in MPI**
- **`MPI_Wtime()`**: Returns the elapsed wall-clock time in seconds.
- **Example:**
  ```c
  double start_time, end_time;
  start_time = MPI_Wtime();
  // Code to measure
  end_time = MPI_Wtime();
  printf("Elapsed time: %f seconds\n", end_time - start_time);
  ```

## **Example Program: Standard Send and Receive**
This MPI program demonstrates a simple send and receive operation.

```c
#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        // Master process (sender)
        printf("Enter a value in master process: ");
        scanf("%d", &x);
        MPI_Send(&x, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        printf("I have sent %d from process 0\n", x);
    } else if (rank == 1) {
        // Receiver process
        MPI_Recv(&x, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        printf("I have received %d in process 1\n", x);
    }

    MPI_Finalize();
    return 0;
}
```

## **Lab Exercises**
1. Write an MPI program using **synchronous send** where:
   - The sender sends a word to the receiver.
   - The receiver toggles each letter and sends it back to the sender.
   - Both processes use synchronous send operations.

2. Write an MPI program where:
   - The master process (process 0) sends a number to each of the slaves.
   - The slave processes receive the number and print it using **standard send**.

3. Write an MPI program where:
   - The root process (process 0) reads an array of size `N` (equal to total processes).
   - The root process sends one element to each slave using **buffered send**.
   - Even-ranked processes compute the **square**, and odd-ranked processes compute the **cube** of the received element.

4. Write an MPI program where:
   - The root process sends an integer to process 1.
   - Each process increments the received value by 1 and passes it to the next process.
   - The last process sends the value back to the root.
   - Implement this using **point-to-point communication routines**.