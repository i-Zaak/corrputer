/* 
 * HDF5Input
 * 
 * @author Jan Fousek <izaak at mail dot muni dot com>
 */

#ifndef HDF5INPUT_H
#define	HDF5INPUT_H

#include "hdf5.h"
#include "DataInputIface.h"
#include "ValueContainer.h"
#include <string>

class HDF5Input : public DataInputIface
{
public:
    HDF5Input();
    HDF5Input(const HDF5Input& orig);
    virtual ~HDF5Input();
    
    void open(char* filename);
    void close();
    
    void loadHeader(ValueContainer* vc);
    ValueStream* loadStream(int index);
    
    void loadStreamName(int index, char* name);
    
    float loadSampleInterval();
    
    ValueContainer* load(char* filename);

    void setDataset(char* dataset);
    
private:
    hid_t h5file;
    hid_t dataset;
    hid_t dataspace;
    int nchans;
    int nsamples;
    std::string datasetpath;

};

#endif	/* HDF5INPUT_H */

