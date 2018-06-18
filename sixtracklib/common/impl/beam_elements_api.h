#ifndef SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_API_H__
#define SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_API_H__

#if !defined( _GPUCODE )

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sixtracklib/_impl/definitions.h"
#include "sixtracklib/common/impl/beam_elements_type.h"
#include "sixtracklib/common/beam_elements.h"
#include "sixtracklib/common/blocks.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#endif /* !defined( _GPUCODE ) */

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(Drift)* NS(Drift_preset)( NS(Drift)* drift );

SIXTRL_FN SIXTRL_STATIC NS(BlockType) NS(Drift_get_type_id)(
    const NS(Drift) *const SIXTRL_RESTRICT drift );

SIXTRL_FN SIXTRL_STATIC NS(block_type_num_t) NS(Drift_get_type_id_num)(
    const NS(Drift) *const SIXTRL_RESTRICT drift );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(Drift_get_length)(
    const NS(Drift) *const SIXTRL_RESTRICT drift );

SIXTRL_FN SIXTRL_STATIC void NS(Drift_set_length)(
    NS(Drift)* SIXTRL_RESTRICT drift, SIXTRL_REAL_T const length );
    
SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC 
NS(Drift) const* NS(Blocks_get_const_drift)( 
    const NS(BlockInfo) *const SIXTRL_RESTRICT block_info );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC NS(Drift)* NS(Blocks_get_drift)( 
    NS(BlockInfo)* SIXTRL_RESTRICT block_info );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(DriftExact)* NS(DriftExact_preset)(
    NS(DriftExact)* drift_exact );

SIXTRL_FN SIXTRL_STATIC NS(BlockType) NS(DriftExact_get_type_id)(
    const NS(DriftExact) *const SIXTRL_RESTRICT drift_exact );

SIXTRL_FN SIXTRL_STATIC NS(block_type_num_t) NS(DriftExact_get_type_id_num)(
    const NS(DriftExact) *const SIXTRL_RESTRICT drift_exact );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(DriftExact_get_length)(
    const NS(DriftExact) *const SIXTRL_RESTRICT drift_exact );

SIXTRL_FN SIXTRL_STATIC void NS(DriftExact_set_length)(
    NS(DriftExact)* SIXTRL_RESTRICT drift_exact, SIXTRL_REAL_T const length );
    
SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC NS(DriftExact) const* 
NS(Blocks_get_const_drift_exact)( 
    const NS(BlockInfo) *const SIXTRL_RESTRICT block_info );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC 
NS(DriftExact)* NS(Blocks_get_drift_exact)( 
    NS(BlockInfo)* SIXTRL_RESTRICT block_info );

/* ------------------------------------------------------------------------- */
    
SIXTRL_FN SIXTRL_STATIC NS(MultiPole)* 
NS(MultiPole_preset)( NS(MultiPole)* multipole );

SIXTRL_FN SIXTRL_STATIC NS(BlockType) NS(MultiPole_get_type_id)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC NS(block_type_num_t) NS(MultiPole_get_type_id_num)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(MultiPole_get_length)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(MultiPole_get_hxl)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(MultiPole_get_hyl)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC SIXTRL_INT64_T NS(MultiPole_get_order)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* 
NS(MultiPole_get_const_bal)( const NS(MultiPole) *const SIXTRL_RESTRICT mp );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* 
NS(MultiPole_get_bal)( NS(MultiPole)* SIXTRL_RESTRICT mp );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(MultiPole_get_bal_value)(
    const NS(MultiPole) *const SIXTRL_RESTRICT mp, 
    SIXTRL_INT64_T const index );

SIXTRL_FN SIXTRL_STATIC void NS(MultiPole_set_length)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_REAL_T const length );

SIXTRL_FN SIXTRL_STATIC void NS(MultiPole_set_hxl)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_REAL_T const hxl );

