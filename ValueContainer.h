/* 
 * ValueContainer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef VALUECONTAINER_H
#define	VALUECONTAINER_H

#include "ValueFrame.h"
#include "ValueStream.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

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
    /**
     * Number of streams in this container, i.e. size of streams attribute.
     */
    int streamsCount;
    
    /**
     * Pole (matice) streamu.
     */
    ValueStream** streams;
   
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & this->streamsCount;
        for (int i = 0; i < this->streamsCount; i++) {
            ar & this->streams[i];
        }
    }
};

#endif	/* VALUECONTAINER_H */

