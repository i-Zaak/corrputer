/* 
 * ScopeWinInput
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "common.h"
#include "ScopeWinInput.h"
#include "DataInputIface.h"
#include "ValueContainer.h"

ScopeWinInput::ScopeWinInput() {
}

ScopeWinInput::ScopeWinInput(const ScopeWinInput& orig) {
}

ScopeWinInput::~ScopeWinInput() {
}

void ScopeWinInput::open(char* filename)
{
    printf("Opening file %s\n", filename);
    this->file = fopen(filename, "rb");
	
    if (this->file == NULL) {
        throw std::runtime_error("File could not be opened.");
    }
    
    printf("opened\n");
}

void ScopeWinInput::close()
{
    fclose(this->file);
}

void ScopeWinInput::loadHeader(ValueContainer* vc)
{
    printf("Loading header...");
    
    fseek(this->file,0,SEEK_SET);
    
    readIG(this->file, &this->ig);
    //printIG(&ig);

    readHG(this->file, &this->hg);
    //printHG( &hg);
		
    if(sizeof (float) !=4){
        throw std::runtime_error("The size of float is wrong!");
    }
    
    vc->setStreamsCount(this->hg.PocetZaznamu);
    vc->setStreamsLength(this->hg.Size);
    
    printf("done.\n");
}

ValueStream* ScopeWinInput::loadStream(int index)
{
    printf("Loading stream %d...", index);
    
    float *data = (float *) malloc(this->hg.Size * sizeof (float));
    if (data == NULL) {
        throw std::runtime_error("Memory allocation failed!");
    }
    
    fseek(this->file, 2146 + index*this->hg.Size*sizeof(float), SEEK_SET);
    
    struct FG_s fg;
    readFG(this->file, &fg);
    //printFG(&fg);

    readData(this->file,data, this->hg.Size);

    // create a new value stream
    ValueStream* stream = new ValueStream();
    stream->reserve(this->hg.Size);
    stream->assign(data, data + this->hg.Size);
    
    delete data;
    
    printf("done.\n");
    
    return stream;
}

ValueContainer* ScopeWinInput::load(char* filename)
{
    this->open(filename);
    
    ValueContainer* vc = new ValueContainer();
    
    for (int i = 0; i < this->hg.PocetZaznamu; i++) {
        vc->setStream(i, this->loadStream(i));
    }
    
    return vc;
}
