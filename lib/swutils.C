#include <stdio.h>
#include <string.h>
#include "swutils.h"

void readIG( FILE *file, IG_s *ig){
	if(fread(&ig->SoftVersion, 20, 1, file) != 1) {
		printf("File reading error\n");
	}
	//ig->SoftVersion[20]='\0';
	if(fread(&ig->CelkovyPocetKanalu, 2, 1, file) != 1) {
		printf("File reading error\n");
	}
}

void readHG(FILE *file, HG_s *hg){
	if(fread(&hg->PocetZaznamu, 2, 1, file) != 1) {
                printf("File reading error\n");
        }
	for (int i = 0; i < MAXCHANNUMB; i++) {
		if(fread(&hg->Zaznam[i], 2, 1, file) != 1) {
        	        printf("File reading error\n");
        	}
	}
	if(fread(&hg->Size, 4, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&hg->Waveform, 2, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&hg->Date, 12, 1, file) != 1) {
		printf("File reading error\n");
	}
	if(fread(&hg->EventDetected, 2, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&hg->Before, 4, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&hg->EventTime.ti_min, 1, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&hg->EventTime.ti_hour, 1, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&hg->EventTime.ti_hund, 1, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&hg->EventTime.ti_sec, 1, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&hg->Comment, COMMENTDIM, 1, file) != 1) {
		printf("File reading error\n");
	}
}

void readFG(FILE *file, FG_s *fg){
	if(fread(&fg->Freq, 2, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&fg->Name, 30, 1, file) != 1) {
		printf("File reading error\n");
	}
	if(fread(&fg->SI, 20, 1, file) != 1) {
		printf("File reading error\n");
	}
	if(fread(&fg->Unit, 2, 1, file) != 1) {
                printf("File reading error\n");
        }
	if(fread(&fg->XUnit, 20, 1, file) != 1) {
		printf("File reading error\n");
	}
	if(fread(&fg->XDelta, 4, 1, file) != 1) {
                printf("File reading error\n");
        }
}


void readData(FILE *file, float* data, DATAindx length){
	for (int i = 0; i < length; i++) {
		if(fread(&data[i], 4, 1, file) != 1) {
        	        printf("File reading error\n");
        	}
	}
}

void printIG(IG_s *ig){
	printf("Version: %.*s\n", 20, ig->SoftVersion);
	printf("Number of channels: %i\n", ig->CelkovyPocetKanalu);
}

void printHG( HG_s *hg ){
	printf("Number of records: %i\n", hg->PocetZaznamu);
	printf("Channels:\n");
	for (int i = 0; i < MAXCHANNUMB; i++) {
		printf("%i: %i\n", i, hg->Zaznam[i]);
	}
	printf("Size of one channel: %ld\n", hg->Size);
	printf("Type [TRUE - wave, FALSE - mesurement]: %i\n", hg->Waveform);
	printf("Date: %.*s\n",12, hg->Date);
	printf("Event detected: %i\n", hg->EventDetected);
	printf("Points before event: %li\n", hg->Before);
	printf("Time of event: %ih %im %ihs %is\n", hg->EventTime.ti_hour, hg->EventTime.ti_min,hg->EventTime.ti_hund,hg->EventTime.ti_sec);
	printf("Comment: %s\n", hg->Comment);
}

void printFG( FG_s *fg ){
	printf("In frequency domain [bool]: %i\n", fg->Freq);
	printf("Name of channel: %s\n", fg->Name);
	printf("Units: %s\n", fg->SI);
	printf("Magnitude of the unit [1 No U,  2 uU, 3 mU, 4 U, 5 kU, 6 MU]: %i\n", fg->Unit);
	printf("Time axis unit: %s\n", fg->XUnit);
	printf("Sample distance [s]: %f\n", fg->XDelta);
}

