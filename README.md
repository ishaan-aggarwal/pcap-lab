# Parallel Computing and Architecture Lab

## Overview
I created this repository to document my learning and solutions for the course **Parallel Computing and Architecture (PCAP) Lab** in my 6th semester at **MIT, Manipal**. This lab focuses on parallel programming using **MPI (Message Passing Interface)** for distributed computing and **CUDA (Compute Unified Device Architecture)** for GPU-based parallelism, primarily using C language.

## Course Objectives
The PCAP lab aims to:
- Teach different MPI APIs for point-to-point and collective communications, as well as error handling.
- Introduce CUDA programming for NVIDIA GPU cards, including host and kernel code development.
- Develop skills in designing and implementing parallel algorithms using various parallel programming environments.

## Lab Structure
The PCAP Lab consists of 12 labs, covering MPI and CUDA programming. This repository currently includes the following labs:

- [Lab 1: Introduction to MPI Execution Environment](lab-1/README.md)
- [Lab 2: Point-to-Point Communications in MPI](lab-2/README.md)
- [Lab 3: Collective Communications in MPI](lab-3/README.md)
- [Lab 4: Collective Communications and Error Handling in MPI](lab-4/README.md)

Each lab folder contains:
- A **README.md** file explaining the core concepts and objectives of the lab.
- **C programs** implementing the lab exercises.

## Getting Started
### Prerequisites
To compile and run the MPI and CUDA programs, you need:

- **MPI (Message Passing Interface)**
  - Install OpenMPI or MPICH
  - Use `mpicc` to compile MPI programs
  
- **CUDA Toolkit** (for CUDA labs)
  - Requires an NVIDIA GPU
  - Use `nvcc` to compile CUDA programs

### Running the Programs
1. Instructions for running MPI programs can be found in [Lab 1](lab-1/README.md).
2. Instructions for running CUDA programs can be found in [Lab 5](lab-5/README.md).

---
_This repository will be updated with more labs over time._

