#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/SimpleComputationFramework.o \
	${OBJECTDIR}/ValueStream.o \
	${OBJECTDIR}/ScopeWinInput.o \
	${OBJECTDIR}/CrossCorrelationComputer.o \
	${OBJECTDIR}/NiftiInput.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/DataInputIface.o \
	${OBJECTDIR}/SourceInfo.o \
	${OBJECTDIR}/ComputationFramework.o \
	${OBJECTDIR}/main_mpi.o \
	${OBJECTDIR}/mpi/Saver.o \
	${OBJECTDIR}/CorrelationComputer.o \
	${OBJECTDIR}/DistributedComputationFramework.o \
	${OBJECTDIR}/FrameContainerGenerator.o \
	${OBJECTDIR}/mpi/common.o \
	${OBJECTDIR}/ValueFrame.o \
	${OBJECTDIR}/Statistics.o \
	${OBJECTDIR}/ValueContainerGenerator.o \
	${OBJECTDIR}/mpi/Worker.o \
	${OBJECTDIR}/_ext/126195727/ConfigFile.o \
	${OBJECTDIR}/lib/swutils.o \
	${OBJECTDIR}/ValueContainer.o \
	${OBJECTDIR}/mpi/Coordinator.o \
	${OBJECTDIR}/SourcePointInfo.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver_release

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver_release: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver_release ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/SimpleComputationFramework.o: SimpleComputationFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/SimpleComputationFramework.o SimpleComputationFramework.cpp

${OBJECTDIR}/ValueStream.o: ValueStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueStream.o ValueStream.cpp

${OBJECTDIR}/ScopeWinInput.o: ScopeWinInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ScopeWinInput.o ScopeWinInput.cpp

${OBJECTDIR}/CrossCorrelationComputer.o: CrossCorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/CrossCorrelationComputer.o CrossCorrelationComputer.cpp

${OBJECTDIR}/NiftiInput.o: NiftiInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/NiftiInput.o NiftiInput.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/DataInputIface.o: DataInputIface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataInputIface.o DataInputIface.cpp

${OBJECTDIR}/SourceInfo.o: SourceInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourceInfo.o SourceInfo.cpp

${OBJECTDIR}/ComputationFramework.o: ComputationFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ComputationFramework.o ComputationFramework.cpp

${OBJECTDIR}/main_mpi.o: main_mpi.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_mpi.o main_mpi.cpp

${OBJECTDIR}/mpi/Saver.o: mpi/Saver.cpp 
	${MKDIR} -p ${OBJECTDIR}/mpi
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/mpi/Saver.o mpi/Saver.cpp

${OBJECTDIR}/CorrelationComputer.o: CorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/CorrelationComputer.o CorrelationComputer.cpp

${OBJECTDIR}/DistributedComputationFramework.o: DistributedComputationFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/DistributedComputationFramework.o DistributedComputationFramework.cpp

${OBJECTDIR}/FrameContainerGenerator.o: FrameContainerGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/FrameContainerGenerator.o FrameContainerGenerator.cpp

${OBJECTDIR}/mpi/common.o: mpi/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/mpi
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/mpi/common.o mpi/common.cpp

${OBJECTDIR}/ValueFrame.o: ValueFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueFrame.o ValueFrame.cpp

${OBJECTDIR}/Statistics.o: Statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/Statistics.o Statistics.cpp

${OBJECTDIR}/ValueContainerGenerator.o: ValueContainerGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainerGenerator.o ValueContainerGenerator.cpp

${OBJECTDIR}/mpi/Worker.o: mpi/Worker.cpp 
	${MKDIR} -p ${OBJECTDIR}/mpi
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/mpi/Worker.o mpi/Worker.cpp

${OBJECTDIR}/_ext/126195727/ConfigFile.o: /media/shared/diplomka/masterserver/ConfigFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/126195727
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/126195727/ConfigFile.o /media/shared/diplomka/masterserver/ConfigFile.cpp

${OBJECTDIR}/lib/swutils.o: lib/swutils.C 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/swutils.o lib/swutils.C

${OBJECTDIR}/ValueContainer.o: ValueContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainer.o ValueContainer.cpp

${OBJECTDIR}/mpi/Coordinator.o: mpi/Coordinator.cpp 
	${MKDIR} -p ${OBJECTDIR}/mpi
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/mpi/Coordinator.o mpi/Coordinator.cpp

${OBJECTDIR}/SourcePointInfo.o: SourcePointInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourcePointInfo.o SourcePointInfo.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver: ${TESTDIR}/_ext/1288231903/ConfigFileTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver: ${TESTDIR}/tests/CrossCorrelationTest.o ${TESTDIR}/tests/CrossCorrelationTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver: ${TESTDIR}/tests/DistributedComputationFrameworkTest.o ${TESTDIR}/tests/DistributedComputationFrameworkTestRunner.o ${TESTDIR}/tests/TestedDistributedComputationFramework.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver: ${TESTDIR}/tests/RunningVarianceTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver: ${TESTDIR}/tests/ValueContainerSerializationTest.o ${TESTDIR}/tests/testrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver $^ ${LDLIBSOPTIONS} 