SIXTRL_FN SIXTRL_STATIC void NS(MultiPole_set_hyl)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_REAL_T const hyl );

SIXTRL_FN SIXTRL_STATIC void NS(MultiPole_set_order)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_INT64_T const order );

SIXTRL_FN SIXTRL_STATIC void NS(MultiPole_set_bal_value)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, 
    SIXTRL_INT64_T const index, SIXTRL_REAL_T const value );

SIXTRL_FN SIXTRL_STATIC void NS(MultiPole_set_bal)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, 
    SIXTRL_INT64_T const order, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* SIXTRL_RESTRICT bal );

SIXTRL_FN SIXTRL_STATIC void NS(MultiPole_assign_ptr_to_bal)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT ptr_to_bal );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC NS(MultiPole) const* 
NS(Blocks_get_const_multipole)( 
    const NS(BlockInfo) *const SIXTRL_RESTRICT block_info );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC 
NS(MultiPole)* NS(Blocks_get_multipole)( 
    NS(BlockInfo)* SIXTRL_RESTRICT block_info );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC NS(BeamBeamBoostData) const* 
NS(BeamBeam_get_const_ptr_boost_data)( 
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC NS(BeamBeamBoostData)*
NS(BeamBeam_get_ptr_boost_data)( NS(BeamBeam)* SIXTRL_RESTRICT beam_beam );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(BeamBeamSigmas) const*
NS(BeamBeam_get_const_ptr_sigmas_matrix)( 
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC NS(BeamBeamSigmas)*
NS(BeamBeam_get_ptr_sigmas_matrix)( NS(BeamBeam)* SIXTRL_RESTRICT beam_beam );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* 
NS(BeamBeam_get_const_n_part_per_slice)( 
    const NS(BeamBem) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* 
NS(BeamBeam_get_n_part_per_slice)( NS(BeamBem)* SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(BeamBeam_get_n_part_per_slice_value)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const index );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_n_part_per_slice_value)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const index,
    SIXTRL_REAL_T const value );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_n_part_per_slice)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* n_part_per_slice_begin );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_assign_n_part_per_slice_ptr)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* n_part_per_slice_begin );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* 
NS(BeamBeam_get_const_x_slices_star)( 
    const NS(BeamBem) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* 
NS(BeamBeam_get_x_slices_star)( NS(BeamBem)* SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(BeamBeam_get_x_slices_star_value)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const index );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_x_slices_star_value)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const index,
    SIXTRL_REAL_T const value );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_x_slices_star)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* x_slices_star_begin );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_assign_x_slices_star_ptr)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* x_slices_star_begin );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* 
NS(BeamBeam_get_const_y_slices_star)( 
    const NS(BeamBem) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* 
NS(BeamBeam_get_y_slices_star)( NS(BeamBem)* SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(BeamBeam_get_y_slices_star_value)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const index );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_y_slices_star_value)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const index,
    SIXTRL_REAL_T const value );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_y_slices_star)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* y_slices_star_begin );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_assign_y_slices_star_ptr)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* y_slices_star_begin );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* 
NS(BeamBeam_get_const_sigma_slices_star)( 
    const NS(BeamBem) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* 
NS(BeamBeam_get_sigma_slices_star)( NS(BeamBem)* SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(BeamBeam_get_sigma_slices_star_value)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const index );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_sigma_slices_star_value)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const index,
    SIXTRL_REAL_T const value );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_sigma_slices_star)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* sigma_slices_star_begin );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_assign_sigma_slices_star_ptr)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* sigma_slices_star_begin );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(block_num_elements_t) NS(BeamBeam_get_num_of_slices)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_num_of_slices)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    NS(block_num_elements_t) const num_of_slices );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(BeamBeam_get_q_part)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_q_part)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, SIXTRL_REAL_T const q_part );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(BeamBeam_get_min_sigma_diff)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_min_sigma_diff)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_REAL_T const min_sigma_diff );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T NS(BeamBeam_get_treshold_singular)(
    const NS(BeamBeam) *const SIXTRL_RESTRICT beam_beam );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeam_set_treshold_singular)(
    NS(BeamBeam)* SIXTRL_RESTRICT beam_beam, 
    SIXTRL_REAL_T const treshold_singular );

