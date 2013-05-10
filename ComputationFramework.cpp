#include "ComputationFramework.h"
#include "common.h"
#include "mpi/common.h"
#include "mpi/api.h"

ComputationFramework::ComputationFramework(std::string* fileIn, std::vector<std::string*> filesOut, CorrelationComputer* cc) {
    this->fileIn = fileIn;
    this->filesOut = filesOut;
    this->fouts = std::vector<std::ofstream*>(filesOut.size());
    this->corelComp = cc;
}

ComputationFramework::ComputationFramework(const ComputationFramework& orig) {
}

ComputationFramework::~ComputationFramework() {
}

//==========================================================================

void ComputationFramework::open()
{
    // prepare a universal data container for data input
    this->vcIn = new ValueContainer();
    this->fin = new std::ifstream(this->fileIn->c_str());
    
    // check for input file problems
    if (!this->fin->good()) {
        char curPath[FILENAME_MAX];
        getcwd(curPath, FILENAME_MAX);
        DEBUG_CERR << "File stream is not good! Failed opening input file '"
                << this->fileIn->c_str() << "' from dir '"
                << curPath << "'." << std::endl;
        throw std::runtime_error("Input file stream is not good.");
    }
    
    // prepare a universal data container for data output
    this->vcOuts = std::vector<ValueContainer*>(this->corelComp->getOutsNumber());
    for(int i=0; i<this->corelComp->getOutsNumber(); i++)
    {
        this->vcOuts[i] = new ValueContainer();
        if (this->filesOut[i] != NULL) {
            this->fouts[i] = new std::ofstream(this->filesOut[i]->c_str());
            // check result
            if (!this->fouts[i]->good()) {
                DEBUG_CERR << "File stream is not good! Failed opening output file '" << this->filesOut[i]->c_str() << "'." << std::endl;
                throw std::runtime_error("Output file stream is not good.");
            }
        } else {
            this->fouts[i] = NULL;
        }
    }
    
    // load header
    this->vcIn->loadHeader(*fin);
    
    // size of a block
    // TODO: magically guess - based on StreamsLength and available memory
    this->blockHeight = 50;
    this->corelWidth = this->vcIn->getStreamsCount();
    
    // limit block height
    if (this->blockHeight > this->corelWidth) {
        // all the streams can be loaded at once
        this->blockHeight = this->corelWidth;
    }
    
    // prepare blocks configuration
    this->blocksInCol = (this->corelWidth + this->blockHeight-1) / this->blockHeight;
    this->blocksCount = this->blocksInCol * this->corelWidth;
    
    // assign input VC to the correlation computer
    this->corelComp->setData(this->vcIn);
    
    // init correlation computer - everything should be configured by now
    this->corelComp->init();
    
    // compute result header and save it
    for(int i=0; i<this->corelComp->getOutsNumber(); i++)
    {
        this->vcOuts[i]->setStreamsCount(this->vcIn->getStreamsCount()*this->vcIn->getStreamsCount());
        this->vcOuts[i]->setStreamsLength(this->corelComp->getOutputLength());
        if (this->fouts[i] != NULL) {
            this->vcOuts[i]->saveHeader(*fouts[i]);
        }
    }
    
    
    // state init
    this->activeBlock = 0;
    this->previousBlock = -1;
    
    // callback
    this->onOpen();
}

//==========================================================================

void ComputationFramework::close()
{
    // callback
    this->onClose();
    
    if (fin != NULL) {
        fin->close();
    }
    for(int i=0; i<this->corelComp->getOutsNumber(); i++)
    {
        if (fouts[i] != NULL) {
            fouts[i]->close();
        }
    }

}
//==========================================================================

int ComputationFramework::getBlocksCount()
{
    return this->blocksCount;
}

//==========================================================================

int ComputationFramework::getActiveBlock()
{
    return this->activeBlock;
}

//==========================================================================

void ComputationFramework::setActiveBlock(int num)
{
    this->activeBlock = num;
}

//==========================================================================

bool ComputationFramework::nextBlock()
{
    this->activeBlock = (this->activeBlock + 1) % this->blocksCount;
    
    // callback
    this->onNextBlock();
    
    return this->activeBlock > 0;
}

//==========================================================================

void ComputationFramework::compute()
{
    // callback
    this->beforeCompute();
    
    this->computeBlock(this->activeBlock);
    
    // callback
    this->afterCompute();
}

//==========================================================================

ValueContainer* ComputationFramework::getInputValues()
{
    return this->vcIn;
}

//==========================================================================

std::vector<ValueContainer*> ComputationFramework::getOutputValues()
{
    return this->vcOuts;
}

//==========================================================================

void ComputationFramework::computeBlock(int blockNum)
{
    // prepare state information
    int startPos = ((blockNum % corelWidth) + (blockNum / corelWidth) * corelWidth * blockHeight);
    int colIndex = blockNum % corelWidth; 
    int blockStartIndex = blockNum / corelWidth * blockHeight;
    
    //printf("ComputeBlock %d\n", blockNum);
    // change of rows?
    if (this->previousBlock < 0 || (blockNum / corelWidth) != (this->previousBlock / corelWidth)) {
        //printf("Changing row: %d --> %d\n", previousBlock, blockNum);
        // free previous rows and load new rows
        for (int y = 0; y < blockHeight; y++) {
            int prevIndex = (this->previousBlock / corelWidth) * blockHeight + y;
            int curIndex = (blockNum / corelWidth) * blockHeight + y;
            if (previousBlock >= 0 && prevIndex >= 0 && prevIndex < corelWidth) {
                this->vcIn->freeStream(prevIndex);
                //printf("ComputeBlock :: free %d\n", prevIndex);
            }
            if (curIndex < corelWidth) {
                this->vcIn->loadStream(curIndex, *fin);
                //printf("ComputeBlock :: load %d\n", curIndex);
            }
        }
    }
    
    // save the block number for later calls
    this->previousBlock = blockNum;
        
    // does this block contain any combination worth computing?
    if (blockStartIndex > colIndex) {
        // nothing would be computed
        return;
    }
        
    // prepare column stream
    if (colIndex < blockStartIndex || colIndex >= blockStartIndex + blockHeight) {
        // load only if this stream is not already loaded
        this->vcIn->loadStream(colIndex, *fin);
        //printf("ComputeBlock :: load column %d\n", colIndex);
    }
        
    // <-- now all the required streams are loaded
            
    // process block
    for (int y = 0; y < blockHeight; y++) {
        // compute correlation
        int one = blockStartIndex + y;
        int two = colIndex;
        if (one >= corelWidth) {
            // we fell down from the correlation matrix!
            break;
        }
        if (one == two) {
            // TODO: fake stream of 1.0s?
            continue;
        } else if (one > two) {
            // only half of the matrix is really computed
            continue;
        }
        std::vector<ValueStream*> vs = corelComp->computePair(one, two);

        // save output
        int resultPos = startPos + y*corelWidth;
        // callback
        this->onResultComputed(resultPos, vs);
        for(int i=0; i < this->corelComp->getOutsNumber(); i++)
        {
            this->vcOuts[i]->setStream(resultPos, vs[i]);
            if (this->fouts[i] != NULL) {
                this->vcOuts[i]->saveStream(resultPos, *fouts[i]);
            }
            this->vcOuts[i]->freeStream(resultPos);
        }
    }

    // free column stream
    if (colIndex < blockStartIndex || colIndex >= blockStartIndex + blockHeight) {
        this->vcIn->freeStream(colIndex);
        //printf("ComputeBlock :: free column %d\n", colIndex);
    }
}

//==========================================================================
