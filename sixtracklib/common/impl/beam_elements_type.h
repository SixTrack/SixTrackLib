#ifndef SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_TYPE_H__
#define SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_TYPE_H__

#if !defined( _GPUCODE )

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "sixtracklib/_impl/definitions.h"
#include "sixtracklib/common/blocks.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#endif /* !defined( _GPUCODE ) */

/* ========================================================================= */
    
typedef struct NS(Drift)
{
    SIXTRL_REAL_T length __attribute__(( aligned( 8 ) ));
}
NS(Drift);   

/* ========================================================================= */

typedef struct NS(DriftExact)
{
    SIXTRL_REAL_T length __attribute__(( aligned( 8 ) ));
}
NS(DriftExact);

/* ========================================================================= */

typedef struct NS(MultiPole)
{
    SIXTRL_REAL_T   length  __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T   hxl     __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T   hyl     __attribute__(( aligned( 8 ) ));
    SIXTRL_INT64_T  order   __attribute__(( aligned( 8 ) ));
    
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* 
        SIXTRL_RESTRICT bal __attribute__(( aligned( 8 ) ));
}
NS(MultiPole);

/* ========================================================================= */

struct NS(BeamBeamBoostData);
struct NS(BeamBeamSigmas);

typedef struct NS(BeamBeam)
{
    SIXTRL_GLOBAL_DEC struct NS(BeamBeamBoostData)* SIXTRL_RESTRICT   
        boost                            __attribute__(( aligned( 8 ) ));
        
    SIXTRL_GLOBAL_DEC struct NS(BeamBeamSigmas)* SIXTRL_RESTRICT 
        sigmas                           __attribute__(( aligned( 8 ) ));
    
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT
        n_part_per_slice                 __attribute__(( aligned( 8 ) ));
    
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT 
        x_slices_star                    __attribute__(( aligned( 8 ) ));
        
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT 
        y_slices_star                    __attribute__(( aligned( 8 ) ));
        
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT 
        sigma_slices_star                __attribute__(( aligned( 8 ) ));
    
    NS(block_num_elements_t) num_of_slices  __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T            q_part         __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T            min_sigma_diff __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T            treshold_sing  __attribute__(( aligned( 8 ) ));
}
NS(BeamBeam);

/* ========================================================================= */

typedef struct NS(Cavity)
{
    SIXTRL_REAL_T   voltage     __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T   frequency   __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T   lag         __attribute__(( aligned( 8 ) ));    
}
NS(Cavity);

/* ========================================================================= */

typedef struct NS(Align)
{
    SIXTRL_REAL_T   tilt        __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T   cz          __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T   sz          __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T   dx          __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T   dy          __attribute__(( aligned( 8 ) ));
}
NS(Align);

/* ========================================================================= */

typedef struct NS(BeamBeamBoostData)
{
    SIXTRL_REAL_T sphi   __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T cphi   __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T tphi   __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T salpha __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T calpha __attribute__(( aligned( 8 ) ));
}
NS(BeamBeamBoostData);

typedef struct NS(BeamBeamSigmas)
{
    SIXTRL_REAL_T sigma_11 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_12 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_13 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_14 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_22 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_23 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_24 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_33 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_34 __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T sigma_44 __attribute__(( aligned( 8 ) ));
}
NS(BeamBeamSigmas);

typedef struct NS(BeamBeamPropagatedSigmasResult)
{
    SIXTRL_REAL_T  sigma_11_hat __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T  sigma_33_hat __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T  cos_theta    __attribute__(( aligned( 8 ) ));
    SIXTRL_REAL_T  sin_theta    __attribute__(( aligned( 8 ) ));    
}
NS(BeamBeamPropagatedSigmasResult);

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE )

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !defined( _GPUCODE ) */
    

#endif /* SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_TYPE_H__ */

/* end: sixtracklib/common/impl/beam_elements_type.h */
