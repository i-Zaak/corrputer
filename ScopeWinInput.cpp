/* 
 * ScopeWinInput
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "common.h"
#include "ScopeWinInput.h"
#include "lib/swutils.h"
#include "DataInputIface.h"
#include "ValueContainer.h"

ScopeWinInput::ScopeWinInput() {
}

ScopeWinInput::ScopeWinInput(const ScopeWinInput& orig) {
}

ScopeWinInput::~ScopeWinInput() {
}

ValueContainer* ScopeWinInput::load(char* filename)
{
    printf("Opening file %s\n", filename);
    FILE *file = fopen(filename, "rb");
	
    if (file == NULL) {
        throw std::runtime_error("File could not be opened.");
    }
    
    printf("done\n");	
    struct IG_s ig;
    struct HG_s hg;

    readIG(file, &ig);
    //printIG(&ig);

    readHG(file, &hg);
    //printHG( &hg);
		
    if(sizeof (float) !=4){
        throw std::runtime_error("The size of float is wrong!");
    }
    
    float *data = (float *) malloc(hg.Size * sizeof (float));
    if (data == NULL) {
        throw std::runtime_error("Memory allocation failed!");
    }

    ValueStream** streams = new ValueStream*[hg.PocetZaznamu];
    
    fseek(file,2146,SEEK_SET);
    for (int i = 0; i < hg.PocetZaznamu; i++) {
        struct FG_s fg;
        readFG(file, &fg);
        //printFG(&fg);

        readData(file,data, hg.Size);
        
        // create a new value stream
        streams[i] = new ValueStream();
        streams[i]->reserve(hg.Size);
        streams[i]->assign(data, data + hg.Size);
    }
    
    // generate the final value container from the streams
    return new ValueContainer(hg.PocetZaznamu, streams);
}