#ifndef COMPUTATIONFRAMEWORK_H
#define	COMPUTATIONFRAMEWORK_H

#include <string>
#include "CorrelationComputer.h"
#include "ValueStream.h"

/**
 * Correlation computation framework.
 * 
 * Handles data loading and saving, manages associated resources.
 * The goal is to allow a simple instantiation of a class extending this
 * abstract framework, setting data input and output plus an instantiated
 * correlation computer and let it compute all / some of the blocks.
 * All the resource management and block operations should be encapsulated here.
 */
class ComputationFramework {
public:
    ComputationFramework(std::string* fileIn, std::vector<std::string*> filesOut, CorrelationComputer* cc);
    ComputationFramework(const ComputationFramework& orig);
    virtual ~ComputationFramework();
    
    /**
     * Ready the class, files and memory.
     */
    void open();
    
    /**
     * Release previously opened resources.
     */
    void close();
    
    /**
     * Returns number of blocks to be computed.
     * 
     * @return Number of blocks.
     */
    int getBlocksCount();
    
    /**
     * Returns the number of the currently active block (the one that would be
     * computed if the method compute() were to be executed).
     */
    int getActiveBlock();
    
    /**
     * Sets the active block that shall be computed next.
     * 
     * @param num Block number.
     */
    void setActiveBlock(int num);

    /**
     * Moves the "active block" counter by one.
     * 
     * @return Is there a block left to be computed?
     */
    bool nextBlock();
    
    /**
     * Performs a correlation computation on a currently active block.
     */
    void compute();
    
    /**
     * Returns the input value container.
     * 
     * @return 
     */
    ValueContainer* getInputValues();
    
    /**
     * Returns the output value container.
     * 
     * @return 
     */
    std::vector<ValueContainer*> getOutputValues();
    
protected:
    // configuration
    int activeBlock;
    int previousBlock;
    int blockHeight;
    
    ValueContainer* vcIn;
    std::vector<ValueContainer*> vcOuts;
    
    std::string* fileIn;
    std::vector<std::string*> filesOut;
    
    std::ifstream* fin;
    std::vector<std::ofstream*> fouts;
    
    CorrelationComputer* corelComp;
    
    // derived values
    int corelWidth;
    int blocksInCol;
    int blocksCount;
    
    virtual void onOpen() {};
    virtual void onClose() {};
    
    virtual void onNextBlock() {};
    
    virtual void beforeCompute() {};
    virtual void afterCompute() {};
    virtual void onResultComputed(int index, std::vector<ValueStream*> vs) {};
    
    void computeBlock(int blockNum);
    
private:

    
};

#endif	/* COMPUTATIONFRAMEWORK_H */

