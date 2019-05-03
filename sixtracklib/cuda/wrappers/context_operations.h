#ifndef SIXTRACKLIB_CUDA_WRAPPERS_CONTEXT_OPERATIONS_H__
#define SIXTRACKLIB_CUDA_WRAPPERS_CONTEXT_OPERATIONS_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdint.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/cuda/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
extern "C" {
#endif /* C++, Host */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(controller_status_t)
NS(CudaContext_perform_send)(
    NS(cuda_arg_buffer_t) SIXTRL_RESTRICT destination,
    const void *const SIXTRL_RESTRICT source_begin,
    NS(controller_size_t) const source_length );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(controller_status_t)
NS(CudaContext_perform_receive)(
    void* SIXTRL_RESTRICT destination,
    NS(controller_size_t) const destination_capacity,
    NS(cuda_arg_buffer_t) SIXTRL_RESTRICT source,
    NS(controller_size_t) const source_length );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(controller_status_t)
NS(CudaContext_perform_remap_send_cobject_buffer_on_grid)(
    NS(cuda_arg_buffer_t) SIXTRL_RESTRICT arg_buffer,
    NS(controller_size_t) const slot_size,
    NS(buffer_size_t) const grid_num_blocks,
    NS(controller_size_t) const grid_threads_per_block );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(controller_status_t)
NS(CudaContext_perform_remap_send_cobject_buffer)(
    NS(cuda_arg_buffer_t) SIXTRL_RESTRICT arg_buffer,
    NS(buffer_size_t) const slot_size );

/* ------------------------------------------------------------------------ */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
}
#endif /* !defined(  _GPUCODE ) && defined( __cplusplus ) */

#endif /* SIXTRACKLIB_CUDA_WRAPPERS_CONTEXT_OPERATIONS_H__ */

/* end: sixtracklib/cuda/wrappers/context_operations.h */
