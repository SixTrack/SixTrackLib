#include "sixtracklib/cuda/controller.h"

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

#include <cstddef>
#include <cstdlib>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/cuda/definitions.h"
#include "sixtracklib/cuda/controller.hpp"
#include "sixtracklib/cuda/argument.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(CudaController)* NS(CudaController_create)( void )
{
    return new st::CudaController( "" );
}

::NS(CudaController)* NS(CudaController_new)(
    const char *const SIXTRL_RESTRICT config_str )
{
    return new st::CudaController( config_str );
}

::NS(CudaController)* NS(CudaController_new_from_node_id)(
    const ::NS(NodeId) *const SIXTRL_RESTRICT node_id,
    const char *const SIXTRL_RESTRICT config_str )
{
    return ( node_id != nullptr )
        ? new st::CudaController( *node_id, config_str ) : nullptr;
}

::NS(CudaController)* NS(CudaController_new_from_node_index)(
    ::NS(node_index_t) const node_index,
    const char *const SIXTRL_RESTRICT config_str )
{
    ::NS(CudaController)* ptr_ctrl = ( node_index != st::NODE_UNDEFINED_INDEX )
        ? new st::CudaController( config_str ) : nullptr;

    if( ptr_ctrl != nullptr )
    {
        ::NS(arch_status_t) const status = ptr_ctrl->selectNode( node_index );

        if( status != st::ARCH_STATUS_SUCCESS )
        {
            delete ptr_ctrl;
            ptr_ctrl = nullptr;
        }
    }

    return ptr_ctrl;
}

::NS(CudaController)* NS(CudaController_new_from_platform_id_and_device_id)(
    ::NS(node_platform_id_t) const platform_id,
    ::NS(node_device_id_t) const device_id,
    const char *const SIXTRL_RESTRICT config_str )
{
    return ( ( platform_id != st::NODE_ILLEGAL_PATFORM_ID ) &&
             ( device_id != st::NODE_ILLEGAL_PATFORM_ID ) )
        ? new st::CudaController( platform_id, device_id, config_str )
        : nullptr;
}

