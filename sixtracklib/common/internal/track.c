#include "sixtracklib/common/track.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/config.h"
#include "sixtracklib/common/internal/beam_elements_defines.h"
#include "sixtracklib/common/internal/particles_defines.h"
#include "sixtracklib/common/output/elem_by_elem_config.h"
#include "sixtracklib/common/output/output_buffer.h"
#include "sixtracklib/common/beam_elements.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/particles.h"

SIXTRL_HOST_FN SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* NS(TrackCpu)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT beam_elements_buffer,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    int const until_turn, int const elem_by_elem_turns )
{
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* ptr_out_buffer = SIXTRL_NULLPTR;

    NS(Buffer)* ptr_output = SIXTRL_NULLPTR;

    if( ( particles_buffer != SIXTRL_NULLPTR ) &&
        ( beam_elements_buffer != SIXTRL_NULLPTR ) &&
        ( until_turn >= 0 ) && ( elem_by_elem_turns >= 0 ) &&
        ( elem_by_elem_turns <= until_turn ) )
    {
        SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* particles =
            NS(Particles_buffer_get_particles)( particles_buffer, 0u );

        bool const has_beam_monitors =
            NS(BeamMonitor_are_present_in_buffer)( beam_elements_buffer );

        bool const prepare_out_buffer =
            ( ( elem_by_elem_turns > 0 ) || ( has_beam_monitors ) );

        int success = ( prepare_out_buffer ) ? -1 : 0;

        if( output_buffer != SIXTRL_NULLPTR )
        {
            ptr_out_buffer = output_buffer;
            success = 0;
        }
        else
        {
            ptr_out_buffer = NS(Buffer_new)( 0u );

            success = NS(BeamMonitor_prepare_particles_out_buffer)(
                beam_elements_buffer, ptr_out_buffer,
                    particles, elem_by_elem_turns );
        }

        if( ( success == 0 ) && ( prepare_out_buffer ) )
        {
            success = NS(BeamMonitor_assign_particles_out_buffer)(
                beam_elements_buffer, ptr_output, elem_by_elem_turns );
        }

        if( ( success == 0 ) && ( elem_by_elem_turns > 0 ) )
        {
            SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* elem_by_elem_particles =
                NS(Particles_buffer_get_particles)( ptr_output, 0u );

            SIXTRL_ASSERT( elem_by_elem_particles != SIXTRL_NULLPTR );
            SIXTRL_ASSERT( NS(Buffer_get_num_of_objects)( ptr_output ) >
                       ( NS(buffer_size_t) )0u );

            success = NS(Track_all_particles_element_by_element_until_turn)(
                particles, beam_elements_buffer, elem_by_elem_turns,
                    elem_by_elem_particles );
        }

        if( ( success == 0 ) && ( elem_by_elem_turns < until_turn ) )
        {
            success = NS(Track_all_particles_until_turn)(
                particles, beam_elements_buffer, until_turn );
        }
    }

    return ptr_output;
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_index )
{
    return NS(Track_particle_beam_element_obj)(
        particles, particle_idx, NS(Buffer_get_const_object)(
            beam_elements, be_index ) );
}

SIXTRL_HOST_FN int NS(Track_subset_of_particles_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_index )
{
    return NS(Track_subset_of_particles_beam_element_obj)(
        particles, particle_idx_begin, particle_idx_end, particle_idx_stride,
        NS(Buffer_get_const_object)( beam_elements, be_index ) );
}


