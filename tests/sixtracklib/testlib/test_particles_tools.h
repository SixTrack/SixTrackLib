#ifndef SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TEST_PARTICLES_TOOLS_H__
#define SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TEST_PARTICLES_TOOLS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdio.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/_impl/definitions.h"
    #include "sixtracklib/common/blocks.h"
    #include "sixtracklib/common/particles.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

void NS(Particles_random_init)( NS(Particles)* SIXTRL_RESTRICT p );
void NS(Particles_realistic_init)( NS(Particles)* SIXTRL_RESTRICT p );

/* ------------------------------------------------------------------------- */

int NS(Particles_have_same_structure)(
    const NS(Particles) *const SIXTRL_RESTRICT lhs,
    const NS(Particles) *const SIXTRL_RESTRICT rhs );

int NS(Particles_map_to_same_memory)(
    const NS(Particles) *const SIXTRL_RESTRICT lhs,
    const NS(Particles) *const SIXTRL_RESTRICT rhs );

int NS(Particles_compare_values)(
    const NS(Particles) *const SIXTRL_RESTRICT lhs,
    const NS(Particles) *const SIXTRL_RESTRICT rhs );

int NS(Particles_compare_values_with_treshold)(
    const NS(Particles) *const SIXTRL_RESTRICT lhs,
    const NS(Particles) *const SIXTRL_RESTRICT rhs,
    SIXTRL_REAL_T const treshold );

void NS(Particles_get_max_difference)(
    NS(Particles)* SIXTRL_RESTRICT max_diff,
    NS(block_size_t)* SIXTRL_RESTRICT max_diff_indices,
    const NS(Particles) *const SIXTRL_RESTRICT lhs,
    const NS(Particles) *const SIXTRL_RESTRICT rhs );

void NS(Particles_print)(
    FILE* SIXTRL_RESTRICT fp,
    const NS(Particles) *const SIXTRL_RESTRICT particles );

void NS(Particles_print_max_diff)(
    FILE* SIXTRL_RESTRICT fp,
    const NS(Particles) *const SIXTRL_RESTRICT max_diff,
    NS(block_size_t) const* max_diff_indices );

/* ------------------------------------------------------------------------- */

int NS(Particles_buffers_have_same_structure)(
    const NS(Blocks) *const SIXTRL_RESTRICT lhs_buffer,
    const NS(Blocks) *const SIXTRL_RESTRICT rhs_buffer );

int NS(Particles_buffers_map_to_same_memory)(
    const NS(Blocks) *const SIXTRL_RESTRICT lhs_buffer,
    const NS(Blocks) *const SIXTRL_RESTRICT rhs_buffer );

int NS(Particles_buffer_compare_values)(
    const NS(Blocks) *const SIXTRL_RESTRICT lhs_buffer,
    const NS(Blocks) *const SIXTRL_RESTRICT rhs_buffer );

int NS(Particles_buffer_compare_values_with_treshold)(
    const NS(Blocks) *const SIXTRL_RESTRICT lhs_buffer,
    const NS(Blocks) *const SIXTRL_RESTRICT rhs_buffer,
    SIXTRL_REAL_T const treshold );

void NS(Particles_buffer_get_max_difference)(
    NS(Blocks)* SIXTRL_RESTRICT max_diff,
    NS(block_size_t)* SIXTRL_RESTRICT max_diff_indices,
    const NS(Blocks) *const SIXTRL_RESTRICT lhs,
    const NS(Blocks) *const SIXTRL_RESTRICT rhs );

void NS(Particles_buffer_print)(
    FILE* SIXTRL_RESTRICT fp,
    const NS(Blocks) *const SIXTRL_RESTRICT particles );

void NS(Particles_buffer_print_max_diff)(
    FILE* SIXTRL_RESTRICT fp,
    const NS(Blocks) *const SIXTRL_RESTRICT max_diff,
    NS(block_size_t) const* max_diff_indices );

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TEST_PARTICLES_TOOLS_H__ */

/* end: tests/sixtracklib/testlib/test_particles_tools.h */