/* ------------------------------------------------------------------------- */

SIXTRL_FN NS(BeamBeamSigmas_get_sigma11)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma11)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_11 );

SIXTRL_FN NS(BeamBeamSigmas_get_sigma12)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma12)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_12 );

SIXTRL_FN NS(BeamBeamSigmas_get_sigma13)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma13)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_13 );

SIXTRL_FN NS(BeamBeamSigmas_get_sigma14)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma14)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_14 );


SIXTRL_FN NS(BeamBeamSigmas_get_sigma22)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma22)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_22 );

SIXTRL_FN NS(BeamBeamSigmas_get_sigma23)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma23)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_23 );

SIXTRL_FN NS(BeamBeamSigmas_get_sigma24)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma24)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_24 );


SIXTRL_FN NS(BeamBeamSigmas_get_sigma33)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma33)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_33 );

SIXTRL_FN NS(BeamBeamSigmas_get_sigma34)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma34)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_34 );



SIXTRL_FN NS(BeamBeamSigmas_get_sigma44)( 
    const NS(BeamBeamSigmas) *const SIXTRL_RESTRICT sigma_matrix );

SIXTRL_FN NS(BeamBeamSigmas_set_sigma44)( 
    NS(BeamBeamSigmas)* SIXTRL_RESTRICT sigma_matrix, 
    SIXTRL_REAL_T const sigma_44 );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeamPropagatedSigmasResult_preset)(
    NS(BeamBeamPropagatedSigmasResult)* SIXTRL_RESTRICT result );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamPropagatedSigmasResult_get_cos_theta)( 
    const NS(BeamBeamPropagatedSigmasResult) *const SIXTRL_RESTRICT result );
    
SIXTRL_FN SIXTRL_STATIC void 
NS(BeamBeamPropagatedSigmasResult_set_cos_theta)(
    NS(BeamBeamPropagatedSigmasResult)* SIXTRL_RESTRICT result,
    SIXTRL_REAL_T const cose_theta );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamPropagatedSigmasResult_get_sin_theta)( 
    const NS(BeamBeamPropagatedSigmasResult) *const SIXTRL_RESTRICT result );
    
SIXTRL_FN SIXTRL_STATIC void 
NS(BeamBeamPropagatedSigmasResult_set_sin_theta)(
    NS(BeamBeamPropagatedSigmasResult)* SIXTRL_RESTRICT result,
    SIXTRL_REAL_T const sin_theta );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamPropagatedSigmasResult_get_sigma_11_hat)( 
    const NS(BeamBeamPropagatedSigmasResult) *const SIXTRL_RESTRICT result );
    
SIXTRL_FN SIXTRL_STATIC void 
NS(BeamBeamPropagatedSigmasResult_set_sigma_11_hat)(
    NS(BeamBeamPropagatedSigmasResult)* SIXTRL_RESTRICT result,
    SIXTRL_REAL_T const sigma_11_hat );

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamPropagatedSigmasResult_get_sigma_33_hat)( 
    const NS(BeamBeamPropagatedSigmasResult) *const SIXTRL_RESTRICT result );
    
SIXTRL_FN SIXTRL_STATIC void 
NS(BeamBeamPropagatedSigmasResult_set_sigma_33_hat)(
    NS(BeamBeamPropagatedSigmasResult)* SIXTRL_RESTRICT result,
    SIXTRL_REAL_T const sigma_11_hat );