SIXTRL_HOST_FN int NS(Track_all_particles_beam_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_index )
{
    return NS(Track_subset_of_particles_beam_element_obj)(
        particles, 0, NS(Particles_get_num_of_particles)( particles ), 1,
        NS(Buffer_get_const_object)( beam_elements, be_index ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_subset_of_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_index_begin,
    NS(buffer_size_t) const be_index_end )
{
    return NS(Track_particle_beam_elements_obj)(
        particles, particle_idx,
        NS(Buffer_get_const_object)( beam_elements, be_index_begin ),
        NS(Buffer_get_const_object)( beam_elements, be_index_end ) );
}

SIXTRL_HOST_FN int NS(Track_subset_of_particles_subset_of_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_index_begin,
    NS(buffer_size_t) const be_index_end )
{
    return NS(Track_subset_of_particles_beam_elements_obj)(
        particles, particle_idx_begin, particle_idx_end, particle_idx_stride,
        NS(Buffer_get_const_object)( beam_elements, be_index_begin ),
        NS(Buffer_get_const_object)( beam_elements, be_index_end ) );
}

SIXTRL_HOST_FN int NS(Track_all_particles_subset_of_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(buffer_size_t) const be_begin_idx, NS(buffer_size_t) const be_end_idx )
{
    return NS(Track_subset_of_particles_beam_elements_obj)(
        particles, 0, NS(Particles_get_num_of_particles)( particles), 1,
        NS(Buffer_get_const_object)( beam_elements, be_begin_idx ),
        NS(Buffer_get_const_object)( beam_elements, be_end_idx ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements )
{
    return NS(Track_particle_beam_elements_obj)( particles, particle_idx,
        NS(Buffer_get_const_objects_begin)( beam_elements ),
        NS(Buffer_get_const_objects_end)( beam_elements ) );
}


SIXTRL_HOST_FN int NS(Track_subset_of_particles_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements )
{
    return NS(Track_subset_of_particles_beam_elements_obj)(
        particles, particle_idx_begin, particle_idx_end, particle_idx_stride,
        NS(Buffer_get_const_objects_begin)( beam_elements ),
        NS(Buffer_get_const_objects_end)( beam_elements ) );
}


SIXTRL_HOST_FN int NS(Track_all_particles_beam_elements)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements )
{
    return NS(Track_subset_of_particles_beam_elements_obj)( particles, 0,
        NS(Particles_get_num_of_particles)( particles ), 1,
        NS(Buffer_get_const_objects_begin)( beam_elements ),
        NS(Buffer_get_const_objects_end)( beam_elements ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_index,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const until_turn )
{
    return NS(Track_particle_until_turn_obj)( particles, particle_index,
        NS(Buffer_get_const_objects_begin)( beam_elements ),
        NS(Buffer_get_const_objects_end)( beam_elements ), until_turn );
}

SIXTRL_HOST_FN int NS(Track_subset_of_particles_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const particle_idx_begin,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const until_turn )
{
    return NS(Track_subset_of_particles_until_turn_obj)(
        particles, particle_idx_begin, particle_idx_end, particle_idx_stride,
        NS(Buffer_get_const_objects_begin)( beam_elements ),
        NS(Buffer_get_const_objects_end)( beam_elements ), until_turn );
}

SIXTRL_HOST_FN int NS(Track_all_particles_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer) const* SIXTRL_RESTRICT beam_elements,
    NS(particle_index_t) const until_turn )
{
    return NS(Track_all_particles_until_turn_obj)( particles,
        NS(Buffer_get_const_objects_begin)( beam_elements ),
        NS(Buffer_get_const_objects_end)( beam_elements ),
        until_turn );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_element_by_element_details)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const idx,
    SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(buffer_size_t) const be_index )
{
    return NS(Track_particle_element_by_element_obj)( particles, idx, config,
        NS(Buffer_get_const_object)( belements, be_index ) );
}

SIXTRL_HOST_FN int NS(Track_subset_of_particles_element_by_element_details)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) idx,
    NS(particle_num_elements_t) const particle_idx_end,
    NS(particle_num_elements_t) const particle_idx_stride,
    SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(buffer_size_t) const be_index )
{
    return NS(Track_subset_of_particles_element_by_element_obj)(
        particles, idx, particle_idx_end, particle_idx_stride, config,
        NS(Buffer_get_const_object)( belements, be_index ) );
}

SIXTRL_HOST_FN int NS(Track_all_particles_element_by_element_details)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(buffer_size_t) const be_index )
{
    return NS(Track_all_particles_element_by_element_obj)( particles, config,
        NS(Buffer_get_const_object)( belements, be_index ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    NS(particle_index_t) const max_turn,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles )
{
    typedef NS(particle_index_t)        index_t;
    typedef NS(particle_num_elements_t) num_elem_t;

    index_t min_particle_id   = ( index_t )0;
    index_t max_particle_id   = ( index_t )0;

    index_t min_at_element_id = ( index_t )0;
    index_t max_at_element_id = ( index_t )0;

    index_t min_at_turn       = ( index_t )0;
    index_t max_at_turn       = ( index_t )0;

    int success = NS(Particles_find_min_max_attributes)( particles,
        &min_particle_id, &max_particle_id,
        &min_at_element_id, &max_at_element_id,
        &min_at_turn, &max_at_turn );

    NS(ElemByElemConfig) config;
    NS(ElemByElemConfig_preset)( &config );

    if( success == 0 )
    {
        num_elem_t const num_beam_elements =
            NS(Buffer_get_num_of_objects)( belements );

        if( ( num_beam_elements >= ( num_elem_t )0u ) &&
            ( num_beam_elements >  ( num_elem_t )(
                max_at_element_id + ( index_t )1u ) ) )
        {
            max_at_element_id = ( index_t )(
                num_beam_elements - ( num_elem_t )1u );
        }

        SIXTRL_ASSERT( min_at_turn >= ( index_t )0u );
        SIXTRL_ASSERT( max_at_turn >= min_at_turn );

        if( max_at_turn < max_turn )
        {
            max_at_turn = max_turn;
        }

        success = NS(ElemByElemConfig_init_detailed)(
            &config, NS(ELEM_BY_ELEM_ORDER_TURN_ELEM_PARTICLES),
            min_particle_id, max_particle_id, min_at_element_id,
            max_at_element_id, min_at_turn, max_at_turn );

        if( success == 0 )
        {
            NS(ElemByElemConfig_set_output_store_address)(
                &config, ( uintptr_t )out_particles );

            success = NS(Track_particle_element_by_element_until_turn_objs)(
                particles, index, &config,
                NS(Buffer_get_const_objects_begin)( belements ),
                NS(Buffer_get_const_objects_end)( belements ), max_turn );
        }
    }

    return success;
}

SIXTRL_HOST_FN int NS(Track_subset_of_particles_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const idx,
    NS(particle_num_elements_t) const idx_end,
    NS(particle_num_elements_t) const stride,
    NS(particle_index_t) const max_turn,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles )
{
    typedef NS(particle_index_t)        index_t;
    typedef NS(particle_num_elements_t) num_elem_t;

    index_t min_particle_id   = ( index_t )0;
    index_t max_particle_id   = ( index_t )0;

    index_t min_at_element_id = ( index_t )0;
    index_t max_at_element_id = ( index_t )0;

    index_t min_at_turn       = ( index_t )0;
    index_t max_at_turn       = ( index_t )0;

    int success = NS(Particles_find_min_max_attributes)( particles,
        &min_particle_id, &max_particle_id,
        &min_at_element_id, &max_at_element_id,
        &min_at_turn, &max_at_turn );

    NS(ElemByElemConfig) config;
    NS(ElemByElemConfig_preset)( &config );

    if( success == 0 )
    {
        num_elem_t const num_beam_elements =
            NS(Buffer_get_num_of_objects)( belements );

        if( ( num_beam_elements >= ( num_elem_t )0u ) &&
            ( num_beam_elements >  ( num_elem_t )(
                max_at_element_id + ( index_t )1u ) ) )
        {
            max_at_element_id = ( index_t )(
                num_beam_elements - ( num_elem_t )1u );
        }

        SIXTRL_ASSERT( min_at_turn >= ( index_t )0u );
        SIXTRL_ASSERT( max_at_turn >= min_at_turn );

        if( max_at_turn < max_turn )
        {
            max_at_turn = max_turn;
        }

        success = NS(ElemByElemConfig_init_detailed)(
            &config, NS(ELEM_BY_ELEM_ORDER_TURN_ELEM_PARTICLES),
            min_particle_id, max_particle_id, min_at_element_id,
            max_at_element_id, min_at_turn, max_at_turn );

        if( success == 0 )
        {
            NS(ElemByElemConfig_set_output_store_address)(
                &config, ( uintptr_t )out_particles );

            success =
            NS(Track_subset_of_particles_element_by_element_until_turn_objs)(
                particles, idx, idx_end, stride, &config,
                NS(Buffer_get_const_objects_begin)( belements ),
                NS(Buffer_get_const_objects_end)( belements ), max_turn );
        }
    }

    return success;
}

SIXTRL_HOST_FN int NS(Track_all_particles_element_by_element)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const max_turn,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles )
{
    typedef NS(particle_num_elements_t) num_elem_t;

    return NS(Track_subset_of_particles_element_by_element)( particles,
        ( num_elem_t )0u, NS(Particles_get_num_of_particles)( particles ),
        ( num_elem_t )1u, max_turn, belements, out_particles );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_element_by_elements_details)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const idx,
    SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(buffer_size_t) const be_begin_idx, NS(buffer_size_t) const be_end_idx )
{
    SIXTRL_ASSERT( be_begin_idx <= be_end_idx );
    SIXTRL_ASSERT( NS(Buffer_get_num_of_objects)( belements ) >= be_end_idx );

    return NS(Track_particle_element_by_element_objs)(
        particles, idx, config,
        NS(Buffer_get_const_object)( belements, be_begin_idx ),
        NS(Buffer_get_const_object)( belements, be_end_idx ) );
}

