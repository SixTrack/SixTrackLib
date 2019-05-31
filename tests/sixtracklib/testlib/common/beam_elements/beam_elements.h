#ifndef SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_HEADER_H__
#define SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_HEADER_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdio.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/internal/beam_elements_defines.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

struct NS(Drift);
struct NS(DriftExact);
struct NS(MultiPole);
struct NS(XYShift);
struct NS(SRotation);
struct NS(Cavity);
struct NS(BeamBeam4D);
struct NS(BeamBeam6D);
struct NS(BeamMonitor);

struct NS(Object);

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC SIXTRL_FN void NS(Drift_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(Drift) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(DriftExact_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(DriftExact) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(MultiPole_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(MultiPole) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(XYShift_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(XYShift) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(SRotation_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(SRotation) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(Cavity_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(Cavity) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(BeamBeam4D_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam4D) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(BeamBeam6D_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam6D) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(BeamMonitor_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamMonitor) *const SIXTRL_RESTRICT e );

SIXTRL_STATIC SIXTRL_FN void NS(BeamElement_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(Object) *const SIXTRL_RESTRICT be_info );

SIXTRL_STATIC SIXTRL_FN int NS(BeamElements_compare_objects)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT rhs );

SIXTRL_STATIC SIXTRL_FN int NS(BeamElements_compare_objects_with_treshold)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT rhs,
    SIXTRL_REAL_T const treshold );

SIXTRL_STATIC SIXTRL_FN int NS(BeamElements_compare_lines)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT rhs_begin );

SIXTRL_STATIC SIXTRL_FN int NS(BeamElements_compare_lines_with_treshold)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT begin,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT rhs_begin,
    SIXTRL_REAL_T const treshold );

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Drift_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(Drift) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(DriftExact_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(DriftExact) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(MultiPole_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(MultiPole) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(XYShift_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(XYShift) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(SRotation_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(SRotation) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Cavity_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(Cavity) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BeamBeam4D_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam4D) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BeamBeam6D_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam6D) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BeamMonitor_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamMonitor) *const SIXTRL_RESTRICT e );


SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BeamElement_print_out)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(Object) *const SIXTRL_RESTRICT info );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Drift_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(Drift) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(DriftExact_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(DriftExact) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(MultiPole_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(MultiPole) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(XYShift_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(XYShift) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(SRotation_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(SRotation) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Cavity_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(Cavity) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BeamBeam4D_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam4D) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BeamBeam6D_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam6D) *const SIXTRL_RESTRICT e );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BeamMonitor_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamMonitor) *const SIXTRL_RESTRICT e );


SIXTRL_EXTERN SIXTRL_HOST_FN void NS(BeamElement_fprint)(
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    SIXTRL_BE_ARGPTR_DEC  const struct NS(Object) *const SIXTRL_RESTRICT info );

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ========================================================================= *
 * ======== INLINE IMPLEMENTATION                                            *
 * ========================================================================= */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/beam_elements.h"
    
    #include "sixtracklib/testlib/common/be_limit_rect.h"
    #include "sixtracklib/testlib/common/be_limit_ellipse.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE void NS(Drift_print)(
    SIXTRL_ARGPTR_DEC const NS(Drift) *const SIXTRL_RESTRICT drift )
{
    printf( "|drift            | length   = %+16.12f m;\r\n",
            NS(Drift_get_length)( drift ) );

    return;
}

SIXTRL_INLINE void NS(DriftExact_print)(
    SIXTRL_ARGPTR_DEC const NS(DriftExact) *const SIXTRL_RESTRICT drift )
{
    printf( "|drift exact      | length   = %+16.12f m;\r\n",
            NS(DriftExact_get_length)( drift ) );

    return;
}

