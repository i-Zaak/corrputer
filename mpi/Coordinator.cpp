#include "common.h"

void runCoordinator()
{
    MPI_PRINTF("Coordinator starting.\n");
    
    // prepare reservations
    bool reserved[blocks];
    memset(reserved, 0, sizeof(bool) * blocks);
    
    // handle reservation requests
    MPI_Status status;
    for (int processed = 0; processed < blocks; processed++) {
        int reserve = -1;
        
        // wait for a reservation
        MPI_Recv(&reserve, 1, MPI_INT, MPI_ANY_SOURCE, MPI_TAG_RESERVEBLOCK, MPI_COMM_WORLD, &status);
        
        // find next free block
        while(reserved[reserve]) {
            reserve = (reserve+1) % blocks;
        }
        
        // reserve the block
        reserved[reserve] = true;
        
        // send back reservation
        MPI_Send(&reserve, 1, MPI_INT, status.MPI_SOURCE, MPI_TAG_RESERVEBLOCK, MPI_COMM_WORLD);
    }
    
    MPI_PRINTF("Coordinator --> Terminator.\n");
    
    // coordinator --> terminator (every block is done)
    int workers = mpiSize - 2;
    for (int terminated = 0; terminated < workers; terminated++) {
        int reserve = -1;
        
        // wait for a reservation
        MPI_Recv(&reserve, 1, MPI_INT, MPI_ANY_SOURCE, MPI_TAG_RESERVEBLOCK, MPI_COMM_WORLD, &status);
        
        // cancel reservation
        reserve = -1;
        
        // send back termination
        MPI_Send(&reserve, 1, MPI_INT, status.MPI_SOURCE, MPI_TAG_RESERVEBLOCK, MPI_COMM_WORLD);
    }
    
    // done!
    MPI_PRINTF("Coordinator finished.\n");
}
