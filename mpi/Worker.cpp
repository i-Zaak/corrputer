#include "common.h"

#include <unistd.h>

void runWorker()
{
    MPI_PRINTF("Worker starting.\n");
    
    // distribute starting blocks evenly among the workers
    int workersCount = mpiSize - 2;
    int workerId = mpiRank - 2;
    framework->setActiveBlock(framework->getBlocksCount() / workersCount * workerId);
    
    // worker loop
    while (true) {
        // request a block reservation
        int reserve = framework->getActiveBlock();
        MPI_COUT << "Worker wants: " << reserve << std::endl;
        MPI_Send(&reserve, 1, MPI_INT, 0, MPI_TAG_RESERVEBLOCK, MPI_COMM_WORLD);
        
        // wait for a reservation result
        MPI_Status status;
        MPI_Recv(&reserve, 1, MPI_INT, MPI_ANY_SOURCE, MPI_TAG_RESERVEBLOCK, MPI_COMM_WORLD, &status);
        MPI_COUT << "Worker got: " << reserve << std::endl;
        
        // termination?
        if (reserve < 0) {
            break;
        }
        
        // forward active block to our framework
        framework->setActiveBlock(reserve);

        // TODO: compute!
        framework->compute();
        
        // TODO: output data
        MPI_COUT << "Worker outputting: " << reserve << std::endl;
        
        // move to another block
        framework->nextBlock();
    }
    
    // done!
    MPI_PRINTF("Worker finished.\n");
}
