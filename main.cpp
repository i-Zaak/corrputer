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

#ifdef MAIN_CORRELATOR

/*
 * 
 */
int main(int argc, char** argv) {
    // load data into universal container
    DataInputIface* di = new ScopeWinInput();
    ValueContainer* vc = di->load("montazr11_segm-s6-14.w");
    //DataInputIface* di = new NiftiInput();
    //ValueContainer* vc = di->load("fM01612_0001.hdr");
    
    // calculate the correlations
    CorrelationComputer* corelComp = new CrossCorrelationComputer();
    
    corelComp->setData(vc);
    corelComp->setTauMax(1000);
    
    corelComp->setWindowSize(1000);
    corelComp->setSubpartLength(100000);
    
    //corelComp->setWindowSize(1);
    
    ValueContainer* cc = corelComp->computeAll();
    
    /*/ save the results
    std::ofstream fout("correl.dat");
    // save data to archive
    {
        boost::archive::binary_oarchive oa(fout);
        // write class instance to archive
        oa << cc;
    	// archive and stream closed when destructors are called
    }/**/
    
    return 0;
}

#endif
