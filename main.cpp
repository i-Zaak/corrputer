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
    // prepare a universal data container for data input
    ValueContainer vc;
    std::ifstream fin("montazr11.vc");
    
    // prepare a universal data container for data output
    ValueContainer vcout;
    std::ofstream fout("montazr11.corel.vc");
    
    // prepare a correlation computer
    CorrelationComputer* corelComp = new CrossCorrelationComputer();
    
    corelComp->setData(&vc);
    corelComp->setTauMax(1000);
    
    corelComp->setWindowSize(1000);
    corelComp->setSubpartLength(100000);
    
    //corelComp->setWindowSize(1);
    
    // load header
    vc.loadHeader(fin);
    
    // compute result header and save it
    vcout.setStreamsCount(vc.getStreamsCount()*vc.getStreamsCount());
    vcout.setStreamsLength(vc.getStreamsLength());
    vcout.saveHeader(fout);
    
    /*
     * Blocks structure for corelWidth=7, blockHeight=5:
     * 
     *  0123456
     *  0123456
     *  0123456
     * ---------
     *  78.....
     *  78.....
     *  78.....
     * ---------
     *  .......
     */
    
    // compute correlations by blocks
    int blockHeight = 5;
    int corelWidth = vc.getStreamsCount();
    int blocksInCol = (corelWidth + blockHeight-1) / blockHeight;
    int blocksCount = blocksInCol * corelWidth;
    
    vc.loadStream(0, fin);
    ValueStream *vsHack = vc.getStream(0);
    for (int blockNum = 0; blockNum < blocksCount; blockNum++) {
        // prepare state information
        int startPos = ((blockNum % corelWidth) + (blockNum / corelWidth) * corelWidth * blockHeight);
        int colIndex = blockNum % corelWidth; 
        int blockStartIndex = blockNum / corelWidth;
        
        // change of rows?
        if ((blockNum % corelWidth) == 0) {
            // free previous rows and load new rows
            for (int y = 0; y < blockHeight; y++) {
                int prevIndex = ((blockNum / corelWidth) - 1) * blockHeight + y;
                int curIndex = blockNum / corelWidth * blockHeight + y;
                if (prevIndex >= 0) {
                    vc.freeStream(prevIndex);
                }
                if (curIndex < corelWidth) {
                    vc.loadStream(curIndex, fin);
                }
            }
        }
        
        // does this block contain any combination worth computing?
        if (blockStartIndex > colIndex) {
            // nothing would be computed
            continue;
        }
        
        // prepare column stream
        if (colIndex < blockStartIndex || colIndex >= blockStartIndex + blockHeight) {
            // load only if this stream is not already loaded
            vc.loadStream(colIndex, fin);
        }
        
        // <-- now all the required streams are loaded
            
        // process block
        for (int y = 0; y < blockHeight; y++) {
            // compute correlation
            int one = blockStartIndex + y;
            int two = colIndex;
            if (one == two) {
                // TODO: fake stream of 1s
                continue;
            } else if (one > two) {
                // only half of the matrix is really computed
                continue;
            }
            ValueStream* vs = corelComp->computePair(one, two);
            
            // save output
            int resultPos = startPos + y*corelWidth;
            vcout.setStream(resultPos, vs);
            vcout.saveStream(resultPos, fout);
            vcout.freeStream(resultPos);
        }
        
        // free column stream
        if (colIndex < blockStartIndex || colIndex >= blockStartIndex + blockHeight) {
            vc.freeStream(colIndex);
        }
        
        printf("= = %02d / %02d = =\n", blockNum, blocksCount-1);
    }
    
    fin.close();
    fout.close();
    
    return 0;
}

#endif
