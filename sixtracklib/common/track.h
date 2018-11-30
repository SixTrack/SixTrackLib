#ifndef SIXTRACKLIB_COMMON_TRACK_H__
#define SIXTRACKLIB_COMMON_TRACK_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
    #include "sixtracklib/common/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_FN SIXTRL_STATIC void NS(Track_particle_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    NS(particle_index_t) const start_beam_element_id );

SIXTRL_FN SIXTRL_STATIC void NS(Track_subset_particles_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_begin_index,
    NS(particle_num_elements_t) const particle_end_index,
    NS(particle_num_elements_t) const particle_index_stride,
    NS(particle_index_t) const start_beam_element_id );

SIXTRL_FN SIXTRL_STATIC void NS(Track_all_particles_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const start_beam_element_id );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC int NS(Track_particle_beam_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info );


SIXTRL_FN SIXTRL_STATIC int NS(Track_subset_of_particles_beam_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info );


SIXTRL_FN SIXTRL_STATIC int NS(Track_all_particles_beam_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC int NS(Track_particle_beam_elements_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end );


SIXTRL_FN SIXTRL_STATIC int NS(Track_subset_of_particles_beam_elements_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end );


SIXTRL_FN SIXTRL_STATIC int NS(Track_all_particles_beam_elements_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC int NS(Track_particle_until_turn_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const end_turn );

SIXTRL_FN SIXTRL_STATIC int NS(Track_subset_of_particles_until_turn_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const end_turn );

SIXTRL_FN SIXTRL_STATIC int NS(Track_all_particles_until_turn_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const end_turn );

/* ------------------------------------------------------------------------- */

typedef SIXTRL_UINT64_T NS(elem_by_elem_order_t);

SIXTRL_FN SIXTRL_STATIC int NS(Track_particle_element_by_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    NS(particle_index_t) const beam_element_id,
    NS(particle_num_elements_t) const total_num_beam_elements_per_turn,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_particle_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_FN SIXTRL_STATIC int NS(Track_particle_element_by_element_objs)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    NS(particle_index_t) start_beam_element_id,
    NS(particle_num_elements_t) const total_num_beam_elements_per_turn,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_particle_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );


SIXTRL_FN SIXTRL_STATIC int NS(Track_subset_of_particles_element_by_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    NS(particle_index_t) const beam_element_id,
    NS(particle_num_elements_t) const total_num_beam_elements_per_turn,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_particle_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_FN SIXTRL_STATIC int NS(Track_subset_of_particles_element_by_element_objs)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    NS(particle_index_t) start_beam_element_id,
    NS(particle_num_elements_t) const total_num_beam_elements_per_turn,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_particle_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );


SIXTRL_FN SIXTRL_STATIC int NS(Track_all_particles_element_by_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const beam_element_id,
    NS(particle_num_elements_t) const total_num_beam_elements_per_turn,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_particle_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_FN SIXTRL_STATIC int NS(Track_all_particles_element_by_element_objs)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) start_beam_element_id,
    NS(particle_num_elements_t) const total_num_beam_elements_per_turn,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_particle_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE )

struct NS(Buffer);

SIXTRL_HOST_FN int NS(Track_particle_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const be_idx );


SIXTRL_HOST_FN int NS(Track_subset_of_particles_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const be_idx );


SIXTRL_HOST_FN int NS(Track_all_particles_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const be_idx );

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_subset_of_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_idx_begin,
    NS(buffer_size_t) const be_idx_end );


SIXTRL_HOST_FN int NS(Track_subset_of_particles_subset_of_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_idx_begin,
    NS(buffer_size_t) const be_idx_end );


SIXTRL_HOST_FN int NS(Track_all_particles_subset_of_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_idx_begin,
    NS(buffer_size_t) const be_idx_end );

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements );


SIXTRL_HOST_FN int NS(Track_subset_of_particles_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements );


SIXTRL_HOST_FN int NS(Track_all_particles_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements );

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const end_turn );

SIXTRL_HOST_FN int NS(Track_subset_of_particles_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const end_turn );

SIXTRL_HOST_FN int NS(Track_all_particles_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const end_turn );

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const beam_element_idx,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles,
    NS(elem_by_elem_order_t) const order );

SIXTRL_HOST_FN int NS(Track_subset_of_particles_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const beam_element_idx,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles,
    NS(elem_by_elem_order_t) const order );

