/* 
 * CrossCorrelationComputer
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef CROSSCORRELATIONCOMPUTER_H
#define	CROSSCORRELATIONCOMPUTER_H

#include "CorrelationComputer.h"

class CrossCorrelationComputer : public CorrelationComputer {
public:
    CrossCorrelationComputer();
    CrossCorrelationComputer(const CrossCorrelationComputer& orig);
    virtual ~CrossCorrelationComputer();
    
    float computePairValue(int one, int two, int start, int steps, int tau);
    
protected:
    virtual void prepareStream(int index);
    
private:
    ValueStream** means;
};

#endif	/* CROSSCORRELATIONCOMPUTER_H */

