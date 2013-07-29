from nipype.interfaces.base import TraitedSpec, CommandLineInputSpec, CommandLine, MpiCommandLineInputSpec, MpiCommandLine, File, traits
from nipype.utils.filemanip import split_filename
import nibabel as nb
import numpy as np
import os


def generate_config(configpath, infilename, outfilename0, outfilename1, 
        corrtype, tau_max, win_size, win_step):
    if configpath is None:
        configpath = 'config.txt'
    f = open(configpath, 'w')
    f.write("[Input]\n\n")
    f.write("filename = %s\n\n" % infilename)
    f.write("[Output]\n\n")
    f.write("filename0 = %s\n" % outfilename0)
    f.write("filename1 = %s\n" % outfilename1)
    f.write("[Correlation]\n\n")
    f.write("# correlation type (currently only Cross is implemented)\n")
    f.write("type = %s\n\n" % corrtype)
    f.write("# maximal value of tau\n")
    f.write("tau_max = %s\n\n" % tau_max)
    f.write("# floating window length in samples\n")
    f.write("window_size = %s\n\n" % win_size)
    f.write("# step of the floating window in samples \n")
    f.write("window_step = %s\n\n" % win_step)
    f.close()


"""
    Corrputer interface
"""

class CorrputerInputSpec(MpiCommandLineInputSpec):
    infile = File(exists=True, mandatory=True)
    inmetafile = File(exists=True, mandatory=True)
    corrtype = traits.Str("Cross", usedefault = True)
    tau_max = traits.Int(desc="maximal value of tau in samples", mandatory=True)
    win_size = traits.Int(desc="floating window length in samples", mandatory=True)
    win_step = traits.Int(desc="step of the floating window in samples", mandatory=True)
    use_mpi = True



class CorrputerOutputSpec(TraitedSpec):
    corr_file = File(exists=True, desc="correlation matrix in time")
    corr_mfile = File(exists=True, desc="correlation matrix in time, metadata")
    tau_file = File(exists=True, desc="time lag matrix in time")
    tau_mfile = File(exists=True, desc="time lag matrix in timei, metadata")


class CorrputerTask(MpiCommandLine):
    _cmd = 'corrputer'
    input_spec = CorrputerInputSpec
    output_spec = CorrputerOutputSpec

    def _run_interface(self, runtime):
        confile = os.path.abspath('corrconfig.txt')
        generate_config(
                configpath = confile, 
                infilename = self.inputs.infile, 
                outfilename0 = 'correl.vc',
                outfilename1 = 'tau.vc', 
                corrtype = self.inputs.corrtype,
                tau_max = self.inputs.tau_max,
                win_size = self.inputs.win_size,
                win_step = self.inputs.win_step)
        self.inputs.args = confile
        runtime = super(CorrputerTask, self)._run_interface(runtime)
        return runtime

    def _list_outputs(self):
        outputs = self.output_spec().get()
        outputs['corr_file'] = os.path.abspath('correl.vc')
        outputs['corr_mfile'] = os.path.abspath('correl.vcm')
        outputs['tau_file'] = os.path.abspath('tau.vc')
        outputs['tau_mfile'] = os.path.abspath('tau.vcm')
        return outputs

"""
 VCGen interface
"""

class VCGenInputSpec(CommandLineInputSpec):
    input_type = traits.Enum('ScopeWin', 'Nifti', 'HDF5', desc="type of input file", mandatory=True, argstr="%s", position=0)
    input_file = File(exists=True, mandatory=True, argstr="%s", position=1)
    output_file = File(mandatory=False, desc="path to the output file to be generated. It should end with a .cv extension. Meta file is generated based on this name.", argstr="%s", position=2)
    dataset = traits.Str(mandatory=False, desc="Dataset path, required only for the HDF5 format", argstr="%s", position=3)

class VCGenOutputSpec(TraitedSpec):
    datafile = File(desc='Output data file',exists=True)
    metafile = File(desc='Output meta file',exists=True)


class VCGenTask(CommandLine):
    _cmd = 'vcgen'
    input_spec = VCGenInputSpec
    output_spec = VCGenOutputSpec

    def _run_interface(self, runtime):
        fname = self.inputs.input_file
        _, base, _ = split_filename(fname)
        self.inputs.output_file = base + '.vc'
        runtime = super(VCGenTask, self)._run_interface(runtime)
        return runtime

    def _list_outputs(self):
        outputs = self.output_spec().get()
        outputs['datafile'] = os.path.abspath(self.inputs.output_file)
        outputs['metafile'] = os.path.abspath(self.inputs.output_file + 'm')
        return outputs



if __name__ == "__main__":
    ## generate config only
    #import sys
    #generate_config(*sys.argv[1:])
    
    ## test the corrputer interface
    #import os
    #corrputer = CorrputerTask()
    #corrputer.inputs.tau_max = 10
    #corrputer.inputs.win_size = 100
    #corrputer.inputs.win_step = 50
    #corrputer.inputs.infile =  os.path.abspath("/home/izaak/Forge/dejvino/masterserver/data/montazr11.vc")
    #corrputer.inputs.n_procs = 7
    #corrputer.run()

    # test the vcgen interface
    vcgen = VCGenTask()
    vcgen.inputs.input_type = 'HDF5'
    vcgen.inputs.input_file = '/mnt/data/izaak/HFA/processed/bandfilt_wflow/preprocess/convert/Easrec-1302211010.h5'
    vcgen.inputs.dataset = '/continuous_data/EEG_raw'
    vcgen.run()

