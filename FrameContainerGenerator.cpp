/* 
 * ValueContainerGenerator
 * 
 * Takes an input file and generates a universal value container used by this
 * project for correlation computations.
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include <fstream>

#include "common.h"
#include "ValueContainer.h"

using namespace std;

#ifdef MAIN_FRAME_CONTAINER_GENERATOR

#define FRAMECONTAINER_FILE_VERSION 1

void printUsage(int argc, char** argv)
{
    cout << "Usage: " << argv[0] << " input_file.vc output_file.fc" << endl;
    cout << "\t" << "input_file.vc - path to the input value container file to be converted." << endl;
    cout << "\t" << "output_file.fc - path to the output frame container file to be generated. It should end with a \".fc\" extension." << endl;
}

/*
 * 
 */
int main(int argc, char** argv)
{
    if (argc != 3) {
        printUsage(argc, argv);
        return 1;
    }
    
    // prepare ValueContainer input
    ValueContainer* vc = new ValueContainer();
    std::ifstream* fin = new std::ifstream(argv[1]);
    
    // check for input file problems
    if (!fin->good()) {
        char curPath[FILENAME_MAX];
        getcwd(curPath, FILENAME_MAX);
        DEBUG_CERR << "File stream is not good! Failed opening input file '"
                << argv[1] << "' from dir '"
                << curPath << "'." << std::endl;
        throw std::runtime_error("Input file stream is not good.");
    }
    
    // prepare output file
    std::ofstream* fout = new std::ofstream(argv[2], std::ios::binary);
    
    // check result
    if (!fout->good()) {
        char curPath[FILENAME_MAX];
        getcwd(curPath, FILENAME_MAX);
        DEBUG_CERR << "File stream is not good! Failed opening output file '"
                << argv[2] << "' in dir '"
                << curPath << "'." << std::endl;
        throw std::runtime_error("Output file stream is not good.");
    }
    
    // load header
    vc->loadHeader(*fin);
    
    //======================================================================
    // write header info
    // version
    int version = FRAMECONTAINER_FILE_VERSION;
    fout->write((char*)&version, 4);
    
    // streams count
    int streamsCount = vc->getStreamsCount();
    printf("Points count: %d\n", streamsCount);
    fout->write((char*)&streamsCount, 4);
    
    // streams length
    int streamsLength = vc->getStreamsLength();
    printf("Frames count: %d\n", streamsLength);
    fout->write((char*)&streamsLength, 4);
    //======================================================================

    // TODO: magically guess the block size based on available memory and the
    // length of the input stream
    int blockSize = 50;
    
    if (blockSize > streamsCount) {
        blockSize = streamsCount;
    }
    
    //======================================================================
    // write data
    for (int block = 0; block <= streamsCount / blockSize; block++)
    {
        printf("Block %3d / %3d, %3d%\n", block, streamsCount / blockSize,
                block * 100 / (streamsCount / blockSize));
        
        // read block streams
        for (int i = 0; i < blockSize; i++) {
            int index = block*blockSize + i;
            
            // free old stream
            if (index - blockSize >= 0) {
                vc->freeStream(index - blockSize);
            }
            
            // load new stream
            if (index >= streamsCount) {
                continue;
            }
            vc->loadStream(index, *fin);
        }
        
        // write part of a frame for every frame
        float blockValues[blockSize];
        int fileBlockBegin = sizeof(int) * 3 // header
                    //+ streamsCount * sizeof(float) * t // previous frames
                    + block * blockSize * sizeof(float); // previous frame blocks
        int blockParts = 0;
        for (int t = 0; t < streamsLength; t++) {
            // find absolute block position in time
            fout->seekp(fileBlockBegin, std::ios::beg);
            fileBlockBegin += streamsCount * sizeof(float);
            
            // write all the parts of a block
            blockParts = 0;
            for (int i = 0; i < blockSize; i++) {
                int index = block*blockSize + i;
                
                if (index >= streamsCount) {
                    continue;
                }
                
                blockValues[i] = vc->getStream(index)->at(t);
                blockParts++;
            }
            
            fout->write((char*)&blockValues, sizeof(float) * blockParts);
            
            if (t % 100000 == 0) {
                printf(" ... frame %8d ... \n", t);
            }
        }
    }
    
    fin->close();
    fout->close();
    
    return 0;
}
#endif