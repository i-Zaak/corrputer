#ifndef DISTRIBUTEDCOMPUTATIONFRAMEWORK_H
#define	DISTRIBUTEDCOMPUTATIONFRAMEWORK_H

#include "ComputationFramework.h"

struct BlockPart
{
    int index;
    std::vector<ValueStream*> values;
};

/**
 * Distributed framework. Data output is disabled as there is a dedicated node
 * saving the computation results.
 */
class DistributedComputationFramework : public ComputationFramework
{
public:
    DistributedComputationFramework(std::string* fileIn, std::vector<std::string*> filesOut, CorrelationComputer* cc);
    virtual ~DistributedComputationFramework();
    
    void exportBlockData(char** buffer, int* size);
    void importBlockData(char* buffer, int size);
protected:
    virtual void onResultComputed(int index, std::vector<ValueStream*> vs);
    
private:
    std::vector<BlockPart*> blockParts;
    
};

#endif	/* DISTRIBUTEDCOMPUTATIONFRAMEWORK_H */

