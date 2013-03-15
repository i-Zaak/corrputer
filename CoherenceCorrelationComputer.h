/* 
 * CoherenceCorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef COHERENCECORRELATIONCOMPUTER_H
#define	COHERENCECORRELATIONCOMPUTER_H

#include "CorrelationComputer.h"
#include <fftw3.h>

class CoherenceCorrelationComputer : public CorrelationComputer {
public:
    CoherenceCorrelationComputer();
    CoherenceCorrelationComputer(const CoherenceCorrelationComputer& orig);
    virtual ~CoherenceCorrelationComputer();
    
    float computePairValue(int one, int two, int start, int steps, int tau);
    
    void setFrequencyRangeBegin(float value);
    void setFrequencyRangeEnd(float value);
    
    void init();
    
protected:
    virtual void prepareStream(int index);
    
private:
    // configuration
    float frequencyRangeBegin;
    float frequencyRangeEnd;
    
    // temporary variables
    fftw_complex *tsOne, *tsTwo;
    fftw_complex *freqOne, *freqTwo;
    fftw_plan planOne, planTwo;
    int fftRangeBegin;
    int fftRangeEnd;
};

#endif	/* COHERENCECORRELATIONCOMPUTER_H */

