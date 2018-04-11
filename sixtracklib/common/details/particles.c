#include "sixtracklib/common/particles.h"
#include "sixtracklib/_impl/namespace_begin.h"
#include "sixtracklib/common/impl/particles_type.h"

#include <assert.h>

#include "sixtracklib/_impl/inline.h"

#include "sixtracklib/common/mem_pool.h"
#include "sixtracklib/common/restrict.h"
#include "sixtracklib/common/single_particle.h"
#include "sixtracklib/common/values.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* ------------------------------------------------------------------------- */

static NS( Particles ) *
    NS( Particles_preset )( NS( Particles ) * SIXTRL_RESTRICT p );

/* ------------------------------------------------------------------------- */

extern size_t NS( Particles_predict_required_capacity )( 
    size_t num_particles, size_t* SIXTRL_RESTRICT ptr_chunk_size,
    size_t* SIXTRL_RESTRICT ptr_alignment, bool make_packed );
    
/* ------------------------------------------------------------------------- */

extern bool NS( Particles_is_packed )( const struct NS( Particles ) *
                                       const SIXTRL_RESTRICT p );

extern bool NS( Particles_manages_own_memory )( const struct NS( Particles ) *
                                                const SIXTRL_RESTRICT p );

extern bool NS( Particles_uses_mempool )( const struct NS( Particles ) *
                                          const SIXTRL_RESTRICT p );

extern bool NS( Particles_uses_single_particle )( const struct NS( Particles ) *
                                                  const SIXTRL_RESTRICT p );

extern struct NS( MemPool ) const* NS( Particles_get_const_mem_pool )(
    const struct NS( Particles ) * const SIXTRL_RESTRICT p );

extern struct NS( SingleParticle ) const* NS(
    Particles_get_const_base_single_particle )( const struct NS( Particles ) *
                                                const SIXTRL_RESTRICT p );

/* ------------------------------------------------------------------------- */

extern struct NS( Particles ) * NS( Particles_new )( size_t npart );

extern struct NS( Particles ) *
    NS( Particles_new_on_mempool )( size_t npart,
                                    struct NS( MemPool ) *
                                        SIXTRL_RESTRICT pool );

extern struct NS( Particles ) * NS( Particles_new_single )();

extern struct NS( Particles ) *
    NS( Particles_new_on_single )( struct NS( SingleParticle ) *
                                   ptr_single_particle );

extern void NS( Particles_free )( struct NS( Particles ) *
                                  SIXTRL_RESTRICT particles );

static bool NS( Particles_map_to_mempool )( struct NS( Particles ) *
                                                SIXTRL_RESTRICT particles,
                                            struct NS( MemPool ) *
                                                SIXTRL_RESTRICT pool,
                                            size_t npart,
                                            size_t alignment, 
                                            bool make_packed );

static bool NS( Particles_map_to_single_particle )(
    struct NS( Particles ) * SIXTRL_RESTRICT particles,
    struct NS( SingleParticle ) * SIXTRL_RESTRICT single_particle );

/* -------------------------------------------------------------------------- */

extern bool NS( Particles_has_defined_alignment )(
    const struct NS( Particles ) * const SIXTRL_RESTRICT p );

extern bool NS( Particles_is_aligned )( const struct NS( Particles ) *
                                            const SIXTRL_RESTRICT p,
                                        size_t alignment );

extern bool NS( Particles_check_alignment )( const struct NS( Particles ) *
                                                 const SIXTRL_RESTRICT p,
                                             size_t alignment );

extern uint64_t NS( Particles_alignment )( const struct NS( Particles ) *
                                           const SIXTRL_RESTRICT p );

/* ------------------------------------------------------------------------- */

extern bool NS( Particles_is_consistent )( const struct NS( Particles ) *
                                           const SIXTRL_RESTRICT p );

/* ------------------------------------------------------------------------- */

extern bool NS( Particles_deep_copy_one )( struct NS( Particles ) *
                                               SIXTRL_RESTRICT dest,
                                           uint64_t dest_id,
                                           struct NS( Particles )
                                               const* SIXTRL_RESTRICT src,
                                           uint64_t src_id );

extern bool NS( Particles_deep_copy_all )( struct NS( Particles ) *
                                               SIXTRL_RESTRICT dest,
                                           struct NS( Particles )
                                               const* SIXTRL_RESTRICT src );

/* ------------------------------------------------------------------------- */
/* ----- Implementation */
/* ------------------------------------------------------------------------- */

NS( Particles ) * NS( Particles_preset )( NS( Particles ) * SIXTRL_RESTRICT p )
{
    if( p != 0 )
    {
        NS( Particles_assign_ptr_to_q0 )( p, 0 );
        NS( Particles_assign_ptr_to_mass0 )( p, 0 );
        NS( Particles_assign_ptr_to_beta0 )( p, 0 );
        NS( Particles_assign_ptr_to_gamma0 )( p, 0 );
        NS( Particles_assign_ptr_to_p0c )( p, 0 );

        NS( Particles_assign_ptr_to_particle_id )( p, 0 );
        NS( Particles_assign_ptr_to_lost_at_element_id )( p, 0 );
        NS( Particles_assign_ptr_to_lost_at_turn )( p, 0 );
        NS( Particles_assign_ptr_to_state )( p, 0 );

        NS( Particles_assign_ptr_to_s )( p, 0 );
        NS( Particles_assign_ptr_to_x )( p, 0 );
        NS( Particles_assign_ptr_to_px )( p, 0 );
        NS( Particles_assign_ptr_to_y )( p, 0 );
        NS( Particles_assign_ptr_to_py )( p, 0 );
        NS( Particles_assign_ptr_to_sigma )( p, 0 );

        NS( Particles_assign_ptr_to_psigma )( p, 0 );
        NS( Particles_assign_ptr_to_delta )( p, 0 );
        NS( Particles_assign_ptr_to_rpp )( p, 0 );
        NS( Particles_assign_ptr_to_rvv )( p, 0 );
        NS( Particles_assign_ptr_to_chi )( p, 0 );

        NS( Particles_set_size )( p, UINT64_C( 0 ) );
        NS( Particles_set_flags )( p, NS( PARTICLES_FLAGS_NONE ) );
        NS( Particles_set_ptr_mem_context )( p, 0 );
        NS( Particles_set_ptr_mem_begin   )( p, 0 );
    }

    return p;
}

