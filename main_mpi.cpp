#include "mpi/common.h"
#include "mpi/api.h"

#include "CrossCorrelationComputer.h"
#include "DistributedComputationFramework.h"

#include "ConfigFile.h"

int mpiRank;
int mpiSize;

int blocks;
CorrelationComputer* corelComp;
DistributedComputationFramework* framework;

#define CONFIG_SECTION_INPUT "Input"
#define CONFIG_SECTION_OUTPUT "Output"
#define CONFIG_SECTION_CORRELATION "Correlation"

#ifdef MAIN_CORRELATOR_MPI

/*
 * 
 */
int main(int argc, char** argv)
{
    // MPI init
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    
    // load configuration file
    if (argc != 2) {
        if (mpiRank == 0) {
            std::cerr << "Usage: config_file" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    ConfigFile config(argv[1]);
    
    std::string fileIn(config.Value(CONFIG_SECTION_INPUT, "filename"));
    std::string* fileOut = NULL;
    
    // Saver process has file output
    std::string outputFilename = config.Value(CONFIG_SECTION_OUTPUT, "filename");
    if (mpiRank == 1) {
        fileOut = new std::string(outputFilename);
    }
    
    // corel init
    // TODO: type based on config
    corelComp = new CrossCorrelationComputer();
    
    corelComp->setTauMax(atoi(config.Value(CONFIG_SECTION_CORRELATION, "tau_max").c_str()));
    corelComp->setWindowSize(atoi(config.Value(CONFIG_SECTION_CORRELATION, "window_size").c_str()));
    corelComp->setStepSize(atoi(config.Value(CONFIG_SECTION_CORRELATION, "window_step").c_str()));
    corelComp->setSubpartStart(atoi(config.Value(CONFIG_SECTION_CORRELATION, "subpart_start", "0").c_str()));
    corelComp->setSubpartLength(atoi(config.Value(CONFIG_SECTION_CORRELATION, "subpart_length", "0").c_str()));
    
    // framework init
    framework = new DistributedComputationFramework(&fileIn, fileOut, corelComp);
    framework->open();
    
    // number of blocks
    blocks = framework->getBlocksCount();
    
    // info print
    if (mpiRank == 0) {
        MPI_COUT << " --------------CONFIGURATION---------------- " << std::endl;
        MPI_COUT << "Input file: " << fileIn << std::endl;
        MPI_COUT << "Output file: " << outputFilename << std::endl;
        MPI_COUT << "Number of processes: " << mpiSize << std::endl;
        MPI_COUT << "Number of blocks: " << blocks << std::endl;
        MPI_COUT << "Number of streams: " << framework->getInputValues()->getStreamsCount() << std::endl;
        MPI_COUT << "Length of streams: " << framework->getInputValues()->getStreamsLength() << std::endl;
        MPI_COUT << "Number of output streams: " << framework->getOutputValues()->getStreamsCount() << std::endl;
        MPI_COUT << "Length of output streams: " << framework->getOutputValues()->getStreamsLength() << std::endl;
        MPI_COUT << "Tau max: " << corelComp->getTauMax() << std::endl;
        MPI_COUT << "Window size: " << corelComp->getWindowSize() << std::endl;
        MPI_COUT << "Window step: " << corelComp->getStepSize() << std::endl;
        MPI_COUT << " ------------------------------------------- " << std::endl;
    }
    
    // assert enough processes
    if (mpiSize < 3) {
        if (mpiRank == 0) {
            MPI_COUT << " !!! Not enough MPI nodes !!! " << std::endl;
        }
        MPI_Finalize();
        return 3;
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    
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