/* ------------------------------------------------------------------------- */

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamBoostData_get_sphi)( SIXTRL_GLOBAL_DEC const 
    NS(BeamBeamBoostData) *const SIXTRL_RESTRICT boost_data );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeamBoostData_set_sphi)(
    NS(BeamBeamBoostData)* SIXTRL_RESTRICT boost_data, 
    SIXTRL_REAL_T const sphi );



SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamBoostData_get_cphi)( 
    const NS(BeamBeamBoostData) *const SIXTRL_RESTRICT boost_data );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeamBoostData_set_cphi)(
    NS(BeamBeamBoostData)* SIXTRL_RESTRICT boost_data, 
    SIXTRL_REAL_T const cphi );



SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamBoostData_get_tphi)( 
    const NS(BeamBeamBoostData) *const SIXTRL_RESTRICT boost_data );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeamBoostData_set_tphi)(
    NS(BeamBeamBoostData)* SIXTRL_RESTRICT boost_data, 
    SIXTRL_REAL_T const tphi );


SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamBoostData_get_salpha)( 
    const NS(BeamBeamBoostData) *const SIXTRL_RESTRICT boost_data );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeamBoostData_set_salpha)(
    NS(BeamBeamBoostData)* SIXTRL_RESTRICT boost_data, 
    SIXTRL_REAL_T const salpha );
    

SIXTRL_FN SIXTRL_STATIC SIXTRL_REAL_T 
NS(BeamBeamBoostData_get_talpha)( 
    const NS(BeamBeamBoostData) *const SIXTRL_RESTRICT boost_data );

SIXTRL_FN SIXTRL_STATIC void NS(BeamBeamBoostData_set_talpha)(
    NS(BeamBeamBoostData)* SIXTRL_RESTRICT boost_data, 
    SIXTRL_REAL_T const talpha );

/* ========================================================================= */
/* ======             Implementation of inline functions            ======== */
/* ========================================================================= */

#if !defined( _GPUCODE )
#include "sixtracklib/common/beam_elements.h"
#endif /* !defined( _GPUCODE ) */

SIXTRL_INLINE NS(Drift)* NS(Drift_preset)( NS(Drift)* drift )
{
    NS(Drift_set_length)( drift, ( SIXTRL_REAL_T )0.0 );
    return drift;
}

SIXTRL_INLINE NS(BlockType) NS(Drift_get_type_id)(
    const NS(Drift) *const SIXTRL_RESTRICT drift )
{
    return ( drift != 0 ) ? NS(BLOCK_TYPE_DRIFT) : NS(BLOCK_TYPE_INVALID);
}

SIXTRL_INLINE NS(block_type_num_t) NS(Drift_get_type_id_num)(
    const NS(Drift) *const SIXTRL_RESTRICT drift )
{
    return NS(BlockType_to_number)( NS(Drift_get_type_id)( drift ) );
        
}

SIXTRL_INLINE SIXTRL_REAL_T NS(Drift_get_length)(
    const NS(Drift) *const SIXTRL_RESTRICT drift )
{
    return ( drift ) ? drift->length : ( SIXTRL_REAL_T )0.0;
}

SIXTRL_INLINE void NS(Drift_set_length)(
    NS(Drift)* SIXTRL_RESTRICT drift, SIXTRL_REAL_T const length )
{
    if( ( drift != 0 ) && ( length >= ( SIXTRL_REAL_T )0.0 ) )
    {
        drift->length = length;
    }
    
    return;
}
    
