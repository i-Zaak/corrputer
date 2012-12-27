#include "common.h"

/**
 * Queue of blocks data in the form of buffer+size.
 */
typedef std::pair< char*, int > BlocksQueueEntry;
typedef std::vector< BlocksQueueEntry* > BlocksQueue;

/**
 * Data structure for exchanging job description used by the Writer task.
 */
typedef struct {
    int blocksCount;
    BlocksQueue* queue;
    pthread_mutex_t queueLock;
} WriterJob;

/**
 * Writer thread.
 */
void* runWriter(void* arg);

//======================================================================

void runSaver()
{   
    MPI_PRINTF("Saver starting.\n");
    
    // fork the Writer task
    WriterJob* writerJob = new WriterJob;
    writerJob->blocksCount = blocks;
    writerJob->queue = new BlocksQueue;
    pthread_mutex_init(&writerJob->queueLock, NULL);
    
    pthread_t thread;
    pthread_create(&thread, NULL, runWriter, writerJob);
    
    // handle output requests
    MPI_Status status;
    for (int processed = 0; processed < blocks; processed++) {
        // wait for a Prepare! request
        int msgSize = 0;
        MPI_Recv(&msgSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_TAG_PREPAREBLOCK, MPI_COMM_WORLD, &status);
        
        // reserve memory block based on the request
        char* msg = (char*)malloc(msgSize);
        
        // wait for an Output! command with data from the previous sender
        MPI_Recv(msg, msgSize, MPI_BYTE, status.MPI_SOURCE, MPI_TAG_OUTPUTBLOCK, MPI_COMM_WORLD, &status);
        
        MPI_PRINTF("Saver received %1.6f MB of data from N%02d.\n", msgSize / (1024.0f * 1024.0f), status.MPI_SOURCE);
        
        // forward data to Writer process
        pthread_mutex_lock(&writerJob->queueLock);
        // <CRITICAL_SECTION>
        writerJob->queue->push_back(new BlocksQueueEntry(msg, msgSize));
        // </CRITICAL_SECTION>
        pthread_mutex_unlock(&writerJob->queueLock);
        
        MPI_PRINTF("Global progress: %3d%\n", processed * 100 / (blocks-1));
    }
    
    // join the Writer task again
    pthread_join(thread, NULL);
    
    // done!
    MPI_PRINTF("Saver finished.\n");
}

//======================================================================

void* runWriter(void* arg)
{
    WriterJob* job = (WriterJob*)arg;
    
    for (int block = 0; block < job->blocksCount; block++) {
        // busy-wait for data in the job queue
        BlocksQueueEntry* entry = NULL;
        do {
            pthread_mutex_lock(&job->queueLock);
            // <CRITICAL_SECTION>
            if (job->queue->size() > 0) {
                entry = job->queue->back();
                job->queue->pop_back();
            }
            // </CRITICAL_SECTION>
            pthread_mutex_unlock(&job->queueLock);
            
            // sleep if no joy
            if (entry == NULL) {
                // wait 100 000 us = 100 ms
                usleep(100000);
            }
        } while (entry == NULL);
        
        // import the data
        framework->importBlockData(entry->first, entry->second);
        //MPI_COUT << "Writer: block #" << block << " - import complete." << std::endl;
        
        // free memory allocated in the Saver thread
        free(entry->first);
        delete entry;
    }
    
    return NULL;
}