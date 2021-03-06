/* 
 * CrossCorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "common.h"
#include "CrossCorrelationComputer.h"
#include "WindowedStatisticsComputer.h"

//==========================================================================

/**
 * Helper class containing statistics chained to a value stream.
 */
class ChainedStatistics : public ChainedObject
{
public:
    ChainedStatistics() {
        this->means = new ValueStream();
        this->variances = new ValueStream();
    }
    virtual ~ChainedStatistics() {
        delete this->means;
        delete this->variances;
    }
    
    ValueStream* getMeans() {
        return this->means;
    }
    ValueStream* getVariances() {
        return this->variances;
    }
    
private:
    ValueStream* means;
    ValueStream* variances;
};

//==========================================================================
//==========================================================================

CrossCorrelationComputer::CrossCorrelationComputer() {
}

CrossCorrelationComputer::CrossCorrelationComputer(const CrossCorrelationComputer& orig) {
}

CrossCorrelationComputer::~CrossCorrelationComputer() {
}

//==========================================================================

float CrossCorrelationComputer::computePairValue(int one, int two, int start, int steps, int tau)
{   
    // values
    ValueStream* vsOne = this->getValues()->getStream(one);
    ValueStream* vsTwo = this->getValues()->getStream(two);
    
    // prepared statistics
    ChainedStatistics* chOne = (ChainedStatistics*)this->getValues()->getChainedData(one);
    ChainedStatistics* chTwo = (ChainedStatistics*)this->getValues()->getChainedData(two);
    
    int stop = start + steps;
    int i;
    
    float meanOne = chOne->getMeans()->at(stop - 1);
    float meanTwo = chTwo->getMeans()->at(stop - 1 + tau);
    float varianceOne = chOne->getVariances()->at(stop - 1);
    float varianceTwo = chTwo->getVariances()->at(stop - 1 + tau);
    
    // compute the result based on the cross-correlation formula
    // TODO: numerically stable sum is needed
    float sum = 0.0f;
    for (i = start; i < stop; i++) {
        float a = (vsOne->at(i) - meanOne) / varianceOne;
        float b = (vsTwo->at(i + tau) - meanTwo) / varianceTwo;
        sum += a * b;
        //printf("((%f - %f) / %f) * ((%f - %f) / %f) = %f\n",
        //        vsOne->at(i), meanOne, varianceOne,
        //        vsTwo->at(i + tau), meanTwo, varianceTwo,
        //        a*b);
    }
    //printf("1.0 / %f * %f = \n", steps, sum, (1.0f / steps) * sum);
    return (1.0f / steps) * sum;
}

//==========================================================================

void CrossCorrelationComputer::prepareStream(int index)
{
    ValueContainer* vc = this->getValues();
    ChainedStatistics* chained = (ChainedStatistics*)vc->getChainedData(index);
    
    // is the stream already prepared?
    if (chained != NULL) {
        // we got it for free!
        return;
    }
    
    // create a new chained object
    chained = new ChainedStatistics();
    vc->setChainedData(index, chained);
    
    // load configuration
    ValueStream* values = vc->getStream(index);
    int windowSize = this->getWindowSize();
    int dataLength = values->size();
    
    //
    //          Statistical data computation
    //
    
    // resulting streams
    ValueStream* means = chained->getMeans();
    ValueStream* variances = chained->getVariances();
    
    int pos;
    WindowedStatisticsComputer stats(windowSize);
    for (pos = 0; pos < dataLength; pos++) {
        stats.nextNumber(values->at(pos));
        means->push_back(stats.getMean());
        variances->push_back(stats.getVariance());
    }
}
