#ifndef SIXTRACKLIB_SIXTRACKLIB_H__
#define SIXTRACKLIB_SIXTRACKLIB_H__

#if !defined( __NAMESPACE )
    #define __NAMESPACE st_
    #define __SIXTRACKLIB_SIXTRACKLIB_UNDEF_NAMESPACE 1
#endif /* !defined( __NAMESPACE ) */

#include "sixtracklib/_impl/definitions.h"

/* ------------------------------------------------------------------------- */

#include "sixtracklib/_impl/namespace_begin.h"
#include "sixtracklib/_impl/path.h"
#include "sixtracklib/_impl/modules.h"

#include "sixtracklib/common/mem_pool.h"
#include "sixtracklib/common/block.h"
#include "sixtracklib/common/impl/block_type.h"
#include "sixtracklib/common/block_drift.h"
#include "sixtracklib/common/impl/block_drift_type.h"
#include "sixtracklib/common/particles.h"
#include "sixtracklib/common/impl/particles_type.h"
#include "sixtracklib/common/particles_sequence.h"
#include "sixtracklib/common/track.h"
#include "sixtracklib/common/values.h"

/* Not optimal having these two as part of the public library interface -> fix this! */
#include "sixtracklib/common/details/random.h"
#include "sixtracklib/common/tests/test_particles_tools.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined( SIXTRACKLIB_ENABLE_MODULE_SIMD ) && \
           ( SIXTRACKLIB_ENABLE_MODULE_SIMD == 1 )
    
    #include "sixtracklib/simd/track.h"
           
#endif /* defined( SIXTRACKLIB_ENABLE_MODULE_SIMD ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
           ( SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1 )
           
    #include "sixtracklib/opencl/ocl_environment.h"
           
#endif /* defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) */

/* ------------------------------------------------------------------------- */

#include "sixtracklib/_impl/namespace_end.h"

#if defined( SIXTRACKLIB_SIXTRACKLIB_UNDEF_NAMESPACE )
    #undef __NAMESPACE 
    #undef __SIXTRACKLIB_SIXTRACKLIB_UNDEF_NAMESPACE
#endif /* defined( SIXTRACKLIB_SIXTRACKLIB_UNDEF_NAMESPACE ) */

#endif /* SIXTRACKLIB_SIXTRACKLIB_H__ */

/* end: sixtracklib/sixtracklib.h */
