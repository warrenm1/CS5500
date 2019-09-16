#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <ctime>

#define MCW MPI_COMM_WORLD

int main(int argc, char **argv){
    srand(time(NULL));

    int rank, size, data, timer;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 

    int temp = rand()%size;

    if(rank == temp) {
        int dest = rand()%size;
        while (dest == rank) {
            dest = rand()%size;
        }
        timer = rand()%60;

        std::cout << 
        "*****************\n" <<
        "*** Time Bomb ***\n" <<
        "*****************\n\n";

        sleep(1);
        std::cout << timer << " seconds on the clock\n\n";
        sleep(1);
        std::cout << "Ready...\n";
        sleep(1);
        std::cout << "Set...\n";
        sleep(1);
        std::cout << "GO!!!\n\n";

        MPI_Send(&timer, 1, MPI_INT, dest, 0, MCW);
    }


    while(1){
        MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);

        if(data == -1) {
            break;
        }

        sleep(1);

        std::cout << "Process " << rank << ": " << data << " seconds\n";

        int gameOver=-1;

        if(data == 0) {
            std::cout << 
            "\n*********************\n" << 
            "***** BOOOOM!!! *****\n" <<
            "*********************\n"<< 
            "\nProcess " << rank << " is The LOSER\n";
            
            for(int i=0; i<size; ++i) {
                MPI_Send(&gameOver, 1, MPI_INT, i, 0, MCW);
            }
        } else {    
            int dest = rand()%size;    
            while (dest == rank) {
                dest = rand()%size;
            }
            data--;
            
            MPI_Send(&data, 1, MPI_INT, dest, 0, MCW);
        }
    }

    MPI_Finalize();

    return 0;
}