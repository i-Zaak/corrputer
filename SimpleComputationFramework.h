#ifndef SIMPLECOMPUTATIONFRAMEWORK_H
#define	SIMPLECOMPUTATIONFRAMEWORK_H

#include "ComputationFramework.h"

/**
 * Basic framework, mostly dummy methods.
 */
class SimpleComputationFramework : public ComputationFramework {
public:
    SimpleComputationFramework(std::string fileIn, std::string fileOut, CorrelationComputer* cc);
    virtual ~SimpleComputationFramework();
    
protected:
    void afterCompute()
    {
        float proc = activeBlock * 100.0f / (1.0f * (blocksCount-1));
        printf("... %02d / %02d ... %2.1f%%\n", activeBlock, blocksCount-1, proc);
    }
    
private:

};

#endif	/* SIMPLECOMPUTATIONFRAMEWORK_H */

