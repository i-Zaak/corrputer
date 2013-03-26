#include "mpi/common.h"
#include "mpi/api.h"

#include "CrossCorrelationComputer.h"
#include "DistributedComputationFramework.h"

#include "ConfigFile.h"
#include "CoherenceCorrelationComputer.h"

int mpiRank;
int mpiSize;

int blocks;
CorrelationComputer* corelComp;
DistributedComputationFramework* framework;

// correlation config file sections
#define CONFIG_SECTION_INPUT "Input"
#define CONFIG_SECTION_OUTPUT "Output"
#define CONFIG_SECTION_CORRELATION "Correlation"

// metadata file sections
#define META_SECTION_SOURCE "Source"

#ifdef MAIN_CORRELATOR_MPI

/**
 * Main wrapper so we can catch exceptions.
 */
int run(int argc, char** argv)
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
    
    std::string metadataInFilename(fileIn);
    metadataInFilename.append("m");
    ConfigFile configMeta(metadataInFilename);
    
    // Saver process has file output
    std::string outputFilename = config.Value(CONFIG_SECTION_OUTPUT, "filename");
    if (mpiRank == 1) {
        fileOut = new std::string(outputFilename);
    }
    
    // corel init
    std::string correlType(config.Value(CONFIG_SECTION_CORRELATION, "type").c_str());
    // based on type from the config
    if (correlType.compare("Cross") == 0) {
        corelComp = new CrossCorrelationComputer();
    } else if (correlType.compare("Coherence") == 0) {
        corelComp = new CoherenceCorrelationComputer();
    } else {
        std::cerr << "Unknown correlation type: " << correlType << std::endl;
        MPI_Finalize();
        return 2;
    }
    
    // common correlation configuration
    corelComp->setTauMax(atoi(config.Value(CONFIG_SECTION_CORRELATION, "tau_max").c_str()));
    corelComp->setWindowSize(atoi(config.Value(CONFIG_SECTION_CORRELATION, "window_size").c_str()));
    corelComp->setStepSize(atoi(config.Value(CONFIG_SECTION_CORRELATION, "window_step").c_str()));
    corelComp->setSubpartStart(atoi(config.Value(CONFIG_SECTION_CORRELATION, "subpart_start", "0").c_str()));
    corelComp->setSubpartLength(atoi(config.Value(CONFIG_SECTION_CORRELATION, "subpart_length", "0").c_str()));
    
    corelComp->setSampleInterval(atof(configMeta.Value(META_SECTION_SOURCE, "sampleInterval").c_str()));
    
    // type-specific
    if (correlType.compare("Coherence") == 0) {
        CoherenceCorrelationComputer* coherenceComp = (CoherenceCorrelationComputer*) corelComp;
        coherenceComp->setFrequencyRangeBegin(atof(config.Value(CONFIG_SECTION_CORRELATION, "frequency_from", "0").c_str()));
        coherenceComp->setFrequencyRangeEnd(atof(config.Value(CONFIG_SECTION_CORRELATION, "frequency_to", "0").c_str()));
    }
    
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
    
    // metadata file create
    if (mpiRank == 1) {
        std::string metadataOutFilename(outputFilename);
        metadataOutFilename.append("m");
        
        // copy original metadata
        std::ifstream mIn(metadataInFilename.c_str());
        if (mIn.fail()) {
            MPI_COUT << "Failed reading metadata file '" << metadataInFilename << "', output metadata file will not be created." << std::endl;
        } else {
            std::ofstream mOut(metadataOutFilename.c_str());
            mOut << mIn.rdbuf();
            mIn.close();

            // append correlation metadata
            mOut << std::endl << "[Correlation]" << std::endl;
            mOut << "type = " << correlType << std::endl;
            mOut << "streamsCount = " << framework->getOutputValues()->getStreamsCount() << std::endl;
            mOut << "streamsLength = " << framework->getOutputValues()->getStreamsLength() << std::endl;
            mOut << "tauMax = " << corelComp->getTauMax() << std::endl;
            mOut << "windowSize = " << corelComp->getWindowSize() << std::endl;
            mOut << "windowStep = " << corelComp->getStepSize() << std::endl;
            mOut << "subpartStart = " << corelComp->getSubpartStart() << std::endl;
            mOut << "subpartLength = " << corelComp->getSubpartLength() << std::endl;

            mOut.close();
        }
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


int main(int argc, char** argv)
{
    try {
        return run(argc, argv);
    } catch (char const* text) {
        MPI_COUT << " !!! Exception !!! " << std::endl;
        MPI_COUT << text << std::endl;
        MPI_COUT << " !!! Exception !!! " << std::endl;
        
        MPI_CERR << "Exception: " << text << std::endl;
    }
    
    MPI_Finalize();
    
    return 666;
}

#endif