SIXTRL_INLINE void NS(MultiPole_print)(
    SIXTRL_ARGPTR_DEC const NS(MultiPole) *const SIXTRL_RESTRICT mp )
{
    typedef NS(multipole_order_t) mp_order_t;

    mp_order_t const order = NS(MultiPole_get_order)( mp );

    printf( "|multipole        | order    = %3d;\r\n"
            "                  | length   = %+16.12f m;\r\n"
            "                  | hxl      = %+16.12f m;\r\n"
            "                  | hyl      = %+16.12f m;\r\n",
            ( int )order, NS(MultiPole_get_length)( mp ),
            NS(MultiPole_get_hxl)( mp ), NS(MultiPole_get_hyl)( mp ) );

    if( order >= ( mp_order_t )0 )
    {
        mp_order_t ii = ( mp_order_t )0;
        mp_order_t const num_k_values = order + ( mp_order_t )1;

        for( ; ii < num_k_values ; ++ii )
        {
            printf( "                  |"
                    "knl[ %3d ] = %+20.12f ; ksl[ %3d ] = %+20.12f \r\n",
                    ( int )ii, NS(MultiPole_get_knl_value)( mp, ii ),
                    ( int )ii, NS(MultiPole_get_ksl_value)( mp, ii ) );
        }
    }
    else
    {
        printf( "                  | knl = n/a ; ksl = n/a\r\n" );
    }

    return;
}

SIXTRL_INLINE void NS(XYShift_print)(
    SIXTRL_ARGPTR_DEC const NS(XYShift) *const SIXTRL_RESTRICT xy_shift )
{
    printf( "|xy_shift         | dx       = %+16.12f m;\r\n"
            "                  | dy       = %+16.12f m;\r\n",
            NS(XYShift_get_dx)( xy_shift ),
            NS(XYShift_get_dy)( xy_shift ) );

    return;
}

SIXTRL_INLINE void NS(SRotation_print)(
    SIXTRL_ARGPTR_DEC const NS(SRotation) *const SIXTRL_RESTRICT srot )
{
    printf( "|srotation        | angle    = %+16.12f deg  ( %+16.12f rad )\r\n"
            "                  | cos_z    = %+13.12f;\r\n"
            "                  | sin_z    = %+13.12f;\r\n",
            NS(SRotation_get_angle_deg)( srot ),
            NS(SRotation_get_angle)( srot ),
            NS(SRotation_get_cos_angle)( srot ),
            NS(SRotation_get_sin_angle)( srot ) );

    return;
}

SIXTRL_INLINE void NS(Cavity_print)(
    SIXTRL_ARGPTR_DEC const NS(Cavity) *const SIXTRL_RESTRICT cav )
{
    printf( "|cavity           | voltage   = %+16.12f V   \r\n"
            "                  | frequency = %+20.12f Hz; \r\n"
            "                  | lag       = %+15.12f deg;\r\n",
            NS(Cavity_get_voltage)( cav ),
            NS(Cavity_get_frequency)( cav ),
            NS(Cavity_get_lag)( cav ) );

    return;
}

SIXTRL_INLINE void NS(BeamBeam4D_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam4D) *const SIXTRL_RESTRICT bb4d )
{
    typedef NS(beambeam4d_real_const_ptr_t)  bb_data_ptr_t;
    typedef SIXTRL_BE_DATAPTR_DEC BB4D_data* BB4D_data_ptr_t;

    bb_data_ptr_t data = NS(BeamBeam4D_get_const_data)( bb4d );
    BB4D_data_ptr_t bb4ddata = (BB4D_data_ptr_t) data;

    SIXTRL_ASSERT( bb4ddata != SIXTRL_NULLPTR );

    printf( "|beambeam4d      | q_part         = %+20e\r\n"
            "                 | N_part         = %+20e\r\n"
            "                 | sigma_x        = %+20.12f\r\n"
            "                 | sigma_y        = %+20.12f\r\n"
            "                 | beta_s         = %+20.12f\r\n"
            "                 | min_sigma_diff = %+20.12f\r\n"
            "                 | Delta_x        = %+20.12f\r\n"
            "                 | Delta_y        = %+20.12f\r\n"
            "                 | Dpx_sub        = %+20.12f\r\n"
            "                 | Dpy_sub        = %+20.12f\r\n"
            "                 | enabled        = %20ld\r\n",
            bb4ddata->q_part,  bb4ddata->N_part,  bb4ddata->sigma_x,
            bb4ddata->sigma_y, bb4ddata->beta_s,  bb4ddata->min_sigma_diff,
            bb4ddata->Delta_x, bb4ddata->Delta_y, bb4ddata->Dpx_sub,
            bb4ddata->Dpy_sub, ( long int )bb4ddata->enabled );

    return;
}

