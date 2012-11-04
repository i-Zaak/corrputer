/* 
 * ValueContainer
 * 
 * @author David Nemecek
 */

#include "ValueContainer.h"

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