/* ------------------------------------------------------------------------ */

size_t NS( Particles_predict_required_capacity )( 
    size_t num_particles, size_t* SIXTRL_RESTRICT ptr_chunk_size,
    size_t* SIXTRL_RESTRICT ptr_alignment, bool make_packed )
{
    static size_t const ZERO_SIZE = (size_t)0u;

    size_t predicted_capacity = ZERO_SIZE;

    if( ( num_particles > ZERO_SIZE ) && ( ptr_chunk_size != 0 ) &&
        ( ptr_alignment != 0 ) )
    {
        size_t double_elem_length  = sizeof( double  ) * num_particles;
        size_t int64_elem_length   = sizeof( int64_t ) * num_particles;

        size_t chunk_size = *ptr_chunk_size;
        size_t alignment = *ptr_alignment;

        assert( ptr_chunk_size != ptr_alignment );

        if( chunk_size == ZERO_SIZE )
        {
            chunk_size = NS( PARTICLES_DEFAULT_MEMPOOL_CHUNK_SIZE );
        }

        assert( chunk_size <= NS( PARTICLES_MAX_ALIGNMENT ) );

        if( alignment == ZERO_SIZE )
        {
            alignment = NS( PARTICLES_DEFAULT_MEMPOOL_ALIGNMENT );
        }

        if( alignment < chunk_size )
        {
            alignment = chunk_size;
        }

        if( ( alignment % chunk_size ) != ZERO_SIZE )
        {
            alignment =
                chunk_size + ( ( alignment / chunk_size ) * chunk_size );
        }

        assert( ( alignment <= NS( PARTICLES_MAX_ALIGNMENT ) ) &&
                ( alignment >= chunk_size ) &&
                ( ( alignment % chunk_size ) == ZERO_SIZE ) );

        /* ----------------------------------------------------------------- */
        
        if( make_packed )
        {
            /* Packing information: 
             * - 1 x uint64_t .... indicator, i.e. what has been packed
             *                     note: Particles = 1
             * - 1 x uint64_t .... npart, i.e. the number of particles that 
             *                     are packed
             * - 1 x uint64_t .... nelem, i.e. the number of elements 
             *                     that have been packed
             * - num x uint64_t .. nelem x offsets, i.e. for each of the num 
             *                     elemens an offset in bytes on where the 
             *                     data is stored.
             *                     Note: the base address from where to add 
             *                     add these offsets is specific to the storage
             *                     mechanism. For NS(MemPool) instances, its
             *                     the NS(MemPool_get_buffer) address */
            
            size_t pack_info_length = 
                sizeof( uint64_t ) + sizeof( uint64_t ) + sizeof( uint64_t ) + 
                sizeof( uint64_t ) * (
                    NS( PARTICLES_NUM_OF_DOUBLE_ELEMENTS ) +
                    NS( PARTICLES_NUM_OF_INT64_ELEMENTS  ) );
            
            size_t const temp = ( pack_info_length / alignment ) * alignment;
            
            if( temp < pack_info_length )
            {
                pack_info_length = temp + alignment;
            }
            
            assert( ( pack_info_length % alignment ) == ZERO_SIZE );            
            predicted_capacity += pack_info_length;
        }
                
        /* ----------------------------------------------------------------- */

        size_t temp = ( double_elem_length / ( alignment ) ) * ( alignment );

        if( temp < double_elem_length )
        {
            temp += alignment;
        }

        double_elem_length = temp;

        /* ----------------------------------------------------------------- */

        temp = ( int64_elem_length / ( alignment ) ) * ( alignment );

        if( temp < int64_elem_length )
        {
            temp += alignment;
        }

        int64_elem_length = temp;

        /* ----------------------------------------------------------------- */

        assert( ( double_elem_length > ZERO_SIZE ) &&
                ( ( double_elem_length % alignment ) == ZERO_SIZE ) &&
                ( int64_elem_length > ZERO_SIZE ) &&
                ( ( int64_elem_length % alignment ) == ZERO_SIZE ) );

        predicted_capacity +=
            NS( PARTICLES_NUM_OF_DOUBLE_ELEMENTS ) * double_elem_length +
            NS( PARTICLES_NUM_OF_INT64_ELEMENTS  ) * int64_elem_length;

        /* By aligning every part of the Particles struct to the
         * required alignment, we can ensure that the whole block used for
         * packing the data will be aligned internally. We have, however, to
         * account for the possibility that the initial address of the whole
         * memory region will be not properly aligned -> increase the capacity
         * by the alignment to allow for some wiggle room here */

        predicted_capacity += alignment;

        *ptr_chunk_size = chunk_size;
        *ptr_alignment = alignment;
    }

    return predicted_capacity;
}

/* ------------------------------------------------------------------------ */

bool NS( Particles_is_packed )( const struct NS( Particles ) *
                                const SIXTRL_RESTRICT p )
{
    return ( ( p != 0 ) && ( ( p->flags & NS( PARTICLES_FLAGS_PACKED ) ) ==
                             NS( PARTICLES_FLAGS_PACKED ) ) );
}

