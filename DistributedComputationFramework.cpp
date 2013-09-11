#include <stdexcept>
#include <cstring>

#include "DistributedComputationFramework.h"
#include "common.h"

DistributedComputationFramework::DistributedComputationFramework(std::string* fileIn, std::vector<std::string*> filesOut, CorrelationComputer* cc) : ComputationFramework(fileIn, filesOut, cc) {
}

DistributedComputationFramework::~DistributedComputationFramework() {
}

void DistributedComputationFramework::onResultComputed(int index, std::vector<ValueStream*> vs)
{
    /*
     * This code will be always performed on the Worker node - no other process
     * uses this framework to actually compute streams.
     */
    
    // create block part
    BlockPart* part = new BlockPart();
    part->index = index;
    part->values = std::vector<ValueStream*>(vs.size());
    for(int i=0; i<this->corelComp->getOutsNumber(); i++)
    {
        part->values[i] = new ValueStream(*vs[i]);
    }
    
    // add it to the list
    this->blockParts.push_back(part);
}

void DistributedComputationFramework::exportBlockData(char** buffer, int* size)
{
    //int streamLength = this->vcOut->getStreamsLength();
    int streamLengths = 0;
    for(int i=0; i<this->corelComp->getOutsNumber(); i++)
    {
        streamLengths += this->vcOuts[i]->getStreamsLength();
    }

    int partSize = sizeof(int) + streamLengths * sizeof(float);
    
    // allocate exported memory chunk
    (*size) = sizeof(int) + partSize * this->blockParts.size();
    (*buffer) = new char[*size];
    
    //printf("Export size: %d\n", *size);
    //printf("Exporting parts: %d\n", this->blockParts.size());
    
    // write number of parts
    unsigned int parts = this->blockParts.size();
    memcpy(*buffer, &parts, sizeof(int));
    
    // prepare pointer to memory region
    char* data = &(*buffer)[sizeof(int)];
    
    // export every block
    for (unsigned int i = 0; i < parts; i++) {
        BlockPart* part = this->blockParts[i];
        // copy memory
        //int mempos = (sizeof(int) + this->vcOut->getStreamsLength() * sizeof(float)) * i;
        int mempos = (partSize) * i;
        memcpy(&data[mempos], &part->index, sizeof(int));
        //memcpy(&data[mempos + sizeof(int)], &(*part->values)[0], partSize - sizeof(int));
        mempos += sizeof(int);
        for(int j=0; j<this->corelComp->getOutsNumber(); j++) {
            int datalen = this->vcOuts[j]->getStreamsLength() * sizeof(float);
            memcpy(&data[mempos], &(*part->values[j])[0], datalen);
            mempos += datalen;
        }
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
    //int streamLength = this->vcOut->getStreamsLength();
    //int partSize = sizeof(int) + streamLength * sizeof(float);
    
    int streamLengths = 0;
    for(int i=0; i<this->corelComp->getOutsNumber(); i++)
    {
        streamLengths += this->vcOuts[i]->getStreamsLength();
    }

    int partSize = sizeof(int) + streamLengths * sizeof(float);

    if ((size - sizeof(int)) % partSize != 0) {
        throw std::runtime_error("Buffer does not have the expected size.");
    }
    
    // read number of parts
    unsigned int parts = 0;
    memcpy(&parts, buffer, sizeof(int));
    if (parts != (size - sizeof(int)) / partSize) {
        DEBUG_CERR << "Based on buffer size: " << (size - sizeof(int)) / partSize
                << " ; Reported: " << parts << std::endl;
        throw std::runtime_error("Reported number of parts does not match buffer size.");
    }
    
    // prepare pointer to memory region
    char* data = &buffer[sizeof(int)];
    
    for (unsigned int i = 0; i < parts; i++) {
        //int mempos = (sizeof(int) + streamLength * sizeof(float)) * i;
        int mempos = (partSize) * i;
        int index;
        memcpy(&index, &data[mempos], sizeof(int));
        mempos += sizeof(int);
        for(int j=0; j < this->corelComp->getOutsNumber(); j++)
        {
            float* values = (float*)&data[mempos];
            // create and insert value stream
            ValueStream* stream = new ValueStream();
            int streamLength = this->vcOuts[j]->getStreamsLength();
            stream->reserve(streamLength);
            stream->assign(values, values + streamLength);
			mempos+=streamLength * sizeof(float);
            this->vcOuts[j]->setStream(index, stream);
            // if we have a file to write to, output and free the memory
            if (this->fouts[j] != NULL) {
                this->vcOuts[j]->saveStream(index, *this->fouts[j]);
                this->vcOuts[j]->freeStream(index);
            } // else: keep the stream in memory
        }
    }
}
