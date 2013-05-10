/*
 * CorrelationComputer
 *
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include <stdexcept>


#include "CorrelationComputer.h"
#include "common.h"
#include <algorithm>

CorrelationComputer::CorrelationComputer() {
    this->container = NULL;
    
    this->windowSize = 100;
    this->windowStep = this->windowSize;
    this->tauMax = 10;
    this->subpartStart = 0;
    this->subpartLength = 0;
    this->sampleInterval = 0.0f;
    
    this->inited = 0;
    this->nOuts = 2; //max corr,  max tau
}

CorrelationComputer::CorrelationComputer(const CorrelationComputer& orig) {
}

CorrelationComputer::~CorrelationComputer() {
}

//======================================================================
// Pre-Init (configuration)
//======================================================================

int CorrelationComputer::getTauMax()
{
    return tauMax;
}

//======================================================================

void CorrelationComputer::setTauMax(int tauMax)
{
    if (inited != 0) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->tauMax = tauMax;
}

//======================================================================

int CorrelationComputer::getWindowSize()
{
    return windowSize;
}

//======================================================================

void CorrelationComputer::setWindowSize(int windowSize)
{
    if (inited != 0) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->windowSize = windowSize;
}

//======================================================================

int CorrelationComputer::getStepSize()
{
    return windowStep;
}

//======================================================================

void CorrelationComputer::setStepSize(int stepSize)
{
    if (inited != 0) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->windowStep = stepSize;
}

//======================================================================

int CorrelationComputer::getSubpartLength()
{
    return subpartLength;
}

//======================================================================

void CorrelationComputer::setSubpartLength(int subpartLength)
{
    if (inited != 0) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->subpartLength = subpartLength;
}

//======================================================================

int CorrelationComputer::getSubpartStart()
{
    return subpartStart;
}

//======================================================================

void CorrelationComputer::setSubpartStart(int subpartStart)
{
    if (inited != 0) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->subpartStart = subpartStart;
}

//======================================================================

float CorrelationComputer::getSampleInterval()
{
    return sampleInterval;
}

//======================================================================

void CorrelationComputer::setSampleInterval(float sampleInterval)
{
    if (inited != 0) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->sampleInterval = sampleInterval;
}

//======================================================================

void CorrelationComputer::setData(ValueContainer* container)
{
    if (inited != 0) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->container = container;
}

//======================================================================
// Init
//======================================================================

void CorrelationComputer::init()
{
    if (inited != 0) {
        throw std::runtime_error("Already inited, cannot re-init.");
    }
    inited = 1;

    // compute derived configuration
    int inDataLength = this->getValues()->getStreamsLength();
    this->inDataStart = std::max(0, this->subpartStart);
    this->inDataStop = std::max(inDataStart+1, inDataLength - tauMax - windowSize + 1);
    if (this->subpartLength > 0) {
        this->inDataStop = std::min(this->subpartLength, inDataLength - tauMax - windowSize);
    }
    if (inDataStart >= inDataStop) {
        throw std::runtime_error("Invalid subpart configuration.");
    }
    int inDataSubpartLength = inDataStop - inDataStart;
    if (windowStep <= 0) {
        throw std::runtime_error("Invalid window step size configuration: <= 0.");
    }
    this->outDataLength = std::max(0, inDataSubpartLength - windowSize) / this->windowStep + 1;
    
    // perform configuration validation
    if (tauMax < 0) {
        throw std::runtime_error("Invalid tau max configuration: < 0.");
    }
    if (windowSize <= 0) {
        throw std::runtime_error("Invalid window size configuration: <= 0.");
    }
    if (this->windowSize > inDataLength) {
        throw std::runtime_error("Invalid window size: must be smaller than data length.");
    }
    if (this->windowSize > inDataLength - tauMax) {
        throw std::runtime_error("Invalid window size: must be smaller than data length - tau max.");
    }
    if (this->outDataLength < 0) {
        throw std::runtime_error("Invalid resulting output data length configuration: < 0.");
    }
    if (this->sampleInterval <= 0.0f) {
        throw std::runtime_error("Invalid sample interval value: <= 0.");
    }
}

//======================================================================
// Post-Init
//======================================================================

int CorrelationComputer::getOutputLength()
{
    if (inited != 1) {
        throw std::runtime_error("Init not yet performed.");
    }
    return this->outDataLength;
}

//======================================================================
//======================================================================

//ValueContainer* CorrelationComputer::computeAll()
//{
//    int count = this->container->getStreamsCount();
//
//    std::cout << "Computing correlations for " << count << " streams..." << std::endl;
//    ValueStream** streams = new ValueStream*[count * count];
//
//    int one;
//    for (one = 0; one < count; one++) {
//        for (int two = 0; two < count; two++) {
//            streams[one * count + two] = this->computePair(one, two);
//            //std::cout << "[" << one << " ; " << two << "] Done." << std::endl;
//        }
//        std::cout << "[" << one << " ; " << count << "] Done." << std::endl;
//        // "safety-plug" for large data taking too long while testing
//        // TODO: remove after testing
//        if (count > 1000 && one >= 4) {
//            return NULL;
//        }
//    }
//
//    std::cout << "All correlations computed." << std::endl;
//    return new ValueContainer(count * count, streams);
//}

//======================================================================

std::vector<ValueStream*> CorrelationComputer::computePair(int one, int two)
{
    if (inited != 1) {
        throw std::runtime_error("Init not yet performed.");
    }

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

    if (vsOne == NULL || vsTwo == NULL) {
        throw std::runtime_error("Value streams not loaded properly.");
    }

    /**
     * Prepare pre-computable data that could speed-up the correlation comp.
     */
    this->prepareStream(one);
    this->prepareStream(two);

    /**
     * Load configuration
     */
    int start = this->inDataStart;
    int stop = this->inDataStop;
    
    /**
     * Find the largest correlation for every window position with changing tau
     * values and create the resulting correlation value stream.
     */
    ValueStream* vsCorel = new ValueStream();
    ValueStream* vsTau = new ValueStream();
    vsCorel->reserve(this->getOutputLength());
    vsTau->reserve(this->getOutputLength());
    for (int pos = start; pos < stop; pos += windowStep) {
        float maxCor = 0.0f;
        int maxTau = 0;
        // try all the tau values
        for (int tau = 0; tau <= tauMax; tau++) {
            float cor = this->computePairValue(one, two, pos, windowSize, tau);
            if (cor > maxCor) {
                maxCor = cor;
                maxTau = tau;
            }
        }
        // save the best value
        vsCorel->push_back(maxCor);
        vsTau->push_back(maxTau);
    }
    std::vector<ValueStream*> results;
    results.push_back(vsCorel);
    results.push_back(vsTau);
    return results;
    
}

//======================================================================

void CorrelationComputer::prepareStream(int index)
{
}

int CorrelationComputer::getOutsNumber(){
    return this->nOuts;
}

