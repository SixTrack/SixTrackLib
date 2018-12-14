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
#include "sixtracklib/common/output/elem_by_elem_config.h"
#include "sixtracklib/common/output/output_buffer.h"
#include "sixtracklib/common/track.h"

#include "sixtracklib/opencl/context.h"
#include "sixtracklib/opencl/argument.h"

#include "sixtracklib/testlib/common/particles.h"
#include "sixtracklib/testlib/testdata/testdata_files.h"

namespace sixtrack
{
    namespace tests
    {
        bool performElemByElemTrackTest(
            ::st_ClContext* SIXTRL_RESTRICT context,
            ::st_Buffer* SIXTRL_RESTRICT beam_elements_buffer,
            ::st_Buffer* SIXTRL_RESTRICT cmp_elem_by_elem_buffer,
            ::st_buffer_size_t const num_turns,
            double const abs_tolerance =
                std::numeric_limits< double >::epsilon() );
    }
}

TEST( C99_OpenCLTrackElemByElemTests,
      TrackElemByElemHostAndDeviceCompareLhcNoBB )
{
    using real_t       = ::st_particle_real_t;
    using part_index_t = ::st_particle_index_t;
    using size_t       = ::st_buffer_size_t;
    using num_elem_t   = ::st_particle_num_elements_t;

    part_index_t const NUM_TURNS   = part_index_t{ 3 };
    size_t const NUM_BEAM_ELEMENTS = size_t{ 5 };
    real_t const ABS_TOLERANCE     = std::numeric_limits< real_t >::epsilon();

    /* --------------------------------------------------------------------- */
    /* Creating a minimal machine description */

    ::st_Buffer* eb = ::st_Buffer_new( size_t{ 0 } );

    for( size_t ii = size_t{ 0 } ; ii < NUM_BEAM_ELEMENTS ; ++ii )
    {
        ::st_Drift* drift = ::st_Drift_add( eb, double{ 1.0 } );
        ASSERT_TRUE( drift != nullptr );
    }

    ::st_Buffer* in_particles_buffer = ::st_Buffer_new_from_file(
        ::st_PATH_TO_LHC_NO_BB_PARTICLES_DUMP );

    ::st_Buffer* elem_by_elem_buffer = ::st_Buffer_new( size_t{ 0 } );

    ::st_Particles* initial_state = ::st_Particles_buffer_get_particles(
        in_particles_buffer, size_t{ 0 } );

    ASSERT_TRUE( initial_state != nullptr );
    ASSERT_TRUE( ::st_Particles_get_num_of_particles(
        initial_state ) > num_elem_t{ 0 } );

    ::st_Particles* particles = ::st_Particles_add_copy(
        elem_by_elem_buffer, initial_state );

    /* --------------------------------------------------------------------- */
    /* Create elem by elem config structure and init from data */

    ::st_ElemByElemConfig elem_by_elem_config;
    ::st_ElemByElemConfig_preset( &elem_by_elem_config );

    ASSERT_TRUE( 0 == ::st_ElemByElemConfig_init( &elem_by_elem_config,
        NS(ELEM_BY_ELEM_ORDER_DEFAULT), eb, particles,
        part_index_t{ 0 }, NUM_TURNS - part_index_t{ 1 } ) );

    size_t elem_by_elem_index_offset = size_t{ 0 };

    ASSERT_TRUE( ::st_ElemByElemConfig_prepare_particles_out_buffer_detailed(
        &elem_by_elem_config, elem_by_elem_buffer,
            &elem_by_elem_index_offset ) == 0 );

    ASSERT_TRUE( elem_by_elem_index_offset == size_t{ 1 } );
    ASSERT_TRUE( ::st_Buffer_get_num_of_objects(
        elem_by_elem_buffer ) == size_t{ 2 } );

    ::st_Particles* elem_by_elem_particles = nullptr;

    elem_by_elem_particles = ::st_Particles_buffer_get_particles(
            elem_by_elem_buffer, elem_by_elem_index_offset );

    ASSERT_TRUE( elem_by_elem_particles != nullptr );

    ::st_Particles* final_state = ::st_Particles_add_copy(
        elem_by_elem_buffer, initial_state );

    /* --------------------------------------------------------------------- */

    ASSERT_TRUE( ::st_Buffer_get_num_of_objects( elem_by_elem_buffer ) ==
                 size_t{ 3 } );

    particles =
        ::st_Particles_buffer_get_particles( elem_by_elem_buffer, 0 );

    elem_by_elem_particles =
        ::st_Particles_buffer_get_particles( elem_by_elem_buffer, 1 );

    final_state =
        ::st_Particles_buffer_get_particles( elem_by_elem_buffer, 2 );

    /* --------------------------------------------------------------------- */
    /* Track element by element on the host: */

    ASSERT_TRUE( 0 == ::st_Track_all_particles_element_by_element_until_turn(
        particles, eb, NUM_TURNS, elem_by_elem_particles ) );

    ASSERT_TRUE( ::st_Particles_copy( final_state, particles ) );
    ASSERT_TRUE( ::st_Particles_copy( particles, initial_state ) );

    ::st_Buffer_delete( in_particles_buffer );
    in_particles_buffer = nullptr;
    initial_state = nullptr;

    /* ===================================================================== */
    /* Init OpenCL context: */

    ::st_ClContext* ctx = ::st_ClContext_create();

    ASSERT_TRUE( ctx != nullptr );

    size_t const num_available_nodes =
        ::st_ClContextBase_get_num_available_nodes( ctx );

    ::st_ClContext_delete( ctx );
    ctx = nullptr;

    std::vector< size_t > nodes;

    for( size_t node_index = size_t{ 0 } ;
            node_index < num_available_nodes ; ++node_index )
    {
        nodes.push_back( node_index );
    }

    if( !nodes.empty() )
    {
        for( size_t const node_index : nodes )
        {
            ctx = ::st_ClContext_create();

            ::st_ClContextBase_enable_debug_mode( ctx );
            ::st_ClContext_disable_optimized_tracking_by_default( ctx );

            ASSERT_TRUE(  ::st_ClContextBase_is_debug_mode_enabled( ctx ) );
            ASSERT_TRUE( !::st_ClContext_uses_optimized_tracking_by_default(
                ctx ) );
            ASSERT_TRUE(  ::st_ClContextBase_select_node_by_index(
                ctx, node_index ) );

            ASSERT_TRUE( ::st_ClContextBase_has_selected_node( ctx ) );

            ::st_context_node_info_t const* node_info =
                ::st_ClContextBase_get_selected_node_info( ctx );

            ASSERT_TRUE( node_info != nullptr );
            ASSERT_TRUE( ::st_ClContextBase_has_remapping_kernel( ctx ) );
            ASSERT_TRUE( ::st_ClContext_has_element_by_element_tracking_kernel(
                ctx ) );

            char id_str[ 32 ];
            ::st_ClContextBase_get_selected_node_id_str( ctx, id_str, 32 );

            std::cout << "# --------------------------------------------------"
                      << "----------------------------------------------------"
                      << "\r\n"
                      << "# Run Test on :: \r\n"
                      << "# ID          :: " << id_str << "\r\n"
                      << "# NAME        :: "
                      << ::st_ComputeNodeInfo_get_name( node_info )
                      << "\r\n" << "# PLATFORM    :: "
                      << ::st_ComputeNodeInfo_get_platform( node_info )
                      << "\r\n" << "# Debug mode  :: "
                      << std::boolalpha
                      << ::st_ClContextBase_is_debug_mode_enabled( ctx )
                      << "\r\n" << "# Optimized   :: "
                      << ::st_ClContext_uses_optimized_tracking_by_default(
                        ctx ) << "\r\n"
                      << std::noboolalpha
                      << "# "
                      << std::endl;

            /* ------------------------------------------------------------ */

            bool const success = sixtrack::tests::performElemByElemTrackTest(
                ctx, eb, elem_by_elem_buffer, NUM_TURNS, ABS_TOLERANCE );

            ::st_ClContext_delete( ctx );
            ctx = nullptr;

            ASSERT_TRUE( success );
        }

        for( size_t const node_index : nodes )
        {
            ctx = ::st_ClContext_create();

            ::st_ClContextBase_disable_debug_mode( ctx );
            ::st_ClContext_disable_optimized_tracking_by_default( ctx );

            ASSERT_TRUE( !::st_ClContextBase_is_debug_mode_enabled( ctx ) );
            ASSERT_TRUE( !::st_ClContext_uses_optimized_tracking_by_default(
                ctx ) );
            ASSERT_TRUE(  ::st_ClContextBase_select_node_by_index(
                ctx, node_index ) );

            ASSERT_TRUE( ::st_ClContextBase_has_selected_node( ctx ) );

            ::st_context_node_info_t const* node_info =
                ::st_ClContextBase_get_selected_node_info( ctx );

            ASSERT_TRUE( node_info != nullptr );
            ASSERT_TRUE( ::st_ClContextBase_has_remapping_kernel( ctx ) );
            ASSERT_TRUE( ::st_ClContext_has_element_by_element_tracking_kernel(
                ctx ) );

            char id_str[ 32 ];
            ::st_ClContextBase_get_selected_node_id_str( ctx, id_str, 32 );

            std::cout << "# --------------------------------------------------"
                      << "----------------------------------------------------"
                      << "\r\n"
                      << "# Run Test on :: \r\n"
                      << "# ID          :: " << id_str << "\r\n"
                      << "# NAME        :: "
                      << ::st_ComputeNodeInfo_get_name( node_info )
                      << "\r\n" << "# PLATFORM    :: "
                      << ::st_ComputeNodeInfo_get_platform( node_info )
                      << "\r\n" << "# Debug mode  :: "
                      << std::boolalpha
                      << ::st_ClContextBase_is_debug_mode_enabled( ctx )
                      << "\r\n" << "# Optimized   :: "
                      << ::st_ClContext_uses_optimized_tracking_by_default(
                        ctx ) << "\r\n"
                      << std::noboolalpha
                      << "# "
                      << std::endl;

            /* ------------------------------------------------------------- */

            bool const success = sixtrack::tests::performElemByElemTrackTest(
                ctx, eb, elem_by_elem_buffer, NUM_TURNS, ABS_TOLERANCE );

            ::st_ClContext_delete( ctx );
            ctx = nullptr;

            ASSERT_TRUE( success );
        }

        for( size_t const node_index : nodes )
        {
            ctx = ::st_ClContext_create();

            ::st_ClContextBase_enable_debug_mode( ctx );
            ::st_ClContext_enable_optimized_tracking_by_default( ctx );

            ASSERT_TRUE( ::st_ClContextBase_is_debug_mode_enabled( ctx ) );
            ASSERT_TRUE( ::st_ClContext_uses_optimized_tracking_by_default(
                ctx ) );
            ASSERT_TRUE(  ::st_ClContextBase_select_node_by_index(
                ctx, node_index ) );

            ASSERT_TRUE( ::st_ClContextBase_has_selected_node( ctx ) );

            ::st_context_node_info_t const* node_info =
                ::st_ClContextBase_get_selected_node_info( ctx );

            ASSERT_TRUE( node_info != nullptr );
            ASSERT_TRUE( ::st_ClContextBase_has_remapping_kernel( ctx ) );
            ASSERT_TRUE( ::st_ClContext_has_element_by_element_tracking_kernel(
                ctx ) );

            char id_str[ 32 ];
            ::st_ClContextBase_get_selected_node_id_str( ctx, id_str, 32 );

            std::cout << "# --------------------------------------------------"
                      << "----------------------------------------------------"
                      << "\r\n"
                      << "# Run Test on :: \r\n"
                      << "# ID          :: " << id_str << "\r\n"
                      << "# NAME        :: "
                      << ::st_ComputeNodeInfo_get_name( node_info )
                      << "\r\n" << "# PLATFORM    :: "
                      << ::st_ComputeNodeInfo_get_platform( node_info )
                      << "\r\n" << "# Debug mode  :: "
                      << std::boolalpha
                      << ::st_ClContextBase_is_debug_mode_enabled( ctx )
                      << "\r\n" << "# Optimized   :: "
                      << ::st_ClContext_uses_optimized_tracking_by_default(
                        ctx ) << "\r\n"
                      << std::noboolalpha
                      << "# "
                      << std::endl;

            /* ------------------------------------------------------------- */

            bool const success = sixtrack::tests::performElemByElemTrackTest(
                ctx, eb, elem_by_elem_buffer, NUM_TURNS, ABS_TOLERANCE );

            ::st_ClContext_delete( ctx );
            ctx = nullptr;

            ASSERT_TRUE( success );
        }

        for( size_t const node_index : nodes )
        {
            ctx = ::st_ClContext_create();

            ::st_ClContextBase_disable_debug_mode( ctx );
            ::st_ClContext_enable_optimized_tracking_by_default( ctx );

            ASSERT_TRUE( !::st_ClContextBase_is_debug_mode_enabled( ctx ) );
            ASSERT_TRUE(  ::st_ClContext_uses_optimized_tracking_by_default(
                ctx ) );
            ASSERT_TRUE(  ::st_ClContextBase_select_node_by_index(
                ctx, node_index ) );

            ASSERT_TRUE( ::st_ClContextBase_has_selected_node( ctx ) );

            ::st_context_node_info_t const* node_info =
                ::st_ClContextBase_get_selected_node_info( ctx );

            ASSERT_TRUE( node_info != nullptr );
            ASSERT_TRUE( ::st_ClContextBase_has_remapping_kernel( ctx ) );
            ASSERT_TRUE( ::st_ClContext_has_element_by_element_tracking_kernel(
                ctx ) );

            char id_str[ 32 ];
            ::st_ClContextBase_get_selected_node_id_str( ctx, id_str, 32 );

            std::cout << "# --------------------------------------------------"
                      << "----------------------------------------------------"
                      << "\r\n"
                      << "# Run Test on :: \r\n"
                      << "# ID          :: " << id_str << "\r\n"
                      << "# NAME        :: "
                      << ::st_ComputeNodeInfo_get_name( node_info )
                      << "\r\n" << "# PLATFORM    :: "
                      << ::st_ComputeNodeInfo_get_platform( node_info )
                      << "\r\n" << "# Debug mode  :: "
                      << std::boolalpha
                      << ::st_ClContextBase_is_debug_mode_enabled( ctx )
                      << "\r\n" << "# Optimized   :: "
                      << ::st_ClContext_uses_optimized_tracking_by_default(
                        ctx ) << "\r\n"
                      << std::noboolalpha
                      << "# "
                      << std::endl;

            /* ------------------------------------------------------------- */

            bool const success = sixtrack::tests::performElemByElemTrackTest(
                ctx, eb, elem_by_elem_buffer, NUM_TURNS, ABS_TOLERANCE );

            ::st_ClContext_delete( ctx );
            ctx = nullptr;

            ASSERT_TRUE( success );
        }
    }
    else
    {
        std::cout << "Unable to run unit-test -> no OpenCL Nodes found \r\n"
                  << "--> skipping!" << std::endl;
    }

    ::st_Buffer_delete( eb );
    ::st_Buffer_delete( elem_by_elem_buffer );
}