${TESTDIR}/_ext/1288231903/ConfigFileTest.o: /media/shared/diplomka/masterserver/tests/ConfigFileTest.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/1288231903
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/_ext/1288231903/ConfigFileTest.o /media/shared/diplomka/masterserver/tests/ConfigFileTest.cpp


${TESTDIR}/tests/CrossCorrelationTest.o: tests/CrossCorrelationTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CrossCorrelationTest.o tests/CrossCorrelationTest.cpp


${TESTDIR}/tests/CrossCorrelationTestRunner.o: tests/CrossCorrelationTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CrossCorrelationTestRunner.o tests/CrossCorrelationTestRunner.cpp


${TESTDIR}/tests/DistributedComputationFrameworkTest.o: tests/DistributedComputationFrameworkTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/DistributedComputationFrameworkTest.o tests/DistributedComputationFrameworkTest.cpp


${TESTDIR}/tests/DistributedComputationFrameworkTestRunner.o: tests/DistributedComputationFrameworkTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/DistributedComputationFrameworkTestRunner.o tests/DistributedComputationFrameworkTestRunner.cpp


${TESTDIR}/tests/TestedDistributedComputationFramework.o: tests/TestedDistributedComputationFramework.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/TestedDistributedComputationFramework.o tests/TestedDistributedComputationFramework.cpp


${TESTDIR}/tests/RunningVarianceTest.o: tests/RunningVarianceTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/RunningVarianceTest.o tests/RunningVarianceTest.cpp


${TESTDIR}/tests/ValueContainerSerializationTest.o: tests/ValueContainerSerializationTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ValueContainerSerializationTest.o tests/ValueContainerSerializationTest.cpp


${TESTDIR}/tests/testrunner.o: tests/testrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/testrunner.o tests/testrunner.cpp


${OBJECTDIR}/SimpleComputationFramework_nomain.o: ${OBJECTDIR}/SimpleComputationFramework.o SimpleComputationFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SimpleComputationFramework.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SimpleComputationFramework_nomain.o SimpleComputationFramework.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SimpleComputationFramework.o ${OBJECTDIR}/SimpleComputationFramework_nomain.o;\
	fi

${OBJECTDIR}/ValueStream_nomain.o: ${OBJECTDIR}/ValueStream.o ValueStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ValueStream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueStream_nomain.o ValueStream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ValueStream.o ${OBJECTDIR}/ValueStream_nomain.o;\
	fi

${OBJECTDIR}/ScopeWinInput_nomain.o: ${OBJECTDIR}/ScopeWinInput.o ScopeWinInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ScopeWinInput.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ScopeWinInput_nomain.o ScopeWinInput.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ScopeWinInput.o ${OBJECTDIR}/ScopeWinInput_nomain.o;\
	fi

${OBJECTDIR}/CrossCorrelationComputer_nomain.o: ${OBJECTDIR}/CrossCorrelationComputer.o CrossCorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CrossCorrelationComputer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CrossCorrelationComputer_nomain.o CrossCorrelationComputer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CrossCorrelationComputer.o ${OBJECTDIR}/CrossCorrelationComputer_nomain.o;\
	fi

${OBJECTDIR}/NiftiInput_nomain.o: ${OBJECTDIR}/NiftiInput.o NiftiInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/NiftiInput.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/NiftiInput_nomain.o NiftiInput.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/NiftiInput.o ${OBJECTDIR}/NiftiInput_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/DataInputIface_nomain.o: ${OBJECTDIR}/DataInputIface.o DataInputIface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DataInputIface.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataInputIface_nomain.o DataInputIface.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DataInputIface.o ${OBJECTDIR}/DataInputIface_nomain.o;\
	fi

${OBJECTDIR}/SourceInfo_nomain.o: ${OBJECTDIR}/SourceInfo.o SourceInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SourceInfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourceInfo_nomain.o SourceInfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SourceInfo.o ${OBJECTDIR}/SourceInfo_nomain.o;\
	fi

${OBJECTDIR}/ComputationFramework_nomain.o: ${OBJECTDIR}/ComputationFramework.o ComputationFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ComputationFramework.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ComputationFramework_nomain.o ComputationFramework.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ComputationFramework.o ${OBJECTDIR}/ComputationFramework_nomain.o;\
	fi

${OBJECTDIR}/main_mpi_nomain.o: ${OBJECTDIR}/main_mpi.o main_mpi.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main_mpi.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_mpi_nomain.o main_mpi.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main_mpi.o ${OBJECTDIR}/main_mpi_nomain.o;\
	fi

