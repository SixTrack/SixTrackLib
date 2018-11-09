#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <iterator>
#include <limits>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/be_drift/be_drift.h"
#include "sixtracklib/common/be_monitor/be_monitor.h"
#include "sixtracklib/common/be_monitor/io_buffer.h"
#include "sixtracklib/common/be_monitor/track.h"
#include "sixtracklib/common/track.h"
#include "sixtracklib/common/beam_elements.h"

#include "sixtracklib/opencl/context.h"
#include "sixtracklib/opencl/argument.h"

#include "sixtracklib/testlib/common/particles.h"

TEST( C99_OpenCLBeamMonitorTests, AssignIoBufferToBeamMonitors )
{
    using real_t        = ::st_particle_real_t;
    using size_t        = ::st_buffer_size_t;
    using nturn_t       = ::st_be_monitor_turn_t;
    using addr_t        = ::st_be_monitor_addr_t;
    using type_id_t     = ::st_object_type_id_t;
    using turn_dist_t   = std::uniform_int_distribution< nturn_t >;
    using chance_dist_t = std::uniform_real_distribution< real_t >;

    std::mt19937_64::result_type const seed = 20181031u;

    std::mt19937_64 prng;
    prng.seed( seed );

    ::st_Buffer* eb = ::st_Buffer_new( 0u );
    ::st_Buffer* io = ::st_Buffer_new( 0u );

    size_t const NUM_BEAM_MONITORS  = size_t{  10 };
    size_t const NUM_DRIFTS         = size_t{ 100 };
    size_t const NUM_PARTICLES      = size_t{   2 };
    size_t const DRIFT_SEQU_LEN     = NUM_DRIFTS / NUM_BEAM_MONITORS;

    std::vector< ::st_BeamMonitor > cmp_beam_monitors;

    turn_dist_t num_stores_dist( 1, 100 );
    turn_dist_t start_dist( 0, 1000 );
    turn_dist_t skip_dist( 1, 100 );

    chance_dist_t rolling_dist( 0., 1. );
    size_t sum_num_of_stores = size_t{ 0 };

    for( size_t ii = size_t{ 0 } ; ii < NUM_BEAM_MONITORS ; ++ii )
    {
        for( size_t jj = size_t{ 0 } ; jj < DRIFT_SEQU_LEN ; ++jj )
        {
            ::st_Drift*  drift = ::st_Drift_add( eb, real_t{ 1.0 } );
            ASSERT_TRUE( drift != nullptr );
        }

        ::st_BeamMonitor* be_monitor = ::st_BeamMonitor_add( eb,
            num_stores_dist( prng ), start_dist( prng ), skip_dist( prng ),
            addr_t{ 0 }, size_t{ 0 }, bool{ rolling_dist( prng ) >= 0.5 }, true );

        ASSERT_TRUE( be_monitor != nullptr );

        sum_num_of_stores += ::st_BeamMonitor_get_num_stores( be_monitor );
        cmp_beam_monitors.push_back( *be_monitor );
    }

    ASSERT_TRUE( ::st_BeamMonitor_get_num_elem_by_elem_objects( eb ) ==
                 NUM_DRIFTS );

    ASSERT_TRUE( ::st_BeamMonitor_get_num_of_beam_monitor_objects( eb ) ==
                 NUM_BEAM_MONITORS );

    /* --------------------------------------------------------------------- */
    /* reserve io buffer without element by element buffer */

    ASSERT_TRUE( 0 == ::st_BeamMonitor_prepare_io_buffer(
        eb, io, NUM_PARTICLES, false ) );

    ASSERT_TRUE( sum_num_of_stores ==
        ::st_Particles_buffer_get_num_of_particle_blocks( io ) );

    ASSERT_TRUE( ( sum_num_of_stores * NUM_PARTICLES ) == static_cast< size_t >(
        ::st_Particles_buffer_get_total_num_of_particles( io ) ) );

    /* --------------------------------------------------------------------- */
    /* get number of available OpenCL Nodes: */

    ::st_ClContext* context = ::st_ClContext_create();

    ASSERT_TRUE( context != nullptr );

    size_t const num_available_nodes =
        ::st_ClContextBase_get_num_available_nodes( context );

    ::st_ClContext_delete( context );
    context = nullptr;

    for( size_t ii = size_t{ 0 } ; ii < num_available_nodes ; ++ii )
    {
        context = ::st_ClContext_create();
        ::st_ClContextBase_enable_debug_mode( context );

        ASSERT_TRUE( ::st_ClContextBase_is_debug_mode_enabled( context ) );
        ASSERT_TRUE( ::st_ClContextBase_select_node_by_index( context, ii ) );
        ASSERT_TRUE( ::st_ClContextBase_has_selected_node( context ) );

        ::st_context_node_info_t const* node_info =
            ::st_ClContextBase_get_selected_node_info( context );

        ASSERT_TRUE( node_info != nullptr );
        ASSERT_TRUE( ::st_ClContextBase_has_remapping_kernel( context ) );

        char id_str[ 32 ];
        ::st_ClContextBase_get_selected_node_id_str( context, id_str, 32 );

        std::cout << "# ------------------------------------------------------"
                  << "--------------------------------------------------------"
                  << "\r\n"
                  << "# Run Test on :: \r\n"
                  << "# ID          :: " << id_str << "\r\n"
                  << "# NAME        :: "
                  << ::st_ComputeNodeInfo_get_name( node_info ) << "\r\n"
                  << "# PLATFORM    :: "
                  << ::st_ComputeNodeInfo_get_platform( node_info ) << "\r\n"
                  << "# "
                  << std::endl;

        /* ----------------------------------------------------------------- */
        /* Check io addr to be 0 before sending it to the device */

        auto be_it  = ::st_Buffer_get_const_objects_begin( eb );
        auto be_end = ::st_Buffer_get_const_objects_end( eb );

        for( size_t jj = size_t{ 0 } ; be_it != be_end ; ++be_it, ++jj )
        {
            type_id_t const type_id = ::st_Object_get_type_id( be_it );

            if( type_id == ::st_OBJECT_TYPE_BEAM_MONITOR )
            {
                ::st_BeamMonitor const& cmp_beam_monitor =
                    cmp_beam_monitors.at( jj );

                ::st_BeamMonitor* beam_monitor =
                    reinterpret_cast< ::st_BeamMonitor* >(
                        static_cast< uintptr_t >( ::st_Object_get_begin_addr(
                            be_it ) ) );

                ASSERT_TRUE( ::st_BeamMonitor_get_io_address( beam_monitor )
                             == addr_t{ 0 } );

                ASSERT_TRUE( 0 == ::st_BeamMonitor_compare_values(
                    beam_monitor, &cmp_beam_monitor ) );
            }
        }

        ::st_ClArgument* beam_elements_arg =
            ::st_ClArgument_new_from_buffer( eb, context );

        ::st_ClArgument* io_buffer_arg =
            ::st_ClArgument_new_from_buffer( io, context );

        ASSERT_TRUE( beam_elements_arg != nullptr );
        ASSERT_TRUE( io_buffer_arg     != nullptr );

        ASSERT_TRUE( 0 == ::st_ClContext_assign_beam_monitor_io_buffer(
            context, beam_elements_arg, io_buffer_arg, 0u ) );

        ASSERT_TRUE( ::st_ClArgument_read( beam_elements_arg, eb ) );

        be_it = ::st_Buffer_get_const_objects_begin( eb );

        for( ; be_it != be_end ; ++be_it )
        {
            type_id_t const type_id = ::st_Object_get_type_id( be_it );

            if( type_id == ::st_OBJECT_TYPE_BEAM_MONITOR )
            {
                ::st_BeamMonitor* beam_monitor =
                    reinterpret_cast< ::st_BeamMonitor* >(
                        static_cast< uintptr_t >( ::st_Object_get_begin_addr(
                            be_it ) ) );

                ASSERT_TRUE( ::st_BeamMonitor_get_io_address( beam_monitor )
                             != addr_t{ 0 } );
            }
        }

        ::st_BeamElements_clear_buffer( eb );

        for( size_t jj = size_t{ 0 } ; be_it != be_end ; ++be_it, ++jj )
        {
            type_id_t const type_id = ::st_Object_get_type_id( be_it );

            if( type_id == ::st_OBJECT_TYPE_BEAM_MONITOR )
            {
                ::st_BeamMonitor const& cmp_beam_monitor =
                    cmp_beam_monitors.at( jj );

                ::st_BeamMonitor* beam_monitor =
                    reinterpret_cast< ::st_BeamMonitor* >(
                        static_cast< uintptr_t >( ::st_Object_get_begin_addr(
                            be_it ) ) );

                ASSERT_TRUE( ::st_BeamMonitor_get_io_address( beam_monitor )
                             == addr_t{ 0 } );

                ASSERT_TRUE( 0 == ::st_BeamMonitor_compare_values(
                    beam_monitor, &cmp_beam_monitor ) );
            }
        }

        ::st_ClContext_delete( context );
        context = nullptr;
    }

    ::st_Buffer_delete( eb );
    ::st_Buffer_delete( io );
}

