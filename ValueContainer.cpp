/* 
 * ValueContainer
 * 
 * @author David Nemecek
 */

#include <stdexcept>

#include "ValueContainer.h"

ValueContainer::ValueContainer() {
    
}

ValueContainer::ValueContainer(int streamsCount, ValueStream** streams) {
    this->streamsCount = streamsCount;
    this->streams = streams;
}

ValueContainer::~ValueContainer() {
}

//==========================================================================

void ValueContainer::loadHeader(std::ifstream &fin)
{
    // reset position
    fin.seekg(0, std::ios::beg);
    
    // version check
    int version;
    fin.read((char*)&version, 4);
    if (version != VALUECONTAINER_FILE_VERSION) {
        throw std::runtime_error("Invalid ValueContainer file version.");
    }
    
    // streams count
    int streamsCount;
    fin.read((char*)&streamsCount, 4);
    if (streamsCount < 1) {
        throw std::runtime_error("Invalid ValueContainer streams count.");
    }
    
    // streams length
    int streamsLength;
    fin.read((char*)&streamsLength, 4);
    if (streamsLength < 1) {
        throw std::runtime_error("Invalid ValueContainer streams length.");
    }
    
    // save header values
    this->setStreamsCount(streamsCount);
    this->setStreamsLength(streamsLength);
}

//==========================================================================

void ValueContainer::saveHeader(std::ofstream &fout)
{
    // reset position
    fout.seekp(0, std::ios::beg);
    
    // version
    int version = VALUECONTAINER_FILE_VERSION;
    fout.write((char*)&version, 4);
    
    // streams count
    fout.write((char*)&this->streamsCount, 4);
    
    // streams length
    fout.write((char*)&this->streamsLength, 4);
}

//==========================================================================

void ValueContainer::loadStream(int index, std::ifstream &fin)
{
    // seek position
    fin.seekg(VALUECONTAINER_FILE_DATAOFFSET + index * this->streamsLength * sizeof(float), std::ios::beg);
    
    // read data block
    float* values = new float[this->streamsLength];
    fin.read((char*)values, sizeof(float) * this->streamsLength);
            
    // generate a stream
    this->streams[index] = new ValueStream();
    this->streams[index]->reserve(this->streamsLength);
    this->streams[index]->assign(values, values + this->streamsLength);
    
    // clear temp memory
    delete values;
}

//==========================================================================

void ValueContainer::saveStream(int index, std::ofstream &fout)
{
    // seek position
    fout.seekp(VALUECONTAINER_FILE_DATAOFFSET + index * this->streamsLength * sizeof(float), std::ios::beg);
    
    // write the data block
    float* data = &((*this->streams[index])[0]);
    fout.write((char*)data, sizeof(float) * this->streamsLength);
}

//==========================================================================

void ValueContainer::freeStream(int index)
{
    ValueStream* vs = this->streams[index];
    
    if (vs == NULL) {
        return;
    }
    
    this->streams[index] = NULL;
    delete vs;
}
