/* 
 * NiftiInput
 * 
 * @see http://nifti.nimh.nih.gov/nifti-1/
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef NIFTIINPUT_H
#define	NIFTIINPUT_H

#include "DataInputIface.h"
#include "ValueContainer.h"

class NiftiInput : public DataInputIface
{
public:
    NiftiInput();
    NiftiInput(const NiftiInput& orig);
    virtual ~NiftiInput();
    
    void open(char* filename);
    void close();
    
    void loadHeader(ValueContainer* vc);
    ValueStream* loadStream(int index);
    
    ValueContainer* load(char* filename);
private:

};

#endif	/* NIFTIINPUT_H */

