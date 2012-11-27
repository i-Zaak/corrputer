/* 
 * CorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "CorrelationComputer.h"
#include "common.h"
#include <algorithm>

CorrelationComputer::CorrelationComputer() {
    this->windowSize = 100;
    this->tauMax = 10;
    this->subpartStart = 0;
    this->subpartLength = 0;
}

CorrelationComputer::CorrelationComputer(const CorrelationComputer& orig) {
}

CorrelationComputer::~CorrelationComputer() {
}

void CorrelationComputer::setData(ValueContainer* container)
{
    this->container = container;
}

ValueContainer* CorrelationComputer::computeAll()
{   
    int count = this->container->getStreamsCount();
    
    std::cout << "Computing correlations for " << count << " streams..." << std::endl;
    //ValueStream** streams = new ValueStream*[count * count];
    
    int one;
    //#pragma omp parallel for
    for (one = 0; one < count; one++) {
        for (int two = 0; two < count; two++) {
            //streams[one * count + two] = this->computePair(one, two);
            this->computePair(one, two);
            //std::cout << "[" << one << " ; " << two << "] Done." << std::endl;
        }
        std::cout << "[" << one << " ; " << count << "] Done." << std::endl;
        // "safety-plug" for large data taking too long while testing
        // TODO: remove after testing
        if (count > 1000 && one >= 4) {
            return NULL;
        }
    }
    
    std::cout << "All correlations computed." << std::endl;
    //return new ValueContainer(count * count, streams);
    return NULL;
}

ValueStream* CorrelationComputer::computePair(int one, int two)
{
    /**
     * Gather computation configuration.
     *  - size of floating computation window
     *  - maximal value of tau (displacement of signals window position)
     *  - starting position of data (0 or more when subpart option is active)
     *  - ending position of data (length of data or less when subpart option
     *          is active)
     */
    ValueStream* vsOne = this->getValues()->getStream(one);
    ValueStream* vsTwo = this->getValues()->getStream(two);
    
    int dataLength = std::min(vsOne->size(), vsTwo->size());
    int tauMax = this->getTauMax();
    int windowSize = this->getWindowSize();
    int windowStep = windowSize;
    
    int start = std::max(0, this->subpartStart);
    int stop = std::max(start+1, dataLength - tauMax - windowSize);
    if (this->subpartLength > 0) {
        stop = std::min(this->subpartLength, dataLength - tauMax - windowSize);
    }
    if (start >= stop) {
        throw std::runtime_error("Invalid subpart configuration.");
    }
    
    /**
     * Prepare pre-computable data that could speed-up the correlation comp.
     */
    this->prepareStream(one);
    this->prepareStream(two);
    
    /**
     * Find the largest correlation for every window position with changing tau
     * values and create the resulting correlation value stream.
     */
    ValueStream* vsCorel = new ValueStream();
    vsCorel->reserve(stop - start);
    for (int pos = start; pos < stop; pos += windowStep) {
        float maxCor = 0.0f;
        // try all the tau values
        for (int tau = 0; tau < tauMax; tau++) {
            float cor = this->computePairValue(one, two, pos, windowSize, tau);
            if (cor > maxCor) {
                maxCor = cor;
            }
        }
        // save the best value
        vsCorel->push_back(maxCor);
    }
    
    return vsCorel;
}

void CorrelationComputer::prepareStream(int index)
{
}