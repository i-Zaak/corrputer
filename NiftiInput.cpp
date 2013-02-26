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

void NiftiInput::open(char* filename)
{
    printf("Opening file %s\n", filename);
    this->file = fopen(filename, "rb");
	
    if (this->file == NULL) {
        throw std::runtime_error("File could not be opened.");
    }
    
    this->filename = filename;
    
    // find filename prefix, i.e. "somefile_001.ext" --> "somefile_"
    std::string digits ("0123456789");
    std::string prefixCandidate = this->filename.substr(0, this->filename.length() - 4 /*strlen(".ext")+1*/);
    int prefixLength = prefixCandidate.find_last_not_of(digits);
    if (prefixLength == std::string::npos) {
        prefixLength = prefixCandidate.length();
    }
    this->filenamePrefix = this->filename.substr(0, prefixLength+1);
    this->filenameNumberLength = prefixCandidate.length() - this->filenamePrefix.length();
    printf("Filename prefix: %s\n", this->filenamePrefix.c_str());
    printf("Filename number length: %d\n", this->filenameNumberLength);
    
    if (this->filenameNumberLength <= 0) {
        throw "Number in filename not found. Invalid file name, must by in the form 'some_name_1234.ext'";
    }
    
    printf("opened\n");
}

void NiftiInput::close()
{
    for (int frame = 1; frame <= this->framesCount; frame++) {
        FILE* f = this->frameFiles.at(frame-1);
        fclose(f);
    }
    
    fclose(this->file);
}

void NiftiInput::loadHeader(ValueContainer* vc)
{
    printf("Loading header...\n");
    
    fseek(this->file,0,SEEK_SET);

    fread(&header, sizeof(header), 1, file);
    
    if (NIFTI_VERSION(header) <= 0) {
        throw std::runtime_error("Invalid header version.");
    }
    
    /*
    fprintf(stderr, "\n%s header information:",filename.c_str());
    fprintf(stderr, "\nXYZT dimensions: %d %d %d %d",header.dim[1],header.dim[2],header.dim[3],header.dim[4]);
    fprintf(stderr, "\nDatatype code and bits/pixel: %d %d",header.datatype,header.bitpix);
    fprintf(stderr, "\nScaling slope and intercept: %.6f %.6f",header.scl_slope,header.scl_inter);
    fprintf(stderr, "\nByte offset to data in datafile: %ld",(long)(header.vox_offset));
    fprintf(stderr, "\n");
    /**/
    
    // basic configuration
    voxelCount = header.dim[1] * header.dim[2] * header.dim[3];
    pointSize = header.bitpix / 8;
    pointDatatype = header.datatype;
    
    vc->setStreamsCount(voxelCount);
    printf("Number of voxels: %d\n", voxelCount);
    
    // find how many "frame" files are available
    printf("Determining the number of available frames...\n\t");
    int maxFrames = 1;
    for (int i = 0; i < this->filenameNumberLength; i++) {
        maxFrames *= 10;
    }
    int frames;
    //this->frameFiles = new std::vector< FILE* >();
    for (frames = 1; frames < maxFrames; frames++) {
        std::string name = this->getFrameFilename(frames);
        FILE* f = fopen(name.c_str(), "rb");

        if (f == NULL) {
            printf("...'%s' not found", name.c_str());
            break;
        }
        frameFiles.push_back(f);
        printf("%d ", frames);
        if (frames % 10 == 0) {
            printf("\n\t");
        }
    }
    frames -= 1;
    vc->setStreamsLength(frames);
    this->framesCount = frames;
    printf("...%d\n", frames);
    
    printf("done.\n");
}

ValueStream* NiftiInput::loadStream(int index)
{
    printf("Loading stream %8d / %8d...", index, voxelCount);
    std::cout.flush();
    ValueStream* vs = new ValueStream();
    for (int frame = 1; frame <= this->framesCount; frame++) {
        FILE* f = this->frameFiles.at(frame-1);
        
        if (NIFTI_ONEFILE(header)) {
            // data in the same file
            // => just move the file pointer
            fseek(f,header.vox_offset, SEEK_SET);
        } else if (strcmp(header.magic, "n+1")) {
            // external .img file
            // => move to the start
            fseek(f,0, SEEK_SET);
        }
        
        // move to the voxel
        fseek(f, pointSize * index, SEEK_CUR);
        
        // load the value
        char data[32];
        int ret = fread(data, pointSize, 1, f);
        if (ret != 1) {
            if (feof(file)) {
                throw std::runtime_error("Datafile reading failed - EOF reached.");
            } else if (ferror(file)) {
                throw std::runtime_error("Datafile reading failed with error.");
            } else {
                throw std::runtime_error("Datafile reading failed.");
            }
        }

        // add value to the stream
        float val = 0.0f;
        switch (pointDatatype) {
            case DT_INT16:
                val = float(((short*)data)[0]);
                break;
            case DT_INT32:
                val = float(((int*)data)[0]);
                break;
            case DT_FLOAT32:
                val = float(((float*)data)[0]);
                break;
            case DT_FLOAT64:
                val = float(((double*)data)[0]);
                break;
            default:
                throw std::runtime_error("Data type not supported.");
        }
        vs->push_back(val);
    }
    printf("done.\n");
    return vs;
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

//======================================================================

std::string NiftiInput::getFrameFilename(int frame)
{
    char number[128];
    sprintf(number, "%0100d", frame);
    std::string name (this->filenamePrefix);
    name.append(std::string(number).substr(100 - this->filenameNumberLength));
    name.append(".img");
    return name;
}