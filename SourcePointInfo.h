/* 
 * SourcePointInfo
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef SOURCEPOINTINFO_H
#define	SOURCEPOINTINFO_H

#include <string>

class SourcePointInfo {
public:
    SourcePointInfo();
    SourcePointInfo(const SourcePointInfo& orig);
    virtual ~SourcePointInfo();
    
private:
    std::string name;
    float sampleDistance;
    
};

#endif	/* SOURCEPOINTINFO_H */

