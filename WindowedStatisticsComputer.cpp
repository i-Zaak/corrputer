/* 
 * File:   WindowedStatisticsComputer.cpp
 * Author: adminuser
 * 
 * Created on February 22, 2013, 11:14 PM
 */

#include "WindowedStatisticsComputer.h"

WindowedStatisticsComputer::WindowedStatisticsComputer(int windowSize) {
    this->windowSize = windowSize;
    this->n = 0;
    this->sum = 0;
    this->mean = 0;
    this->variance = 0;
    this->M2 = 0;
    this->M2History = new std::queue< float >();
    this->valueHistory = new std::queue< float >();
}

WindowedStatisticsComputer::WindowedStatisticsComputer(const WindowedStatisticsComputer& orig) {
}

WindowedStatisticsComputer::~WindowedStatisticsComputer() {
}

void WindowedStatisticsComputer::nextNumber(float value)
{
    // window limit?
    if (n >= windowSize) {
        // remove the oldest element
        float oldM2 = M2History->front();
        M2 -= oldM2;
        M2History->pop();
        
        float oldValue = valueHistory->front();
        sum -= oldValue;
        valueHistory->pop();
    } else {
        // grow
        n++;
    }
    
    valueHistory->push(value);
    
    float delta = value - mean;
    
    sum += value;
    mean = sum/n;
    
    M2 = M2 + delta*(value - mean);
    M2History->push(M2);
 
    variance = M2/(n - 1);
}

float WindowedStatisticsComputer::getMean()
{
    return this->mean;
}

float WindowedStatisticsComputer::getVariance()
{
    return this->variance;
}