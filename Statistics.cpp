
#include "common.h"
#include "Statistics.h"

/*
 * This whole block was taken and adapted from Python to C++ from the following
 * address: http://taylortree.com/running-variance/
 */

float powersumavg(int bar, ValueStream* series, int period, float pval)
{
    if (period < 1) {
        throw std::runtime_error("period must be 1 or greater");
    }
 
    if (bar < 0) {
        bar = 0;
    }
 
    float newamt = series->at(bar);
 
    float result = 0.0f;
    
    if (bar < period) {
        result = pval + (newamt * newamt - pval) / (bar + 1.0);
    } else {
        float oldamt = series->at(bar - period);
        result = pval + (((newamt * newamt) - (oldamt * oldamt)) / period);
    }
 
    return result;
}

//==========================================================================

float running_var(int bar, ValueStream* series, int period, float asma, float apowsumavg)
{
    if (period < 1) {
        throw std::runtime_error("period must be 1 or greater");
    }
    
    if (bar <= 0) {
        return 0.0f;
    }
 
    int windowsize = bar + 1;
    if (windowsize >= period) {
        windowsize = period;
    }
 
    return (apowsumavg * windowsize - windowsize * asma * asma) / windowsize;
}

//==========================================================================


float cumulative_sma(int bar, ValueStream* series, float prevma)
{
    
 
    if (bar <= 0) {
        return series->at(0);
    }
    return prevma + ((series->at(bar) - prevma) / (bar + 1.0));
}

//==========================================================================

float running_sma(int bar, ValueStream* series, int period, float prevma)
{
    
    if (period < 1) {
        throw std::runtime_error("period must be 1 or greater");
    }
    
    if (bar <= 0) {
        return series->at(0);
    } else if (bar < period) {
        return cumulative_sma(bar, series, prevma);
    }
 
    return prevma + ((series->at(bar) - series->at(bar - period)) / ((float)period));
}
