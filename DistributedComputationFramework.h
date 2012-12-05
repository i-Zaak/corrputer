#ifndef DISTRIBUTEDCOMPUTATIONFRAMEWORK_H
#define	DISTRIBUTEDCOMPUTATIONFRAMEWORK_H

#include "ComputationFramework.h"

/**
 * Distributed framework. Data output is disabled as there is a dedicated node
 * saving the computation results.
 */
class DistributedComputationFramework : public ComputationFramework {
public:
    DistributedComputationFramework(std::string* fileIn, CorrelationComputer* cc);
    virtual ~DistributedComputationFramework();
    
protected:
    
private:

};

#endif	/* DISTRIBUTEDCOMPUTATIONFRAMEWORK_H */

