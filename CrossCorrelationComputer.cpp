/* 
 * CrossCorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "CrossCorrelationComputer.h"

CrossCorrelationComputer::CrossCorrelationComputer() {
}

CrossCorrelationComputer::CrossCorrelationComputer(const CrossCorrelationComputer& orig) {
}

CrossCorrelationComputer::~CrossCorrelationComputer() {
}

float CrossCorrelationComputer::computePairValue(int one, int two, int start, int steps, int tau)
{   
    ValueStream* vsOne = this->getValues()->getStream(one);
    ValueStream* vsTwo = this->getValues()->getStream(two);
    
    int stop = start + steps;
    int i;
    
    // TODO: lazy-load statistical data
    float meanOne = 1.0f;//this->means[one]->at(start);
    float meanTwo = 1.0f;//this->means[two]->at(start + tau);
    float varianceOne = 1.0f;
    float varianceTwo = 1.0f;
    
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
    // TODO: cache-like approach = check if the data is already loaded and if
    //       so, return immediately.
    
    // data loading (should be internally performed lazily and cache-like)
    ValueContainer* vc = this->getValues();
    ValueStream* values = vc->getStream(index);
    
    // load configuration
    int windowSize = this->getWindowSize();
    int dataLength = values->size();
    
    //
    //          Statistical data computation
    //
    
    // resulting means
    ValueStream* means = new ValueStream();
    
    int pos;
    int sum = 0;
    // unrolled init loop to fill the window
    for (pos = 0; pos < windowSize; pos++) {
        float val = values->at(pos);
        sum += val;
        means->push_back(sum / (pos+1));
    }
    // windowed running mean computation
    float invN = 1.0f / windowSize; // precomputed value
    for (pos = windowSize; pos < dataLength; pos++) {
        float val = values->at(pos);
        float valOld = values->at(pos - windowSize);
        sum += val - valOld;
        means->push_back(sum * invN);
    }
    
    // TODO: save the calculated means for later
    // TODO: free older and no longer needed memory
    delete means;
}