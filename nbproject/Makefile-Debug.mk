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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ValueStream.o \
	${OBJECTDIR}/ScopeWinInput.o \
	${OBJECTDIR}/CrossCorrelationComputer.o \
	${OBJECTDIR}/NiftiInput.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/SourceInfo.o \
	${OBJECTDIR}/DataInputIface.o \
	${OBJECTDIR}/CorrelationComputer.o \
	${OBJECTDIR}/Statistics.o \
	${OBJECTDIR}/ValueFrame.o \
	${OBJECTDIR}/ValueContainerGenerator.o \
	${OBJECTDIR}/lib/swutils.o \
	${OBJECTDIR}/ValueContainer.o \
	${OBJECTDIR}/SourcePointInfo.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f2 \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -fopenmp
CXXFLAGS=-m64 -fopenmp

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver_debug

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver_debug: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -fopenmp -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver_debug ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/ValueStream.o: ValueStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueStream.o ValueStream.cpp

${OBJECTDIR}/ScopeWinInput.o: ScopeWinInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ScopeWinInput.o ScopeWinInput.cpp

${OBJECTDIR}/CrossCorrelationComputer.o: CrossCorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/CrossCorrelationComputer.o CrossCorrelationComputer.cpp

${OBJECTDIR}/NiftiInput.o: NiftiInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/NiftiInput.o NiftiInput.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/SourceInfo.o: SourceInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourceInfo.o SourceInfo.cpp

${OBJECTDIR}/DataInputIface.o: DataInputIface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataInputIface.o DataInputIface.cpp

${OBJECTDIR}/CorrelationComputer.o: CorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/CorrelationComputer.o CorrelationComputer.cpp

${OBJECTDIR}/Statistics.o: Statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/Statistics.o Statistics.cpp

${OBJECTDIR}/ValueFrame.o: ValueFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueFrame.o ValueFrame.cpp

${OBJECTDIR}/ValueContainerGenerator.o: ValueContainerGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainerGenerator.o ValueContainerGenerator.cpp

${OBJECTDIR}/lib/swutils.o: lib/swutils.C 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/swutils.o lib/swutils.C

${OBJECTDIR}/ValueContainer.o: ValueContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainer.o ValueContainer.cpp

${OBJECTDIR}/SourcePointInfo.o: SourcePointInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourcePointInfo.o SourcePointInfo.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/CrossCorrelationTest.o ${TESTDIR}/tests/CrossCorrelationTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lcppunit 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/RunningVarianceTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver: ${TESTDIR}/tests/ValueContainerSerializationTest.o ${TESTDIR}/tests/testrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver $^ ${LDLIBSOPTIONS} `pkg-config --libs cppunit`   


${TESTDIR}/tests/CrossCorrelationTest.o: tests/CrossCorrelationTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CrossCorrelationTest.o tests/CrossCorrelationTest.cpp


${TESTDIR}/tests/CrossCorrelationTestRunner.o: tests/CrossCorrelationTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CrossCorrelationTestRunner.o tests/CrossCorrelationTestRunner.cpp


${TESTDIR}/tests/RunningVarianceTest.o: tests/RunningVarianceTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/RunningVarianceTest.o tests/RunningVarianceTest.cpp


${TESTDIR}/tests/ValueContainerSerializationTest.o: tests/ValueContainerSerializationTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ValueContainerSerializationTest.o tests/ValueContainerSerializationTest.cpp


${TESTDIR}/tests/testrunner.o: tests/testrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -MMD -MP -MF $@.d -o ${TESTDIR}/tests/testrunner.o tests/testrunner.cpp


${OBJECTDIR}/ValueStream_nomain.o: ${OBJECTDIR}/ValueStream.o ValueStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ValueStream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueStream_nomain.o ValueStream.cpp;\
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
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ScopeWinInput_nomain.o ScopeWinInput.cpp;\
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
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CrossCorrelationComputer_nomain.o CrossCorrelationComputer.cpp;\
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
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/NiftiInput_nomain.o NiftiInput.cpp;\
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
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/SourceInfo_nomain.o: ${OBJECTDIR}/SourceInfo.o SourceInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SourceInfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourceInfo_nomain.o SourceInfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SourceInfo.o ${OBJECTDIR}/SourceInfo_nomain.o;\
	fi

${OBJECTDIR}/DataInputIface_nomain.o: ${OBJECTDIR}/DataInputIface.o DataInputIface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DataInputIface.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataInputIface_nomain.o DataInputIface.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DataInputIface.o ${OBJECTDIR}/DataInputIface_nomain.o;\
	fi

${OBJECTDIR}/CorrelationComputer_nomain.o: ${OBJECTDIR}/CorrelationComputer.o CorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CorrelationComputer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CorrelationComputer_nomain.o CorrelationComputer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CorrelationComputer.o ${OBJECTDIR}/CorrelationComputer_nomain.o;\
	fi

${OBJECTDIR}/Statistics_nomain.o: ${OBJECTDIR}/Statistics.o Statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Statistics.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Statistics_nomain.o Statistics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Statistics.o ${OBJECTDIR}/Statistics_nomain.o;\
	fi

${OBJECTDIR}/ValueFrame_nomain.o: ${OBJECTDIR}/ValueFrame.o ValueFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ValueFrame.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueFrame_nomain.o ValueFrame.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ValueFrame.o ${OBJECTDIR}/ValueFrame_nomain.o;\
	fi

${OBJECTDIR}/ValueContainerGenerator_nomain.o: ${OBJECTDIR}/ValueContainerGenerator.o ValueContainerGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ValueContainerGenerator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainerGenerator_nomain.o ValueContainerGenerator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ValueContainerGenerator.o ${OBJECTDIR}/ValueContainerGenerator_nomain.o;\
	fi

${OBJECTDIR}/lib/swutils_nomain.o: ${OBJECTDIR}/lib/swutils.o lib/swutils.C 
	${MKDIR} -p ${OBJECTDIR}/lib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lib/swutils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/swutils_nomain.o lib/swutils.C;\
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
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainer_nomain.o ValueContainer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ValueContainer.o ${OBJECTDIR}/ValueContainer_nomain.o;\
	fi

${OBJECTDIR}/SourcePointInfo_nomain.o: ${OBJECTDIR}/SourcePointInfo.o SourcePointInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SourcePointInfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -DMAIN_CORRELATOR -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourcePointInfo_nomain.o SourcePointInfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SourcePointInfo.o ${OBJECTDIR}/SourcePointInfo_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver_debug

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
