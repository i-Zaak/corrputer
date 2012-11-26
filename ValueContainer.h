/* 
 * ValueContainer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef VALUECONTAINER_H
#define	VALUECONTAINER_H

#define VALUECONTAINER_FILE_VERSION 1
#define VALUECONTAINER_FILE_DATAOFFSET 64

#include "ValueFrame.h"
#include "ValueStream.h"

#include <fstream>

class ValueContainer {
public:
    ValueContainer();
    ValueContainer(int streamsCount, ValueStream** streams);
    ValueContainer(const ValueContainer& orig);
    virtual ~ValueContainer();
    
    /**
     * Returns the number of available streams.
     * 
     * @return 
     */
    int getStreamsCount() {
        return this->streamsCount;
    }
    
    void setStreamsCount(int count) {
        this->streamsCount = count;
        
        // allocate required memory for streams
        this->streams = new ValueStream*[streamsCount];
    }
    
    /**
     * Returns the number of values in a stream.
     * 
     * @return 
     */
    int getStreamsLength() {
        return this->streamsLength;
    }
    
    void setStreamsLength(int length) {
        this->streamsLength = length;
    }
    
    /**
     * Returns a single value stream.
     * 
     * @param index
     * @return 
     */
    ValueStream* getStream(int index) {
        return this->streams[index];
    }
    
    /**
     * Assigns a single value stream to the given index.
     * This method should not be normally used.
     * 
     * @param index
     * @param vs
     */
    void setStream(int index, ValueStream* vs) {
        this->streams[index] = vs;
    }
    
    //==========================================================================
   
    /**
     * Loads header from a file.
     * This is more or less an internal method.
     * 
     * @param index
     * @param fout
     */
    void loadHeader(std::ifstream &fin);
    
    /**
     * Saves header to a file.
     * This is more or less an internal method.
     * 
     * @param index
     * @param fout
     */
    void saveHeader(std::ofstream &fout);
    
    /**
     * Loads the given stream from a file.
     * This is more or less an internal method.
     * 
     * @param index
     * @param fout
     */
    void loadStream(int index, std::ifstream &fin);
    
    /**
     * Saves the given stream to a file.
     * This is more or less an internal method.
     * 
     * @param index
     * @param fout
     */
    void saveStream(int index, std::ofstream &fout);
    
    /**
     * Frees resources associated with the given stream.
     */
    void freeStream(int index);
    
private:
    /**
     * Number of streams in this container, i.e. size of streams attribute.
     */
    int streamsCount;
    
    /**
     * Number of values in every stream.
     */
    int streamsLength;
    
    /**
     * Array of streams.
     */
    ValueStream** streams;
   
};

#endif	/* VALUECONTAINER_H */

