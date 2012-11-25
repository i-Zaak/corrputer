/* 
 * ValueContainer
 * 
 * @author David Nemecek
 */

#include <stdexcept>

#include "ValueContainer.h"

ValueContainer::ValueContainer() {
    
}

ValueContainer::ValueContainer(int framesCount, ValueFrame* frames) {
    throw "Not implemented";
}

ValueContainer::ValueContainer(int streamsCount, ValueStream** streams) {
    this->streamsCount = streamsCount;
    this->streams = streams;
}

ValueContainer::ValueContainer(const ValueContainer& orig) {
    throw "Not implemented";
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
    fin >> version;
    if (version != VALUECONTAINER_FILE_VERSION) {
        throw std::runtime_error("Invalid ValueContainer file version.");
    }
    
    // streams count
    int streamsCount;
    fin >> streamsCount;
    if (streamsCount < 1) {
        throw std::runtime_error("Invalid ValueContainer streams count.");
    }
    
    // streams length
    int streamsLength;
    fin >> streamsLength;
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
    fout << ((int)VALUECONTAINER_FILE_VERSION);
    
    // streams count
    fout << this->streamsCount;
    
    // streams length
    fout << this->streamsLength;
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
