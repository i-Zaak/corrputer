/* 
 * ScopeWinInput
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef SCOPEWININPUT_H
#define	SCOPEWININPUT_H

#include "DataInputIface.h"
#include "ValueContainer.h"

class ScopeWinInput : public DataInputIface
{
public:
    ScopeWinInput();
    ScopeWinInput(const ScopeWinInput& orig);
    virtual ~ScopeWinInput();
    
    ValueContainer* load(char* filename);
private:

};

#endif	/* SCOPEWININPUT_H */