SIXTRL_HOST_FN int NS(Track_subset_of_particles_element_by_elements_details)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) idx,
    NS(particle_num_elements_t) const idx_end,
    NS(particle_num_elements_t) const stride,
    SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(buffer_size_t) const be_begin_idx, NS(buffer_size_t) const be_end_idx )
{
    SIXTRL_ASSERT( be_begin_idx <= be_end_idx );
    SIXTRL_ASSERT( be_end_idx <= NS(Buffer_get_num_of_objects)( belements ) );

    return NS(Track_subset_of_particles_element_by_element_objs)(
        particles, idx, idx_end, stride, config,
        NS(Buffer_get_const_object)( belements, be_begin_idx ),
        NS(Buffer_get_const_object)( belements, be_end_idx ) );
}

SIXTRL_HOST_FN int NS(Track_all_particles_element_by_elements_details)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(buffer_size_t) const be_begin_idx, NS(buffer_size_t) const be_end_idx )
{
    SIXTRL_ASSERT( be_begin_idx <= be_end_idx );
    SIXTRL_ASSERT( be_end_idx <= NS(Buffer_get_num_of_objects)( belements ) );

    return NS(Track_all_particles_element_by_element_objs)( particles, config,
        NS(Buffer_get_const_object)( belements, be_begin_idx ),
        NS(Buffer_get_const_object)( belements, be_end_idx ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_element_by_element_until_turn_details)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_index_t) const index,
    SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(particle_index_t) const until_turn )
{
    return NS(Track_particle_element_by_element_until_turn_objs)(
        particles, index, config,
        NS(Buffer_get_const_objects_begin)( belements ),
        NS(Buffer_get_const_objects_end)( belements ), until_turn );
}

