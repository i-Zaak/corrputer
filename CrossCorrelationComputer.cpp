/* 
 * CrossCorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "CrossCorrelationComputer.h"

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
using namespace boost::accumulators;

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
 
    // compute statistical information about the two streams
    accumulator_set<float, stats<tag::mean, tag::variance > > accOne;
    accumulator_set<float, stats<tag::mean, tag::variance > > accTwo;

    int stop = start + steps;
    int i;
    for (i = start; i < stop; i++) {
        accOne(vsOne->at(i));
        accTwo(vsTwo->at(i+tau));
    }

    float meanOne = mean(accOne);
    float meanTwo = mean(accTwo);
    float varianceOne = variance(accOne);
    float varianceTwo = variance(accTwo);
    
    // compute the result based on the formula
    accumulator_set<float, stats<tag::sum > > accSum;
    for (i = start; i < stop; i++) {
        float a = (vsOne->at(i) - meanOne) / varianceOne;
        float b = (vsTwo->at(i + tau) - meanTwo) / varianceTwo;
        accSum(a * b);
    }
    
    return (1.0f / steps) * sum(accSum);
}