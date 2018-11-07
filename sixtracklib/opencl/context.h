#ifndef SIXTRACKLIB_OPENCL_CONTEXT_H__
#define SIXTRACKLIB_OPENCL_CONTEXT_H__

#if !defined( __CUDACC__ )

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <limits.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/opencl/internal/base_context.h"
    #include "sixtracklib/opencl/argument.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    class ClContext : public ClContextBase
    {
        private:

        using _base_context_t   = ClContextBase;

        public:

        using  num_turns_t      = SIXTRL_INT64_T;

        ClContext();

        explicit ClContext( size_type const node_index );
        explicit ClContext( node_id_t const node_id );
        explicit ClContext( char const* node_id_str );

        ClContext( platform_id_t const platform_idx,
                   device_id_t const device_idx );

        ClContext( ClContext const& other ) = delete;
        ClContext( ClContext&& other ) = delete;

        ClContext& operator=( ClContext const& other ) = delete;
        ClContext& operator=( ClContext&& other ) = delete;

        virtual ~ClContext() SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        bool hasTrackingKernel() const SIXTRL_NOEXCEPT;
        kernel_id_t trackingKernelId() const SIXTRL_NOEXCEPT;
        bool setTrackingKernelId( kernel_id_t const kernel_id );

        int track( num_turns_t const turn );
        int track( num_turns_t const turn, kernel_id_t const track_kernel_id );

        int track( ClArgument& SIXTRL_RESTRICT_REF particles_arg,
                   ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
                   num_turns_t const turn );

        int track( ClArgument& particles_arg, ClArgument& beam_elements_arg,
                   num_turns_t const turn, kernel_id_t const track_kernel_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        bool hasSingleTurnTrackingKernel() const SIXTRL_NOEXECPT;
        kernel_id_t singleTurnTackingKernelId() const SIXTRL_NOEXCEPT;
        bool setSingleTurnTrackingKernelId( kernel_id_t const track_kernel_id );

        int trackSingleTurn();

        int trackSingleTurn( kernel_id_t const track_kernel_id );

        int trackSingleTurn( ClArgument& SIXTRL_RESTRICT_REF particles_arg,
                             ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg );

        int trackSingleTurn( ClArgument& particles_arg,
                             ClArgument& beam_elements_arg,
                             kernel_id_t const track_kernel_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        bool hasElementByElementTrackingKernel() const SIXTRL_NOEXECEPT;
        kernel_id_t const elementByElementTrackingKernel() const SIXTRL_NOEXCEPT;
        bool setElementByElementTrackingKernelId(
            kernel_id_t const track_kernel_id );

        int trackElementByElement( size_type io_particle_block_offset );

        int trackElementByElement( size_type io_particle_block_offset,
                                   kernel_id_t const track_kernel_id );

        int trackElementByElement( ClArgument& SIXTRL_RESTRICT_REF particles_arg,
                                   ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
                                   ClArgument& SIXTRL_RESTRICT_REF elem_by_elem_buffer,
                                   size_type io_particle_block_offset,
                                   kernel_id_t const track_kernel_id );

        int trackElementByElement( ClArgument& SIXTRL_RESTRICT_REF particles_arg,
                                   ClArgument& SIXTRL_RESTRICT_REF beam_elements_arg,
                                   ClArgument& SIXTRL_RESTRICT_REF elem_by_elem_buffer,
                                   size_type io_particle_block_offset,
                                   kernel_id_t const track_kernel_id );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        bool hasAssignBeamMonitorIoBufferKernel() const SIXTRL_NOEXECEPT;
        kernel_id_t const assignBeamMonitorIoBufferKernelId() const SIXTRL_NOEXCEPT;
        bool setAssignBeamMonitorIoBufferKernelId(
            kernel_id_t const track_kernel_id );

        int assignBeamMonitorIoBuffer( ClArgument& SIXTRL_RESTRICT_REF io_buffer,
                                       size_type const io_particle_block_offset =
                                           size_type{ 0 } );

        int assignBeamMonitorIoBuffer( ClArgument& SIXTRL_RESTRICT_REF io_buffer,
                                       size_type const io_particle_block_offset,
                                       kernel_id_t const assign_kernel_id );

        protected:

        virtual bool doInitDefaultPrograms() override;
        virtual bool doInitDefaultKernels()  override;

        private:

        bool doInitDefaultProgramsPrivImpl();
        bool doInitDefaultKernelsPrivImpl();

        program_id_t m_track_until_turn_program_id;
        program_id_t m_track_single_turn_program_id;
        program_id_t m_track_elem_by_elem_program_id;
        program_id_t m_assign_be_mon_io_buffer_program_id;

        kernel_id_t  m_track_until_turn_kernel_id;
        kernel_id_t  m_track_single_turn_kernel_id;
        kernel_id_t  m_track_elem_by_elem_kernel_id;
        kernel_id_t  m_assign_be_mon_io_buffer_kernel_id;
    };
}

#if !defined( _GPUCODE )
extern "C" {
#endif /* !defined( _GPUCODE ) */

typedef SIXTRL_CXX_NAMESPACE::ClContext              NS(ClContext);
typedef SIXTRL_CXX_NAMESPACE::ClContext::num_turns_t NS(context_num_turns_t);

#if !defined( _GPUCODE )
}
#endif /* !defined( _GPUCODE ) */

#else /* !defined( __cplusplus ) */

typedef void NS(ClContext);
typedef SIXTRL_INT64_T NS(context_num_turns_t);

#endif /* defined( __cplusplus ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_HOST_FN NS(ClContext)* NS(ClContext_create)();
SIXTRL_HOST_FN NS(ClContext)* NS(ClContext_new)( const char* node_id_str );
SIXTRL_HOST_FN void NS(ClContext_delete)( NS(ClContext)* SIXTRL_RESTRICT ctx );
SIXTRL_HOST_FN void NS(ClContext_clear)(  NS(ClContext)* SIXTRL_RESTRICT ctx );

/* ========================================================================= */

SIXTRL_HOST_FN bool NS(ClContext_has_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN int NS(ClContext_get_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN bool NS(ClContext_set_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_HOST_FN int NS(ClContext_continue_tracking)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, NS(context_num_turns_t) const turn );

SIXTRL_HOST_FN int NS(ClContext_continue_tracking_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const track_kernel_id,
    NS(context_num_turns_t) const turn );

SIXTRL_HOST_FN int NS(ClContext_track(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(context_num_turns_t) const turn );

SIXTRL_HOST_FN int NS(ClContext_track_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT ptr_beam_elements_arg,
    NS(context_num_turns_t) const turn, int const tracking_kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN bool NS(ClContext_has_single_turn_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN int NS(ClContext_get_single_turn_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN bool NS(ClContext_set_single_turn_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const tracking_kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_HOST_FN int NS(ClContext_continue_tracking_single_turn)(
    NS(ClContext)* SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN int NS(ClContext_continue_tracking_single_turn_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id );

SIXTRL_HOST_FN int NS(ClContext_continue_track_single_turn)(
    NS(ClContext)* SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN int NS(ClContext_continue_track_single_turn_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const tracking_kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN bool NS(ClContext_has_element_by_element_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN int NS(ClContext_get_element_by_element_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN bool NS(ClContext_set_element_by_element_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const tracking_kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_HOST_FN int NS(ClContext_continue_tracking_element_by_element)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const io_particle_block_offset );

SIXTRL_HOST_FN int NS(ClContext_continue_tracking_element_by_element_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const io_particle_block_offset,
    int const kernel_id );

SIXTRL_HOST_FN int NS(ClContext_track_element_by_element)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const io_particle_block_offset );

SIXTRL_HOST_FN int NS(ClContext_track_element_by_element_with_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(buffer_size_t) const io_particle_block_offset,
    int const tracking_kernel_id );

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN bool NS(ClContext_has_assign_beam_monitor_io_buffer_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN int NS(ClContext_get_assign_beam_monitor_io_buffer_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx );

SIXTRL_HOST_FN bool NS(ClContext_set_assign_beam_monitor_io_buffer_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx,
    int const assign_kernel_id );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_HOST_FN int NS(ClContext_assign_beam_monitor_io_buffer)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT io_buffer,
    NS(buffer_size_t) const io_particle_block_offset );

SIXTRL_HOST_FN int NS(ClContext_assign_beam_monitor_io_buffer_with_kernel_id)(
    NS(ClContext)*  SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT io_buffer,
    NS(buffer_size_t) const io_particle_block_offset,
    int const assign_kernel_id );

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* !defined( __CUDACC__ ) */

#endif /* SIXTRACKLIB_OPENCL_CONTEXT_H__ */

/* end: sixtracklib/opencl/context.h */
