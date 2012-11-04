/* 
 * ValueContainer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef VALUECONTAINER_H
#define	VALUECONTAINER_H

#include "ValueFrame.h"
#include "ValueStream.h"

class ValueContainer {
public:
    ValueContainer(int framesCount, ValueFrame* frames);
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
     * Returns the number of frames available.
     * 
     * @return 
     */
    int getFramesCount() {
        throw "Not implemented";
    }
    
    /**
     * Returns a single frame from this container.
     * 
     * @param index
     * @return 
     */
    ValueFrame* getFrame(int index) {
        throw "Not implemented";
    }
    
private:
    int streamsCount;
    ValueStream** streams;
    
};

#endif	/* VALUECONTAINER_H */

