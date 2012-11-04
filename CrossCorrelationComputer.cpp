/* 
 * CrossCorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "CrossCorrelationComputer.h"

#include <iostream>
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

ValueStream* CrossCorrelationComputer::computePair(int one, int two, int start, int steps, int tau)
{
    ValueStream* vsOne = this->getValues()->getStream(one);
    ValueStream* vsTwo = this->getValues()->getStream(two);
 
    accumulator_set<float, stats<tag::mean, tag::variance > > accOne;
    accumulator_set<float, stats<tag::mean, tag::variance > > accTwo;

    int stop = start + steps;
    for (int i = start; i < stop; i++) {
        accOne(vsOne->at(i));
        accTwo(vsTwo->at(i+tau));
    }

    // Display the results ...
    std::cout << "[" << one << ";" << two << "]" << std::endl
            << "\tMean: \t"
            << mean(accOne) << "; " << mean(accTwo) << std::endl
            << "\tVariance: \t"
            << variance(accOne) << "; " << variance(accTwo) << std::endl
            ;
    
    
    
    return new ValueStream(100);
}