SIXTRL_HOST_FN int
    NS(Track_subset_of_particles_element_by_element_until_turn_details)(
        SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
        NS(particle_num_elements_t) idx,
        NS(particle_num_elements_t) const idx_end,
        NS(particle_num_elements_t) const stride,
        SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
            *const SIXTRL_RESTRICT config,
        SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer)
            *const SIXTRL_RESTRICT belements,
        NS(particle_index_t) const until_turn )
{
    return NS(Track_subset_of_particles_element_by_element_until_turn_objs)(
        particles, idx, idx_end, stride, config,
        NS(Buffer_get_const_objects_begin)( belements ),
        NS(Buffer_get_const_objects_end)( belements ), until_turn );
}

SIXTRL_HOST_FN int
    NS(Track_all_particles_element_by_element_until_turn_details)(
        SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_ELEM_BY_ELEM_CONFIG_ARGPTR_DEC const NS(ElemByElemConfig)
            *const SIXTRL_RESTRICT config,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(particle_index_t) const until_turn )
{
    return NS(Track_all_particles_element_by_element_until_turn_objs)(
        particles, config, NS(Buffer_get_const_objects_begin)( belements ),
        NS(Buffer_get_const_objects_end)( belements ), until_turn );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(Track_particle_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) const index,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(particle_index_t) const until_turn,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles )
{
    typedef NS(particle_index_t)        index_t;
    typedef NS(particle_num_elements_t) num_elem_t;

    index_t min_particle_id   = ( index_t )0;
    index_t max_particle_id   = ( index_t )0;

    index_t min_at_element_id = ( index_t )0;
    index_t max_at_element_id = ( index_t )0;

    index_t min_at_turn       = ( index_t )0;
    index_t max_at_turn       = ( index_t )0;

    int success = NS(Particles_find_min_max_attributes)( particles,
        &min_particle_id, &max_particle_id,
        &min_at_element_id, &max_at_element_id,
        &min_at_turn, &max_at_turn );

    NS(ElemByElemConfig) config;
    NS(ElemByElemConfig_preset)( &config );

    if( success == 0 )
    {
        num_elem_t const num_beam_elements =
            NS(Buffer_get_num_of_objects)( belements );

        if( ( num_beam_elements >= ( num_elem_t )0u ) &&
            ( num_beam_elements >  ( num_elem_t )(
                max_at_element_id + ( index_t )1u ) ) )
        {
            max_at_element_id = ( index_t )(
                num_beam_elements - ( num_elem_t )1u );
        }

        SIXTRL_ASSERT( min_at_turn >= ( index_t )0u );
        SIXTRL_ASSERT( max_at_turn >= min_at_turn );

        if( max_at_turn < until_turn )
        {
            max_at_turn = until_turn;
        }

        success = NS(ElemByElemConfig_init_detailed)(
            &config, NS(ELEM_BY_ELEM_ORDER_TURN_ELEM_PARTICLES),
            min_particle_id, max_particle_id, min_at_element_id,
            max_at_element_id, min_at_turn, max_at_turn );

        if( success == 0 )
        {
            NS(ElemByElemConfig_set_output_store_address)(
                &config, ( uintptr_t )out_particles );

            success = NS(Track_particle_element_by_element_until_turn_objs)(
                particles, index, &config,
                NS(Buffer_get_const_objects_begin)( belements ),
                NS(Buffer_get_const_objects_end)( belements ), until_turn );
        }
    }

    return success;
}

