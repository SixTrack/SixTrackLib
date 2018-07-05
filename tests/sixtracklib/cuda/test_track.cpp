#define _USE_MATH_DEFINES

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

#include <cuda_runtime_api.h>
#include <cuda.h>

#include <gtest/gtest.h>

#include "sixtracklib/_impl/definitions.h"
#include "sixtracklib/_impl/path.h"

#include "sixtracklib/common/blocks.h"
#include "sixtracklib/common/beam_elements.h"
#include "sixtracklib/common/particles.h"
#include "sixtracklib/common/track.h"

#include "sixtracklib/testlib/test_particles_tools.h"
#include "sixtracklib/testlib/test_track_tools.h"
#include "sixtracklib/testlib/testdata_files.h"

#include "sixtracklib/cuda/cuda_env.h"

namespace sixtracklib
{
    bool read_testdata_and_run_tracking_test(
        const char *const path_to_testdata,
        int const num_of_blocks, int const threads_per_block )
    {
        st_Blocks initial_particles_buffer;
        st_Blocks result_particles_buffer;
        st_Blocks beam_elements;
        st_Blocks elem_by_elem_buffer;

        st_Blocks_preset( &initial_particles_buffer );
        st_Blocks_preset( &result_particles_buffer );
        st_Blocks_preset( &elem_by_elem_buffer );
        st_Blocks_preset( &beam_elements );

        uint64_t NUM_OF_TURNS = uint64_t{ 0 };

        bool success = ( st_Tracks_restore_testdata_from_binary_file(
            path_to_testdata, &NUM_OF_TURNS, &initial_particles_buffer,
            &result_particles_buffer, &beam_elements, &elem_by_elem_buffer ) );

        /* --------------------------------------------------------------------- */

        st_block_size_t const NUM_OF_BEAM_ELEMENTS =
            st_Blocks_get_num_of_blocks( &beam_elements );

        st_block_size_t const NUM_OF_PARTICLE_BLOCKS =
            st_Blocks_get_num_of_blocks( &initial_particles_buffer );

        uint64_t NUM_OF_PARTICLES = uint64_t{ 0 };

        st_BlockInfo const* part_block_it  =
            st_Blocks_get_const_block_infos_begin( &initial_particles_buffer );

        st_BlockInfo const* part_block_end =
            st_Blocks_get_const_block_infos_end( &initial_particles_buffer );

        for( ; part_block_it != part_block_end ; ++part_block_it )
        {
            st_Particles const* particles =
                st_Blocks_get_const_particles( part_block_it );

            NUM_OF_PARTICLES += st_Particles_get_num_particles( particles );
        }

        /* --------------------------------------------------------------------- */

        st_Blocks particles_buffer;
        st_Blocks_preset( &particles_buffer );

        success &= ( 0 == st_Blocks_init_from_serialized_data( &particles_buffer,
        st_Blocks_get_const_data_begin( &initial_particles_buffer ),
        st_Blocks_get_total_num_bytes(  &initial_particles_buffer ) ) );

        st_Blocks calculated_elem_by_elem_buffer;
        st_Blocks_preset( &calculated_elem_by_elem_buffer );

        bool use_elem_by_elem_buffer = false;

        st_block_size_t const AVAILABLE_ELEM_BY_ELEM_BLOCKS =
            st_Blocks_get_num_of_blocks( &elem_by_elem_buffer );

        st_block_size_t const NUM_IO_ELEMENTS_PER_TURN =
            NUM_OF_BEAM_ELEMENTS * NUM_OF_PARTICLE_BLOCKS;

        if( ( success ) && ( NUM_OF_TURNS > uint64_t{ 0 } ) &&
            ( ( NUM_OF_TURNS * NUM_IO_ELEMENTS_PER_TURN )
                <= AVAILABLE_ELEM_BY_ELEM_BLOCKS ) )
        {
            success &= ( 0 == st_Blocks_init_from_serialized_data(
                &calculated_elem_by_elem_buffer,
                st_Blocks_get_const_data_begin( &calculated_elem_by_elem_buffer ),
                st_Blocks_get_total_num_bytes(  &calculated_elem_by_elem_buffer ) )
            );

            st_Particles_buffer_preset_values( &calculated_elem_by_elem_buffer );

            use_elem_by_elem_buffer = true;
        }

        st_Blocks* ptr_elem_by_elem_buffer = ( use_elem_by_elem_buffer )
            ? &elem_by_elem_buffer : nullptr;

        /* ******************************************************************** */
        /* *****                  CUDA based tracking                     ***** */
        /* ******************************************************************** */

        success &= ( st_Track_particles_on_cuda(
            num_of_blocks, threads_per_block, NUM_OF_TURNS,
            &particles_buffer, &beam_elements, ptr_elem_by_elem_buffer ) );

        /* ******************************************************************** */
        /* *****              End of CUDA based tracking                  ***** */
        /* ******************************************************************** */

        success &= ( st_Particles_buffers_have_same_structure(
            &initial_particles_buffer, &result_particles_buffer ) );

        success &= ( st_Particles_buffers_have_same_structure(
            &initial_particles_buffer, &particles_buffer ) );

        success &= ( !st_Particles_buffers_map_to_same_memory(
            &initial_particles_buffer, &result_particles_buffer ) );

        success &= ( !st_Particles_buffers_map_to_same_memory(
            &initial_particles_buffer, &particles_buffer ) );

        if( 0 == st_Particles_buffer_compare_values(
            &result_particles_buffer, &particles_buffer ) )
        {
            std::cout << "calculated result and result from testdata are "
                        "bit-for-bit identical --> Success!" << std::endl;
        }
        else
        {
            st_Blocks max_diff_buffer;
            st_Blocks_preset( &max_diff_buffer );

            st_block_size_t const MAX_DIST_DATA_CAPACITY =
                st_Blocks_predict_data_capacity_for_num_blocks(
                    &max_diff_buffer, NUM_OF_PARTICLE_BLOCKS ) +
                st_Particles_predict_blocks_data_capacity(
                    &max_diff_buffer, NUM_OF_PARTICLE_BLOCKS, 1u );

            st_Blocks_init( &max_diff_buffer,
                            NUM_OF_PARTICLE_BLOCKS, MAX_DIST_DATA_CAPACITY );

            for( st_block_size_t ii = 0 ; ii < NUM_OF_PARTICLE_BLOCKS ; ++ii )
            {
                st_Particles* particles = st_Blocks_add_particles(
                    &max_diff_buffer, 1u );

                if( particles != nullptr )
                {
                    st_Particles_preset_values( particles );
                }
            }

            std::vector< st_block_size_t > max_diff_index(
                NUM_OF_PARTICLE_BLOCKS * 20, st_block_size_t{ 0 } );

            st_Blocks_serialize( &max_diff_buffer );

            st_Particles_buffer_get_max_difference(
                &max_diff_buffer, max_diff_index.data(),
                &result_particles_buffer, &particles_buffer );

            fprintf( stdout, "|Diff| = |precalculated result - calculated|\r\n" );

            st_Particles_buffer_print_max_diff(
                stdout, &max_diff_buffer, max_diff_index.data() );

            st_Blocks_free( &max_diff_buffer );
        }

        if( use_elem_by_elem_buffer )
        {
            st_block_size_t ll = ( st_block_size_t )0u;

            st_block_size_t const num_elem_by_elem_per_turn =
                NUM_OF_PARTICLE_BLOCKS * NUM_OF_BEAM_ELEMENTS;

            st_BlockInfo const* block_it = st_Blocks_get_const_block_infos_begin(
                &calculated_elem_by_elem_buffer );

            st_BlockInfo const* block_end = st_Blocks_get_const_block_infos_end(
                &calculated_elem_by_elem_buffer );

            st_BlockInfo const* cmp_block_it =
                st_Blocks_get_const_block_infos_begin( &elem_by_elem_buffer );

            st_BlockInfo const* cmp_block_end =
                st_Blocks_get_const_block_infos_end( &elem_by_elem_buffer );

            success &= ( ( block_it      != nullptr ) &&
                        ( block_end     != nullptr ) &&
                        ( cmp_block_it  != nullptr ) &&
                        ( cmp_block_end != nullptr ) );

            success &= ( std::distance( cmp_block_end, cmp_block_it ) >=
                        std::distance( block_end,     block_it     ) );

            for( ; block_it != block_end ; ++block_it, ++cmp_block_it )
            {
                st_Particles const* particles =
                    st_Blocks_get_const_particles( block_it );

                st_Particles const* cmp_particles =
                    st_Blocks_get_const_particles( cmp_block_it );

                success &= ( st_Particles_have_same_structure(
                    particles, cmp_particles ) );

                success &= ( !st_Particles_map_to_same_memory(
                    particles, cmp_particles ) );

                if( 0 != st_Particles_compare_values( particles, cmp_particles ) )
                {
                    st_block_size_t const turn = ll / num_elem_by_elem_per_turn;
                    st_block_size_t       temp = ll % num_elem_by_elem_per_turn;

                    st_block_size_t const particle_block_index =
                        temp / NUM_OF_BEAM_ELEMENTS;

                    st_block_size_t const beam_element_index =
                        temp % NUM_OF_BEAM_ELEMENTS;

                    fprintf( stdout, "first deviation in elem_by_elem buffer @"
                            "elem_by_elem_block_index = %8lu :: "
                            "turn = %8lu / part_block_idx = %8ld / "
                            "beam_elem_id = %8ld\r\n",
                            ll, turn, particle_block_index, beam_element_index );

                    break;
                }
            }
        }

        /* --------------------------------------------------------------------- */

        st_Blocks_free( &calculated_elem_by_elem_buffer );
        st_Blocks_free( &particles_buffer );

        st_Blocks_free( &initial_particles_buffer );
        st_Blocks_free( &result_particles_buffer );
        st_Blocks_free( &beam_elements );
        st_Blocks_free( &elem_by_elem_buffer );


        return success;
    }
}

