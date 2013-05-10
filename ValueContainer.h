/* 
 * ValueContainer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef VALUECONTAINER_H
#define VALUECONTAINER_H

#define VALUECONTAINER_FILE_VERSION 1
#define VALUECONTAINER_FILE_DATAOFFSET 64

#include "ValueFrame.h"
#include "ValueStream.h"

#include <fstream>

/**
 * Base class used for chained objects (for details: {@see ValueContainer}).
 */
class ChainedObject {
public:
    ChainedObject() {};
    virtual ~ChainedObject() {};
};

/**
 * Value container holds an array of streams. Streams contain float values.
 * This class works as a universal value exchange storage.
 * 
 * It features methods used for serialisation and deserialisation to and from
 * binary streams.
 * Dynamic loading and unloading is supported - the container is able to load
 * stream data on demand and free the associated memory upon request.
 * 
 * It is possible to associate arbitrary blocks of memory to any stream.
 * The process is called "chaining" - when the stream is to be freed from the
 * memory, the data chained to this stream is delete-ed as well.
 * The chained memory is required to be allocated by "new" so it can be freed
 * using "delete". This provides a way to associate objects and to use their
 * destructors.
 */
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
    
    void setStreamsCount(int count);
    
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
    
    //==========================================================================
   
    /**
     * Returns pointer to previously set chained data or NULL when no previous
     * setting occurred.
     * 
     * @param index
     * @return 
     */
    ChainedObject* getChainedData(int index);
    
    /**
     * Chains a pointer value to the given stream index.
     * 
     * @param index
     * @param data
     */
    void setChainedData(int index, ChainedObject* data);
    
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
    
    /**
     * Are we the owners of the streams memory?
     */
    int managedStreams;
    
    /**
     * Pointer array chained to this one. The size corresponds to the streams
     * array.
     * 
     * The purpose of the chained data is to make the memory management easier.
     */
    ChainedObject** chainedData;
   
};

#endif	/* VALUECONTAINER_H */