SIXTRL_HOST_FN int NS(Track_subset_of_particles_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    NS(particle_num_elements_t) idx,
    NS(particle_num_elements_t) const idx_end,
    NS(particle_num_elements_t) const stride,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(particle_index_t) const until_turn,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles )
{
    typedef NS(particle_index_t)        index_t;
    typedef NS(particle_num_elements_t) num_elem_t;

    index_t min_particle_id   = ( index_t )0;
    index_t max_particle_id   = ( index_t )0;

    index_t min_at_element_id = ( index_t )0;
    index_t max_at_element_id = ( index_t )0;

    index_t min_at_turn       = ( index_t )0;
    index_t max_at_turn       = ( index_t )0;

    int success = NS(Particles_find_min_max_attributes)( particles,
        &min_particle_id, &max_particle_id,
        &min_at_element_id, &max_at_element_id,
        &min_at_turn, &max_at_turn );

    NS(ElemByElemConfig) config;
    NS(ElemByElemConfig_preset)( &config );

    if( success == 0 )
    {
        num_elem_t const num_beam_elements =
            NS(Buffer_get_num_of_objects)( belements );

        if( ( num_beam_elements >= ( num_elem_t )0u ) &&
            ( num_beam_elements >  ( num_elem_t )(
                max_at_element_id + ( index_t )1u ) ) )
        {
            max_at_element_id = ( index_t )(
                num_beam_elements - ( num_elem_t )1u );
        }

        SIXTRL_ASSERT( min_at_turn >= ( index_t )0u );
        SIXTRL_ASSERT( max_at_turn >= min_at_turn );

        if( max_at_turn < until_turn )
        {
            max_at_turn = until_turn;
        }

        success = NS(ElemByElemConfig_init_detailed)(
            &config, NS(ELEM_BY_ELEM_ORDER_TURN_ELEM_PARTICLES),
            min_particle_id, max_particle_id, min_at_element_id,
            max_at_element_id, min_at_turn, max_at_turn );

        if( success == 0 )
        {
            NS(ElemByElemConfig_set_output_store_address)(
                &config, ( uintptr_t )out_particles );

            success =
            NS(Track_subset_of_particles_element_by_element_until_turn_objs)(
                particles, idx, idx_end, stride, &config,
                NS(Buffer_get_const_objects_begin)( belements ),
                NS(Buffer_get_const_objects_end)( belements ), until_turn );
        }
    }

    return success;
}

