#include "ComputationFramework.h"
#include "common.h"

ComputationFramework::ComputationFramework(std::string* fileIn, std::string* fileOut, CorrelationComputer* cc) {
    this->fileIn = fileIn;
    this->fileOut = fileOut;
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
    this->vcOut = new ValueContainer();
    if (this->fileOut != NULL) {
        this->fout = new std::ofstream(this->fileOut->c_str());
        // check result
        if (!this->fin->good()) {
            DEBUG_CERR << "File stream is not good! Failed opening output file '" << this->fileOut->c_str() << "'." << std::endl;
            throw std::runtime_error("Output file stream is not good.");
        }
    } else {
        this->fout = NULL;
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
    this->vcOut->setStreamsCount(this->vcIn->getStreamsCount()*this->vcIn->getStreamsCount());
    this->vcOut->setStreamsLength(this->corelComp->getOutputLength());
    if (this->fout != NULL) {
        this->vcOut->saveHeader(*fout);
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

ValueContainer* ComputationFramework::getOutputValues()
{
    return this->vcOut;
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
        //printf("ComputeBlock :: free column %d\n", colIndex);
    }
}

//==========================================================================
