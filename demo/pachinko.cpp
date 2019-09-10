#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <ctime>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD

using namespace std;

int main(int argc, char **argv){

    int rank, size;
    int data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 
    srand(time(NULL)+rank);

    if(rank==3){
        for(int i=0;i<rank;++i)cout<<"    ";
        cout << "*" << endl;
        int dest = rank;
        if(rand()%2)dest+=1;else dest-=1;
        MPI_Send(&rank,1,MPI_INT,dest,0,MCW);
    }


    while(1){
        MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);

        if(data==-1)break;

        sleep(1);

        for(int i=0;i<rank;++i)cout<<"    ";
        cout << "*" << endl;

        int poisonPill=-1;

        if(!(rand()%8)){
            cout<<"aughhhhhh!\n";
            for(int i=0;i<size;++i){
                MPI_Send(&poisonPill,1,MPI_INT,i,0,MCW);
            }
        
        } else {
                    
            int dest = rank;
            if(rand()%2)dest+=1;else dest-=1;
            if(dest<0)dest=1;
            if(dest>=size)dest=size-2;
            MPI_Send(&rank,1,MPI_INT,dest,0,MCW);
        }
    }


    MPI_Finalize();

    return 0;
}