bool NS( Particles_manages_own_memory )( const struct NS( Particles ) *
                                         const SIXTRL_RESTRICT p )
{
    return ( ( p != 0 ) && ( p->ptr_mem_context != 0 ) &&
             ( ( p->flags & NS( PARTICLES_FLAGS_OWNS_MEMORY ) ) ==
               NS( PARTICLES_FLAGS_OWNS_MEMORY ) ) );
}

bool NS( Particles_uses_mempool )( const struct NS( Particles ) *
                                   const SIXTRL_RESTRICT p )
{
    return ( ( p != 0 ) && ( p->ptr_mem_context != 0 ) &&
             ( ( p->flags & NS( PARTICLES_FLAGS_MEM_CTX_MEMPOOL ) ) ==
               NS( PARTICLES_FLAGS_MEM_CTX_MEMPOOL ) ) );
}

bool NS( Particles_uses_single_particle )( const struct NS( Particles ) *
                                           const SIXTRL_RESTRICT p )
{
    return ( ( p != 0 ) && ( p->ptr_mem_context != 0 ) &&
             ( ( p->flags & NS( PARTICLES_FLAGS_MEM_CTX_SINGLEPARTICLE ) ) ==
               NS( PARTICLES_FLAGS_MEM_CTX_SINGLEPARTICLE ) ) );
}

NS( MemPool )
const* NS( Particles_get_const_mem_pool )( const struct NS( Particles ) *
                                           const SIXTRL_RESTRICT p )
{
    NS( MemPool ) const* ptr_mem_pool = 0;

    if( ( p != 0 ) && ( p->ptr_mem_context != 0 ) &&
        ( ( p->flags & NS( PARTICLES_FLAGS_MEM_CTX_MEMPOOL ) ) ==
          NS( PARTICLES_FLAGS_MEM_CTX_MEMPOOL ) ) )
    {
        ptr_mem_pool = (NS( MemPool ) const*)p->ptr_mem_context;
    }

    return ptr_mem_pool;
}

NS( SingleParticle )
const* NS( Particles_get_const_base_single_particle )(
    const struct NS( Particles ) * const SIXTRL_RESTRICT p )
{
    NS( SingleParticle ) const* ptr_single_particle = 0;

    if( ( p != 0 ) && ( p->ptr_mem_context != 0 ) &&
        ( ( p->flags & NS( PARTICLES_FLAGS_MEM_CTX_SINGLEPARTICLE ) ) ==
          NS( PARTICLES_FLAGS_MEM_CTX_SINGLEPARTICLE ) ) )
    {
        ptr_single_particle = (NS( SingleParticle ) const*)p->ptr_mem_context;
    }

    return ptr_single_particle;
}

/* ------------------------------------------------------------------------ */

bool NS( Particles_map_to_single_particle )( struct NS( Particles ) *
                                                 SIXTRL_RESTRICT particles,
                                             struct NS( SingleParticle ) *
                                                 SIXTRL_RESTRICT single )
{
    bool success = false;

    if( ( single != 0 ) && ( particles != 0 ) )
    {
        NS( Particles_assign_ptr_to_q0 )( particles, &single->q0 );
        NS( Particles_assign_ptr_to_mass0 )( particles, &single->mass0 );
        NS( Particles_assign_ptr_to_beta0 )( particles, &single->beta0 );
        NS( Particles_assign_ptr_to_gamma0 )( particles, &single->gamma0 );
        NS( Particles_assign_ptr_to_p0c )( particles, &single->p0c );

        NS( Particles_assign_ptr_to_particle_id )( particles, &single->partid );
        NS( Particles_assign_ptr_to_lost_at_element_id )
        ( particles, &single->elemid );

        NS( Particles_assign_ptr_to_lost_at_turn )( particles, &single->turn );
        NS( Particles_assign_ptr_to_state )( particles, &single->state );

        NS( Particles_assign_ptr_to_s )( particles, &single->s );
        NS( Particles_assign_ptr_to_x )( particles, &single->x );
        NS( Particles_assign_ptr_to_y )( particles, &single->y );
        NS( Particles_assign_ptr_to_px )( particles, &single->px );
        NS( Particles_assign_ptr_to_py )( particles, &single->py );
        NS( Particles_assign_ptr_to_sigma )( particles, &single->sigma );

        NS( Particles_assign_ptr_to_psigma )( particles, &single->psigma );
        NS( Particles_assign_ptr_to_delta )( particles, &single->delta );
        NS( Particles_assign_ptr_to_rpp )( particles, &single->rpp );
        NS( Particles_assign_ptr_to_rvv )( particles, &single->rvv );
        NS( Particles_assign_ptr_to_chi )( particles, &single->chi );
        
        NS( Particles_set_ptr_mem_begin )( particles, &single );
        
        success = true;
    }

    return success;
}

