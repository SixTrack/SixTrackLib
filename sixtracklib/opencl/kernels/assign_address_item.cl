#ifndef SIXTRACKLIB_OPENCL_KERNELS_PROCESS_ASSIGN_ADDRESS_ITEMS_CL_H__
#define SIXTRACKLIB_OPENCL_KERNELS_PROCESS_ASSIGN_ADDRESS_ITEMS_CL_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/opencl/internal/default_compile_options.h"
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/buffer/assign_address_item_kernel_impl.h"
    #include "sixtracklib/opencl/internal/status_flag.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

__kernel void NS(AssignAddressItem_process_managed_buffer_opencl)(
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT map_buffer,
    NS(buffer_size_t) const map_slot_size,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char* SIXTRL_RESTRICT dest_buffer,
    NS(buffer_size_t) const dest_slot_size,
    NS(arch_size_t) const dest_buffer_id,
    SIXTRL_BUFFER_DATAPTR_DEC unsigned char const* SIXTRL_RESTRICT src_buffer,
    NS(buffer_size_t) const src_slot_size,
    NS(arch_size_t) const src_buffer_id )
{
    typedef NS(buffer_size_t) buf_size_t;
    buf_size_t const start_idx = ( buf_size_t )get_global_id( 0 );
    buf_size_t const stride = ( buf_size_t )get_global_size( 0 );

    NS(AssignAddressItem_assign_all_managed_buffer_kernel_impl)(
        map_buffer, map_slot_size, start_idx, stride,
        dest_buffer, dest_slot_size, dest_buffer_id,
        src_buffer,  src_slot_size,  src_buffer_id );
}

#endif /* SIXTRACKLIB_OPENCL_KERNELS_PROCESS_ASSIGN_ADDRESS_ITEMS_CL_H__ */
/* end: /opencl/kernels/assign_address_item.cl */
