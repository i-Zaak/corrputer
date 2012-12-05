#include "common.h"

#include "CrossCorrelationComputer.h"
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
    SimpleComputationFramework framework(new std::string("montazr11.vc"), new std::string("montazr11.corel.vc"), corelComp);
    
    // compute every block
    framework.open();
    do {
        framework.compute();
    } while (framework.nextBlock());
    framework.close();
    
    return 0;
}

#endif
