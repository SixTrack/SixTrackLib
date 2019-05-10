#ifndef SIXTRACKLIB_CUDA_IMPL_TRACK_PARTICLES_KERNEL_CUDA_HEADER_CUH__
#define SIXTRACKLIB_CUDA_IMPL_TRACK_PARTICLES_KERNEL_CUDA_HEADER_CUH__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/internal/buffer_main_defines.h"
    #include "sixtracklib/common/output/elem_by_elem_config.h"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */

__global__ void NS(CudaTrack_particles_until_turn_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elem_buffer,
    NS(buffer_size_t) const slot_size,
    NS(buffer_size_t) const until_turn );

__global__ void NS(CudaTrack_particles_until_turn_debug_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elem_buffer,
    NS(buffer_size_t) const slot_size,
    NS(buffer_size_t) const until_turn,
    SIXTRL_DATAPTR_DEC NS(cuda_success_flag_t)* SIXTRL_RESTRICT success_flag );

/* ------------------------------------------------------------------------- */

__global__ void NS(CudaTrack_track_elem_by_elem_until_turn_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elem_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const slot_size,
    SIXTRL_DATAPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICt elem_by_elem_config,
    NS(buffer_size_t) const out_buffer_offset_index,
    NS(buffer_size_t) const until_turn );

__global__ void NS(CudaTrack_track_elem_by_elem_until_turn_debug_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elem_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const slot_size,
    SIXTRL_DATAPTR_DEC const NS(ElemByElemConfig)
        *const SIXTRL_RESTRICt elem_by_elem_config,
    NS(buffer_size_t) const out_buffer_offset_index,
    NS(buffer_size_t) const until_turn,
    SIXTRL_DATAPTR_DEC NS(cuda_success_flag_t)* SIXTRL_RESTRICT success_flag );

/* ------------------------------------------------------------------------- */

__global__ void NS(CudaTrack_particles_line_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elem_buffer,
    NS(buffer_size_t) const slot_size,
    NS(buffer_size_t) const belem_begin_id,
    NS(buffer_size_t) const belem_end_id,
    bool const finish_turn );

__global__ void NS(CudaTrack_particles_line_debug_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elem_buffer,
    NS(buffer_size_t) const slot_size,
    NS(buffer_size_t) const belem_begin_id,
    NS(buffer_size_t) const belem_end_id,
    bool const finish_turn,
    SIXTRL_DATAPTR_DEC NS(cuda_success_flag_t)* SIXTRL_RESTRICT success_flag );

/* ------------------------------------------------------------------------- */

__global__ void NS(Cuda_assign_output_to_be_monitors_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elem_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const slot_size,
    NS(particle_index_t) const min_turn_id,
    NS(buffer_size_t) const out_buffer_offset_index );

__global__ void NS(Cuda_assign_output_to_be_monitors_debug_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT beam_elem_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT output_buffer,
    NS(buffer_size_t) const slot_size,
    NS(particle_index_t) const min_turn_id,
    NS(buffer_size_t) const out_buffer_offset_index,
    SIXTRL_DATAPTR_DEC NS(cuda_success_flag_t)* SIXTRL_RESTRICT success_flag );

/* ------------------------------------------------------------------------- */

__global__ void NS(Cuda_fetch_particle_addresses_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT paddr_buffer,
    NS(buffer_size_t) const slot_size );

__global__ void NS(Cuda_fetch_particle_addresses_debug_kernel)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT particles_buffer,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT paddr_buffer,
    NS(buffer_size_t) const slot_size,
    SIXTRL_DATAPTR_DEC NS(cuda_success_flag_t)* SIXTRL_RESTRICT success_flag );

/* ------------------------------------------------------------------------- */

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKLIB_CUDA_IMPL_TRACK_PARTICLES_KERNEL_CUDA_HEADER_CUH__ */

/* end sixtracklib/cuda/impl/track_particles_kernel.cuh */
