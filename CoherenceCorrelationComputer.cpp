/* 
 * CoherenceCorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "common.h"
#include "CoherenceCorrelationComputer.h"
#include "WindowedStatisticsComputer.h"

//==========================================================================

float getFftFrequency(int index, float samplingFreq, int windowSize)
{
    return index * (samplingFreq / windowSize);
}

//==========================================================================

CoherenceCorrelationComputer::CoherenceCorrelationComputer() {
    this->frequencyRangeBegin = 0.0f;
    this->frequencyRangeEnd = 0.0f;
}

CoherenceCorrelationComputer::CoherenceCorrelationComputer(const CoherenceCorrelationComputer& orig) {
}

CoherenceCorrelationComputer::~CoherenceCorrelationComputer() {
    fftw_destroy_plan(this->planOne);
    fftw_destroy_plan(this->planTwo);
    fftw_free(this->tsOne);
    fftw_free(this->tsTwo);
    fftw_free(this->freqOne);
    fftw_free(this->freqTwo);
}

//==========================================================================

void CoherenceCorrelationComputer::setFrequencyRangeBegin(float value)
{
    if (isInited()) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->frequencyRangeBegin = value;
}

void CoherenceCorrelationComputer::setFrequencyRangeEnd(float value)
{
    if (isInited()) {
        throw std::runtime_error("Already inited, config change is forbidden.");
    }
    this->frequencyRangeEnd = value;
}

//======================================================================

void CoherenceCorrelationComputer::init()
{
    CorrelationComputer::init();
    
    int N = this->getWindowSize();
    this->tsOne = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    this->tsTwo = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    this->freqOne = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    this->freqTwo = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    
    if (freqOne == NULL || freqTwo == NULL) {
        throw std::runtime_error("Failed allocating memory for FFT.");
    }
    
    this->planOne = fftw_plan_dft_1d(N, tsOne, freqOne, FFTW_FORWARD, FFTW_ESTIMATE);
    this->planTwo = fftw_plan_dft_1d(N, tsTwo, freqTwo, FFTW_FORWARD, FFTW_ESTIMATE);
    
    if (planOne == NULL || planTwo == NULL) {
        throw std::runtime_error("Failed creating FFT plan.");
    }
    
    /**
     * Find the begin index & end index in the power-spectrum that corresponds
     * to the frequency range we are interested in.
     */
    int fftSize = (this->getWindowSize() / 2 + 1) + 1; // last valid index + 1
    float samplesPerSecond = 1.0f / this->getSampleInterval();
    // init for the whole range
    this->fftRangeBegin = 0;
    this->fftRangeEnd = fftSize - 1;
    // is there a limit?
    if (this->frequencyRangeBegin != 0.0f || this->frequencyRangeEnd != 0.0f) {
        // limit
        // ensure: begin <= end
        if (frequencyRangeEnd > frequencyRangeBegin) {
            float tmp = frequencyRangeEnd;
            frequencyRangeEnd = frequencyRangeBegin;
            frequencyRangeBegin = tmp;
        }
        // find begin & end index in the FFT result
        for (int i = 0; i < fftSize; i++) {
            // compute frequency
            float freq = i * (samplesPerSecond / ((float)fftSize));
            // move the start?
            if (freq <= frequencyRangeBegin) {
                this->fftRangeBegin = i;
            }
            // found the end?
            if (freq >= frequencyRangeEnd) {
                this->fftRangeEnd = i;
                break;
            }
        }
    }
}

//==========================================================================

float CoherenceCorrelationComputer::computePairValue(int one, int two, int start, int steps, int tau)
{   
    // values
    ValueStream* vsOne = this->getValues()->getStream(one);
    ValueStream* vsTwo = this->getValues()->getStream(two);
    
    int stop = start + steps;
    int i;
    
    // compute power-spectra for both signals using FFT
    float* fone = &((*vsOne)[0]);
    float* ftwo = &((*vsTwo)[0]);
    for (i = start; i < stop; i++) {
        this->tsOne[i - start][0] = fone[i];
        this->tsTwo[i - start][0] = ftwo[i+tau];
    }
    fftw_execute(this->planOne);
    fftw_execute(this->planTwo);
    
    // computer the power-spectra statistics
    WindowedStatisticsComputer statsOne(fftRangeEnd-fftRangeBegin+1);
    WindowedStatisticsComputer statsTwo(fftRangeEnd-fftRangeBegin+1);
    for (i = fftRangeBegin; i <= fftRangeEnd; i++) {
        statsOne.nextNumber(this->freqOne[i][0]);
        statsTwo.nextNumber(this->freqTwo[i][0]);
    }
    float meanOne = statsOne.getMean();
    float meanTwo = statsTwo.getMean();
    float varianceOne = statsOne.getVariance();
    float varianceTwo = statsTwo.getVariance();
    
    // compute the result based on the cross-correlation formula
    // TODO: numerically stable sum is needed
    float sum = 0.0f;
    for (i = fftRangeBegin; i <= fftRangeEnd; i++) {
        float a = (freqOne[i][0] - meanOne) / varianceOne;
        float b = (freqTwo[i][0] - meanTwo) / varianceTwo;
        sum += a * b;
        //printf("((%f - %f) / %f) * ((%f - %f) / %f) = %f\n",
        //        vsOne->at(i), meanOne, varianceOne,
        //        vsTwo->at(i + tau), meanTwo, varianceTwo,
        //        a*b);
    }
    //printf("1.0 / %f * %f = \n", steps, sum, (1.0f / steps) * sum);
    return (1.0f / (fftRangeEnd+1 - fftRangeBegin)) * sum;
}

//==========================================================================

void CoherenceCorrelationComputer::prepareStream(int index)
{
    // TODO: move FFT and other time-demanding computations here!
}