bool NS( Particles_map_to_mempool )( struct NS( Particles ) *
                                         SIXTRL_RESTRICT particles,
                                     struct NS( MemPool ) *
                                         SIXTRL_RESTRICT pool,
                                     size_t npart,
                                     size_t alignment, 
                                     bool make_packed )
{
    bool success = false;

    typedef unsigned char  uchar_t;
    
    static size_t const ZERO_SIZE = (size_t)0u;

    if( ( pool != 0 ) && ( particles != 0 ) && ( npart > ZERO_SIZE ) &&
        ( npart <= ( size_t )UINT64_MAX ) &&
        ( alignment > ZERO_SIZE ) )
    {
        unsigned char* particles_begin = 0;
        
        NS( Particles ) rollback_particles = *particles;
        NS( MemPool ) rollback_mem_pool = *pool;

        /* try to not use goto's -> rewrite with a dummy do-while loop.
         * change back to plain goto's in case this is less
         * clear/more complicated */

        do
        {
            NS( AllocResult ) add_result;
            
            uint64_t  elem_length;
            uint64_t  elem_offset;
            uint64_t* pack_info_iter = 0;            
            
            uint64_t const num_of_attributes =                 
                NS(PARTICLES_NUM_OF_DOUBLE_ELEMENTS) +
                NS(PARTICLES_NUM_OF_INT64_ELEMENTS);
            
            unsigned char* ptr_elem = 0;
            
            size_t const min_double_member_length = sizeof( double  ) * npart;
            size_t const min_int64_member_length  = sizeof( int64_t ) * npart;
            
            assert( ( ( alignment % sizeof( uint64_t ) ) == ZERO_SIZE ) &&
                    ( ( alignment % sizeof( double   ) ) == ZERO_SIZE ) &&
                    ( ( alignment % sizeof( int64_t  ) ) == ZERO_SIZE ) );
            
            NS( AllocResult_preset )( &add_result );

            /* ------------------------------------------------------------- */
            /* Pack information: */
            
            if( make_packed )
            {
                /* TODO: provide this information somewhere centrally!!!!! */
                uint64_t const pack_indicator   = UINT64_C( 1 );                
                uint64_t const num_of_particles = ( uint64_t )npart;
                
                size_t const offset_info_block_len = 
                    sizeof( pack_indicator ) + 
                    sizeof( num_of_attributes ) + 
                    sizeof( num_of_particles ) + 
                    sizeof( uint64_t ) * num_of_attributes;
                    
                add_result = NS(MemPool_append_aligned)(
                    pool, offset_info_block_len, alignment );
                
                if( ( !NS( AllocResult_valid )( &add_result ) ) ||
                    ( !NS( AllocResult_is_aligned)( &add_result, alignment ) ) )
                {
                    break;                
                }
                
                particles_begin = NS( AllocResult_get_pointer )( &add_result );
                pack_info_iter  = ( uint64_t* )particles_begin;
                
                *pack_info_iter++ = pack_indicator;
                *pack_info_iter++ = num_of_particles;
                *pack_info_iter++ = num_of_attributes;
            }
            
            ptr_elem = NS(MemPool_get_next_begin_pointer)( pool, alignment );
            
            assert( ( !make_packed ) || ( 0 <= ( ptr_elem - 
                ( ( uchar_t* )( pack_info_iter + num_of_attributes ) ) ) ) );
            
            /* ------------------------------------------------------------- */
            /* q0: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( !make_packed )
            {
                particles_begin = ptr_elem;
            }
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_q0 )( particles, ( double*) ptr_elem );            
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* mass0: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_mass0 )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* beta0: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_beta0 )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;
            
            /* ------------------------------------------------------------- */
            /* gamma0: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_gamma0 )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;
            
            /* ------------------------------------------------------------- */
            /* p0c: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_p0c )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* partid: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_int64_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_int64_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_particle_id )( 
                particles, ( int64_t* )ptr_elem );
            
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* elemid: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_int64_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_int64_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_lost_at_element_id)( 
                particles, ( int64_t* )ptr_elem );
            
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* turn: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_int64_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_int64_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_lost_at_turn )( 
                particles, ( int64_t* )ptr_elem );
            
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* state: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_int64_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_int64_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_state )( 
                particles, ( int64_t* )ptr_elem );
            
            if( make_packed ) *pack_info_iter++ = elem_offset;
            
            /* ------------------------------------------------------------- */
            /* s: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_s )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* x: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_x )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* y: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_y )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* px: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_px )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* py: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_py )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* sigma: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_sigma )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* psigma: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_psigma )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* delta: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_delta )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* rpp: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_rpp )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* rvv: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_rvv )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ------------------------------------------------------------- */
            /* chi: */

            add_result = NS( MemPool_append_aligned )(
                pool, min_double_member_length, alignment );
            
            if( !NS( AllocResult_valid )( &add_result ) ) break;                
            
            ptr_elem    = NS( AllocResult_get_pointer )( &add_result );
            elem_offset = NS( AllocResult_get_offset )( &add_result );
            elem_length = NS( AllocResult_get_length )( &add_result );
            
            if( ( elem_length < min_double_member_length ) ||
                ( !NS(AllocResult_is_aligned)( &add_result, alignment ) ) )
            {
                break;
            }
            
            NS( Particles_assign_ptr_to_chi )( particles, ( double*)ptr_elem );
            if( make_packed ) *pack_info_iter++ = elem_offset;

            /* ============================================================= */
            
            success = true;
            
        } while( false );

        if( success )
        {
            assert( particles_begin != 0 );
            NS(Particles_set_ptr_mem_begin)( particles, particles_begin );
        }
        else
        {
            *particles = rollback_particles;
            *pool = rollback_mem_pool;
        }
    }

    return success;
}

/* ------------------------------------------------------------------------- */

