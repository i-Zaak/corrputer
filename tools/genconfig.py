from nipype.interfaces.base import TraitedSpec, MpiCommandLineInputSpec, MpiCommandLine, File, traits
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



class CorrputerInputSpec(MpiCommandLineInputSpec):
    infile = File(exists=True, mandatory=True)
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


if __name__ == "__main__":
    #import sys
    #generate_config(*sys.argv[1:])
    import os
    corrputer = CorrputerTask()
    corrputer.inputs.tau_max = 10
    corrputer.inputs.win_size = 100
    corrputer.inputs.win_step = 50
    corrputer.inputs.infile =  os.path.abspath("/home/izaak/Forge/dejvino/masterserver/data/montazr11.vc")
    corrputer.inputs.n_procs = 7

    corrputer.run()