SIXTRL_HOST_FN int NS(Track_all_particles_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const beam_element_idx,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles,
    NS(elem_by_elem_order_t) const order );


SIXTRL_HOST_FN int NS(Track_particle_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const turn_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_HOST_FN int NS(Track_subset_of_particle_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const turn_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_HOST_FN int NS(Track_all_particles_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC struct NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const turn_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

#endif /* defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= */
/* =====        Implementation of Inline functions and methods         ===== */
/* ========================================================================= */

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <math.h>
#endif /* #if !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/generated/config.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/beam_elements.h"
    #include "sixtracklib/common/buffer/buffer_type.h"

    #include "sixtracklib/common/be_drift/track.h"
    #include "sixtracklib/common/be_cavity/track.h"
    #include "sixtracklib/common/be_multipole/track.h"
    #include "sixtracklib/common/be_monitor/track.h"
    #include "sixtracklib/common/be_srotation/track.h"
    #include "sixtracklib/common/be_xyshift/track.h"

    #if !defined( SIXTRL_DISABLE_BEAM_BEAM )
        #include "sixtracklib/common/be_beambeam/track.h"
    #endif /* !defined( SIXTRL_DISABLE_BEAM_BEAM ) */
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */


SIXTRL_INLINE void NS(Track_particle_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    NS(particle_index_t) const start_beam_element_id )
{
    if( NS(Particles_get_state_value)( particles, particle_index ) )
    {
        NS(Particles_increment_at_turn_value)(
            particles, particle_index );

        NS(Particles_set_at_element_id_value)(
            particles, particle_index, start_beam_element_id );
    }

    return;
}

SIXTRL_INLINE void NS(Track_subset_particles_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_index,
    NS(particle_num_elements_t) const particle_end_index,
    NS(particle_num_elements_t) const particle_index_stride,
    NS(particle_index_t) const start_beam_element_id )
{
    SIXTRL_ASSERT( particle_index_stride >  ( NS(particle_num_elements_t) )0 );
    SIXTRL_ASSERT( particle_index  >= ( NS(particle_num_elements_t) )0 );
    SIXTRL_ASSERT( particle_index  <= particle_end_index );

    for( ; particle_index < particle_end_index ;
           particle_index += particle_index_stride )
    {
        if( NS(Particles_get_state_value)( particles, particle_index ) )
        {
            NS(Particles_increment_at_turn_value)(
                particles, particle_index );

            NS(Particles_set_at_element_id_value)(
                particles, particle_index, start_beam_element_id );
        }
    }

    return;
}

SIXTRL_INLINE void NS(Track_all_particles_increment_at_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const start_beam_element_id )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t ii = ( num_elem_t )0u;
    num_elem_t const num_particles =
        NS(Particles_get_num_of_particles)( particles );

    for( ; ii < num_particles ; ++ii )
    {
        if( NS(Particles_get_state_value)( particles, ii ) )
        {
            NS(Particles_increment_at_turn_value)( particles, ii );

            NS(Particles_set_at_element_id_value)(
                particles, ii, start_beam_element_id );
        }
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE int NS(Track_particle_beam_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info )
{
    typedef NS(object_type_id_t) type_id_t;
    typedef NS(buffer_addr_t)    address_t;

    int ret = 0;

    type_id_t const    type_id = NS(Object_get_type_id)( be_info );
    address_t const begin_addr = NS(Object_get_begin_addr)( be_info );

    SIXTRL_ASSERT( begin_addr != ( address_t )0u );
    SIXTRL_ASSERT( particle_index >= ( NS(particle_num_elements_t) )0 );

    SIXTRL_ASSERT( particle_index <
                   NS(Particles_get_num_of_particles)( particles ) );

    SIXTRL_ASSERT( NS(Particles_get_state_value)( particles, particle_index ) ==
                   ( NS(particle_index_t) )1 );

    switch( type_id )
    {
        case NS(OBJECT_TYPE_DRIFT):
        {
            typedef NS(Drift)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            #if defined( SIXTRL_ENABLE_APERATURE_CHECK ) && \
                       ( SIXTRL_ENABLE_APERATURE_CHECK == 1 )

            NS(Particles_set_at_element_id_value)(
                particles, particle_index, beam_element_id );
            #endif /* SIXTRL_ENABLE_APERATURE_CHECK  */

            ret = NS(Track_particle_drift)( particles, particle_index, belem );
            break;
        }

        case NS(OBJECT_TYPE_DRIFT_EXACT):
        {
            typedef NS(DriftExact)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            #if defined( SIXTRL_ENABLE_APERATURE_CHECK ) && \
                       ( SIXTRL_ENABLE_APERATURE_CHECK == 1 )

            NS(Particles_set_at_element_id_value)(
                particles, particle_index, beam_element_id );
            #endif /* SIXTRL_ENABLE_APERATURE_CHECK  */

            ret = NS(Track_particle_drift_exact)(
                particles, particle_index, belem );

            break;
        }

        case NS(OBJECT_TYPE_MULTIPOLE):
        {
            typedef NS(MultiPole)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            ret = NS(Track_particle_multipole)( particles, particle_index, belem );
            break;
        }

        case NS(OBJECT_TYPE_CAVITY):
        {
            typedef NS(Cavity)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            ret = NS(Track_particle_cavity)( particles, particle_index, belem );
            break;
        }

        case NS(OBJECT_TYPE_XYSHIFT):
        {
            typedef NS(XYShift)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            ret = NS(Track_particle_xy_shift)( particles, particle_index, belem );
            break;
        }

        case NS(OBJECT_TYPE_SROTATION):
        {
            typedef NS(SRotation)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            ret = NS(Track_particle_srotation)( particles, particle_index, belem );
            break;
        }

        case NS(OBJECT_TYPE_BEAM_MONITOR):
        {
            typedef NS(BeamMonitor)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            NS(Particles_set_at_element_id_value)(
                particles, particle_index, beam_element_id );

            ret = NS(Track_particle_beam_monitor)(
                particles, particle_index, belem );

            break;
        }

        #if !defined( SIXTRL_DISABLE_BEAM_BEAM )

        case NS(OBJECT_TYPE_BEAM_BEAM_4D):
        {
            typedef NS(BeamBeam4D)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            ret = NS(Track_particle_beam_beam_4d)(
                particles, particle_index, belem );
            break;
        }

        case NS(OBJECT_TYPE_BEAM_BEAM_6D):
        {
            typedef NS(BeamBeam6D)   belem_t;
            typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_to_belem_t;
            ptr_to_belem_t belem = ( ptr_to_belem_t )( uintptr_t )begin_addr;

            ret = NS(Track_particle_beam_beam_6d)(
                particles, particle_index, belem );
            break;
        }

        #endif /* !defined( SIXTRL_DISABLE_BEAM_BEAM ) */

        default:
        {
            NS(Particles_set_state_value)( particles, particle_index, 0 );
            NS(Particles_set_at_element_id_value)(
                particles, particle_index, beam_element_id );

            ret = -8;
        }
    };

    return ret;
}


SIXTRL_INLINE int NS(Track_subset_of_particles_beam_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info )
{
    typedef NS(particle_index_t) index_t;

    SIXTRL_ASSERT( particle_idx_stride >  ( NS(particle_num_elements_t) )0 );
    SIXTRL_ASSERT( particle_idx        >= ( NS(particle_num_elements_t) )0 );
    SIXTRL_ASSERT( particle_idx_end    >= particle_idx );

    for( ; particle_idx < particle_idx_end ; particle_idx += particle_idx_stride )
    {
        if( NS(Particles_get_state_value)( particles, particle_idx ) == ( index_t )1 )
        {
            NS(Track_particle_beam_element_obj)(
                particles, particle_idx, beam_element_id, be_info );
        }
    }

    return 0;
}

SIXTRL_INLINE int NS(Track_all_particles_beam_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_info )
{
    return NS(Track_subset_of_particles_beam_element_obj)(
        particles, 0u, NS(Particles_get_num_of_particles)( particles ), 1u,
            beam_element_id, be_info );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE int NS(Track_particle_beam_elements_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_it,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end )
{
    typedef NS(particle_index_t)  index_t;

    SIXTRL_STATIC_VAR index_t const LOST_STATE = ( index_t )0u;

    SIXTRL_ASSERT( be_it  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( be_end != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ( ( uintptr_t )be_it ) <= ( ( uintptr_t )be_end ) );

    if( NS(Particles_get_state_value)( particles, particle_idx ) != LOST_STATE )
    {
        int ret = 0;

        NS(particle_index_t) beam_element_id =
            NS(Particles_get_at_element_id_value)( particles, particle_idx );

        while( ( ret == 0 ) && ( be_it != be_end ) )
        {
            ret = NS(Track_particle_beam_element_obj)(
                particles, particle_idx, beam_element_id++, be_it++ );
        }

        if( NS(Particles_get_state_value)(
                particles, particle_idx ) != LOST_STATE )
        {
            NS(Particles_set_at_element_id_value)(
                particles, particle_idx, beam_element_id );
        }

        SIXTRL_ASSERT( ( ret == 0 ) ||
            ( NS(Particles_get_state_value)( particles, particle_idx ) !=
              ( index_t )1 ) );
    }

    return 0;
}


SIXTRL_INLINE int NS(Track_subset_of_particles_beam_elements_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) index,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end )
{
    SIXTRL_ASSERT( begin != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( end   != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ( ( uintptr_t )begin ) <= ( ( uintptr_t )end ) );

    SIXTRL_ASSERT( particle_idx_stride > ( NS(particle_num_elements_t) )0u );
    SIXTRL_ASSERT( index >= ( NS(particle_num_elements_t) )0u );
    SIXTRL_ASSERT( index <= particle_idx_end );

    for( ; index < particle_idx_end ; index += particle_idx_stride )
    {
        NS(Track_particle_beam_elements_obj)( particles, index, begin, end );
    }

    return 0;
}


SIXTRL_INLINE int NS(Track_all_particles_beam_elements_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end )
{
    return NS(Track_subset_of_particles_beam_elements_obj)( particles, 0u,
        NS(Particles_get_num_of_particles)( particles ), 1u, begin, end );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE int NS(Track_particle_until_turn_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const end_turn )
{
    typedef NS(particle_index_t) index_t;

    SIXTRL_STATIC_VAR index_t const LOST_STATE = ( index_t )0;

    index_t state = NS(Particles_get_state_value)( particles, index );
    index_t turn  = NS(Particles_get_at_turn_value)( particles, index );

    index_t const start_beam_element_id =
        NS(Particles_get_at_element_id_value)( particles, index );

    SIXTRL_ASSERT( be_begin != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( be_end   != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ( ( uintptr_t )be_begin ) <= ( ( uintptr_t )be_end ) );

    while( ( state != LOST_STATE ) && ( turn < end_turn ) )
    {
        SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* be_it = be_begin;
        index_t beam_element_id = start_beam_element_id;

        for( ; be_it != be_end ; ++be_it, ++beam_element_id )
        {
            int const ret = NS(Track_particle_beam_element_obj)(
                    particles, index, beam_element_id, be_it );

            if( 0 != ret )
            {
                state = NS(Particles_get_state_value)( particles, index );
                SIXTRL_ASSERT( state == LOST_STATE );
                break;
            }
        }

        if( state != LOST_STATE )
        {
            ++turn;

            NS(Particles_set_at_element_id_value)(
                particles, index, start_beam_element_id );

            NS(Particles_set_at_turn_value)( particles, index, turn );
        }
    }

    return 0;
}

SIXTRL_INLINE int NS(Track_subset_of_particles_until_turn_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) index,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const end_turn )
{
    SIXTRL_ASSERT( index >= ( NS(particle_num_elements_t) )0 );
    SIXTRL_ASSERT( particle_idx_stride > ( NS(particle_num_elements_t) )0 );
    SIXTRL_ASSERT( index <= particle_idx_end );

    for( ; index < particle_idx_end ; index += particle_idx_stride )
    {
        NS(Track_particle_until_turn_obj)(
            particles, index, be_begin, be_end, end_turn );
    }

    return 0;
}

SIXTRL_INLINE int NS(Track_all_particles_until_turn_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    NS(particle_index_t) const end_turn )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    num_elem_t const end_idx = NS(Particles_get_num_of_particles)( particles );
    num_elem_t ii = ( num_elem_t )0u;

    for( ; ii < end_idx ; ++ii )
    {
        NS(Track_particle_until_turn_obj)(
            particles, ii, be_begin, be_end, end_turn );
    }

    return 0;
}

SIXTRL_INLINE int NS(Track_particle_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    NS(particle_index_t) start_beam_element_id,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_INLINE int NS(Track_particle_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    NS(particle_index_t) start_beam_element_id,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_INLINE int NS(Track_all_particles_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const start_beam_element_id,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );


SIXTRL_INLINE int NS(Track_particle_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const turn_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_INLINE int NS(Track_subset_of_particle_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const turn_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

SIXTRL_INLINE int NS(Track_all_particles_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const turn_id,
    NS(elem_by_elem_order_t) const order,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );

#if !defined( _GPUCODE )

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE int NS(Track_particle_element_by_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    NS(particle_index_t) beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT ptr_be_obj,
    NS(particle_num_elements_t) const total_num_beam_elements_per_turn,
    NS(particle_index_t) const max_particle_id,
    NS(particle_index_t) const min_particle_id,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles );


SIXTRL_INLINE int NS(Track_particle_element_by_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    NS(particle_index_t) beam_element_id,
    NS(particle_num_elements_t) const num_elem_by_elem_objects_per_turn,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_it,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT ptr_out_object )
{
    typedef NS(particle_index_t)            index_t;
    typedef NS(particle_num_elements_t)     num_elem_t;
    typedef NS(buffer_size_t)               buf_size_t;

    int ret = 0;

    SIXTRL_BUFFER_OBJ_DATAPTR_DEC NS(Particles)* out_particles =
            NS(BufferIndex_get_particles)( ptr_out_object );

    num_elem_t const out_num_particles =
            NS(Particles_get_num_of_particles)( out_particles );

    index_t const at_turn_id = NS(Particles_get_at_turn_value)(
        particles, particle_index );

    index_t const in_particle_id = NS(Particles_get_particle_id_value)(
        particls, particle_index );

    num_elem_t out_particle_index =
        at_turn_id * num_elem_by_elem_objects_per_turn +!b14apg
        !

    SIXTRL_ASSERT( be_it  != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( be_end != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ( ( uintptr_t )be_it ) <= ( ( uintptr_t )be_end ) );
    SIXTRL_ASSERT( particle_index >= ( num_elem_t )0u );

    SIXTRL_ASSERT( particle_index <
        NS(Particles_get_num_of_particles)( particles ) );

    for( ; be_it != be_end ; ++be_it )
    {


        if( ( out_particles != SIXTRL_NULLPTR ) &&
            ( at_turn_id >= ( index_t )0u ) &&
            (
        {
            NS(Particles_copy_single)( out_particles, particle_index,
                                       particles, particle_index );

            if( NS(Particles_get_state_value)( out_particles, particle_index ) ==
                ( index_t )1 )
            {
                NS(Particles_set_at_element_id_value)(
                    out_particles, particle_index, beam_element_id );
            }
        }
        else
        {
            NS(Particles_set_at_element_id_value)(
                particles, particle_index, beam_element_id );

            NS(Particles_set_state_value)(
                particles, particle_index, ( NS(particle_index_t) )0u );

            ret = -1;
            break;
        }

        if( 0 != NS(Track_particle_beam_element_obj)(
                particles, particle_index, beam_element_id++, be_it ) )
        {
            break;
        }
    }

    return ret;
}

SIXTRL_INLINE int NS(Track_subset_of_particles_element_by_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    NS(particle_index_t) const start_beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT out_obj_begin )
{
    SIXTRL_ASSERT( particle_idx_stride > ( NS(particle_num_elements_t) )0u );
    SIXTRL_ASSERT( particle_idx >= ( NS(particle_num_elements_t) )0u );
    SIXTRL_ASSERT( particle_idx <= particle_idx_end );

    for( ; particle_idx < particle_idx_end ; particle_idx += particle_idx_stride )
    {
        NS(Track_particle_element_by_element_obj)(
            particles, particle_idx, start_beam_element_id,
            be_begin, be_end, out_obj_begin );
    }

    return 0;
}

SIXTRL_INLINE int NS(Track_all_particles_element_by_element_obj)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const start_beam_element_id,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT be_end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object)* SIXTRL_RESTRICT out_obj_begin )
{
    return NS(Track_subset_of_particles_element_by_element_obj)(
        particles, 0u, NS(Particles_get_num_of_particles)( particles ), 1u,
        start_beam_element_id, be_begin, be_end, out_obj_begin );
}

/* ------------------------------------------------------------------------- */

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_COMMON_TRACK_H__ */

/* end: sixtracklib/common/track.h */