SIXTRL_INLINE SIXTRL_GLOBAL_DEC NS(Drift) const* NS(Blocks_get_const_drift)( 
    const NS(BlockInfo) *const SIXTRL_RESTRICT block_info )
{
    #if !defined( _GPUCODE )
    
    NS(BlockType) const type_id = 
        NS(BlockInfo_get_type_id)( block_info );
    
    SIXTRL_GLOBAL_DEC void const* ptr_begin = 
        NS(BlockInfo_get_const_ptr_begin)( block_info );    
    
    #else
    
    SIXTRL_GLOBAL_DEC void const* ptr_begin = 0;
    NS(BlockType) type_id = NS(BLOCK_TYPE_INVALID);    
    
    if( block_info != 0 )
    {
        NS(BlockInfo) const info = *block_info;
        ptr_begin = NS(BlockInfo_get_const_ptr_begin)( &info );
        type_id   = NS(BlockInfo_get_type_id)( &info );
    }
    
    #endif /* !defined( _GPUCODE ) */
    
    SIXTRL_ASSERT( ( ptr_begin == 0 ) ||
                   ( ( ( ( uintptr_t )ptr_begin ) % 8u ) == 0u ) );
    
    return ( type_id == NS(BLOCK_TYPE_DRIFT) )
        ? ( SIXTRL_GLOBAL_DEC NS(Drift) const* )ptr_begin : 0;
}

SIXTRL_INLINE SIXTRL_GLOBAL_DEC NS(Drift)* NS(Blocks_get_drift)( 
    NS(BlockInfo)* SIXTRL_RESTRICT block_info )
{
    return ( SIXTRL_GLOBAL_DEC NS(Drift)* 
        )NS(Blocks_get_const_drift)( block_info );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(DriftExact)* NS(DriftExact_preset)( NS(DriftExact)* drift )
{
    NS(DriftExact_set_length)( drift, ( SIXTRL_REAL_T )0.0 );
    return drift;
}

SIXTRL_INLINE NS(BlockType) NS(DriftExact_get_type_id)(
    const NS(DriftExact) *const SIXTRL_RESTRICT drift )
{
    return ( drift != 0 ) ? NS(BLOCK_TYPE_DRIFT_EXACT) : NS(BLOCK_TYPE_INVALID);
}

SIXTRL_INLINE NS(block_type_num_t) NS(DriftExact_get_type_id_num)(
    const NS(DriftExact) *const SIXTRL_RESTRICT drift )
{
    return NS(BlockType_to_number)( NS(DriftExact_get_type_id)( drift ) );
        
}

SIXTRL_INLINE SIXTRL_REAL_T NS(DriftExact_get_length)(
    const NS(DriftExact) *const SIXTRL_RESTRICT drift )
{
    return ( drift ) ? drift->length : ( SIXTRL_REAL_T )0.0;
}

SIXTRL_INLINE void NS(DriftExact_set_length)(
    NS(DriftExact)* SIXTRL_RESTRICT drift, SIXTRL_REAL_T const length )
{
    if( ( drift != 0 ) && ( length >= ( SIXTRL_REAL_T )0.0 ) )
    {
        drift->length = length;
    }
    
    return;
}
    
SIXTRL_INLINE SIXTRL_GLOBAL_DEC NS(DriftExact) const* 
NS(Blocks_get_const_drift_exact)( 
    const NS(BlockInfo) *const SIXTRL_RESTRICT block_info )
{
    #if !defined( _GPUCODE )
    
    NS(BlockType) const type_id = 
        NS(BlockInfo_get_type_id)( block_info );
    
    SIXTRL_GLOBAL_DEC void const* ptr_begin = 
        NS(BlockInfo_get_const_ptr_begin)( block_info );    
    
    #else
    
    SIXTRL_GLOBAL_DEC void const* ptr_begin = 0;
    NS(BlockType) type_id = NS(BLOCK_TYPE_INVALID);    
    
    if( block_info != 0 )
    {
        NS(BlockInfo) const info = *block_info;
        ptr_begin = NS(BlockInfo_get_const_ptr_begin)( &info );
        type_id   = NS(BlockInfo_get_type_id)( &info );
    }
    
    #endif /* !defined( _GPUCODE ) */
    
    SIXTRL_ASSERT( ( ptr_begin == 0 ) ||
                   ( ( ( ( uintptr_t )ptr_begin ) % 8u ) == 0u ) );
    
    return ( type_id == NS(BLOCK_TYPE_DRIFT_EXACT) )
        ? ( SIXTRL_GLOBAL_DEC NS(DriftExact) const* )ptr_begin : 0;
}

SIXTRL_INLINE SIXTRL_GLOBAL_DEC NS(DriftExact)* NS(Blocks_get_drift_exact)( 
    NS(BlockInfo)* SIXTRL_RESTRICT block_info )
{
    return ( SIXTRL_GLOBAL_DEC NS(DriftExact)* 
        )NS(Blocks_get_const_drift_exact)( block_info );
}

/* ------------------------------------------------------------------------- */
    
SIXTRL_INLINE NS(MultiPole)* NS(MultiPole_preset)( NS(MultiPole)* multipole )
{
    NS(MultiPole_set_order)(  multipole, ( SIXTRL_INT64_T )0 );
    NS(MultiPole_set_hxl)(    multipole, ( SIXTRL_REAL_T )0.0 );
    NS(MultiPole_set_hyl)(    multipole, ( SIXTRL_REAL_T )0.0 );
    NS(MultiPole_set_length)( multipole, ( SIXTRL_REAL_T )0.0 );
    NS(MultiPole_assign_ptr_to_bal)( multipole, 0 );
    
    return multipole;
}

SIXTRL_INLINE NS(BlockType) NS(MultiPole_get_type_id)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole )
{
    return NS(BLOCK_TYPE_MULTIPOLE);
}

