import ctypes
import time
import os


import numpy as np

from .cbeam import cBeam

modulepath=os.path.dirname(os.path.abspath(__file__))

try:
  import pyopencl as cl
  os.environ['PYOPENCL_COMPILER_OUTPUT']='1'
  srcpath='-I%s'%modulepath
  src=open(os.path.join(modulepath,'block.c')).read()
  ctx = cl.create_some_context(interactive=False)
  prg=cl.Program(ctx,src).build(options=[srcpath])
  queue = cl.CommandQueue(ctx)
  mf = cl.mem_flags
  rw=mf.READ_WRITE | mf.COPY_HOST_PTR
except ImportError("Warning: error import OpenCL: track_cl not available"):
  pass


value_t = np.dtype((np.float64,
               {'i32':('i4', 0),
                'u64':('u8', 0),
                'i64':('i8', 0),
                'tag':('u2', 6)}))


class typeid(object):
  IntegerID=0
  DoubleID=1
  DriftID=2
  DriftExactID=3
  MultipoleID=4
  CavityID=5
  AlignID=6
  BlockID=7


blocklibpath=os.path.join(modulepath, 'block.so')
blocklib=ctypes.CDLL(blocklibpath)
blocklib.Block_track.argtypes=[ctypes.c_void_p, # *data
                               ctypes.c_void_p, # *particles
                               ctypes.c_uint64, # blockid
                               ctypes.c_uint64, # nturn
                               ctypes.c_uint64, # elembyelemid
                               ctypes.c_uint64 ] # turnbyturnid


class ElemByElem(object):
    def __init__(self,block,offset,size,nelem,npart,nturn):
        self.block=block
        self.offset=offset
        self.size=size
        self.nelem=nelem
        self.npart=npart
        self.nturn=nturn
    def get_beam(self):
        particles=self.block.data[self.offset:
                        self.offset+self.size]
        beam=cBeam(particles=particles)
        print beam.particles.shape
        beam.particles=beam.particles.reshape((self.nturn,self.npart))
        return beam

class TurnByTurn(object):
    def __init__(self,block,offset,size,npart,nturn):
        self.block=block
        self.offset=offset
        self.size=size
        self.npart=npart
        self.nturn=nturn
    def get_beam(self):
        particles=self.block.data[self.offset:
                        self.offset+self.size]
        beam=cBeam(particles=particles)
        beam.particles=beam.particles.reshape((self.nturn,self.npart))
        return beam

class cBlock(object):
  def __init__(self,size=512):
    self.size=size
    self.last=0
    self.data=np.zeros(size,value_t)
    self.offsets=[]
    self.blockid=None
  def _resize(self,n):
    if (self.last+n)>=len(self.data):
      newsize=(self.last+n)*2
      newdata=np.zeros(newsize,value_t)
      newdata[:self.size]=self.data
      self.data=newdata
      self.size=newsize
  def _add_float(self,data):
    self._resize(1)
    self.data[self.last]=data
    self.last+=1
  def _add_integer(self,data):
    self._resize(1)
    self.data['i64'][self.last]=data
    self.last+=1
  def _add_float_array(self,data):
    self._resize(len(data))
    self.data[self.last:self.last+len(data)]=data
    self.last+=len(data)
  def _add_integer_array(self,data):
    self._resize(len(data))
    self.data['i64'][self.last:self.last+len(data)]=data
    self.last+=len(data)
  def Drift(self, length=0):
    self.offsets.append(self.last)
    self._add_integer(typeid.DriftID)
    self._add_float(length)
  def Multipole(self,knl=[],ksl=[],length=0,hxl=0,hyl=0):
    bal=np.array(sum(zip(knl,ksl),()))
    fact=1
    for n in range(len(bal)/2):
        bal[n*2:n*2+2]/=fact
        fact*=(n+1)
    self.offsets.append(self.last)
    self._add_integer(typeid.MultipoleID)
    if len(bal)>=2 and len(bal)%2==0:
      order=len(bal)/2-1
    else:
      raise ValueError("Size of bal must be even")
    self._add_integer(order)
    self._add_float(length)
    self._add_float(hxl)
    self._add_float(hyl)
    self._add_float_array(bal)
  def Cavity(self,volt=0,freq=0,lag=0):
    self.offsets.append(self.last)
    self._add_integer(typeid.CavityID)
    self._add_float(volt)
    self._add_float(freq)
    self._add_float(lag/180.*np.pi)
  def Align(self,tilt=0,dx=0,dy=0):
    self.offsets.append(self.last)
    self._add_integer(typeid.AlignID)
    cz=np.cos(tilt/180.*np.pi)
    sz=np.sin(tilt/180.*np.pi)
    self._add_float(cz)
    self._add_float(sz)
    self._add_float(dx)
    self._add_float(dy)
  def Block(self,offsets=None):
    if offsets==None:
       offsets=self.offsets
    self.blockid=self.last
    self._add_integer(typeid.BlockID)
    self._add_integer(len(offsets))
    self._add_integer_array(offsets)
  def _set_elembyelem(self,beam,nturn):
    nelem=len(self.offsets)
    size=beam.get_size()*nelem*nturn
    self._add_float_array(np.zeros(size))
    return ElemByElem(self,self.last,size,nelem,nturn,beam.npart)
  def _set_turnbyturn(self,beam):
    size=beam.get_size()*nturn
    self._add_float_array(np.zeros(size))
    return TurnByTurn(self,self.last,size,nturn,beam.npart)
  def track(self,beam,nturn=1,elembyelem=False,turnbyturn=False):
    elembyelemid=0;turnbyturnid=0;
    if elembyelem:
        _elembyelem=self._set_elembyelem(beam,nturn)
        elembyelemid=_elembyelem.offset
    if turnbyturn:
        _turnbyturn=self._set_turnbyturn(beam,nturn)
        turnbyturnid=_turnbyturn.offset
    print self.blockid,nturn,elembyelemid,turnbyturnid,self.size
    blocklib.Block_track(self.data.ctypes.data, beam.ctypes(),
                         self.blockid, nturn,
                         elembyelemid,turnbyturnid)
    if elembyelem:
      self.elembyelem=_elembyelem.get_beam()
    if turnbyturn:
      self.turnbyturn=_turnbyturn.get_beam()
  def track_cl(self,beam,nturn=1,elembyelem=False,turnbyturn=False):
    elembyelemid=0;turnbyturnid=0;
    if elembyelem:
        _elembyelem=self._set_elembyelem(beam,nturn)
        elembyelemid=_elembyelem.offset
    if turnbyturn:
        _turnbyturn=self._set_turnbyturn(beam,nturn)
        turnbyturnid=_turnbyturn.offset
    data_g=cl.Buffer(ctx, rw, hostbuf=self.data)
    part_g=cl.Buffer(ctx, rw, hostbuf=beam.particles)
    blockid=np.uint64(self.blockid)
    nturn=np.uint64(nturn)
    npart=np.uint64(beam.npart)
    elembyelemid=np.uint64(elembyelemid)
    turnbyturnid=np.uint64(turnbyturnid)
    prg.Block_track(queue,[beam.npart],None,
                    data_g, part_g,
                    blockid, nturn, npart,
                    elembyelemid, turnbyturnid)
    cl.enqueue_copy(queue,self.data,data_g)
    cl.enqueue_copy(queue,beam.particles,part_g)
    if elembyelem:
      self.elembyelem=_elembyelem.get_beam()
    if turnbyturn:
      self.turnbyturn=_turnbyturn.get_beam()