/* ========================================================================= */
/* =====  track drifts of constant length                                    */
/* ========================================================================= */

TEST( CudaTrackTests, TrackDrifts )
{
    bool const success = sixtracklib::read_testdata_and_run_tracking_test(
        st_PATH_TO_TEST_TRACKING_DRIFT_DATA, 32, 8 );

    ASSERT_TRUE( success );
}

TEST( CudaTrackTests, TrackDriftsExact )
{
    bool const success = sixtracklib::read_testdata_and_run_tracking_test(
        st_PATH_TO_TEST_TRACKING_DRIFT_EXACT_DATA, 32, 8 );

    ASSERT_TRUE( success );
}

TEST( CudaTrackTests, TrackMultiPoles )
{
    bool const success = sixtracklib::read_testdata_and_run_tracking_test(
        st_PATH_TO_TEST_TRACKING_MULTIPOLE_DATA, 32, 8 );

    ASSERT_TRUE( success );
}

TEST( CudaTrackTests, TrackBeamBeams )
{
    bool const success = sixtracklib::read_testdata_and_run_tracking_test(
        st_PATH_TO_TEST_TRACKING_BEAM_BEAM_DATA, 32, 8 );

    ASSERT_TRUE( success );
}

TEST( CudaTrackTests, TrackCavities )
{
    bool const success = sixtracklib::read_testdata_and_run_tracking_test(
        st_PATH_TO_TEST_TRACKING_CAVITY_DATA, 32, 8 );

    ASSERT_TRUE( success );
}

TEST( CudaTrackTests, TrackAligns )
{
    bool const success = sixtracklib::read_testdata_and_run_tracking_test(
        st_PATH_TO_TEST_TRACKING_ALIGN_DATA, 32, 8 );

    ASSERT_TRUE( success );
}

/* ************************************************************************* */


/* end: sixtracklib/opencl/tests/test_track.cpp */
