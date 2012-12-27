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
    ValueStream* computePair(int one, int two);
    virtual float computePairValue(int one, int two, int start, int steps, int tau) = 0;

    //======================================================================
    // Computation configuration
    
    int getTauMax();
    void setTauMax(int tauMax);
    
    int getWindowSize();
    void setWindowSize(int windowSize);
    
    int getStepSize();
    void setStepSize(int stepSize);

    int getSubpartLength();
    void setSubpartLength(int subpartLength);

    int getSubpartStart();
    void setSubpartStart(int subpartStart);

    //======================================================================
    
    /**
     * Performs initialisations of internal structures. After this call any
     * configuration changing operations will result in error.
     */
    virtual void init();
    
    //======================================================================
    
    int getOutputLength();
    
protected:
    ValueContainer* getValues() {
        return this->container;
    }
    
    /**
     * Prepares values and statistics needed later on for correlation
     * computations. Acts as a cache maintainer.
     */
    virtual void prepareStream(int index);
    
private:
    ValueContainer* container;
    
    int windowSize;
    int windowStep;
    int tauMax;
    int subpartStart;
    int subpartLength;
    
    int inited;
    
    int inDataStart;
    int inDataStop;
    int outDataLength;
};

#endif	/* CORRELATIONCOMPUTER_H */

