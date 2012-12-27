#include <stdexcept>
#include <cstring>

#include "DistributedComputationFramework.h"
#include "common.h"

DistributedComputationFramework::DistributedComputationFramework(std::string* fileIn, CorrelationComputer* cc) : ComputationFramework(fileIn, NULL, cc) {
}

DistributedComputationFramework::~DistributedComputationFramework() {
}

void DistributedComputationFramework::onResultComputed(int index, ValueStream* vs)
{
    /*
     * This code will be always performed on the Worker node - no other process
     * uses this framework to actually compute streams.
     */
    
    // create block part
    BlockPart* part = new BlockPart();
    part->index = index;
    part->values = *vs;
    
    // add it to the list
    this->blockParts.push_back(part);
}

void DistributedComputationFramework::exportBlockData(char** buffer, int* size)
{
    int streamLength = this->vcOut->getStreamsLength();
    int partSize = sizeof(int) + streamLength * sizeof(float);
    
    // allocate exported memory chunk
    (*size) = sizeof(int) + partSize * this->blockParts.size();
    (*buffer) = new char[*size];
    
    //printf("Export size: %d\n", *size);
    //printf("Exporting parts: %d\n", this->blockParts.size());
    
    // write number of parts
    int parts = this->blockParts.size();
    memcpy(*buffer, &parts, sizeof(int));
    
    // prepare pointer to memory region
    char* data = &(*buffer)[sizeof(int)];
    
    // export every block
    for (unsigned int i = 0; i < parts; i++) {
        BlockPart* part = this->blockParts[i];
        // copy memory
        int mempos = (sizeof(int) + this->vcOut->getStreamsLength() * sizeof(float)) * i;
        memcpy(&data[mempos], &part->index, sizeof(int));
        memcpy(&data[mempos + sizeof(int)], &part->values[0], partSize - sizeof(int));
    }
    // free every block
    for (unsigned int i = 0; i < parts; i++) {
        BlockPart* part = this->blockParts[i];
        // free block part - no longer needed
        delete part;
    }
    this->blockParts.clear();
}

void DistributedComputationFramework::importBlockData(char* buffer, int size)
{
    int streamLength = this->vcOut->getStreamsLength();
    int partSize = sizeof(int) + streamLength * sizeof(float);
    if ((size - sizeof(int)) % partSize != 0) {
        throw std::runtime_error("Buffer does not have the expected size.");
    }
    
    // read number of parts
    int parts = 0;
    memcpy(&parts, buffer, sizeof(int));
    if (parts != (size - sizeof(int)) / partSize) {
        DEBUG_CERR << "Based on buffer size: " << (size - sizeof(int)) / partSize
                << " ; Reported: " << parts << std::endl;
        throw std::runtime_error("Reported number of parts does not match buffer size.");
    }
    
    // prepare pointer to memory region
    char* data = &buffer[sizeof(int)];
    
    for (int i = 0; i < parts; i++) {
        int mempos = (sizeof(int) + streamLength * sizeof(float)) * i;
        int index;
        memcpy(&index, &data[mempos], sizeof(int));
        float* values = (float*)&data[mempos + sizeof(int)];
        // create and insert value stream
        ValueStream* stream = new ValueStream();
        stream->reserve(streamLength);
        stream->assign(values, values + streamLength);
        this->vcOut->setStream(index, stream);
        //this->vcOut->saveStream(index, ???);
        //this->vcOut->freeStream(index);
    }
}
