#ifndef SIXTRACKLIB_OPENCL_KERNELS_BE_MONITORS_ASSIGN_IO_BUFFER_CL__
#define SIXTRACKLIB_OPENCL_KERNELS_BE_MONITORS_ASSIGN_IO_BUFFER_CL__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/internal/default_compile_options.h"

    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer/managed_buffer_minimal.h"
    #include "sixtracklib/common/buffer/managed_buffer_remap.h"
    #include "sixtracklib/common/internal/particles_defines.h"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/track.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

__kernel void NS(BeamMonitor_assign_io_buffer_from_offset_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elements_buf,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT io_buffer,
    unsigned long const num_particles,
    unsigned long const io_particles_block_offset );

/* ========================================================================= */

__kernel void NS(BeamMonitor_assign_io_buffer_from_offset_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elements_buf,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT io_buffer,
    unsigned long const num_particles,
    unsigned long const io_particles_block_offset )
{
    typedef NS(buffer_size_t) buf_size_t;

    size_t const global_id               = get_global_id( 0 );
    size_t const global_size             = get_global_size( 0 );
    size_t const gid_to_assign_io_buffer = ( size_t )0u;

    if( global_id == gid_to_assign_io_buffer )
    {
        size_t const slot_size = ( size_t )8u;

        NS(BeamMonitor_assign_io_buffer_from_offset)(
            beam_elements_buffer, io_buffer, num_particles,
                io_particles_block_offset );
    }

    return;
}

#endif /* SIXTRACKLIB_OPENCL_KERNELS_BE_MONITORS_ASSIGN_IO_BUFFER_CL__ */

/* end: sixtracklib/opencl/kernels/be_monitors_assign_io_buffer.cl */
