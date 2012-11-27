/* 
 * CrossCorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "CrossCorrelationComputer.h"

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

CrossCorrelationComputer::CrossCorrelationComputer() {
}

CrossCorrelationComputer::CrossCorrelationComputer(const CrossCorrelationComputer& orig) {
}

CrossCorrelationComputer::~CrossCorrelationComputer() {
}

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
    
    float meanOne = chOne->getMeans()->at(start);
    float meanTwo = chTwo->getMeans()->at(start + tau);
    float varianceOne = chOne->getVariances()->at(start);
    float varianceTwo = chTwo->getVariances()->at(start + tau);
    
    // compute the result based on the formula
    float sum = 0.0f;
    for (i = start; i < stop; i++) {
        float a = (vsOne->at(i) - meanOne) / varianceOne;
        float b = (vsTwo->at(i + tau) - meanTwo) / varianceTwo;
        sum += a * b;
    }
    
    return (1.0f / steps) * sum;
}

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
    int sum = 0;
    // unrolled init loop to fill the window
    for (pos = 0; pos < windowSize; pos++) {
        float val = values->at(pos);
        sum += val;
        means->push_back(sum / (pos+1));
        
        // TODO: compute variances
        variances->push_back(1.0f);
    }
    // windowed running mean computation
    float invN = 1.0f / windowSize; // precomputed value
    for (pos = windowSize; pos < dataLength; pos++) {
        float val = values->at(pos);
        float valOld = values->at(pos - windowSize);
        sum += val - valOld;
        means->push_back(sum * invN);
        
        // TODO: compute variances
        variances->push_back(1.0f);
    }
}