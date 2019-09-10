#include <iostream>
#include <mpi.h>
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
    MPI_Request myrequest;
    MPI_Status mystatus;
    int myflag;
    double time0, time1;

    
    time0=MPI_Wtime();
    if(!rank){
        MPI_Irecv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,&myrequest);
        for(int i=0;i<5;++i){
            MPI_Test(&myrequest, &myflag, &mystatus);
            if(myflag) break;
            cout<<"Still waiting for the passport...\n";
            sleep(1);
        }
        if(myflag){
            cout<<"passport arrived! I'm off!\n";
        }else{
            cout<<"time to call my congressperson...\n";
            MPI_Wait(&myrequest,&mystatus);
            cout<<"passport arrived! I'm off!\n";
        }
    }else{
        sleep(10);
        MPI_Send(&rank,1,MPI_INT,0,0,MCW);
        cout<<"UPS person delivered the passport successfully.\n";
    }
    time1=MPI_Wtime();

    if(!rank)cout<<"Time needed: "<<time1-time0<<endl;


    MPI_Finalize();

    return 0;
}