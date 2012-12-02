#include "ComputationFramework.h"

ComputationFramework::ComputationFramework(std::string fileIn, std::string fileOut, CorrelationComputer* cc) {
    this->fileIn = new std::string(fileIn);
    this->fileOut = new std::string(fileOut);
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
    
    // prepare a universal data container for data output
    this->vcOut = new ValueContainer();
    if (this->fileOut != NULL) {
        this->fout = new std::ofstream(this->fileOut->c_str());
    } else {
        this->fout = NULL;
    }
    
    // load header
    this->vcIn->loadHeader(*fin);
    
    // compute result header and save it
    this->vcOut->setStreamsCount(this->vcIn->getStreamsCount()*this->vcIn->getStreamsCount());
    this->vcOut->setStreamsLength(this->vcIn->getStreamsLength());
    if (this->fout != NULL) {
        this->vcOut->saveHeader(*fout);
    }
    
    // size of a block
    // TODO: magically guess - based on StreamsLength and available memory
    this->blockHeight = 80;
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
    if (fout != NULL) {
        fout->close();
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
    this->activeBlock++;
    return this->activeBlock < this->getBlocksCount();
    
    // callback
    this->onNextBlock();
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

void ComputationFramework::computeBlock(int blockNum)
{
    // prepare state information
    int startPos = ((blockNum % corelWidth) + (blockNum / corelWidth) * corelWidth * blockHeight);
    int colIndex = blockNum % corelWidth; 
    int blockStartIndex = blockNum / corelWidth;
    
    // change of rows?
    if (this->previousBlock < 0 || (blockNum / corelWidth) != (this->previousBlock / corelWidth)) {
        // free previous rows and load new rows
        for (int y = 0; y < blockHeight; y++) {
            int prevIndex = (this->previousBlock / corelWidth) * blockHeight + y;
            int curIndex = (blockNum / corelWidth) * blockHeight + y;
            if (prevIndex >= 0 && prevIndex < corelWidth) {
                this->vcIn->freeStream(prevIndex);
            }
            if (curIndex < corelWidth) {
                this->vcIn->loadStream(curIndex, *fin);
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
        ValueStream* vs = corelComp->computePair(one, two);

        // save output
        int resultPos = startPos + y*corelWidth;
        // callback
        this->onResultComputed(resultPos, vs);
        this->vcOut->setStream(resultPos, vs);
        if (this->fout != NULL) {
            this->vcOut->saveStream(resultPos, *fout);
        }
        this->vcOut->freeStream(resultPos);
    }

    // free column stream
    if (colIndex < blockStartIndex || colIndex >= blockStartIndex + blockHeight) {
        this->vcIn->freeStream(colIndex);
    }
}

//==========================================================================