SIXTRL_INLINE NS(block_type_num_t) NS(MultiPole_get_type_id_num)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole )
{
    return NS(BlockType_to_number)( NS(BLOCK_TYPE_MULTIPOLE) );
}

SIXTRL_INLINE SIXTRL_REAL_T NS(MultiPole_get_length)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT(  ( multipole != 0 ) && 
                    ( multipole->length >= ( SIXTRL_REAL_T )0.0 ) );
    
    return multipole->length;
}

SIXTRL_INLINE SIXTRL_REAL_T NS(MultiPole_get_hxl)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT(  ( multipole != 0 ) && 
                    ( multipole->hyl > ( SIXTRL_REAL_T )0.0 ) );
    
    return multipole->hxl;
}

SIXTRL_INLINE SIXTRL_REAL_T NS(MultiPole_get_hyl)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT(  ( multipole != 0 ) && 
                    ( multipole->hyl > ( SIXTRL_REAL_T )0.0 ) );
    
    return multipole->hyl;
}

SIXTRL_INLINE SIXTRL_INT64_T NS(MultiPole_get_order)(
    const NS(MultiPole) *const SIXTRL_RESTRICT multipole )
{
    SIXTRL_ASSERT( ( multipole != 0 ) && ( multipole->order >= 0 ) );
    return multipole->order;
}

SIXTRL_INLINE SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* 
NS(MultiPole_get_const_bal)( const NS(MultiPole) *const SIXTRL_RESTRICT mp )
{
    SIXTRL_ASSERT( mp != 0 );
    return mp->bal;
}

SIXTRL_INLINE SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* 
NS(MultiPole_get_bal)( NS(MultiPole)* SIXTRL_RESTRICT mp )
{
    return ( SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* )NS(MultiPole_get_bal)( mp );
}

SIXTRL_INLINE SIXTRL_REAL_T NS(MultiPole_get_bal_value)(
    const NS(MultiPole) *const SIXTRL_RESTRICT mp, SIXTRL_INT64_T const index )
{
    SIXTRL_ASSERT( ( mp != 0 ) && ( index >= 0 ) && 
                   ( index < ( 2 * mp->order + 2 ) ) );
     
    return ( mp->bal != 0 ) ? mp->bal[ index ] : ( SIXTRL_REAL_T )0.0;
}

SIXTRL_INLINE void NS(MultiPole_set_length)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_REAL_T const length )
{
    SIXTRL_ASSERT( multipole != 0 );
    multipole->length = length;
    
    return;
}