SIXTRL_HOST_FN int NS(Track_all_particles_element_by_element_until_turn)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT belements,
    NS(particle_index_t) const until_turn,
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT out_particles )
{
    return NS(Track_subset_of_particles_element_by_element_until_turn)(
        particles, 0, NS(Particles_get_num_of_particles)( particles ), 1,
            belements, until_turn, out_particles );
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* NS(TrackCpu)(
    SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)* SIXTRL_RESTRICT particles,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT beam_elements,
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    int const until_turn, int const elem_by_elem_turns )
{
    NS(Buffer)* ptr_output = SIXTRL_NULLPTR;

    typedef NS(buffer_size_t)       buf_size_t;
    typedef NS(particle_index_t)    index_t;

    if( ( particles != SIXTRL_NULLPTR ) &&
        ( beam_elements != SIXTRL_NULLPTR ) &&
        ( until_turn >= 0 ) && ( elem_by_elem_turns >= 0 ) &&
        ( elem_by_elem_turns <= until_turn ) )
    {
        int success = -1;

        if( output_buffer != SIXTRL_NULLPTR )
        {
            ptr_output = output_buffer;
        }
        else
        {
            ptr_output = NS(Buffer_new)( 0u );
        }

        if( ptr_output != SIXTRL_NULLPTR )
        {
            buf_size_t elem_by_elem_index_offset = ( buf_size_t )0u;
            buf_size_t beam_monitor_index_offset = ( buf_size_t )0u;
            index_t min_turn_id                  = ( index_t )0u;

            success  = NS(OutputBuffer_prepare)(
                    beam_elements, ptr_output, particles, elem_by_elem_turns,
                    &elem_by_elem_index_offset, &beam_monitor_index_offset,
                    &min_turn_id );

            if( success == 0 )
            {
                success = NS(BeamMonitor_assign_output_buffer_from_offset)(
                    beam_elements, ptr_output, min_turn_id,
                        beam_monitor_index_offset );
            }

            if( ( success == 0 ) && ( elem_by_elem_turns > 0 ) )
            {
                SIXTRL_PARTICLE_ARGPTR_DEC NS(Particles)*
                elem_by_elem_particles = NS(Particles_buffer_get_particles)(
                    ptr_output, elem_by_elem_index_offset );

                SIXTRL_ASSERT( elem_by_elem_particles != SIXTRL_NULLPTR );
                SIXTRL_ASSERT( NS(Buffer_get_num_of_objects)( ptr_output ) >
                           ( NS(buffer_size_t) )0u );

                success = NS(Track_all_particles_element_by_element_until_turn)(
                    particles, beam_elements, elem_by_elem_turns,
                        elem_by_elem_particles );
            }

            if( ( success == 0 ) && ( elem_by_elem_turns < until_turn ) )
            {
                success = NS(Track_all_particles_until_turn)(
                    particles, beam_elements, until_turn );
            }

            if( success != 0 )
            {
                NS(Buffer_delete)( ptr_output );
                ptr_output = SIXTRL_NULLPTR;
            }
        }
    }

    return ptr_output;
}

/* end: /common/internal/track.c */
