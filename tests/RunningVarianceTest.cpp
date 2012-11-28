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

// tested functions
#include "../Statistics.h"

//==========================================================================

/*
 * Simple C++ Test Suite
 */

void testExample() {
    std::cout << "RunningVarianceTest test example" << std::endl;
    
    ValueStream vs;
    vs.push_back(3);
    vs.push_back(5);
    vs.push_back(8);
    vs.push_back(10);
    vs.push_back(4);
    vs.push_back(8);
    vs.push_back(12);
    vs.push_back(15);
    vs.push_back(11);
    vs.push_back(9);

    float prev_powersumavg = 0.0f;
    float prev_sma = 0.0f;
    int period = 3;
    
    for (int bar = 0; bar < vs.size(); bar++) {
        float price = vs[bar];
        
        float new_sma = running_sma(bar, &vs, period, prev_sma);
        float new_powersumavg = powersumavg(bar,
                                  &vs,
                                  period,
                                  prev_powersumavg);
        float new_var = running_var(bar,
                          &vs,
                          period,
                          new_sma,
                          new_powersumavg);
 
        char msg[200];
        sprintf(msg, "SMA=%.4f, PSA=%.4f, Var=%.4f", new_sma, new_powersumavg, new_var);
        
        std::cout << "bar " << bar << " " << msg << std::endl;
 
        prev_sma = new_sma;
        prev_powersumavg = new_powersumavg;
    }
 
    /*
Results of call:
bar 0: SMA=3.0000, PSA=9.0000, Var=0.0000
bar 1: SMA=4.0000, PSA=17.0000, Var=1.0000
bar 2: SMA=5.3333, PSA=32.6667, Var=4.2222
bar 3: SMA=7.6667, PSA=63.0000, Var=4.2222
bar 4: SMA=7.3333, PSA=60.0000, Var=6.2222
bar 5: SMA=7.3333, PSA=60.0000, Var=6.2222
bar 6: SMA=8.0000, PSA=74.6667, Var=10.6667
bar 7: SMA=11.6667, PSA=144.3333, Var=8.2222
bar 8: SMA=12.6667, PSA=163.3333, Var=2.8889
bar 9: SMA=11.6667, PSA=142.3333, Var=6.2222
     */
}

void test2() {
    std::cout << "RunningVarianceTest test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (RunningVarianceTest) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% RunningVarianceTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testExample (RunningVarianceTest)" << std::endl;
    testExample();
    std::cout << "%TEST_FINISHED% time=0 testExample (RunningVarianceTest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (RunningVarianceTest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (RunningVarianceTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

