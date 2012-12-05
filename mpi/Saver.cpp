#include "common.h"

void runSaver()
{   
    MPI_PRINTF("Saver starting.\n");
    // TODO: unignore this process
    MPI_PRINTF("Saver finished.\n");
    return;
    
    // compute size of data that is to be received
    int outputSize = (framework->getInputValues()->getStreamsLength() * sizeof(float));
    int outputMsgSize = outputSize + sizeof(int);
    
    // handle output requests
    MPI_Status status;
    char* msg = (char*)malloc(outputMsgSize);
    for (int processed = 0; processed < blocks; processed++) {
        // wait for a request
        MPI_Recv(msg, outputMsgSize, MPI_BYTE, MPI_ANY_SOURCE, MPI_TAG_OUTPUTBLOCK, MPI_COMM_WORLD, &status);
        
        // TODO: forward data to Writer process
    }
    
    // done!
    MPI_PRINTF("Saver finished.\n");
}
