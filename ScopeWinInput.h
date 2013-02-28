/* 
 * ScopeWinInput
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef SCOPEWININPUT_H
#define	SCOPEWININPUT_H

#include "lib/swutils.h"
#include "DataInputIface.h"
#include "ValueContainer.h"

class ScopeWinInput : public DataInputIface
{
public:
    ScopeWinInput();
    ScopeWinInput(const ScopeWinInput& orig);
    virtual ~ScopeWinInput();
    
    void open(char* filename);
    void close();
    
    void loadHeader(ValueContainer* vc);
    ValueStream* loadStream(int index);
    
    void loadStreamName(int index, char* name);
    
    float loadSampleInterval();
    
    ValueContainer* load(char* filename);
    
private:
    FILE* file;

    struct IG_s ig;
    struct HG_s hg;
};

#endif	/* SCOPEWININPUT_H */

