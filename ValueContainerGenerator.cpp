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
#include "DataInputIface.h"
#include "ScopeWinInput.h"
#include "NiftiInput.h"

using namespace std;

#ifdef MAIN_VALUE_CONTAINER_GENERATOR

void printUsage(int argc, char** argv)
{
    cout << "Usage: " << argv[0] << " input_type input_file output_file" << endl;
    cout << "\t" << "input_type - type of input file. Possible values: "
            << "ScopeWin" << ", "
            << "Nifti" //<< ", "
            << endl;
    cout << "\t" << "input_file - path to the input file to be converted." << endl;
    cout << "\t" << "output_file - path to the output file to be generated. It should end with a \".vc\" extension." << endl;
}

/*
 * 
 */
int main(int argc, char** argv)
{
    if (argc != 4) {
        printUsage(argc, argv);
        return 1;
    }
    
    // prepare a DataInputIface instance
    DataInputIface* di;
    if (strcmp(argv[1], "ScopeWin") == 0) {
        di = new ScopeWinInput();
    } else if (strcmp(argv[1], "Nifti") == 0) {
        di = new NiftiInput();
    } else {
        cout << "Unknown input type: " << argv[1] << endl;
        printUsage(argc, argv);
        return 2;
    }
    
    // open the file and read the header information
    try {
        di->open(argv[2]);
    } catch (...) {
        cout << "Failed opening input file: " << argv[2] << endl;
    }
    
    // temporary vc for file-saving
    ValueContainer vc;
    
    // prepare the output file
    std::ofstream fout(argv[3], std::ios::binary);
    
    // load & save the header
    di->loadHeader(&vc);
    vc.saveHeader(fout);
    
    // read and save every value stream
    int streamsCount = vc.getStreamsCount();
    for (int i = 0; i < streamsCount; i++) {
        ValueStream* vs = di->loadStream(i);
        vc.setStream(i, vs);
        
        vc.saveStream(i, fout);
        
        vc.setStream(i, NULL);
        delete vs;
    }
    di->close();
    fout.close();
    
    return 0;
}
#endif