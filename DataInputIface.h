#ifndef DATAINPUTIFACE_H
#define	DATAINPUTIFACE_H

#include "ValueContainer.h"
#include <list>

class DataInputIface {
public:
    DataInputIface();
    DataInputIface(const DataInputIface& orig);
    virtual ~DataInputIface();
    
    virtual void open(char* filename) = 0;
    virtual void close() = 0;
    
    virtual void loadHeader(ValueContainer* vc) = 0;
    virtual ValueStream* loadStream(int index) = 0;
    
    virtual void loadStreamName(int index, char* name) = 0;
    
    virtual float loadSampleInterval() = 0;
    
    virtual ValueContainer* load(char* filename) = 0;
private:

};

#endif	/* DATAINPUTIFACE_H */

