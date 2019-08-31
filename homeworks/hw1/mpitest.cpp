#include <iostream>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

/*
    A program that has each process send its rank number to process rank+1%size, then prints out both its rank as well as the data it received
*/
int main(int argc, char** argv){
    int rank, size, data;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    MPI_Send(&rank, 1, MPI_INT, (rank+1)%size, 0, MCW);
    MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);

    std::cout << "Process of rank " << rank << ", received from process of rank " << data << std::endl;

    MPI_Finalize();

    return 0;
} // main