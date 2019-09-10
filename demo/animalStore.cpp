#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>
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
    MPI_Status mystatus;
    int tag;
    int source;
    int weight;
    int animalType;

    MPI_Send(&rank,1,MPI_INT,(rank+1)%size,0,MCW);
    MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);


    if(rank==0){  // I am the animal salesperson
        for(int i=0;i<size-1;++i){
            MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG,MCW,&mystatus);
            tag = mystatus.MPI_TAG;
            source = mystatus.MPI_SOURCE;
            MPI_Recv(&weight,1,MPI_INT,source,tag,MCW,MPI_STATUS_IGNORE);
            if(tag==0){
                cout<<"sending a pig of weight "<<weight<<" to farmer "<<source<<".\n";
                animalType=0;
            }else{
                cout<<"sending a horse of weight "<<weight<<" to farmer "<<source<<".\n";
                animalType=1;
            }

            MPI_Send(&animalType,1,MPI_INT,source,0,MCW);

        }

    }else{        // I am a farmer
        sleep(rand()%5);
        if(!(rand()%2)){
            // I want a pig
            weight=rand()%30;
            cout<<"Farmer "<<rank<<" asked for a pig that weighs " << weight << "." <<endl;
            MPI_Send(&weight,1,MPI_INT,0,0,MCW);
        }else{
            // I want a horse
            weight=rand()%400;
            cout<<"Farmer "<<rank<<" asked for a horse that weighs " << weight << "." <<endl;
            MPI_Send(&weight,1,MPI_INT,0,1,MCW);

        }
                        
        MPI_Recv(&animalType,1,MPI_INT,0,0,MCW,MPI_STATUS_IGNORE);
        if(animalType==0){
            cout<<"Farmer "<<rank<<" received a pig that weighs " << weight << "." <<endl;
        }else{
            cout<<"Farmer "<<rank<<" received a horse that weighs " << weight << "." <<endl;
        }
    }

    MPI_Finalize();

    return 0;
}