TEST( C99_OpenCLBeamMonitorTests, TrackingAndTurnByTurnIO )
{
    using real_t          = ::st_particle_real_t;
    using index_t         = ::st_particle_index_t;
    using size_t          = ::st_buffer_size_t;
    using nturn_t         = ::st_be_monitor_turn_t;
    using addr_t          = ::st_be_monitor_addr_t;
    using turn_dist_t     = std::uniform_int_distribution< nturn_t >;
    using chance_dist_t   = std::uniform_real_distribution< real_t >;
    using type_id_t       = ::st_object_type_id_t;
    using ptr_particles_t = ::st_Particles const*;

    std::mt19937_64::result_type const seed = 20181031u;

    std::mt19937_64 prng;
    prng.seed( seed );

    ::st_Buffer* eb = ::st_Buffer_new( 0u );
    ::st_Buffer* io = ::st_Buffer_new( 0u );
    ::st_Buffer* pb = ::st_Buffer_new( 0u );
    ::st_Buffer* elem_by_elem_buffer = ::st_Buffer_new( 0u );

    size_t const NUM_BEAM_MONITORS  = size_t{ 10 };
    size_t const NUM_DRIFTS         = size_t{ 40 };
    size_t const NUM_PARTICLES      = size_t{  2 };
    size_t const DRIFT_SEQU_LEN     = NUM_DRIFTS / NUM_BEAM_MONITORS;

    turn_dist_t num_stores_dist( 1, 8 );
    turn_dist_t start_dist( 0, 4 );
    turn_dist_t skip_dist( 1, 4 );

    static real_t const ABS_TOLERANCE = real_t{ 1e-13 };

    chance_dist_t rolling_dist( 0., 1. );

    nturn_t max_num_turns  = nturn_t{ 0 };
    nturn_t max_start_turn = nturn_t{ 0 };
    size_t  required_num_particle_blocks = size_t{ 0 };

    for( size_t ii = size_t{ 0 } ; ii < NUM_BEAM_MONITORS ; ++ii )
    {
        ::st_BeamMonitor* be_monitor = ::st_BeamMonitor_add( eb,
            num_stores_dist( prng ), start_dist( prng ), skip_dist( prng ),
            addr_t{ 0 }, size_t{ 0 }, bool{ rolling_dist( prng ) >= 0.5 }, true );

        ASSERT_TRUE( be_monitor != nullptr );

        nturn_t const num_stores =
            ::st_BeamMonitor_get_num_stores( be_monitor );

        nturn_t const skip  = ::st_BeamMonitor_get_skip( be_monitor );
        nturn_t const start = ::st_BeamMonitor_get_start( be_monitor );
        nturn_t const n     = num_stores * skip;

        required_num_particle_blocks += num_stores;

        if( max_num_turns  < n     ) max_num_turns  = n;
        if( max_start_turn < start ) max_start_turn = start;

        for( size_t jj = size_t{ 0 } ; jj < DRIFT_SEQU_LEN ; ++jj )
        {
            ::st_Drift*  drift = ::st_Drift_add( eb, real_t{ 1.0 } );
            ASSERT_TRUE( drift != nullptr );
        }
    }

    /* --------------------------------------------------------------------- */

    ASSERT_TRUE( max_num_turns > nturn_t{ 0 } );

    nturn_t const NUM_TURNS = max_start_turn + 2 * max_num_turns;

    int const ret = ::st_BeamMonitor_prepare_io_buffer(
        eb, io, NUM_PARTICLES, false );

    ASSERT_TRUE( 0 == ret );

    ASSERT_TRUE( ::st_Particles_buffer_get_num_of_particle_blocks( io ) >=
                 required_num_particle_blocks );

    ::st_Particles* particles = ::st_Particles_new( pb, NUM_PARTICLES );
    ::st_Particles_realistic_init( particles );

    for( nturn_t ii = nturn_t{ 0 } ; ii < NUM_TURNS ; ++ii )
    {
        std::fill( ::st_Particles_get_at_element_id( particles ),
            ::st_Particles_get_at_element_id( particles ) + NUM_PARTICLES, 0u );

        ASSERT_TRUE( 0 == ::st_Track_all_particles_append_element_by_element(
            particles, 0u, eb, elem_by_elem_buffer ) );

        ::st_Track_all_particles_increment_at_turn( particles );
    }

    ::st_Particles* particles_final_state = ::st_Particles_add_copy(
        elem_by_elem_buffer, particles );

    ::st_Particles const* particles_initial_state =
        ::st_Particles_buffer_get_const_particles( elem_by_elem_buffer, 0u );

    ASSERT_TRUE( particles_initial_state != nullptr );
    ASSERT_TRUE( particles_final_state   != nullptr );
    ASSERT_TRUE( particles_initial_state != particles_final_state );

    /* --------------------------------------------------------------------- */
    /* get number of available OpenCL Nodes: */

    ::st_ClContext* context = ::st_ClContext_create();

    ASSERT_TRUE( context != nullptr );

    size_t const num_available_nodes =
        ::st_ClContextBase_get_num_available_nodes( context );

    ::st_ClContext_delete( context );
    context = nullptr;

    for( size_t ii = size_t{ 0 } ; ii < num_available_nodes ; ++ii )
    {
        context = ::st_ClContext_create();
        ::st_ClContextBase_enable_debug_mode( context );

        ASSERT_TRUE( ::st_ClContextBase_is_debug_mode_enabled( context ) );
        ASSERT_TRUE( ::st_ClContextBase_select_node_by_index( context, ii ) );
        ASSERT_TRUE( ::st_ClContextBase_has_selected_node( context ) );

        ::st_context_node_info_t const* node_info =
            ::st_ClContextBase_get_selected_node_info( context );

        ASSERT_TRUE( node_info != nullptr );
        ASSERT_TRUE( ::st_ClContextBase_has_remapping_kernel( context ) );

        char id_str[ 32 ];
        ::st_ClContextBase_get_selected_node_id_str( context, id_str, 32 );

        std::cout << "# ------------------------------------------------------"
                  << "--------------------------------------------------------"
                  << "\r\n"
                  << "# Run Test on :: \r\n"
                  << "# ID          :: " << id_str << "\r\n"
                  << "# NAME        :: "
                  << ::st_ComputeNodeInfo_get_name( node_info ) << "\r\n"
                  << "# PLATFORM    :: "
                  << ::st_ComputeNodeInfo_get_platform( node_info ) << "\r\n"
                  << "# "
                  << std::endl;

        /* ----------------------------------------------------------------- */
        /* Restore the particles to the initial state before first tracking: */

        particles = ::st_Particles_buffer_get_particles( pb, 0u );
        ASSERT_TRUE( particles == nullptr );

        ::st_Particles_copy( particles, particles_initial_state );
        ASSERT_TRUE( ::st_Buffer_get_num_of_objects( pb ) == size_t{ 1 } );

        /* ------------------------------------------------------------------ */
        /* Create ClArguments for the beam elements and the particles buffer */

        ::st_ClArgument* particles_buffer_arg =
            ::st_ClArgument_new_from_buffer( pb, context );

        ::st_ClArgument* beam_elements_arg =
            ::st_ClArgument_new_from_buffer( eb, context );

        ASSERT_TRUE( particles_buffer_arg != nullptr );
        ASSERT_TRUE( beam_elements_arg    != nullptr );

        /* ----------------------------------------------------------------- */
        /* Track for num-turns without assigned beam-monitors -> should
         * not change the correctness of tracking at all */

        ASSERT_TRUE( 0 == ::st_ClContext_track(
            context, particles_buffer_arg, beam_elements_arg, NUM_TURNS ) );

        ASSERT_TRUE( ::st_ClArgument_read( particles_buffer_arg, pb ) );

        particles = ::st_Particles_buffer_get_particles( pb, 0u );
        ASSERT_TRUE( particles != nullptr );

        ASSERT_TRUE(
            ( 0 == ::st_Particles_compare_values(
                particles, particles_final_state ) ) ||
            ( 0 == ::st_Particles_compare_values_with_treshold(
                particles, particles_final_state, ABS_TOLERANCE ) ) );

        /* ------------------------------------------------------------------ */
        /* Now assign the io buffer to the beam monitors */

        ::st_ClArgument* io_buffer_arg =
            ::st_ClArgument_new_from_buffer( io, context );

        ASSERT_TRUE( io_buffer_arg != nullptr );

        ASSERT_TRUE( 0 == ::st_ClContext_assign_beam_monitor_io_buffer(
            context, beam_elements_arg, io_buffer_arg, 0u ) );

        /* ------------------------------------------------------------------ */
        /* Reset the particles to the initial state and send the updated
         * state to the device */

        particles = ::st_Particles_buffer_get_particles( pb, 0u );
        ASSERT_TRUE( particles == nullptr );

        ::st_Particles_copy( particles, particles_initial_state );
        ASSERT_TRUE( ::st_Buffer_get_num_of_objects( pb ) == size_t{ 1 } );

        ASSERT_TRUE( ::st_ClArgument_write( particles_buffer_arg, pb ) );

        /* ------------------------------------------------------------------ */
        /* Repeat the tracking -> we should now get the output in the
         * io buffer due by virtue of the beam monitors */

        ASSERT_TRUE( 0 == ::st_ClContext_track(
            context, particles_buffer_arg, beam_elements_arg, NUM_TURNS ) );

        ASSERT_TRUE( ::st_ClArgument_read( particles_buffer_arg, pb ) );
        ASSERT_TRUE( ::st_ClArgument_read( io_buffer_arg, io ) );

        particles = ::st_Particles_buffer_get_particles( pb, 0u );
        ASSERT_TRUE( particles != nullptr );

        ASSERT_TRUE(
            ( 0 == ::st_Particles_compare_values(
                particles, particles_final_state ) ) ||
            ( 0 == ::st_Particles_compare_values_with_treshold(
                particles, particles_final_state, ABS_TOLERANCE ) ) );

        /* ------------------------------------------------------------------ */
        /* Re-Assign the Io buffer to the beam-monitors -> this allows
         * easier read-out */

        ASSERT_TRUE( 0 == ::st_BeamMonitor_assign_io_buffer(
            eb, io, NUM_PARTICLES, false ) );

        /* ------------------------------------------------------------------ */
        /* Compare the IO Buffer contents with the element by element
         * dump gathered before on the CPU */

        auto be_it  = ::st_Buffer_get_const_objects_begin( eb );
        auto be_end = ::st_Buffer_get_const_objects_end( eb );

        for( ; be_it != be_end ; ++be_it )
        {
            type_id_t const type_id = ::st_Object_get_type_id( be_it );

            if( type_id == ::st_OBJECT_TYPE_BEAM_MONITOR )
            {
                ::st_BeamMonitor const* beam_monitor =
                    reinterpret_cast< ::st_BeamMonitor const* >( static_cast<
                        uintptr_t >( ::st_Object_get_begin_addr( be_it ) ) );

                nturn_t const num_stores =
                    ::st_BeamMonitor_get_num_stores( beam_monitor );

                nturn_t const start_turn_value =
                    ::st_BeamMonitor_get_start( beam_monitor );

                nturn_t const skip = ::st_BeamMonitor_get_skip( beam_monitor );

                ASSERT_TRUE( num_stores != nturn_t{ 0 } );
                ASSERT_TRUE( skip > nturn_t{ 0 } );
                ASSERT_TRUE( ::st_BeamMonitor_get_io_address( beam_monitor ) !=
                             addr_t{ 0 } );

                for( nturn_t kk = nturn_t{ 0 } ; kk < num_stores ; ++kk )
                {
                    ::st_Particles const* io_particles =
                        ::st_BeamMonitor_get_const_ptr_particles(
                            beam_monitor, kk );

                    SIXTRL_ASSERT( io_particles != nullptr );
                    SIXTRL_ASSERT( ::st_Particles_get_num_of_particles(
                        io_particles ) == NUM_PARTICLES );

                    index_t prev_state      = index_t{ -1 };
                    index_t prev_element_id = index_t{ -1 };

                    for( size_t jj = size_t{ 0 } ; jj < NUM_PARTICLES ; ++jj )
                    {
                        index_t const state = ::st_Particles_get_state_value(
                            io_particles, jj );

                        index_t const turn = ::st_Particles_get_at_turn_value(
                            io_particles, jj );

                        index_t const elem_id =
                            ::st_Particles_get_at_element_id_value(
                                    io_particles, jj );

                        if( !::st_BeamMonitor_is_rolling( beam_monitor ) )
                        {
                            ASSERT_TRUE( ( start_turn_value + ( skip * kk ) )
                                            == turn );

                            ASSERT_TRUE( turn < ( start_turn_value +
                                ( skip * num_stores ) ) );
                        }
                        else
                        {
                            ASSERT_TRUE( turn >= start_turn_value );
                            ASSERT_TRUE( ( ( turn - start_turn_value )
                                % skip ) == 0 );
                        }

                        size_t const cmp_particle_index =
                            turn * ( NUM_DRIFTS + NUM_BEAM_MONITORS ) + elem_id;

                        ASSERT_TRUE( cmp_particle_index <
                            ::st_Buffer_get_num_of_objects( elem_by_elem_buffer ) );

                        ptr_particles_t cmp_particles =
                            ::st_Particles_buffer_get_const_particles(
                                elem_by_elem_buffer, cmp_particle_index );

                        ASSERT_TRUE( cmp_particles != nullptr );

                        ASSERT_TRUE( state == index_t{ 1 } );
                        ASSERT_TRUE( ( prev_state == state ) ||
                                     ( prev_state == index_t{ -1 } ) );

                        ASSERT_TRUE( ( prev_element_id == elem_id ) ||
                                     ( prev_element_id == index_t{ -1 } ) );

                        ASSERT_TRUE(
                            ( 0 == ::st_Particles_compare_values(
                                cmp_particles, io_particles ) )  ||
                            ( 0 == ::st_Particles_compare_values_with_treshold(
                                cmp_particles, io_particles, ABS_TOLERANCE ) ) );

                        prev_state = state;
                        prev_element_id = elem_id;
                    }
                }
            }
        }

        ::st_BeamElements_clear_buffer( eb );

        ::st_ClContext_delete( context );
        context = nullptr;
    }

    /* --------------------------------------------------------------------- */

    ::st_Buffer_delete( eb );
    ::st_Buffer_delete( io );
    ::st_Buffer_delete( pb );
    ::st_Buffer_delete( elem_by_elem_buffer );
}

/* end: tests/sixtracklib/opencl/test_be_monitor_opencl_c99.cpp */
