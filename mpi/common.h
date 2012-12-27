#ifndef MPI_COMMON_H
#define	MPI_COMMON_H

#include "../common.h"

#include <mpi.h>
#include <sys/time.h>
#include <pthread.h>

#define MPI_TAG_RESERVEBLOCK    1000

#define MPI_TAG_PREPAREBLOCK    2000
#define MPI_TAG_OUTPUTBLOCK     2001

extern int mpiRank;
extern int mpiSize;

extern int blocks;

#include "../CorrelationComputer.h"
extern CorrelationComputer* corelComp;

#include "../DistributedComputationFramework.h"
extern DistributedComputationFramework* framework;

void mpiPrintIdentifier();

#define MPI_COUT mpiPrintIdentifier(); std::cout
#define MPI_PRINTF(...) mpiPrintIdentifier(); printf(__VA_ARGS__)

#endif	/* MPI_COMMON_H */

