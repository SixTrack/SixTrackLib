import pickle
import cobjects
import pysixtrack

import temp_particles as tp


# Load pysixtrack line
pyst_example = 'bbsimple'
pyst_path = pysixtrack.__file__
input_folder = '/'.join(pyst_path.split('/')[:-2]+['examples', pyst_example])
with open(input_folder+'/line.pkl', 'rb') as fid:
	line = pickle.load(fid) 

# Load sixtracklib ebe data
dump_to_be_loaded = "../build/examples/c99/stlib_dump.bin"
buf = cobjects.CBuffer.from_file(dump_to_be_loaded)
ebe = []
for iob in range(buf.n_objects):
    ebe.append(buf.get_object(tp.Particles, iob))

i_part = 1
for ii, elem in enumerate(line):

	
	ptest = pysixtrack.Particles()

	before = ebe[ii]
	for ff in before.get_fields():
		name = ff[0]
		try:
			setattr(ptest, name, getattr(before, name)[i_part])
		except Exception as err:
			pass

	elem[2].track(ptest)

	print(elem[0])
	print(ptest.x, ebe[ii+1].x[i_part])



	
