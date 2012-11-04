#ifndef DATAINPUTIFACE_H
#define	DATAINPUTIFACE_H

#include "ValueContainer.h"

class DataInputIface {
public:
    DataInputIface();
    DataInputIface(const DataInputIface& orig);
    virtual ~DataInputIface();
    
    virtual ValueContainer* load(char* filename) = 0;
private:

};

#endif	/* DATAINPUTIFACE_H */

