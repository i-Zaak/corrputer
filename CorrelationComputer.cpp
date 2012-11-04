/* 
 * CorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "CorrelationComputer.h"

CorrelationComputer::CorrelationComputer() {
}

CorrelationComputer::CorrelationComputer(const CorrelationComputer& orig) {
}

CorrelationComputer::~CorrelationComputer() {
}

void CorrelationComputer::setData(ValueContainer* container)
{
    this->container = container;
}

ValueContainer* CorrelationComputer::computeAll()
{
    int count = this->container->getStreamsCount();
    ValueStream** streams = new ValueStream*[count];
    
    for (int one = 0; one < count; one++) {
        for (int two = 0; two < count; two++) {
            streams[one * count + two] = this->computePair(one, two);
        }
    }
    return new ValueContainer(count * count, streams);
}

ValueStream* CorrelationComputer::computePair(int one, int two)
{
    
}