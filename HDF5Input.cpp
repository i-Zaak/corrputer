/* 
 * HDF5Input
 * 
 * @author Jan Fousek <izaak at mail dot muni dot com>
 */

#include "common.h"
#include "HDF5Input.h"
#include "DataInputIface.h"
#include "ValueContainer.h"
#include <string.h>

HDF5Input::HDF5Input() {
}

HDF5Input::HDF5Input(const HDF5Input& orig) {
}

HDF5Input::~HDF5Input() {
}

void HDF5Input::open(char* filename)
{
    printf("Opening file %s\n", filename);
    this->h5file = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);
    
    if (this->h5file < 0) {
        throw std::runtime_error("File could not be opened.");
    }
    
    printf("opened\n");


    this->dataset = H5Dopen(this->h5file, this->datasetpath.c_str());

    if (this->dataset < 0) {
        throw std::runtime_error("Couldn't select dataset.");
    }

    this->dataspace = H5Dget_space(this->dataset);

    if (this->dataspace < 0) {
        throw std::runtime_error("Couldn't select dataspace.");
    }
}
void HDF5Input::setDataset(char* dataset)
{
    this->datasetpath = std::string(dataset,strlen(dataset));
}


void HDF5Input::close()
{
    H5Fclose(this->h5file);
}

void HDF5Input::loadHeader(ValueContainer* vc)
{
    printf("Gathering metadata...");
    hsize_t dimsr[2];
    hsize_t maxdimsr[2];
    herr_t status;
    status = H5Sget_simple_extent_dims(this->dataspace, dimsr, maxdimsr); 
    if (status< 0) {
        throw std::runtime_error("Couldn't get the data dimensions.");
    }
    
    vc->setStreamsCount(dimsr[0]);
    vc->setStreamsLength(dimsr[1]);
    this->nchans = dimsr[0];
    this->nsamples = dimsr[1];
    
    printf("done.\n");
    printf("samples: %d, channels: %d\n",this->nsamples ,this->nchans);
}

float HDF5Input::loadSampleInterval()
{
    printf("FIXME! Hardcoded 5kHz sampling frequency.");
    return 0.0002;
}

ValueStream* HDF5Input::loadStream(int index)
{
    herr_t status;
    hsize_t count[2];
    hsize_t offset[2];
	hid_t memspace;
	hsize_t memdim[1];
	hsize_t memcount[1];
	hsize_t memoffset[1];

    printf("Loading stream %d...", index);
    
	hid_t datatype = H5Dget_type(this->dataset);
	hid_t native_type = H5Tget_native_type(datatype, H5T_DIR_ASCEND);

	int* dataint;
	if(H5Tequal(H5T_NATIVE_INT,native_type)){
    	int *dataint = (int *) malloc(this->nsamples * sizeof (int));
    	if (dataint == NULL) {
    	    throw std::runtime_error("Memory allocation failed!");
    	}
	}else if(!H5Tequal(H5T_NATIVE_FLOAT,native_type)){
		throw std::runtime_error("Data are not float nor int!");
	}
    float *data = (float *) malloc(this->nsamples * sizeof (float));
    if (data == NULL) {
        throw std::runtime_error("Memory allocation failed!");
    }


    offset[0] = index;
    offset[1] = 0;

    count[0]  = 1;  
    count[1]  = this->nsamples;

	memoffset[0] = 0;
	memcount[0]  = this->nsamples;
	memdim[0]    = this->nsamples; 


    status = H5Sselect_hyperslab(this->dataspace, H5S_SELECT_SET, offset, NULL, count, NULL);
    if (status< 0) {
        throw std::runtime_error("Couldn't select data subspace.");
    }
	memspace = H5Screate_simple(1, memdim, NULL);
	status = H5Sselect_hyperslab(memspace, H5S_SELECT_SET, memoffset, NULL, memcount, NULL);
    if (status< 0) {
        throw std::runtime_error("Couldn't select memory subspace.");
    }

	if(H5Tequal(H5T_NATIVE_FLOAT,native_type)){
    	status = H5Dread(this->dataset, H5T_IEEE_F32LE, memspace, this->dataspace, H5P_DEFAULT, data);
	}else{
    	status = H5Dread(this->dataset, H5T_STD_I32LE, memspace, this->dataspace, H5P_DEFAULT, dataint);
    	std::copy(dataint, dataint + this->nsamples, data);
	}
    if (status< 0) {
        throw std::runtime_error("Couldn't read data subspace.");
    }

    
    // create a new value stream
    ValueStream* stream = new ValueStream();
    stream->reserve(this->nsamples);
    stream->assign(data, data + this->nsamples);
    
    delete data;
	if(H5Tequal(H5T_NATIVE_INT,native_type)){
		delete dataint;
	}
    
    printf("done.\n");
    
    return stream;
}

void HDF5Input::loadStreamName(int index, char* name)
{
    printf("FIXME! Hardcoded names of the channels.");
    sprintf(name, "%d", index );
}

ValueContainer* HDF5Input::load(char* filename)
{
    this->open(filename);
    
    ValueContainer* vc = new ValueContainer();
    
    for (int i = 0; i < this->nchans; i++) {
        vc->setStream(i, this->loadStream(i));
    }
    
    return vc;
}
