#include "beam.h"
#include "value.h"

#ifndef _BLOCK
#define _BLOCK

typedef enum type_t {IntegerID, DoubleID,
             DriftID, DriftExactID,
             MultipoleID, CavityID, AlignID,
             BlockID} type_t;


#ifdef _GPUCODE

CLKERNEL void Block_track(CLGLOBAL value_t *data,
                         CLGLOBAL Particle *particles,
                         uint64_t blockid, uint64_t nturn, uint64_t npart,
                         uint64_t elembyelemid,  uint64_t turnbyturnid);
#else

int Block_track(value_t *data, Beam *beam,
                uint64_t blockid, uint64_t nturn,
                uint64_t elembyelemid,  uint64_t turnbyturnid);

#endif


#endif
