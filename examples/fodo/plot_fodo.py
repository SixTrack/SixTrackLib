import numpy as np
import matplotlib.pyplot as plt

import sixtracklib


block=sixtracklib.cBlock(2)
kqf=0.8; kqd=-0.7;ld=1.5;
block.Drift(ld)
block.Multipole([0.,kqf],[0.,0.],0,0,0)
block.Drift(ld)
block.Multipole([0.,kqd],[0.,0.],0,0,0)
block.Block()


npart=2
beam=sixtracklib.cBeam(npart)
beam.particles['x'][:npart/2]=np.linspace(0,1,npart/2)
beam.particles['y'][npart/2:]=np.linspace(0,1,npart/2)

#plt.clf()
#plt.plot(beam.particles['x'],beam.particles['px'])
#plt.plot(beam.particles['y'],beam.particles['py'])
nturn=3
block.track(beam,nturn,elembyelem=True,turnbyturn=True)
#plt.plot(beam.particles['x'],beam.particles['px'])
#plt.plot(beam.particles['y'],beam.particles['py'])

print block.elembyelem.particles['turn']
print block.turnbyturn.particles['turn']
assert (block.elembyelem.particles['turn'][0,:,0]==np.arange(3)).all()
assert (block.turnbyturn.particles['turn'][:,0]==np.arange(3)).all()

npart=2
beam=sixtracklib.cBeam(npart)
beam.particles['x'][:npart/2]=np.linspace(0,1,npart/2)
beam.particles['y'][npart/2:]=np.linspace(0,1,npart/2)

nturn=3
block.track_cl(beam,nturn,elembyelem=True)

print block.elembyelem.particles['turn']
assert (block.elembyelem.particles['turn'][0,:,0]==np.arange(3)).all()
assert (block.turnbyturn.particles['turn'][:,0]==np.arange(3)).all()

