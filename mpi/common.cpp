#include "common.h"

void mpiPrintIdentifier() {
    struct timeval time;
    gettimeofday(&time, NULL);
    int timeHrs = (time.tv_sec / 60 / 60) % 24;
    int timeMins = (time.tv_sec / 60) % 60;
    int timeSec = time.tv_sec % 60;
    printf("[%02d:%02d:%02d.%06d][N%02d] ", timeHrs, timeMins, timeSec, time.tv_usec,
            mpiRank);
}
