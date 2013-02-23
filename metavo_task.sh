#!/bin/bash
#PBS -N corel_mpi
#PBS -q short
#PBS -l walltime=2:00:00
#PBS -l mem=2000mb
#PBS -l nodes=8:ppn=4:linux:x86_64:nfs4

# Pocet uzlu MPI (odpovida poctu CPU)
NODES=32

# Pracovni adresar (obsahuje program, konfiguraci, data)
WD=/storage/home/dejvino/corel/masterserver/run/

# Nazev konfiguracniho souboru ke spusteni
CFG_FILE=corel_config.txt

# Nazev souboru programu ke spusteni
APP=./masterserver_release

# ===================================================================

# priprava prostredi
. /packages/run/modules-2.0/init/sh
module add modules ics.muni.cz
module add openmpi

# OPRAVA chybneho nodefile
PBS_NODEFLE=`echo $PBS_NODEFILE | sed "s/\/\//\//g"`

# ===================================================================

# instalace

# ...

# ===================================================================

# spusteni

cd $WD

RUN="-n $NODES --hostfile $PBS_NODEFILE -x PATH -x LD_LIBRARY_PATH -wdir $WD"

#########################

date

mpiexec $RUN $APP $CFG_FILE

date

#########################

# uklid

# ...

