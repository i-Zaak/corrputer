/* 
 * File:   RunningVarianceTest.cpp
 * Author: dejvino
 *
 * Created on 28.11.2012, 9:59:55
 */

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../common.h"
#include "../ValueStream.h"

// tested class
#include "../WindowedStatisticsComputer.h"

#define IS_EPSILON_EQUAL(v1, v2, e) (v1 >= v2-e && v1 <= v2+e)

//==========================================================================

/*
 * Simple C++ Test Suite
 */
void test1() {
    std::cout << "RunningVarianceTest test 2" << std::endl;
    
    WindowedStatisticsComputer stats(5);
    stats.nextNumber(1);
    stats.nextNumber(2);
    stats.nextNumber(3);
    stats.nextNumber(2);
    stats.nextNumber(1);
    
    std::cout << "Mean: " << stats.getMean() << std::endl;
    std::cout << "Variance: " << stats.getVariance() << std::endl;
    
    float m = stats.getMean();
    float v = stats.getVariance();
    if (!IS_EPSILON_EQUAL(m, 1.8f, 0.001f)) {
        std::cout << "%TEST_FAILED% invalid mean." << std::endl;
    }
    if (!IS_EPSILON_EQUAL(v, 0.7f, 0.001f)) {
        std::cout << "%TEST_FAILED% invalid variance." << std::endl;
    }
}

void test2() {
    std::cout << "RunningVarianceTest test 3" << std::endl;
    
    WindowedStatisticsComputer stats(2);
    stats.nextNumber(1);
    stats.nextNumber(2);
    stats.nextNumber(3);
    stats.nextNumber(2);
    stats.nextNumber(1);
    
    std::cout << "Mean: " << stats.getMean() << std::endl;
    std::cout << "Variance: " << stats.getVariance() << std::endl;
    
    float m = stats.getMean();
    float v = stats.getVariance();
    if (!IS_EPSILON_EQUAL(m, 1.5f, 0.001f)) {
        std::cout << "%TEST_FAILED% invalid mean." << std::endl;
    }
    if (!IS_EPSILON_EQUAL(v, 0.5f, 0.001f)) {
        std::cout << "%TEST_FAILED% invalid variance." << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% RunningVarianceTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testExample (RunningVarianceTest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 testExample (RunningVarianceTest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (RunningVarianceTest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (RunningVarianceTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

