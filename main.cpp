/* 
 * File:   main.cpp
 * Author: adminuser
 *
 * Created on October 26, 2012, 10:53 AM
 */

#include "common.h"
#include "DataInputIface.h"
#include "ScopeWinInput.h"
#include "CrossCorrelationComputer.h"
#include "CorrelationComputer.h"

/*
 * 
 */
int main(int argc, char** argv) {
    // load data into universal container
    DataInputIface* di = new ScopeWinInput();
    ValueContainer* vc = di->load("montazr11_segm-s6-14.w");
    
    // calculate the correlations
    CorrelationComputer* corelComp = new CrossCorrelationComputer();
    corelComp->setData(vc);
    ValueContainer* cc = corelComp->computeAll();
    
    // save the results
    // TODO: save cc to file
    
    return 0;
}

