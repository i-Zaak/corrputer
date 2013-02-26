/* 
 * NiftiInput
 * 
 * @see http://nifti.nimh.nih.gov/nifti-1/
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef NIFTIINPUT_H
#define	NIFTIINPUT_H

#include "lib/nifti1.h"
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
    FILE* file;
    std::string filename;
    std::string filenamePrefix;
    int filenameNumberLength;
    
    nifti_1_header header;
    
    int framesCount;
    std::vector< FILE* > frameFiles;
    
    int voxelCount;
    int pointSize;
    int pointDatatype;
    
    std::string getFrameFilename(int number);
};

#endif	/* NIFTIINPUT_H */