namespace sixtrack
{
    namespace tests
    {
        bool performElemByElemTrackTest(
            ::st_ClContext* SIXTRL_RESTRICT context,
            ::st_Buffer* SIXTRL_RESTRICT beam_elements_buffer,
            ::st_Buffer* SIXTRL_RESTRICT cmp_elem_by_elem_buffer,
            ::st_buffer_size_t const num_turns,
            double const abs_tolerance )
        {
            using size_t = ::st_buffer_size_t;

            bool success = false;

            int ret = 0;
            size_t const num_elem_by_elem_objects =
                ::st_Buffer_get_num_of_objects( cmp_elem_by_elem_buffer );

            ::st_Buffer* pb = ::st_Buffer_new( 0u );
            ::st_Buffer* elem_by_elem_buffer  = ::st_Buffer_new( 0u );

            if( ( num_elem_by_elem_objects >= size_t{ 3 } ) &&
                ( pb != nullptr ) && ( beam_elements_buffer != nullptr ) &&
                ( cmp_elem_by_elem_buffer != nullptr ) &&
                ( num_turns > size_t{ 0 } ) && ( context != nullptr ) &&
                ( ::st_ClContextBase_has_selected_node( context ) ) &&
                ( abs_tolerance >= double{ 0. } ) )
            {
                success = true;
            }

            ::st_Particles* particles                        = nullptr;
            ::st_Particles const* final_state                = nullptr;
            ::st_Particles const* cmp_elem_by_elem_particles = nullptr;

            if( success )
            {
                particles = ::st_Particles_add_copy( pb,
                    ::st_Particles_buffer_get_const_particles(
                        cmp_elem_by_elem_buffer, 0u ) );

                cmp_elem_by_elem_particles =
                    ::st_Particles_buffer_get_const_particles(
                        cmp_elem_by_elem_buffer, 1u );

                final_state = ::st_Particles_buffer_get_const_particles(
                    cmp_elem_by_elem_buffer, 2u );
            }

            size_t const ebe_size = ::st_Particles_get_num_of_particles(
                cmp_elem_by_elem_particles );

            success = ( ( final_state   != nullptr ) &&
                        ( particles     != nullptr ) &&
                        ( cmp_elem_by_elem_particles != nullptr ) &&
                        ( ebe_size > size_t{ 0 } ) );

            ::st_Particles* elem_by_elem_particles = nullptr;

            if( success )
            {
                elem_by_elem_particles =
                    ::st_Particles_new( elem_by_elem_buffer, ebe_size );

                if( elem_by_elem_particles == nullptr )
                {
                    std::cout << "ret 01 : " << ret << std::endl;
                    success = false;
                }
            }

            /* ------------------------------------------------------------- */
            /* Create ClArguments for beam elements & the particles buffer   */

            ::st_ClArgument* particles_buffer_arg    = nullptr;
            ::st_ClArgument* beam_elements_arg       = nullptr;
            ::st_ClArgument* elem_by_elem_buffer_arg = nullptr;

            if( success )
            {
                particles_buffer_arg =
                    ::st_ClArgument_new_from_buffer( pb, context );

                beam_elements_arg =
                    ::st_ClArgument_new_from_buffer(
                        beam_elements_buffer, context );

                elem_by_elem_buffer_arg =
                    ::st_ClArgument_new_from_buffer(
                        elem_by_elem_buffer, context );
            }

            success = ( ( particles_buffer_arg    != nullptr ) &&
                        ( beam_elements_arg       != nullptr ) &&
                        ( elem_by_elem_buffer_arg != nullptr ) );

            if( !success )
            {
                std::cout << "ret 02" << std::endl;
            }

            /* ------------------------------------------------------------- */
            /* Track for num-turns without assigned beam-monitors -> should
             * not change the correctness of tracking at all */

            if( success )
            {
                ret = ::st_ClContext_track_element_by_element(
                    context, particles_buffer_arg, beam_elements_arg,
                    elem_by_elem_buffer_arg, num_turns, 0 );

                if( ret != 0 )
                {
                    std::cout << "ret 03 : " << ret << std::endl;
                    success = false;
                }
            }

            if( success )
            {
                success = ::st_ClArgument_read( particles_buffer_arg, pb );
                particles = ::st_Particles_buffer_get_particles( pb, 0u );
                success &= ( particles != nullptr );
            }

            if( !success )
            {
                std::cout << "ret 04" << std::endl;
            }

            if( success )
            {
                success = ::st_ClArgument_read(
                    elem_by_elem_buffer_arg, elem_by_elem_buffer );

                elem_by_elem_particles = ::st_Particles_buffer_get_particles(
                    elem_by_elem_buffer, 0u );

                success &= ( elem_by_elem_particles != nullptr );
            }

            if( !success )
            {
                std::cout << "ret 05" << std::endl;
            }

            if( success )
            {
                ret = ::st_Particles_compare_values_with_treshold(
                    cmp_elem_by_elem_particles, elem_by_elem_particles,
                    abs_tolerance );

                if( ret != 0 )
                {
                    std::cout << "ret 06 : " << ret << std::endl;
                    success = false;
                }

                if( !success )
                {
                    ::st_Buffer* diff_buffer = ::st_Buffer_new( 0u );
                    ::st_Particles* diff = ::st_Particles_new( diff_buffer,
                        ::st_Particles_get_num_of_particles( particles ) );

                    ::st_Particles_calculate_difference(
                        particles, final_state, diff );

//                     std::cout << std::endl << "cmp_elem_by_elem_buffer = " << std::endl;
//                     ::st_Particles_print_out( cmp_elem_by_elem_particles );

//                     std::cout << std::endl << "elem_by_elem_particles = " << std::endl;
//                     ::st_Particles_print_out( elem_by_elem_particles );

//                     std::cout << std::endl << "diff = " << std::endl;
//                     ::st_Particles_print_out( diff );

                    ::st_Buffer_delete( diff_buffer );
                    diff_buffer = nullptr;
                }
            }

            ::st_ClArgument_delete( particles_buffer_arg );
            ::st_ClArgument_delete( beam_elements_arg );
            ::st_ClArgument_delete( elem_by_elem_buffer_arg );

            ::st_Buffer_delete( pb );
            ::st_Buffer_delete( elem_by_elem_buffer );

            return success;
        }
    }
}

/* end: */
