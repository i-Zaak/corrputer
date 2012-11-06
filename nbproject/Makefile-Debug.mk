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
	${OBJECTDIR}/SourceInfo.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/DataInputIface.o \
	${OBJECTDIR}/CorrelationComputer.o \
	${OBJECTDIR}/ValueFrame.o \
	${OBJECTDIR}/lib/swutils.o \
	${OBJECTDIR}/ValueContainer.o \
	${OBJECTDIR}/SourcePointInfo.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-fopenmp
CXXFLAGS=-fopenmp

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lboost_serialization

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -fopenmp -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/ValueStream.o: ValueStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueStream.o ValueStream.cpp

${OBJECTDIR}/ScopeWinInput.o: ScopeWinInput.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/ScopeWinInput.o ScopeWinInput.cpp

${OBJECTDIR}/CrossCorrelationComputer.o: CrossCorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/CrossCorrelationComputer.o CrossCorrelationComputer.cpp

${OBJECTDIR}/SourceInfo.o: SourceInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourceInfo.o SourceInfo.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/DataInputIface.o: DataInputIface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataInputIface.o DataInputIface.cpp

${OBJECTDIR}/CorrelationComputer.o: CorrelationComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/CorrelationComputer.o CorrelationComputer.cpp

${OBJECTDIR}/ValueFrame.o: ValueFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueFrame.o ValueFrame.cpp

${OBJECTDIR}/lib/swutils.o: lib/swutils.C 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/swutils.o lib/swutils.C

${OBJECTDIR}/ValueContainer.o: ValueContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/ValueContainer.o ValueContainer.cpp

${OBJECTDIR}/SourcePointInfo.o: SourcePointInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/SourcePointInfo.o SourcePointInfo.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/masterserver

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
