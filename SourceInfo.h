/* 
 * SourceInfo
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef SOURCEINFO_H
#define	SOURCEINFO_H

#include "SourcePointInfo.h"

class SourceInfo {
public:
    SourceInfo();
    SourceInfo(const SourceInfo& orig);
    virtual ~SourceInfo();
    
private:
    int pointsCount;
    SourcePointInfo* points;
    
};

#endif	/* SOURCEINFO_H */

