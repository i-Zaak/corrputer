/* 
 * CorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "CorrelationComputer.h"
#include "common.h"
#include <algorithm>
#include <boost/progress.hpp>

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
    ValueStream** streams = new ValueStream*[count * count];
    
    int one;
    #pragma omp parallel for
    for (one = 0; one < count; one++) {
        for (int two = 0; two < count; two++) {
            // execution time measure
            boost::progress_timer timer;
            
            streams[one * count + two] = this->computePair(one, two);
            std::cout << "[" << one << " ; " << two << "] Done." << std::endl;
        }
    }
    return new ValueContainer(count * count, streams);
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
    int stop = dataLength - tauMax - windowSize;
    if (this->subpartLength > 0) {
        stop = std::min(this->subpartLength, dataLength - tauMax - windowSize);
    }
    if (start >= stop) {
        throw "Invalid subpart configuration.";
    }
    
    /**
     * Find the largest correlation for every window position with changing tau
     * values and create the resulting correlation value stream.
     */
    ValueStream* vsCorel = new ValueStream(stop - start);
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