import os
import nipype.interfaces.utility as util
import nipype.pipeline.engine as pe
import nipype.interfaces.io as nio
import interfaces.corrputer as cptr


"""
====================================

experiment specific parameters. Use os.path.join to avoid funny windows path delimiters.

====================================
"""

# Path to the top dir of the raw data.
base_dir = '/mnt/data/izaak/HFA'

# pipeline workdir 
workdir = os.path.join(base_dir, 'processed', 'corrpute_wflow')

# input time series
raw_data =os.path.join(base_dir, 'processed', 'bandfilt_wflow','preprocess','convert','Easrec-1302211010.h5')

# hdf5 input dataset
dset = '/continuous_data/EEG_raw'

# mpi nprocs
n_procs = 7

"""
====================================

Define nodes: source, merge and sink.

====================================
"""
vcgen = pe.Node(interface=cptr.VCGenTask(), name='vcgen')
vcgen.inputs.input_type = 'HDF5'
vcgen.inputs.input_file = raw_data
vcgen.inputs.dataset = dset

corrputer = pe.Node(interface=cptr.CorrputerTask(), name='corrputer')
corrputer.inputs.tau_max = 5   
corrputer.inputs.win_size = 5000
corrputer.inputs.win_step = 4500
corrputer.inputs.n_procs = n_procs

"""
====================================

Define pipeline (aka workflow)

====================================
"""
corrpute = pe.Workflow(name='corrpute')
corrpute.base_dir = workdir


"""
====================================

Connect nodes

====================================
"""
#TODO connect nodes -- replace input/output strings
corrpute.connect(vcgen, 'datafile', corrputer, 'infile')
corrpute.connect(vcgen, 'metafile', corrputer, 'inmetafile')


"""
====================================

Run pipeline and create graph

====================================
"""

corrpute.run()
corrpute.write_graph(graph2use='flat')

