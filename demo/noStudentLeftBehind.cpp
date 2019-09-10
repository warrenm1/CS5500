#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD

using namespace std;

int main(int argc, char **argv){

    int rank, size;
    int data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 
    srand(rank);

    sleep(rand()%10);
    MPI_Barrier(MCW);

    cout<<"I am "<<rank<<" of "<<size<<"; got a message from "<<data<<endl;

    MPI_Finalize();

    return 0;
}