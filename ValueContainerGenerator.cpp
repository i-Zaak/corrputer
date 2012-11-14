/* 
 * ValueContainerGenerator
 * 
 * Takes an input file and generates a universal value container used by this
 * project.
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include <fstream>

#include "common.h"

using namespace std;

#ifdef VALUE_CONTAINER_GENERATOR

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
    ValueContainer vc;
    try {
        di->open(argv[2], &vc);
    } catch (...) {
        cout << "Failed opening input file: " << argv[2] << endl;
    }
    
    // prepare the output file
    std::ofstream fout(argv[3]);
    
    // save the header
    vc.saveHeader(fout);
    
    // read and save every value stream
    int streamsCount = vc.getStreamsCount();
    for (int i = 0; i < streamsCount; i++) {
        vc.saveStream(i, fout);
    }
    fout.close();
    
    return 0;
}
#endif