NS( Particles ) * NS( Particles_new )( size_t npart )
{
    NS( Particles )* particles = 0;
    NS( MemPool )* ptr_mem_pool = 0;

    size_t chunk_size = NS( PARTICLES_DEFAULT_MEMPOOL_CHUNK_SIZE );
    size_t alignment = NS( PARTICLES_DEFAULT_MEMPOOL_ALIGNMENT );

    size_t const required_capacity =
        NS( Particles_predict_required_capacity )( 
            npart, &chunk_size, &alignment, true );

    if( ( required_capacity > (size_t)0u ) && ( (uint64_t)npart < UINT64_MAX ) )
    {
        bool success = false;

        ptr_mem_pool = (NS( MemPool )*)malloc( sizeof( NS( MemPool ) ) );

        if( ptr_mem_pool != 0 )
        {
            NS( MemPool_init )( ptr_mem_pool, required_capacity, chunk_size );

            if( ( NS( MemPool_get_buffer )( ptr_mem_pool ) == 0 ) ||
                ( NS( MemPool_get_chunk_size )( ptr_mem_pool ) !=
                  chunk_size ) ||
                ( NS( MemPool_get_capacity )( ptr_mem_pool ) <
                  required_capacity ) )
            {
                NS( MemPool_free )( ptr_mem_pool );
                free( ptr_mem_pool );
                ptr_mem_pool = 0;
            }
        }

        particles = NS( Particles_preset )(
            (NS( Particles )*)malloc( sizeof( NS( Particles ) ) ) );

        if( ( ptr_mem_pool != 0 ) && ( particles != 0 ) &&
            ( NS( Particles_map_to_mempool )(
                particles, ptr_mem_pool, npart, alignment, true ) ) )
        {
            uint64_t flags = NS( PARTICLES_FLAGS_PACKED ) |
                             NS( PARTICLES_FLAGS_OWNS_MEMORY ) |
                             NS( PARTICLES_FLAGS_MEM_CTX_MEMPOOL );

            uint64_t temp_alignment = (uint64_t)alignment;

            if( temp_alignment <= NS( PARTICLES_MAX_ALIGNMENT ) )
            {
                flags |= ( temp_alignment
                           << NS( PARTICLES_FLAGS_ALIGN_MASK_OFFSET_BITS ) );
            } else
            {
                /* this should not be necessary, but for paranoia's sake: */
                flags &= ~( NS( PARTICLES_FLAGS_ALIGN_MASK ) );
            }

            assert( NS(Particles_get_mem_begin )( particles ) != 0 );
            
            NS( Particles_set_flags )( particles, flags );
            NS( Particles_set_size )( particles, (uint64_t)npart );
            NS( Particles_set_ptr_mem_context )( particles, ptr_mem_pool );

            success = true;
        }

        if( !success )
        {
            if( ptr_mem_pool != 0 )
            {
                NS( MemPool_free )( ptr_mem_pool );
                free( ptr_mem_pool );
                ptr_mem_pool = 0;
            }

            if( particles != 0 )
            {
                NS( Particles_free )( particles );
                free( particles );
                particles = 0;
            }
        }

        assert(
            ( ( success ) && ( particles != 0 ) && ( ptr_mem_pool != 0 ) ) ||
            ( ( !success ) && ( particles == 0 ) && ( ptr_mem_pool == 0 ) ) );
    }

    return particles;
}

/* ------------------------------------------------------------------------- */

NS( Particles ) *
    NS( Particles_new_on_mempool )( size_t npart,
                                    NS( MemPool ) * SIXTRL_RESTRICT pool )
{
    NS( Particles )* particles = 0;

    size_t chunk_size = NS( MemPool_get_chunk_size )( pool );
    size_t alignment = NS( PARTICLES_DEFAULT_MEMPOOL_ALIGNMENT );

    size_t const required_capacity =
        NS( Particles_predict_required_capacity )( 
            npart, &chunk_size, &alignment, true );

    if( ( required_capacity > (size_t)0u ) &&
        ( chunk_size == NS( MemPool_get_chunk_size )( pool ) ) &&
        ( chunk_size > (size_t)0u ) && ( alignment >= chunk_size ) &&
        ( (uint64_t)npart < UINT64_MAX ) )
    {
        bool success = false;

        particles = NS( Particles_preset )(
            (NS( Particles )*)malloc( sizeof( NS( Particles ) ) ) );

        if( ( particles != 0 ) && 
            ( NS( Particles_map_to_mempool )( 
                particles, pool, npart, alignment, true ) ) )
        {
            uint64_t flags = NS( PARTICLES_FLAGS_PACKED ) |
                             NS( PARTICLES_FLAGS_MEM_CTX_MEMPOOL );

            uint64_t temp_alignment = (uint64_t)alignment;

            if( temp_alignment <= NS( PARTICLES_MAX_ALIGNMENT ) )
            {
                flags |= ( temp_alignment
                           << NS( PARTICLES_FLAGS_ALIGN_MASK_OFFSET_BITS ) );
            } else
            {
                /* this should not be necessary, but for paranoia's sake: */
                flags &= ~( NS( PARTICLES_FLAGS_ALIGN_MASK ) );
            }

            assert( NS(Particles_get_mem_begin )( particles ) != 0 );
            
            NS( Particles_set_flags )( particles, flags );
            NS( Particles_set_size )( particles, (uint64_t)npart );
            NS( Particles_set_ptr_mem_context )( particles, pool );
            
            success = true;
        }

        if( ( !success ) && ( particles != 0 ) )
        {
            NS( Particles_free )( particles );
            free( particles );
            particles = 0;
        }

        assert( ( ( success ) && ( particles != 0 ) ) ||
                ( ( !success ) && ( particles == 0 ) ) );
    }

    return particles;
}

/* ------------------------------------------------------------------------ */