::NS(CudaController)* NS(CudaController_new_from_cuda_device_index)(
    ::NS(cuda_dev_index_t) const cuda_device_index,
    const char *const SIXTRL_RESTRICT config_str )
{
     return ( cuda_device_index >= ::NS(cuda_dev_index_t){ 0 } )
         ? new st::CudaController( cuda_device_index, config_str )
         : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(CudaController_select_node_by_cuda_device_index)(
    NS(CudaController)* SIXTRL_RESTRICT ctrl,
    NS(cuda_dev_index_t) const cuda_device_index )
{
    return ( ctrl != nullptr )
        ? ctrl->selectNodeByCudaIndex( cuda_device_index )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(CudaController_select_node_by_cuda_pci_bus_id)(
    NS(CudaController)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT cuda_pci_bus_id )
{
    return ( ctrl != nullptr )
        ? ctrl->selectNodeByPciBusId( cuda_pci_bus_id )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

void NS(CudaController_delete)( NS(CudaController)* SIXTRL_RESTRICT ctrl )
{
    delete ctrl;
    return;
}

/* ------------------------------------------------------------------------- */

::NS(CudaNodeInfo) const* NS(CudaController_get_ptr_node_info_by_index)(
     const ::NS(CudaController) *const SIXTRL_RESTRICT ctrl,
     ::NS(node_index_t) const index )
{
    return ( ctrl != nullptr ) ? ctrl->ptrNodeInfo( index ) : nullptr;
}

::NS(CudaNodeInfo) const*
NS(CudaController_get_ptr_node_info_by_platform_id_and_device_id)(
     const ::NS(CudaController) *const SIXTRL_RESTRICT ctrl,
     ::NS(node_platform_id_t) const platform_idx,
     ::NS(node_device_id_t) const device_idx )
{
    return ( ctrl != nullptr ) ? ctrl->ptrNodeInfo( platform_idx, device_idx )
        : nullptr;
}

::NS(CudaNodeInfo) const* NS(CudaController_get_ptr_node_info_by_node_id)(
     const ::NS(CudaController) *const SIXTRL_RESTRICT ctrl,
     const ::NS(NodeId) *const SIXTRL_RESTRICT node_id )
{
    return ( ( ctrl != nullptr ) && ( node_id != nullptr ) )
        ? ctrl->ptrNodeInfo( *node_id ) : nullptr;
}

::NS(CudaNodeInfo) const* NS(CudaController_get_ptr_node_info)(
     const ::NS(CudaController) *const SIXTRL_RESTRICT ctrl,
     char const* SIXTRL_RESTRICT node_id_str )
{
    return ( ctrl != nullptr ) ? ctrl->ptrNodeInfo( node_id_str ) : nullptr;
}

::NS(CudaNodeInfo) const* NS(CudaController_get_ptr_node_info_by_cuda_dev_index)(
     const ::NS(CudaController) *const SIXTRL_RESTRICT ctrl,
     ::NS(cuda_dev_index_t) const cuda_device_index )
{
    return ( ctrl != nullptr )
        ? ctrl->ptrNodeInfoByCudaDeviceIndex( cuda_device_index ) : nullptr;
}

::NS(CudaNodeInfo) const* NS(CudaController_get_ptr_node_info_by_pci_bus_id)(
     const ::NS(CudaController) *const SIXTRL_RESTRICT ctrl,
     char const* SIXTRL_RESTRICT pci_bus_id_str )
{
    return ( ctrl != nullptr )
        ? ctrl->ptrNodeInfoByPciBusId( pci_bus_id_str ) : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(ctrl_kernel_id_t) NS(CudaController_add_kernel_config)(
    ::NS(CudaController)* SIXTRL_RESTRICT ctrl,
    const ::NS(CudaKernelConfig) *const SIXTRL_RESTRICT cuda_kernel_config )
{
    return ( ( ctrl != nullptr ) && ( cuda_kernel_config != nullptr ) )
        ? ctrl->addCudaKernelConfig( *cuda_kernel_config )
        : st::CudaController::ILLEGAL_KERNEL_ID;
}

::NS(ctrl_kernel_id_t) NS(CudaController_add_kernel_config_detailed)(
    ::NS(CudaController)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT kernel_name,
    ::NS(ctrl_size_t) const num_arguments,
    ::NS(ctrl_size_t) const grid_dim,
    ::NS(ctrl_size_t) const shared_mem_per_block,
    ::NS(ctrl_size_t) const max_blocks_limit,
    char const* SIXTRL_RESTRICT config_str )
{
    return ( ctrl != nullptr )
        ? ctrl->addCudaKernelConfig( kernel_name, num_arguments, grid_dim,
            shared_mem_per_block, max_blocks_limit, config_str )
        : st::CudaController::ILLEGAL_KERNEL_ID;
}

/* ------------------------------------------------------------------------- */

::NS(CudaKernelConfig)* NS(CudaController_get_ptr_kernel_config)(
    ::NS(CudaController)* SIXTRL_RESTRICT ctrl,
    ::NS(ctrl_kernel_id_t) const kernel_id )
{
    return ( ctrl != nullptr ) ? ctrl->ptrKernelConfig( kernel_id ) : nullptr;
}

::NS(CudaKernelConfig)* NS(CudaController_get_ptr_kernel_config_by_kernel_name)(
    ::NS(CudaController)* SIXTRL_RESTRICT ctrl,
    char const* SIXTRL_RESTRICT kernel_name )
{
    return ( ctrl != nullptr )
        ? ctrl->ptrKernelConfig( kernel_name ) : nullptr;
}

/* ------------------------------------------------------------------------- */

::NS(arch_status_t) NS(CudaController_remap_managed_cobject_buffer)(
    ::NS(CudaController)* SIXTRL_RESTRICT ctrl,
    ::NS(cuda_arg_buffer_t) SIXTRL_RESTRICT managed_buffer_begin,
    ::NS(arch_size_t) const slot_size )
{
    return ( ctrl != nullptr )
        ? ctrl->remap( managed_buffer_begin, slot_size )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

bool NS(CudaController_is_managed_cobject_buffer_remapped)(
    ::NS(CudaController)* SIXTRL_RESTRICT ctrl,
    ::NS(cuda_arg_buffer_t) SIXTRL_RESTRICT managed_buffer_begin,
    ::NS(arch_size_t) const slot_size )
{
    return ( ( ctrl != nullptr ) &&
             ( ctrl->isRemapped( managed_buffer_begin, slot_size ) ) );
}

::NS(arch_status_t) NS(CudaController_send_memory)(
    ::NS(CudaController)* SIXTRL_RESTRICT ctrl,
    ::NS(cuda_arg_buffer_t) SIXTRL_RESTRICT destination,
    void const* SIXTRL_RESTRICT source, ::NS(arch_size_t) const source_length )
{
    return ( ctrl != nullptr )
        ? ctrl->sendMemory( destination, source, source_length )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(CudaController_receive_memory)(
    ::NS(CudaController)* SIXTRL_RESTRICT ctrl,
    void* SIXTRL_RESTRICT destination,
    ::NS(cuda_const_arg_buffer_t) SIXTRL_RESTRICT source,
    ::NS(arch_size_t) const source_length )
{
    return ( ctrl != nullptr )
        ? ctrl->receiveMemory( destination, source, source_length )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

#endif /* C++, Host */

/* end: sixtracklib/cuda/internal/controller_c99.cpp */
