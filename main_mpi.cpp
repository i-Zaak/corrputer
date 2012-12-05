#ifdef MAIN_CORRELATOR_MPI

#include "mpi/common.h"
#include "mpi/api.h"

#include "CrossCorrelationComputer.h"
#include "DistributedComputationFramework.h"

int mpiRank;
int mpiSize;

int blocks;
CorrelationComputer* corelComp;
DistributedComputationFramework* framework;

/*
 * 
 */
int main(int argc, char** argv)
{
    // MPI init
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    
    // TODO: incorporate command line arguments
    std::string fileIn("montazr11.vc");
    
    // corel init
    corelComp = new CrossCorrelationComputer();
        
    /*corelComp->setTauMax(10);
    corelComp->setWindowSize(100);
    corelComp->setSubpartLength(1000);*/
    
    corelComp->setTauMax(1000);
    corelComp->setWindowSize(1000);
    corelComp->setSubpartLength(100000);
    
    // framework init
    framework = new DistributedComputationFramework(&fileIn, corelComp);
    framework->open();
    
    // number of blocks
    blocks = framework->getBlocksCount();
    
    // info print
    if (mpiRank == 0) {
        MPI_COUT << "Input file: " << fileIn << std::endl;
        MPI_COUT << "Number of processes: " << mpiSize << std::endl;
        MPI_COUT << "Number of blocks: " << blocks << std::endl;
        MPI_COUT << "Number of streams: " << framework->getInputValues()->getStreamsCount() << std::endl;
        MPI_COUT << "Length of streams: " << framework->getInputValues()->getStreamsLength() << std::endl;
    }
    
    // fork processes
    switch (mpiRank) {
        case 0:
            runCoordinator();
            break;
        case 1:
            runSaver();
            break;
        default:
            runWorker();
            break;
    }
    
    framework->close();
    
    MPI_Finalize();
    
    return 0;
}
#endif

