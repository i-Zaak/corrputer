#ifndef TESTEDDISTRIBUTEDCOMPUTATIONFRAMEWORK_H
#define	TESTEDDISTRIBUTEDCOMPUTATIONFRAMEWORK_H

#include "../DistributedComputationFramework.h"

/**
 * Class extended to enable "result stealing" - computed results are exported
 * outside of this class so the serialization results can be checked against
 * the original values.
 */
class TestedDistributedComputationFramework : public DistributedComputationFramework {
public:
    TestedDistributedComputationFramework(std::string* fileIn, std::string* fileOut, CorrelationComputer* cc);
    virtual ~TestedDistributedComputationFramework();
    
    void setResultsForTesting(ValueStream** results) {
        this->results = results;
    }
    
protected:
    virtual void onResultComputed(int index, ValueStream* vs);
    
private:
    ValueStream** results;
};

#endif	/* TESTEDDISTRIBUTEDCOMPUTATIONFRAMEWORK_H */

