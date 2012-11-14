/* 
 * NiftiInput
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "common.h"
#include "NiftiInput.h"
#include "lib/swutils.h"
#include "DataInputIface.h"
#include "ValueContainer.h"
#include "lib/nifti1.h"

NiftiInput::NiftiInput() {
}

NiftiInput::NiftiInput(const NiftiInput& orig) {
}

NiftiInput::~NiftiInput() {
}

ValueContainer* NiftiInput::load(char* filename)
{
    //
    // Open and load a nifti-1 header file.
    //
    printf("Opening file %s\n", filename);
    FILE *file = fopen(filename, "rb");
	
    if (file == NULL) {
        throw std::runtime_error("File could not be opened.");
    }
    printf("done\n");	
    
    nifti_1_header header;
    fread(&header, sizeof(header), 1, file);
    
    if (NIFTI_VERSION(header) <= 0) {
        throw std::runtime_error("Invalid header version.");
    }
    
    /*
    fprintf(stderr, "\n%s header information:",filename);
    fprintf(stderr, "\nXYZT dimensions: %d %d %d %d",header.dim[1],header.dim[2],header.dim[3],header.dim[4]);
    fprintf(stderr, "\nDatatype code and bits/pixel: %d %d",header.datatype,header.bitpix);
    fprintf(stderr, "\nScaling slope and intercept: %.6f %.6f",header.scl_slope,header.scl_inter);
    fprintf(stderr, "\nByte offset to data in datafile: %ld",(long)(header.vox_offset));
    fprintf(stderr, "\n");
    /**/

    
    int voxelCount = header.dim[1] * header.dim[2] * header.dim[3];
    int frameCount = header.dim[4];
    int pointSize = header.bitpix / 8;
    int pointDatatype = header.datatype;
    
    //
    // Based on the header - move file pointer or open a data file.
    //
    if (NIFTI_ONEFILE(header)) {
        // data in the same file
        // => just move the file pointer
        fseek(file,header.vox_offset, SEEK_SET);
    } else if (strcmp(header.magic, "n+1")) {
        // external .img file
        // => close the header file
        fclose(file);
        printf("Header file closed.\n");
        // prepare datafile name
        char datafile[256];
        char ext[] = "img";
        strcpy(datafile, filename);
        datafile[strlen(datafile)-3] = ext[0];
        datafile[strlen(datafile)-2] = ext[1];
        datafile[strlen(datafile)-1] = ext[2];
        // open the datafile
        file = fopen(datafile, "rb");
        if (file == NULL) {
            throw std::runtime_error("Datafile could not be opened.");
        }
        printf("Data file opened.\n");
    }
    
    //
    // Load data values
    //
    // first prepare the resulting streams
    ValueStream** streams = new ValueStream*[voxelCount];
    for (int i = 0; i < voxelCount; i++) {
        streams[i] = new ValueStream();
        streams[i]->reserve(frameCount);
    }
    // then read every frame
    void* data = malloc(pointSize * voxelCount);
    if (data == NULL) {
        throw std::runtime_error("Datafile memory allocation failed.");
    }
    for (int i = 0; i < frameCount; i++) {
        printf("Frame %d...\n", i);
        int ret = fread(data, pointSize, voxelCount, file);
        if (ret != voxelCount) {
            if (feof(file)) {
                throw std::runtime_error("Datafile reading failed - EOF reached.");
            } else if (ferror(file)) {
                throw std::runtime_error("Datafile reading failed with error.");
            } else {
                throw std::runtime_error("Datafile reading failed.");
            }
        }

        // add values to their streams
        for (int j = 0; j < voxelCount; j++) {
            float val = 0.0f;
            switch (pointDatatype) {
                case DT_INT16:
                    val = float(((short*)data)[j]);
                    break;
                case DT_INT32:
                    val = float(((int*)data)[j]);
                    break;
                case DT_FLOAT32:
                    val = float(((float*)data)[j]);
                    break;
                case DT_FLOAT64:
                    val = float(((double*)data)[j]);
                    break;
                default:
                    throw std::runtime_error("Data type not supported.");
            }
            streams[j]->push_back(val);
        }
    }
    free(data);
    fclose(file);
    printf("File closed.\n");
    
    // generate the final value container from the streams
    return new ValueContainer(voxelCount, streams);
}