${OBJECTDIR}/mpi/Saver_nomain.o: ${OBJECTDIR}/mpi/Saver.o mpi/Saver.cpp 
	${MKDIR} -p ${OBJECTDIR}/mpi
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mpi/Saver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/mpi/Saver_nomain.o mpi/Saver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/mpi/Saver.o ${OBJECTDIR}/mpi/Saver_nomain.o;\
	fi

${OBJECTDIR}/CorrelationComputer_nomain.o: ${OBJECTDIR}/CorrelationComputer.o CorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CorrelationComputer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CorrelationComputer_nomain.o CorrelationComputer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CorrelationComputer.o ${OBJECTDIR}/CorrelationComputer_nomain.o;\
	fi

${OBJECTDIR}/DistributedComputationFramework_nomain.o: ${OBJECTDIR}/DistributedComputationFramework.o DistributedComputationFramework.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DistributedComputationFramework.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/DistributedComputationFramework_nomain.o DistributedComputationFramework.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DistributedComputationFramework.o ${OBJECTDIR}/DistributedComputationFramework_nomain.o;\
	fi

${OBJECTDIR}/FrameContainerGenerator_nomain.o: ${OBJECTDIR}/FrameContainerGenerator.o FrameContainerGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FrameContainerGenerator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/FrameContainerGenerator_nomain.o FrameContainerGenerator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FrameContainerGenerator.o ${OBJECTDIR}/FrameContainerGenerator_nomain.o;\
	fi

${OBJECTDIR}/mpi/common_nomain.o: ${OBJECTDIR}/mpi/common.o mpi/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/mpi
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mpi/common.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/mpi/common_nomain.o mpi/common.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/mpi/common.o ${OBJECTDIR}/mpi/common_nomain.o;\
	fi

${OBJECTDIR}/ValueFrame_nomain.o: ${OBJECTDIR}/ValueFrame.o ValueFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ValueFrame.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueFrame_nomain.o ValueFrame.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ValueFrame.o ${OBJECTDIR}/ValueFrame_nomain.o;\
	fi

${OBJECTDIR}/Statistics_nomain.o: ${OBJECTDIR}/Statistics.o Statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Statistics.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Statistics_nomain.o Statistics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Statistics.o ${OBJECTDIR}/Statistics_nomain.o;\
	fi

${OBJECTDIR}/ValueContainerGenerator_nomain.o: ${OBJECTDIR}/ValueContainerGenerator.o ValueContainerGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ValueContainerGenerator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainerGenerator_nomain.o ValueContainerGenerator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ValueContainerGenerator.o ${OBJECTDIR}/ValueContainerGenerator_nomain.o;\
	fi

${OBJECTDIR}/mpi/Worker_nomain.o: ${OBJECTDIR}/mpi/Worker.o mpi/Worker.cpp 
	${MKDIR} -p ${OBJECTDIR}/mpi
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mpi/Worker.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/mpi/Worker_nomain.o mpi/Worker.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/mpi/Worker.o ${OBJECTDIR}/mpi/Worker_nomain.o;\
	fi

${OBJECTDIR}/_ext/126195727/ConfigFile_nomain.o: ${OBJECTDIR}/_ext/126195727/ConfigFile.o /media/shared/diplomka/masterserver/ConfigFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/126195727
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/126195727/ConfigFile.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/126195727/ConfigFile_nomain.o /media/shared/diplomka/masterserver/ConfigFile.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/126195727/ConfigFile.o ${OBJECTDIR}/_ext/126195727/ConfigFile_nomain.o;\
	fi

${OBJECTDIR}/lib/swutils_nomain.o: ${OBJECTDIR}/lib/swutils.o lib/swutils.C 
	${MKDIR} -p ${OBJECTDIR}/lib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lib/swutils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/swutils_nomain.o lib/swutils.C;\
	else  \
	    ${CP} ${OBJECTDIR}/lib/swutils.o ${OBJECTDIR}/lib/swutils_nomain.o;\
	fi

${OBJECTDIR}/ValueContainer_nomain.o: ${OBJECTDIR}/ValueContainer.o ValueContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ValueContainer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainer_nomain.o ValueContainer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ValueContainer.o ${OBJECTDIR}/ValueContainer_nomain.o;\
	fi

${OBJECTDIR}/mpi/Coordinator_nomain.o: ${OBJECTDIR}/mpi/Coordinator.o mpi/Coordinator.cpp 
	${MKDIR} -p ${OBJECTDIR}/mpi
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mpi/Coordinator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/mpi/Coordinator_nomain.o mpi/Coordinator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/mpi/Coordinator.o ${OBJECTDIR}/mpi/Coordinator_nomain.o;\
	fi

${OBJECTDIR}/SourcePointInfo_nomain.o: ${OBJECTDIR}/SourcePointInfo.o SourcePointInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SourcePointInfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourcePointInfo_nomain.o SourcePointInfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SourcePointInfo.o ${OBJECTDIR}/SourcePointInfo_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver_release

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
