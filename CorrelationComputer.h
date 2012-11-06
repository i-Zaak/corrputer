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
    
    ValueContainer* computeAll();
    ValueStream* computePair(int one, int two);
    virtual float computePairValue(int one, int two, int start, int steps, int tau) = 0;

    int getTauMax() const {
        return tauMax;
    }

    void setTauMax(int tauMax) {
        this->tauMax = tauMax;
    }

    int getWindowSize() const {
        return windowSize;
    }

    void setWindowSize(int windowSize) {
        this->windowSize = windowSize;
    }

    int getSubpartLength() const {
        return subpartLength;
    }

    void setSubpartLength(int subpartLength) {
        this->subpartLength = subpartLength;
    }

    int getSubpartStart() const {
        return subpartStart;
    }

    void setSubpartStart(int subpartStart) {
        this->subpartStart = subpartStart;
    }

protected:
    ValueContainer* getValues() {
        return this->container;
    }
    
private:
    ValueContainer* container;
    
    int windowSize;
    int tauMax;
    int subpartStart;
    int subpartLength;
};

#endif	/* CORRELATIONCOMPUTER_H */