NS( Particles ) * NS( Particles_new_single )()
{
    typedef NS( Particles ) particle_t;
    typedef NS( SingleParticle ) single_t;

    particle_t* ptr_particles =
        NS( Particles_preset )( (particle_t*)malloc( sizeof( particle_t ) ) );

    single_t* ptr_single = (single_t*)malloc( sizeof( single_t ) );

    bool success = false;

    if( ( ptr_particles != 0 ) && ( ptr_single != 0 ) &&
        ( NS( Particles_map_to_single_particle )( ptr_particles,
                                                  ptr_single ) ) )
    {
        uint64_t flags = NS( PARTICLES_FLAGS_OWNS_MEMORY ) |
                         NS( PARTICLES_FLAGS_MEM_CTX_SINGLEPARTICLE );

        NS( Particles_set_flags )( ptr_particles, flags );
        NS( Particles_set_size )( ptr_particles, UINT64_C( 1 ) );
        NS( Particles_set_ptr_mem_context )( ptr_particles, ptr_single );

        success = true;
    }

    if( !success )
    {
        if( ptr_single != 0 )
        {
            free( ptr_single );
            ptr_single = 0;
        }

        if( ptr_particles != 0 )
        {
            free( ptr_particles );
            ptr_particles = 0;
        }
    }

    assert( ( ( success ) && ( ptr_particles != 0 ) && ( ptr_single != 0 ) ) ||
            ( ( !success ) && ( ptr_particles == 0 ) && ( ptr_single == 0 ) ) );

    return ptr_particles;
}

/* ------------------------------------------------------------------------ */

NS( Particles ) *
    NS( Particles_new_on_single )( NS( SingleParticle ) * ptr_single )
{
    typedef NS( Particles ) particle_t;

    particle_t* ptr_particles =
        NS( Particles_preset )( (particle_t*)malloc( sizeof( particle_t ) ) );

    bool success = false;

    if( ( ptr_particles != 0 ) && ( ptr_single != 0 ) &&
        ( NS( Particles_map_to_single_particle )( ptr_particles,
                                                  ptr_single ) ) )
    {
        uint64_t flags = NS( PARTICLES_FLAGS_MEM_CTX_SINGLEPARTICLE );

        NS( Particles_set_flags )( ptr_particles, flags );
        NS( Particles_set_size )( ptr_particles, UINT64_C( 1 ) );
        NS( Particles_set_ptr_mem_context )( ptr_particles, ptr_single );

        success = true;
    }

    if( !success )
    {
        if( ptr_particles != 0 )
        {
            free( ptr_particles );
            ptr_particles = 0;
        }
    }

    assert( ( ( success ) && ( ptr_particles != 0 ) ) ||
            ( ( !success ) && ( ptr_particles == 0 ) ) );

    return ptr_particles;
}

/* ------------------------------------------------------------------------ */

void NS( Particles_free )( struct NS( Particles ) * SIXTRL_RESTRICT particles )
{
    if( NS( Particles_manages_own_memory )( particles ) )
    {
        if( NS( Particles_uses_mempool )( particles ) )
        {
            NS( MemPool )* ptr_mem_pool =
                (NS( MemPool )*)NS( Particles_get_const_mem_pool )( particles );

            if( ptr_mem_pool != 0 )
            {
                NS( MemPool_free )( ptr_mem_pool );
                free( ptr_mem_pool );
                ptr_mem_pool = 0;
            }
        }

        if( NS( Particles_uses_single_particle )( particles ) )
        {
            typedef NS( SingleParticle ) single_t;

            single_t* ptr_single_particle = (single_t*)NS(
                Particles_get_const_base_single_particle )( particles );

            if( ptr_single_particle != 0 )
            {
                free( ptr_single_particle );
                ptr_single_particle = 0;
            }
        }
    }

    NS( Particles_preset )( particles );

    return;
}

/* -------------------------------------------------------------------------- */

bool NS( Particles_has_defined_alignment )( const struct NS( Particles ) *
                                            const SIXTRL_RESTRICT p )
{
    return ( NS( Particles_alignment )( p ) != UINT64_C( 0 ) );
}

bool NS( Particles_is_aligned )( const struct NS( Particles ) *
                                     const SIXTRL_RESTRICT p,
                                 size_t alignment )
{
    bool is_aligned = false;

    if( ( alignment != UINT64_C( 0 ) ) &&
        ( alignment <= NS( PARTICLES_MAX_ALIGNMENT ) ) )
    {
        uint64_t const align_flags = NS( Particles_alignment )( p );

        if( align_flags != UINT64_C( 0 ) )
        {
            /* Has defined alignment == true */

            uint64_t const asked_alignment = (uint64_t)alignment;

            is_aligned =
                ( ( asked_alignment == align_flags ) ||
                  ( ( asked_alignment < align_flags ) &&
                    ( ( align_flags % asked_alignment ) == UINT64_C( 0 ) ) ) );

            assert( ( !is_aligned ) ||
                    ( NS( Particles_check_alignment )( p, alignment ) ) );
        } else if( ( p != 0 ) && ( NS( Particles_get_x )( p ) != 0 ) )
        {
            /* No defined alignment but at least one member is not 0 ->
             * verify that the alignment is true  by checking each member */

            is_aligned = NS( Particles_check_alignment )( p, alignment );
        }
    }

    return is_aligned;
}

