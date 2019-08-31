#include <iostream>
#include <ctime>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

/*
    This program uses MPI to simulate Time Bomb, a childhood favorite game of Dr. Watson. This game consists of a process generating the Time Bomb with a randomly initialized countdown timer, then passing the bomb to another randomly selected process. That process will decrement the timer, then pass the bomb again. Once the timer reaches zero, the bomb explodes, and the process holding the bomb is declared "The Loser". In this setting, the game will end and all processes terminate.
*/
int main(int argc, char** argv){
    int rank, size, data, timer;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    srand(time(NULL) + rank);

    if (rank == rand() % size) {
        // initialize time bomb
    }
    //     int dest = rank;
    //     if(rand()%2)dest+=1;else dest-=1;
    //     MPI_Send(&rank,1,MPI_INT,dest,0,MCW);

    while(1){
        MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);

        if(timer==0) {
            std::cout << "Process " << rank << " is The Loser!!!\n";
            break;
        }

    //     int poisonPill=-1;

    //     if(!(rand()%8)){
    //         cout<<"aughhhhhh!\n";
    //         for(int i=0;i<size;++i){
    //             MPI_Send(&poisonPill,1,MPI_INT,i,0,MCW);
    //         }
        
    //     } else {
                    
    //         int dest = rank;
    //         if(rand()%2)dest+=1;else dest-=1;
    //         if(dest<0)dest=1;
    //         if(dest>=size)dest=size-2;
    //         MPI_Send(&rank,1,MPI_INT,dest,0,MCW);
    //     }
    // }

    MPI_Finalize();

    return 0;
} // main