SIXTRL_INLINE void NS(MultiPole_set_hxl)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_REAL_T const hxl )
{
    SIXTRL_ASSERT( multipole != 0 );
    multipole->hxl = hxl;
    
    return;
}

SIXTRL_INLINE void NS(MultiPole_set_hyl)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_REAL_T const hyl )
{
    SIXTRL_ASSERT( multipole != 0 );
    multipole->hyl = hyl;
    
    return;
}

SIXTRL_INLINE void NS(MultiPole_set_order)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_INT64_T const order )
{
    SIXTRL_ASSERT( ( multipole != 0 ) && ( order >= 0 ) );
    multipole->order = order;
    
    return;
}

SIXTRL_INLINE void NS(MultiPole_set_bal_value)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, 
    SIXTRL_INT64_T const index, SIXTRL_REAL_T const value )
{
    SIXTRL_ASSERT( ( multipole != 0 ) && ( index >= 0 ) &&
                   ( index < ( 2 * multipole->order + 2 ) ) );
    
    multipole->bal[ index ] = value;
    return;
}

SIXTRL_INLINE void NS(MultiPole_set_bal)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, SIXTRL_INT64_T const order, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T const* SIXTRL_RESTRICT bal )
{
    SIXTRL_ASSERT( ( multipole != 0 ) && ( order > 0 ) && ( bal != 0 ) );    
    SIXTRACKLIB_COPY_VALUES( SIXTRL_REAL_T, multipole->bal, bal, 
                             ( 2 * order + 2 ) );
    
    return;
}

SIXTRL_INLINE void NS(MultiPole_assign_ptr_to_bal)(
    NS(MultiPole)* SIXTRL_RESTRICT multipole, 
    SIXTRL_GLOBAL_DEC SIXTRL_REAL_T* SIXTRL_RESTRICT ptr_to_bal )
{
    SIXTRL_ASSERT( multipole != 0 );
    multipole->bal = ptr_to_bal;
    
    return;
}

SIXTRL_INLINE SIXTRL_GLOBAL_DEC NS(MultiPole) const* 
NS(Blocks_get_const_multipole)(
    const NS(BlockInfo) *const SIXTRL_RESTRICT block_info )
{
    #if !defined( _GPUCODE )
    
    NS(BlockType) const type_id = 
        NS(BlockInfo_get_type_id)( block_info );
    
    SIXTRL_GLOBAL_DEC void const* ptr_begin = 
        NS(BlockInfo_get_const_ptr_begin)( block_info );    
    
    #else
    
    SIXTRL_GLOBAL_DEC void const* ptr_begin = 0;
    NS(BlockType) type_id = NS(BLOCK_TYPE_INVALID);    
    
    if( block_info != 0 )
    {
        NS(BlockInfo) const info = *block_info;
        ptr_begin = NS(BlockInfo_get_const_ptr_begin)( &info );
        type_id   = NS(BlockInfo_get_type_id)( &info );
    }
    
    #endif /* !defined( _GPUCODE ) */
    
    SIXTRL_ASSERT( ( ptr_begin == 0 ) ||
                   ( ( ( ( uintptr_t )ptr_begin ) % 8u ) == 0u ) );
    
    return ( type_id == NS(BLOCK_TYPE_MULTIPOLE) )
        ? ( SIXTRL_GLOBAL_DEC NS(MultiPole) const* )ptr_begin : 0;
}

SIXTRL_INLINE SIXTRL_GLOBAL_DEC NS(MultiPole)*
NS(Blocks_get_multipole)( NS(BlockInfo)* SIXTRL_RESTRICT block_info )
{
    return ( SIXTRL_GLOBAL_DEC NS(MultiPole)* )NS(Blocks_get_const_multipole)( 
        block_info );
}

#if !defined( _GPUCODE )
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_API_H__ */

/* end: sixtracklib/common/impl/beam_elements_api.h  */