bool NS( Particles_check_alignment )( const struct NS( Particles ) *
                                          const SIXTRL_RESTRICT p,
                                      size_t n )
{
    bool is_aligned = false;

    static size_t const Z0 = (size_t)0u;

    if( ( p != 0 ) && ( n != Z0 ) && ( NS( Particles_get_q0 )( p ) != 0 ) &&
        ( NS( Particles_get_mass0 )( p ) != 0 ) &&
        ( NS( Particles_get_beta0 )( p ) != 0 ) &&
        ( NS( Particles_get_gamma0 )( p ) != 0 ) &&
        ( NS( Particles_get_p0c )( p ) != 0 ) &&
        ( NS( Particles_get_particle_id )( p ) != 0 ) &&
        ( NS( Particles_get_lost_at_element_id )( p ) != 0 ) &&
        ( NS( Particles_get_lost_at_turn )( p ) != 0 ) &&
        ( NS( Particles_get_state )( p ) != 0 ) &&
        ( NS( Particles_get_s )( p ) != 0 ) &&
        ( NS( Particles_get_x )( p ) != 0 ) &&
        ( NS( Particles_get_y )( p ) != 0 ) &&
        ( NS( Particles_get_px )( p ) != 0 ) &&
        ( NS( Particles_get_py )( p ) != 0 ) &&
        ( NS( Particles_get_sigma )( p ) != 0 ) &&
        ( NS( Particles_get_psigma )( p ) != 0 ) &&
        ( NS( Particles_get_delta )( p ) != 0 ) &&
        ( NS( Particles_get_rpp )( p ) != 0 ) &&
        ( NS( Particles_get_rvv )( p ) != 0 ) &&
        ( NS( Particles_get_chi )( p ) != 0 ) )
    {
        is_aligned =
            ( ( ( ( (uintptr_t)NS( Particles_get_q0 )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_mass0 )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_beta0 )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_gamma0 )( p ) ) % n ) ==
                Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_p0c )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_particle_id )( p ) ) % n ) ==
                Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_lost_at_element_id )( p ) ) %
                  n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_lost_at_turn )( p ) ) % n ) ==
                Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_state )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_s )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_x )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_y )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_px )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_py )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_sigma )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_psigma )( p ) ) % n ) ==
                Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_delta )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_rpp )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_rvv )( p ) ) % n ) == Z0 ) &&
              ( ( ( (uintptr_t)NS( Particles_get_chi )( p ) ) % n ) == Z0 ) );
    }

    return is_aligned;
}

uint64_t NS( Particles_alignment )( const struct NS( Particles ) *
                                    const SIXTRL_RESTRICT p )
{
    uint64_t alignment = UINT64_C( 0 );

    if( p != 0 )
    {
        uint64_t const flags = NS( Particles_get_flags )( p );
        alignment = ( ( flags & NS( PARTICLES_FLAGS_ALIGN_MASK ) ) >>
                      NS( PARTICLES_FLAGS_ALIGN_MASK_OFFSET_BITS ) );
    }

    return alignment;
}

/* ------------------------------------------------------------------------ */

bool NS( Particles_is_consistent )( const NS( Particles ) *
                                    const SIXTRL_RESTRICT p )
{
    bool is_consistent = false;

    static size_t const ZERO = (size_t)0u;
    size_t const num_particles = NS( Particles_get_size )( p );

    if( ( p != 0 ) && ( num_particles > ZERO ) )
    {
        is_consistent  = ( NS( Particles_get_q0 )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_mass0 )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_beta0 )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_gamma0 )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_p0c )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_particle_id )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_lost_at_element_id )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_lost_at_turn )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_state )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_s )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_x )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_y )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_px )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_py )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_sigma )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_psigma )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_delta )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_rpp )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_rvv )( p ) != 0 );
        is_consistent &= ( NS( Particles_get_chi )( p ) != 0 );

        if( ( is_consistent ) && ( NS( Particles_manages_own_memory )( p ) ) )
        {
            is_consistent =
                ( ( NS( Particles_get_const_ptr_mem_context )( p ) != 0 ) &&
                  ( ( NS( Particles_uses_mempool )( p ) ) ||
                    ( NS( Particles_uses_single_particle )( p ) ) ) );
        }

        if( ( is_consistent ) &&
            ( NS( Particles_has_defined_alignment )( p ) ) )
        {
            uint64_t const def_alignment = NS( Particles_alignment )( p );
            is_consistent = NS( Particles_check_alignment )( p, def_alignment );
        }

        if( ( is_consistent ) && ( NS( Particles_is_packed( p ) ) ) )
        {

            ptrdiff_t const min_double_len = sizeof( double ) * num_particles;
            ptrdiff_t const min_int64_len = sizeof( int64_t ) * num_particles;

            /* ------------------------------------------------------------- */
            /* distance q0 -> mass0 */
            
            unsigned char const* prev_elem =
                (unsigned char*)NS( Particles_get_q0 )( p );

            unsigned char const* ptr_elem =
                (unsigned char*)NS( Particles_get_mass0 )( p );

            is_consistent = ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance mass0 -> beta0 */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_beta0 )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance beta0 -> gamma0 */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_gamma0 )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance gamma0 -> p0c */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_p0c )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance p0c -> partid */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_particle_id )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_int64_len );

            /* ------------------------------------------------------------- */
            /* distance partid -> elemid */

            prev_elem = ptr_elem;
            ptr_elem =
                (unsigned char*)NS( Particles_get_lost_at_element_id )( p );

            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_int64_len );

            /* ------------------------------------------------------------- */
            /* distance elemid -> turn */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_lost_at_turn )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_int64_len );

            /* ------------------------------------------------------------- */
            /* distance turn -> state */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_state )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_int64_len );

            /* ------------------------------------------------------------- */
            /* distance state -> s */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_s )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance s -> x */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_x )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance x -> y */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_y )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance y -> px */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_px )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance px -> py */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_py )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance py -> sigma */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_sigma )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance sigma -> psigma */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_psigma )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance psigma -> delta */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_delta )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance delta -> rpp */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_rpp )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance rpp -> rvv */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_rvv )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );

            /* ------------------------------------------------------------- */
            /* distance rvv -> chi */

            prev_elem = ptr_elem;
            ptr_elem = (unsigned char*)NS( Particles_get_chi )( p );
            is_consistent &= ( ( ptr_elem - prev_elem ) >= min_double_len );
        }
    }

    return is_consistent;
}

/* ------------------------------------------------------------------------ */

