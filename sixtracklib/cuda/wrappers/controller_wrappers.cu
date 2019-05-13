#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/cuda/wrappers/controller_wrappers.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#include !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <cuda_runtime_api.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/buffer/buffer_type.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/kernel_config_base.h"

    #include "sixtracklib/cuda/definitions.h"
    #include "sixtracklib/cuda/argument.h"
    #include "sixtracklib/cuda/control/kernel_config.h"
    #include "sixtracklib/cuda/kernels/managed_buffer_remap.cuh"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

void NS(Buffer_remap_cuda_wrapper)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT kernel_config,
    NS(CudaArgument)* SIXTRL_RESTRICT buffer_arg )
{
    dim3 const* ptr_blocks =
        NS(CudaKernelConfig_get_ptr_const_blocks)( kernel_config );

    dim3 const* ptr_threads =
        NS(CudaKernelConfig_get_ptr_const_threads_per_block)( kernel_config );

    /* kernel config */

    SIXTRL_ASSERT( ptr_blocks != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( ptr_threads_per_block != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( NS(KernelConfig_get_arch_id)( kernel_config ) ==
        NS(ARCHITECTURE_CUDA) );

    SIXTRL_ASSERT( !NS(KernelConfig_needs_update)( kernel_config ) );

    /* argument: */

    SIXTRL_ASSERT( buffer_arg != SIXTRL_NULLPTR );
    SIXTRL_ASSERT( NS(Argument_get_arch_id)( buffer_arg ) ==
                   NS(ARCHITECTURE_CUDA) );

    SIXTRL_ASSERT( NS(Argument_has_argument_buffer)( buffer_arg) );
    SIXTRL_ASSERT( NS(Argument_uses_cobjects_buffer)( buffer_arg ) );
    SIXTRL_ASSERT( NS(Argument_get_const_cobjects_buffer)(
        buffer_arg ) != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( NS(Argument_get_const_ptr_base_controller)(
        buffer_arg ) != SIXTRL_NULLPTR );

    SIXTRL_ASSERT( NS(Argument_get_cobjects_buffer_slot_size)( buffer_arg ) > ( NS(buffer_size_t) )0u );

    NS(ManagedBuffer_remap_cuda)<<< *ptr_blocks, *ptr_threads >>>(
        NS(CudaArgument_get_cuda_arg_buffer)( buffer_arg ),
        NS(Argument_get_cobjects_buffer_slot_size)( buffer_arg ) );
}

void NS(CudaController_managed_buffer_remap_debug)(
    const NS(CudaKernelConfig) *const SIXTRL_RESTRICT conf,
    NS(CudaArgument)* SIXTRL_RESTRICT buffer_arg,
    NS(buffer_size_t) const slot_size,
    NS(cuda_arg_buffer_t) SIXTRL_RESTRICT ptr_debug_register )
{
    dim3 const* ptr_blocks = SIXTRL_NULLPTR;
    dim3 const* ptr_threads = SIXTRL_NULLPTR;

    if( ( slot_size > ( NS(buffer_size_t) )0u ) &&
        ( NS(KernelConfig_get_arch_id)( conf ) == NS(ARCHITECTURE_CUDA) ) &&
        ( !NS(KernelConfig_needs_update)( conf ) ) )
    {
        ptr_blocks = NS(CudaKernelConfig_get_ptr_const_blocks)( conf );

        ptr_threads =
            NS(CudaKernelConfig_get_ptr_const_threads_per_block)( conf );
    }

    if( ( ptr_blocks  != SIXTRL_NULLPTR ) &&
        ( ptr_threads != SIXTRL_NULLPTR ) &&
        ( buffer_arg != SIXTRL_NULLPTR ) &&
        ( NS(Argument_has_argument_buffer)( buffer_arg ) ) &&
        ( NS(Argument_uses_cobjects_buffer)( buffer_arg ) ) &&
        ( NS(Argument_get_const_cobjects_buffer)( buffer_arg ) !=
          SIXTRL_NULLPTR ) &&
        ( NS(Argument_get_const_ptr_base_controller)( buffer_arg) !=
          SIXTRL_NULLPTR ) &&
        ( NS(Argument_get_cobjects_buffer_slot_size)( buffer_arg ) >
          NS(arch_size_t)0u ) &&
        ( ptr_debug_register != SXITRL_NULLPTR ) )
    {
        NS(ManagedBuffer_remap_cuda_debug)<<< *ptr_blocks, *ptr_threads >>>(
            NS(CudaArgument_get_cuda_arg_buffer)( buffer_arg ),
            NS(Argument_get_cobjects_buffer_slot_size)( buffer_arg ),
            ptr_debug_register );
    }
}

/* end: sixtracklib/cuda/wrappers/controller_wrappers.cu */