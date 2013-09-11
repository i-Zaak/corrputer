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
        this->stDevs = new ValueStream();
    }
    virtual ~ChainedStatistics() {
        delete this->means;
        delete this->stDevs;
    }
    
    ValueStream* getMeans() {
        return this->means;
    }
    ValueStream* getStDevs() {
        return this->stDevs;
    }
    
private:
    ValueStream* means;
    ValueStream* stDevs;
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
    float stDevOne = chOne->getStDevs()->at(stop - 1);
    float stDevTwo = chTwo->getStDevs()->at(stop - 1 + tau);

    
    // compute the result based on the cross-correlation formula
    // TODO: numerically stable sum is needed
    float sum = 0.0f;
    for (i = start; i < stop; i++) {
        float a = (vsOne->at(i) - meanOne) / stDevOne;
        float b = (vsTwo->at(i + tau) - meanTwo) / stDevTwo;
        sum += a * b;
        //printf("((%f - %f) / %f) * ((%f - %f) / %f) = %f %f\n",
        //        vsOne->at(i), meanOne, stDevOne,
        //        vsTwo->at(i + tau), meanTwo, stDevTwo,
        //        a*b,sum);
    }
    //printf("1.0 / %d * %f = %f\n", steps, sum, (1.0f / steps  * sum));
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
    ValueStream* stDevs = chained->getStDevs();
    
    int pos;
    WindowedStatisticsComputer stats(windowSize);
    for (pos = 0; pos < dataLength; pos++) {
        stats.nextNumber(values->at(pos));
        means->push_back(stats.getMean());
        //stDevs->push_back(stats.getStDev());
        stDevs->push_back(stats.getStDev());
    }
}