bool NS( Particles_deep_copy_one )( struct NS( Particles ) *
                                        SIXTRL_RESTRICT dest,
                                    uint64_t dest_id,
                                    struct NS( Particles )
                                        const* SIXTRL_RESTRICT source,
                                    uint64_t source_id )
{
    bool success = false;

    if( ( dest != 0 ) && ( NS( Particles_get_size )( dest ) > dest_id ) &&
        ( source != 0 ) && ( NS( Particles_get_size )( source ) > source_id ) )
    {
        NS( Particles_set_q0_value )
        ( dest, dest_id, NS( Particles_get_q0_value )( source, source_id ) );

        NS( Particles_set_mass0_value )
        ( dest, dest_id, NS( Particles_get_mass0_value )( source, source_id ) );

        NS( Particles_set_beta0_value )
        ( dest, dest_id, NS( Particles_get_beta0_value )( source, source_id ) );

        NS( Particles_set_gamma0_value )
        ( dest,
          dest_id,
          NS( Particles_get_gamma0_value )( source, source_id ) );

        NS( Particles_set_p0c_value )
        ( dest, dest_id, NS( Particles_get_p0c_value )( source, source_id ) );

        NS( Particles_set_particle_id_value )
        ( dest,
          dest_id,
          NS( Particles_get_particle_id_value )( source, source_id ) );

        NS( Particles_set_lost_at_element_id_value )
        ( dest,
          dest_id,
          NS( Particles_get_lost_at_element_id_value )( source, source_id ) );

        NS( Particles_set_lost_at_turn_value )
        ( dest,
          dest_id,
          NS( Particles_get_lost_at_turn_value )( source, source_id ) );

        NS( Particles_set_state_value )
        ( dest, dest_id, NS( Particles_get_state_value )( source, source_id ) );

        NS( Particles_set_s_value )
        ( dest, dest_id, NS( Particles_get_s_value )( source, source_id ) );

        NS( Particles_set_x_value )
        ( dest, dest_id, NS( Particles_get_x_value )( source, source_id ) );

        NS( Particles_set_y_value )
        ( dest, dest_id, NS( Particles_get_y_value )( source, source_id ) );

        NS( Particles_set_px_value )
        ( dest, dest_id, NS( Particles_get_px_value )( source, source_id ) );

        NS( Particles_set_py_value )
        ( dest, dest_id, NS( Particles_get_py_value )( source, source_id ) );

        NS( Particles_set_sigma_value )
        ( dest, dest_id, NS( Particles_get_sigma_value )( source, source_id ) );

        NS( Particles_set_psigma_value )
        ( dest,
          dest_id,
          NS( Particles_get_psigma_value )( source, source_id ) );

        NS( Particles_set_delta_value )
        ( dest, dest_id, NS( Particles_get_delta_value )( source, source_id ) );

        NS( Particles_set_rpp_value )
        ( dest, dest_id, NS( Particles_get_rpp_value )( source, source_id ) );

        NS( Particles_set_rvv_value )
        ( dest, dest_id, NS( Particles_get_rvv_value )( source, source_id ) );

        NS( Particles_set_chi_value )
        ( dest, dest_id, NS( Particles_get_chi_value )( source, source_id ) );

        success = true;
    }

    return success;
}

/* ------------------------------------------------------------------------ */

bool NS( Particles_deep_copy_all )( struct NS( Particles ) *
                                        SIXTRL_RESTRICT dest,
                                    struct NS( Particles )
                                        const* SIXTRL_RESTRICT source )
{
    bool success = false;

    if( ( dest != 0 ) && ( source != 0 ) &&
        ( NS( Particles_get_size )( dest ) ==
          NS( Particles_get_size )( source ) ) )
    {
        assert( NS( Particles_is_consistent )( dest ) );
        assert( NS( Particles_is_consistent )( source ) );

        NS( Particles_set_q0 )( dest, NS( Particles_get_q0 )( source ) );
        NS( Particles_set_mass0 )( dest, NS( Particles_get_mass0 )( source ) );
        NS( Particles_set_beta0 )( dest, NS( Particles_get_beta0 )( source ) );
        NS( Particles_set_gamma0 )
        ( dest, NS( Particles_get_gamma0 )( source ) );
        NS( Particles_set_p0c )( dest, NS( Particles_get_p0c )( source ) );

        NS( Particles_set_particle_id )
        ( dest, NS( Particles_get_particle_id )( source ) );

        NS( Particles_set_lost_at_element_id )
        ( dest, NS( Particles_get_lost_at_element_id )( source ) );

        NS( Particles_set_lost_at_turn )
        ( dest, NS( Particles_get_lost_at_turn )( source ) );

        NS( Particles_set_state )( dest, NS( Particles_get_state )( source ) );

        NS( Particles_set_s )( dest, NS( Particles_get_s )( source ) );
        NS( Particles_set_x )( dest, NS( Particles_get_x )( source ) );
        NS( Particles_set_y )( dest, NS( Particles_get_y )( source ) );
        NS( Particles_set_px )( dest, NS( Particles_get_px )( source ) );
        NS( Particles_set_py )( dest, NS( Particles_get_py )( source ) );
        NS( Particles_set_sigma )( dest, NS( Particles_get_sigma )( source ) );

        NS( Particles_set_psigma )
        ( dest, NS( Particles_get_psigma )( source ) );
        NS( Particles_set_delta )( dest, NS( Particles_get_delta )( source ) );
        NS( Particles_set_rpp )( dest, NS( Particles_get_rpp )( source ) );
        NS( Particles_set_rvv )( dest, NS( Particles_get_rvv )( source ) );
        NS( Particles_set_chi )( dest, NS( Particles_get_chi )( source ) );

        success = true;
    }

    return success;
}

/* end: sixtracklib/common/details/particles.c */
