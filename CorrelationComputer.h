/* 
 * CorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef CORRELATIONCOMPUTER_H
#define	CORRELATIONCOMPUTER_H

#include "ValueContainer.h"
#include "ValueStream.h"

class CorrelationComputer {
public:
    CorrelationComputer();
    CorrelationComputer(const CorrelationComputer& orig);
    virtual ~CorrelationComputer();
    
    void setData(ValueContainer* container);
    
    virtual ValueContainer* computeAll();
    virtual ValueStream* computePair(int one, int two);
    virtual ValueStream* computePair(int one, int two, int start, int steps, int tau) = 0;

protected:
    ValueContainer* getValues() {
        return this->container;
    }
    
private:
    ValueContainer* container;
    
};

#endif	/* CORRELATIONCOMPUTER_H */