SIXTRL_INLINE void NS(BeamBeam6D_print)(
    SIXTRL_BE_ARGPTR_DEC const struct NS(BeamBeam6D) *const SIXTRL_RESTRICT bb6d )
{
    typedef SIXTRL_REAL_T                       real_t;
    typedef NS(beambeam6d_real_const_ptr_t)     bb_data_ptr_t;
    typedef SIXTRL_BE_DATAPTR_DEC BB6D_data*    BB6D_data_ptr_t;
    typedef SIXTRL_BE_DATAPTR_DEC real_t const* ptr_real_t;

    bb_data_ptr_t data = NS(BeamBeam6D_get_const_data)( bb6d );
    BB6D_data_ptr_t bb6ddata = (BB6D_data_ptr_t) data;

    if( ( bb6ddata != SIXTRL_NULLPTR ) && ( bb6ddata->enabled ) )
    {
        int num_slices = (int)(bb6ddata->N_slices);
        int ii = 0;

        ptr_real_t N_part_per_slice =
            SIXTRL_BB_GET_PTR(bb6ddata, N_part_per_slice);

        ptr_real_t x_slices_star =
            SIXTRL_BB_GET_PTR(bb6ddata, x_slices_star);

        ptr_real_t y_slices_star =
            SIXTRL_BB_GET_PTR(bb6ddata, y_slices_star);

        ptr_real_t sigma_slices_star =
            SIXTRL_BB_GET_PTR(bb6ddata, sigma_slices_star);

        SIXTRL_ASSERT( N_part_per_slice  != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( x_slices_star     != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( y_slices_star     != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( sigma_slices_star != SIXTRL_NULLPTR );

        printf( "|beambeam6d      | enabled                = %20ld\r\n"
                "                 | sphi                   = %+20e\r\n"
                "                 | calpha                 = %+20e\r\n"
                "                 | S33                    = %+20.12f\r\n"
                "                 | N_slices               = %+20d\r\n",
                ( long int )bb6ddata->enabled,
                (bb6ddata->parboost).sphi, (bb6ddata->parboost).calpha,
                (bb6ddata->Sigmas_0_star).Sig_33_0, num_slices );

        for( ; ii < num_slices ; ++ii )
        {
            printf( ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . "
                    ". . . . . . . . . . . . . . . . . . . . . . . . . . . . \r\n"
                    "                 | N_part_per_slice[%4d]  = %20e\r\n"
                    "                 | x_slices_star[%4d]     = %20.12f\r\n"
                    "                 | y_slices_star[%4d]     = %20.12f\r\n"
                    "                 | sigma_slices_star[%4d] = %20.12f\r\n",
                    ii, N_part_per_slice[ ii ],
                    ii, x_slices_star[ ii ],
                    ii, y_slices_star[ ii ],
                    ii, sigma_slices_star[ ii ] );
        }
    }
    else
    {
        printf( "|beambeam6d      | enabled                = %20ld\r\n",
                ( long int )0 );
    }

    return;
}

SIXTRL_INLINE void NS(BeamMonitor_print)(
    SIXTRL_ARGPTR_DEC const NS(BeamMonitor) *const SIXTRL_RESTRICT monitor )
{
    int const is_rolling =
        NS(BeamMonitor_is_rolling)( monitor ) ? 1 : 0;

    int const is_turn_ordered =
        NS(BeamMonitor_is_turn_ordered)( monitor ) ? 1 : 0;

    SIXTRL_ASSERT( monitor != SIXTRL_NULLPTR );

    printf( "|beam-monitor     | num stores       = %20d\r\n"
            "                  | start turn       = %20d\r\n"
            "                  | skip turns       = %20d\r\n"
            "                  | out_address      = %20lu\r\n"
            "                  | min_particle_id  = %20d\r\n"
            "                  | max_particle_id  = %20d\r\n"
            "                  | is_rolling       = %20d\r\n"
            "                  | is_turn_ordered  = %20d\r\n",
            ( int )NS(BeamMonitor_get_num_stores)( monitor ),
            ( int )NS(BeamMonitor_get_start)( monitor ),
            ( int )NS(BeamMonitor_get_skip)( monitor ),
            ( unsigned long )NS(BeamMonitor_get_out_address)( monitor ),
            ( int )NS(BeamMonitor_get_min_particle_id)( monitor ),
            ( int )NS(BeamMonitor_get_max_particle_id)( monitor ),
            is_rolling, is_turn_ordered );

    return;
}

SIXTRL_INLINE void NS(BeamElement_print)(
    SIXTRL_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT be_info )
{
    if( be_info != SIXTRL_NULLPTR )
    {
        NS(object_type_id_t) const type_id = NS(Object_get_type_id)( be_info );
        NS(buffer_addr_t) const addr = NS(Object_get_begin_addr)( be_info );

        switch( type_id )
        {
            case NS(OBJECT_TYPE_DRIFT):
            {
                typedef NS(Drift) beam_element_t;
                typedef SIXTRL_DATAPTR_DEC beam_element_t const* ptr_belem_t;

                ptr_belem_t beam_element = ( ptr_belem_t )( uintptr_t )addr;

                SIXTRL_ASSERT( sizeof( beam_element_t ) <=
                               NS(Object_get_size)( be_info ) );

                NS(Drift_print)( beam_element );

                break;
            }

            case NS(OBJECT_TYPE_DRIFT_EXACT):
            {
                typedef NS(DriftExact) beam_element_t;
                typedef SIXTRL_DATAPTR_DEC beam_element_t const* ptr_belem_t;

                ptr_belem_t beam_element = ( ptr_belem_t )( uintptr_t )addr;

                SIXTRL_ASSERT( sizeof( beam_element_t ) <=
                               NS(Object_get_size)( be_info ) );

                NS(DriftExact_print)( beam_element );

                break;
            }

            case NS(OBJECT_TYPE_MULTIPOLE):
            {
                typedef NS(MultiPole) beam_element_t;
                typedef SIXTRL_DATAPTR_DEC beam_element_t const* ptr_belem_t;

                ptr_belem_t beam_element = ( ptr_belem_t )( uintptr_t )addr;

                SIXTRL_ASSERT( sizeof( beam_element_t ) <=
                               NS(Object_get_size)( be_info ) );

                NS(MultiPole_print)( beam_element );

                break;
            }

            case NS(OBJECT_TYPE_CAVITY):
            {
                typedef NS(Cavity) beam_element_t;
                typedef SIXTRL_DATAPTR_DEC beam_element_t const* ptr_belem_t;

                ptr_belem_t beam_element = ( ptr_belem_t )( uintptr_t )addr;

                SIXTRL_ASSERT( sizeof( beam_element_t ) <=
                               NS(Object_get_size)( be_info ) );

                NS(Cavity_print)( beam_element );

                break;
            }

            case NS(OBJECT_TYPE_XYSHIFT):
            {
                typedef NS(XYShift) beam_element_t;
                typedef SIXTRL_DATAPTR_DEC beam_element_t const* ptr_belem_t;

                ptr_belem_t beam_element = ( ptr_belem_t )( uintptr_t )addr;

                SIXTRL_ASSERT( sizeof( beam_element_t ) <=
                               NS(Object_get_size)( be_info ) );

                NS(XYShift_print)( beam_element );

                break;
            }

            case NS(OBJECT_TYPE_SROTATION):
            {
                typedef NS(SRotation) beam_element_t;
                typedef SIXTRL_DATAPTR_DEC beam_element_t const* ptr_belem_t;

                ptr_belem_t beam_element = ( ptr_belem_t )( uintptr_t )addr;

                SIXTRL_ASSERT( sizeof( beam_element_t ) <=
                               NS(Object_get_size)( be_info ) );

                NS(SRotation_print)( beam_element );

                break;
            }

            case NS(OBJECT_TYPE_BEAM_BEAM_4D):
            {
                typedef SIXTRL_DATAPTR_DEC NS(BeamBeam4D) const* 
                        ptr_to_belem_t;                
                
                ptr_to_belem_t beam_element = 
                    ( ptr_to_belem_t )( uintptr_t )addr;

                NS(BeamBeam4D_print)( beam_element );
                break;
            }

            case NS(OBJECT_TYPE_BEAM_BEAM_6D):
            {
                typedef SIXTRL_DATAPTR_DEC NS(BeamBeam6D) const* 
                        ptr_to_belem_t;
                        
                ptr_to_belem_t beam_element = 
                    ( ptr_to_belem_t )( uintptr_t )addr;

                NS(BeamBeam6D_print)( beam_element );
                break;
            }

            case NS(OBJECT_TYPE_BEAM_MONITOR):
            {
                typedef SIXTRL_DATAPTR_DEC NS(BeamMonitor) const* 
                        ptr_to_belem_t;
                        
                ptr_to_belem_t beam_element = 
                    ( ptr_to_belem_t )( uintptr_t )addr;

                NS(BeamMonitor_print)( beam_element );
                break;
            }
            
            case NS(OBJECT_TYPE_LIMIT_RECT):
            {
                typedef SIXTRL_DATAPTR_DEC NS(LimitRect) const* ptr_to_belem_t;
                
                ptr_to_belem_t beam_element = 
                    ( ptr_to_belem_t )( uintptr_t )addr;

                NS(LimitRect_print_out)( beam_element );                
                break;
            }
            
            case NS(OBJECT_TYPE_LIMIT_ELLIPSE):
            {
                typedef SIXTRL_DATAPTR_DEC NS(LimitEllipse) const* 
                        ptr_to_belem_t;
                        
                ptr_to_belem_t beam_element = 
                    ( ptr_to_belem_t )( uintptr_t )addr;

                NS(LimitEllipse_print_out)( beam_element );
                break;
            }
            
            case NS(OBJECT_TYPE_DIPEDGE):
            {
                /* typedef SIXTRL_DATAPTR_DEC NS(LimitEllipse) const* 
                           ptr_to_belem_t;
                 
                ptr_to_belem_t beam_element = 
                    ( ptr_to_belem_t )( uintptr_t )addr;

                NS(DipoleEdge_print_out)( beam_element ); */
                break;
            }

            default:
            {
                printf( "|unknown          | type_id  = %3d;\r\n"
                        "                  | size     = %8lu bytes;\r\n"
                        "                  | addr     = %16p;\r\n",
                        ( int )type_id, NS(Object_get_size)( be_info ),
                        ( void const* )( uintptr_t )addr );
            }
        };
    }

    return;
}


SIXTRL_INLINE int NS(BeamElements_compare_objects)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT rhs )
{
    int compare_value = -1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        typedef NS(buffer_addr_t)       address_t;
        typedef NS(object_type_id_t)    type_id_t;

        type_id_t const lhs_type_id = NS(Object_get_type_id)( lhs );

        type_id_t const rhs_type_id = NS(Object_get_type_id)( rhs );

        if( lhs_type_id == rhs_type_id )
        {
            address_t const lhs_addr = NS(Object_get_begin_addr)( lhs );
            address_t const rhs_addr = NS(Object_get_begin_addr)( rhs );

            if( ( lhs_addr != ( address_t)0u ) &&
                ( rhs_addr != ( address_t)0u ) && ( lhs_addr != rhs_addr ) )
            {
                switch( lhs_type_id )
                {
                    case NS(OBJECT_TYPE_DRIFT):
                    {
                        typedef NS(Drift)                           belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(Drift_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    case NS(OBJECT_TYPE_DRIFT_EXACT):
                    {
                        typedef NS(DriftExact)                       belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const*  ptr_belem_t;

                        compare_value = NS(DriftExact_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    case NS(OBJECT_TYPE_MULTIPOLE):
                    {
                        typedef NS(MultiPole)                       belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(MultiPole_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    case NS(OBJECT_TYPE_XYSHIFT):
                    {
                        typedef NS(XYShift)                          belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const*  ptr_belem_t;

                        compare_value = NS(XYShift_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    case NS(OBJECT_TYPE_SROTATION):
                    {
                        typedef NS(SRotation)                        belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const*  ptr_belem_t;

                        compare_value = NS(SRotation_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    case NS(OBJECT_TYPE_CAVITY):
                    {
                        typedef NS(Cavity)                           belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const*  ptr_belem_t;

                        compare_value = NS(Cavity_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    #if !defined( SIXTRL_DISABLE_BEAM_BEAM )

                    case NS(OBJECT_TYPE_BEAM_BEAM_4D):
                    {
                        typedef NS(BeamBeam4D)                      belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(BeamBeam4D_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    case NS(OBJECT_TYPE_BEAM_BEAM_6D):
                    {
                        typedef NS(BeamBeam6D)                      belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(BeamBeam6D_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    #endif /* !defined( SIXTRL_DISABLE_BEAM_BEAM ) */

                    case NS(OBJECT_TYPE_BEAM_MONITOR):
                    {
                        typedef NS(BeamMonitor)                      belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const*  ptr_belem_t;

                        compare_value = NS(BeamMonitor_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    case NS(OBJECT_TYPE_LIMIT):
                    {
                        typedef NS(Limit) belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const*  ptr_belem_t;

                        compare_value = NS(Limit_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }
                    
                    case NS(OBJECT_TYPE_DIPEDGE):
                    {
                        typedef NS(DipoleEdge) belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const*  ptr_belem_t;

                        compare_value = NS(DipoleEdge_compare_values)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr );

                        break;
                    }

                    default:
                    {
                        compare_value = -1;
                    }
                };
            }
            else if( lhs_addr != ( address_t )0u )
            {
                compare_value = ( rhs_addr != lhs_addr ) ? +1 : 0;
            }
            else if( rhs_addr != ( address_t )0u )
            {
                compare_value = ( rhs_addr != lhs_addr ) ? -1 : 0;
            }
        }
        else if( lhs_type_id > rhs_type_id )
        {
            compare_value = +1;
        }
    }

    return compare_value;
}

SIXTRL_INLINE int NS(BeamElements_compare_objects_with_treshold)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT lhs,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC const NS(Object) *const SIXTRL_RESTRICT rhs,
    SIXTRL_REAL_T const treshold )
{
    int compare_value = -1;

    if( ( lhs != SIXTRL_NULLPTR ) && ( rhs != SIXTRL_NULLPTR ) )
    {
        typedef NS(buffer_addr_t)       address_t;
        typedef NS(object_type_id_t)    type_id_t;

        type_id_t const lhs_type_id = NS(Object_get_type_id)( lhs );

        type_id_t const rhs_type_id = NS(Object_get_type_id)( rhs );

        if( lhs_type_id == rhs_type_id )
        {
            address_t const lhs_addr = NS(Object_get_begin_addr)( lhs );
            address_t const rhs_addr = NS(Object_get_begin_addr)( rhs );

            if( ( lhs_addr != ( address_t)0u ) &&
                ( rhs_addr != ( address_t)0u ) && ( lhs_addr != rhs_addr ) )
            {
                switch( lhs_type_id )
                {
                    case NS(OBJECT_TYPE_DRIFT):
                    {
                        typedef NS(Drift)                            belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const*  ptr_belem_t;

                        compare_value = NS(Drift_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            treshold );

                        break;
                    }

                    case NS(OBJECT_TYPE_DRIFT_EXACT):
                    {
                        typedef NS(DriftExact)                      belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(DriftExact_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            treshold  );

                        break;
                    }

                    case NS(OBJECT_TYPE_MULTIPOLE):
                    {
                        typedef NS(MultiPole)                       belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(MultiPole_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            treshold  );

                        break;
                    }

                    case NS(OBJECT_TYPE_XYSHIFT):
                    {
                        typedef NS(XYShift)                         belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(XYShift_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            treshold  );

                        break;
                    }

                    case NS(OBJECT_TYPE_SROTATION):
                    {
                        typedef NS(SRotation)                       belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(SRotation_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            treshold  );

                        break;
                    }

                    case NS(OBJECT_TYPE_CAVITY):
                    {
                        typedef NS(Cavity)                          belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(Cavity_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            treshold  );

                        break;
                    }

                    #if !defined( SIXTRL_DISABLE_BEAM_BEAM )

                    case NS(OBJECT_TYPE_BEAM_BEAM_4D):
                    {
                        typedef NS(BeamBeam4D)                      belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(BeamBeam4D_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr, treshold );

                        break;
                    }

                    case NS(OBJECT_TYPE_BEAM_BEAM_6D):
                    {
                        typedef NS(BeamBeam6D)                      belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(BeamBeam6D_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr, treshold );

                        break;
                    }

                    #endif /* !defined( SIXTRL_DISABLE_BEAM_BEAM ) */

                    case NS(OBJECT_TYPE_BEAM_MONITOR):
                    {
                        typedef NS(BeamMonitor)                          belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(BeamMonitor_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            treshold  );

                        break;
                    }

                    case NS(OBJECT_TYPE_LIMIT):
                    {
                        typedef NS(Limit) belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = NS(Limit_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            treshold  );

                        break;
                    }
                    
                    case NS(OBJECT_TYPE_DIPEDGE):
                    {
                        typedef NS(DipoleEdge) belem_t;
                        typedef SIXTRL_BE_ARGPTR_DEC belem_t const* ptr_belem_t;

                        compare_value = 
                        NS(DipoleEdge_compare_values_with_treshold)(
                            ( ptr_belem_t )( uintptr_t )lhs_addr,
                            ( ptr_belem_t )( uintptr_t )rhs_addr,
                            treshold  );

                        break;
                    }

                    default:
                    {
                        compare_value = -1;
                    }
                };
            }
            else if( lhs_addr != ( address_t )0u )
            {
                compare_value = ( rhs_addr != lhs_addr ) ? +1 : 0;
            }
            else if( rhs_addr != ( address_t )0u )
            {
                compare_value = ( rhs_addr != lhs_addr ) ? -1 : 0;
            }
        }
        else if( lhs_type_id > rhs_type_id )
        {
            compare_value = +1;
        }
    }

    return compare_value;
}


SIXTRL_INLINE int NS(BeamElements_compare_lines)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT rhs_it )
{
    int compare_value = -1;

    if( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) )
    {
        SIXTRL_ASSERT( ( ptrdiff_t )( lhs_end - lhs_it) > 0 );

        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
        {
            compare_value = NS(BeamElements_compare_objects)( lhs_it, rhs_it );

            if( 0 != compare_value )
            {
                break;
            }
        }
    }

    return compare_value;
}

SIXTRL_INLINE int NS(BeamElements_compare_lines_with_treshold)(
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT lhs_it,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT lhs_end,
    SIXTRL_BUFFER_OBJ_ARGPTR_DEC NS(Object) const* SIXTRL_RESTRICT rhs_it,
    SIXTRL_REAL_T const treshold )
{
    int compare_value = -1;

    if( ( lhs_it != SIXTRL_NULLPTR ) && ( lhs_end != SIXTRL_NULLPTR ) &&
        ( rhs_it != SIXTRL_NULLPTR ) )
    {
        SIXTRL_ASSERT( ( ptrdiff_t )( lhs_end - lhs_it) > 0 );

        for( ; lhs_it != lhs_end ; ++lhs_it, ++rhs_it )
        {
            compare_value = NS(BeamElements_compare_objects_with_treshold)(
                lhs_it, rhs_it, treshold );

            if( 0 != compare_value )
            {
                break;
            }
        }
    }

    return compare_value;
}

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_COMMON_BEAM_ELEMENTS_HEADER_H__ */

/* end: tests/sixtracklib/testlib/common/beam_elements.h */
