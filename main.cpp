/* 
 * File:   main.cpp
 * Author: adminuser
 *
 * Created on October 26, 2012, 10:53 AM
 */

#include "common.h"
#include <fstream>

#include "DataInputIface.h"

#include "ScopeWinInput.h"
#include "NiftiInput.h"

#include "CrossCorrelationComputer.h"
#include "CorrelationComputer.h"
#include "ComputationFramework.h"
#include "SimpleComputationFramework.h"

#ifdef MAIN_CORRELATOR

/*
 * 
 */
int main(int argc, char** argv)
{
    // TODO: process command line arguments
    
    // prepare a correlation computer
    CorrelationComputer* corelComp = new CrossCorrelationComputer();
    
    /*corelComp->setTauMax(1000);
    corelComp->setWindowSize(1000);
    corelComp->setSubpartLength(100000);*/
    
    corelComp->setTauMax(10);
    corelComp->setWindowSize(100);
    corelComp->setSubpartLength(10000);
    
    // prepare computation framework
    SimpleComputationFramework framework("montazr11.vc", "montazr11.corel.vc", corelComp);
    
    // compute every block
    framework.open();
    do {
        framework.compute();
    } while (framework.nextBlock());
    framework.close();
    
    return 0;
}

#endif
