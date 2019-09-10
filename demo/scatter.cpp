#include <iostream>
#include <mpi.h>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD

using namespace std;

int main(int argc, char **argv){

    int rank, size;
    int data;
    int bigdata[16];
    int lildata[4];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 

    for(int i=0;i<16;++i)bigdata[i]=100+i;
    for(int j=0;j<4;++j)lildata[j]=rank*10+j;

    MPI_Scatter(bigdata, 4, MPI_INT, lildata, 4, MPI_INT, 0, MCW);

    cout<<"p"<<rank<<":"<<lildata[0]<<" "<<lildata[1]<<" "<<lildata[2]<<" "<<lildata[3]<<" "<<endl;


    MPI_Finalize();

    return 0;
}