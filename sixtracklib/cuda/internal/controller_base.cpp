#include "sixtracklib/cuda/internal/controller_base.hpp"

#if defined( __cplusplus ) && !defined( __CUDA_ARCH__ ) && !defined( _GPUCODE )

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/controller_base.hpp"
#include "sixtracklib/common/control/controller_on_nodes_base.hpp"
#include "sixtracklib/common/buffer.h"

#include "sixtracklib/cuda/internal/argument_base.hpp"
#include "sixtracklib/cuda/wrappers/context_operations.h"

namespace SIXTRL_CXX_NAMESPACE
{
    CudaControllerBase::node_info_t const* CudaControllerBase::ptrNodeInfo(
        CudaControllerBase::size_type const index ) const SIXTRL_NOEXCEPT
    {
        using node_info_t = CudaControllerBase::node_info_t;
        auto node_info_base = this->ptrNodeInfoBase( index );

        return ( node_info_base != nullptr )
            ? node_info_base->asDerivedNodeInfo< node_info_t >(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA )
            : nullptr;
    }

    CudaControllerBase::node_info_t const* CudaControllerBase::ptrNodeInfo(
        CudaControllerBase::platform_id_t const platform_idx,
        CudaControllerBase::device_id_t const device_idx ) const SIXTRL_NOEXCEPT
    {
        return this->ptrNodeInfo( this->doFindAvailableNodesIndex(
            platform_idx, device_idx ) );
    }

    CudaControllerBase::node_info_t const* CudaControllerBase::ptrNodeInfo(
        CudaControllerBase::node_id_t const& node_id ) const SIXTRL_NOEXCEPT
    {
        return this->ptrNodeInfo( this->doFindAvailableNodesIndex(
            node_id.platformId(), node_id.deviceId() ) );
    }

    CudaControllerBase::node_info_t const* CudaControllerBase::ptrNodeInfo(
        char const* SIXTRL_RESTRICT node_id_str ) const SIXTRL_NOEXCEPT
    {
        return this->ptrNodeInfo( this->doFindAvailableNodesIndex(
            node_id_str ) );
    }

    CudaControllerBase::node_info_t const* CudaControllerBase::ptrNodeInfo(
        std::string const& SIXTRL_RESTRICT_REF
            node_id_str ) const SIXTRL_NOEXCEPT
    {
        return this->ptrNodeInfo( this->doFindAvailableNodesIndex(
            node_id_str.c_str() ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    bool CudaControllerBase::selectNodeByCudaIndex(
        CudaControllerBase::cuda_device_index_t const cuda_device_index )
    {
        return this->doSelectNode(
            this->doFindAvailableNodesByCudaDeviceIndex( cuda_device_index ) );
    }

    bool CudaControllerBase::selectNodeByPciBusId(
        std::string const& SIXTRL_RESTRICT_REF pci_bus_id )
    {
        return this->doSelectNode(
            this->doFindAvailableNodesByPciBusId( pci_bus_id.c_str() ) );
    }

    bool CudaControllerBase::selectNodeByPciBusId(
        char const* SIXTRL_RESTRICT pci_bus_id )
    {
        return this->doSelectNode(
            this->doFindAvailableNodesByPciBusId( pci_bus_id ) );
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    CudaControllerBase::CudaControllerBase( char const* config_str ) :
        ControllerOnNodesBase( SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA,
            SIXTRL_ARCHITECTURE_CUDA_STR, config_str )
    {
        bool const success = this->doInitAllCudaNodes();
        ( void )success;
    }

    CudaControllerBase::status_t CudaControllerBase::doSend(
        CudaControllerBase::ptr_arg_base_t SIXTRL_RESTRICT dest_arg,
        const void *const SIXTRL_RESTRICT source,
        CudaControllerBase::size_type const source_length )
    {
        using _this_t    = SIXTRL_CXX_NAMESPACE::CudaControllerBase;
        using status_t   = _this_t::status_t;
        using size_t     = _this_t::size_type;
        using cuda_arg_t = SIXTRL_CXX_NAMESPACE::CudaArgumentBase;
        using cuda_arg_buffer_t = cuda_arg_t::cuda_arg_buffer_t;

        status_t status = status_t{ -1 };

        SIXTRL_ASSERT( this->readyForSend() );
        SIXTRL_ASSERT( dest_arg != nullptr );
        SIXTRL_ASSERT( source   != nullptr );
        SIXTRL_ASSERT( source_length > size_t{ 0 } );
        SIXTRL_ASSERT( dest_arg->capacity() >= source_length );

        if( dest_arg->hasArgumentBuffer() )
        {
            cuda_arg_t* cuda_arg = dest_arg->asDerivedArgument< cuda_arg_t >(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA );

            if( ( cuda_arg != nullptr ) && ( cuda_arg->hasCudaArgBuffer() ) )
            {
                cuda_arg_buffer_t arg_buffer = cuda_arg->cudaArgBuffer();
                SIXTRL_ASSERT( arg_buffer != nullptr );

                status = ::NS(CudaContext_perform_send)(
                    arg_buffer, source, source_length );
            }
        }

        return status;
    }

    CudaControllerBase::status_t CudaControllerBase::doReceive(
        void* SIXTRL_RESTRICT destination,
        CudaControllerBase::size_type const dest_capacity,
        CudaControllerBase::ptr_arg_base_t SIXTRL_RESTRICT src_arg )
    {
        using _this_t    = CudaControllerBase;
        using status_t   = _this_t::status_t;
        using size_t     = _this_t::size_type;
        using cuda_arg_t = SIXTRL_CXX_NAMESPACE::CudaArgumentBase;
        using cuda_arg_buffer_t = cuda_arg_t::cuda_arg_buffer_t;

        status_t status = status_t{ -1 };

        SIXTRL_ASSERT( this->readyForReceive() );
        SIXTRL_ASSERT( destination != nullptr );
        SIXTRL_ASSERT( src_arg != nullptr );
        SIXTRL_ASSERT( src_arg->size() > size_t{ 0 } );
        SIXTRL_ASSERT( dest_capacity >= src_arg->size() );

        if( src_arg->hasArgumentBuffer() )
        {
            cuda_arg_t* cuda_arg = src_arg->asDerivedArgument< cuda_arg_t >(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA );

            if( ( cuda_arg != nullptr ) && ( cuda_arg->hasCudaArgBuffer() ) )
            {
                cuda_arg_buffer_t arg_buffer = cuda_arg->cudaArgBuffer();
                SIXTRL_ASSERT( arg_buffer != nullptr );

                status = ::NS(CudaContext_perform_receive)( destination,
                    dest_capacity, arg_buffer, src_arg->size() );
            }
        }

        return status;
    }

    CudaControllerBase::status_t CudaControllerBase::doRemapSentCObjectsBuffer(
        CudaControllerBase::ptr_arg_base_t SIXTRL_RESTRICT arg,
        CudaControllerBase::size_type const arg_size )
    {
        using    _this_t = CudaControllerBase;
        using   status_t = _this_t::status_t;
        using     size_t = _this_t::size_type;
        using cuda_arg_t = SIXTRL_CXX_NAMESPACE::CudaArgumentBase;
        using c_buffer_t = cuda_arg_t::c_buffer_t;
        using cuda_arg_buffer_t = cuda_arg_t::cuda_arg_buffer_t;

        SIXTRL_ASSERT( arg != nullptr );

        status_t status = status_t{ -1 };
        size_t len = ( arg->size() > arg_size ) ? arg->size() : arg_size;

        SIXTRL_ASSERT( this->readyForRemap() );
        SIXTRL_ASSERT( len > size_t{ 0 } );

        if( ( arg->hasArgumentBuffer() ) && ( arg->usesCObjectsBuffer() ) )
        {
            cuda_arg_t* cuda_arg = arg->asDerivedArgument< cuda_arg_t >(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA );

            if( ( cuda_arg != nullptr ) && ( cuda_arg->hasCudaArgBuffer() ) )
            {
                cuda_arg_buffer_t arg_buffer = cuda_arg->cudaArgBuffer();
                SIXTRL_ASSERT( arg_buffer != nullptr );

                c_buffer_t* buffer = cuda_arg->ptrCObjectsBuffer();
                SIXTRL_ASSERT( buffer != nullptr );

                size_t const slot_size = ::NS(Buffer_get_slot_size)( buffer );
                status = ::NS(CudaContext_perform_remap_send_cobject_buffer)(
                    arg_buffer, slot_size );
            }
        }

        return status;
    }

    bool CudaControllerBase::doSelectNode(
        CudaControllerBase::node_index_t const node_index )
    {
        using _base_ctrl_t = SIXTRL_CXX_NAMESPACE::ControllerOnNodesBase;
        using node_info_base_t = CudaControllerBase::node_info_base_t;
        using node_info_t = CudaControllerBase::node_info_t;
        using cuda_dev_index_t = node_info_t::cuda_dev_index_t;

        bool success = false;

        node_info_base_t* node_base = this->doGetPtrNodeInfoBase( node_index );

        node_info_t* ptr_node_info = ( node_base != nullptr )
            ? node_base->asDerivedNodeInfo< node_info_t >(
                SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA ) : nullptr;

        if( ( ptr_node_info != nullptr ) &&
            ( ptr_node_info->hasCudaDeviceIndex() ) )
        {
            cuda_dev_index_t cuda_dev_index = ptr_node_info->cudaDeviceIndex();

            if( cuda_dev_index != node_info_t::ILLEGAL_DEV_INDEX )
            {
                ::cudaError_t const err = ::cudaSetDevice( cuda_dev_index );

                if( err == ::cudaSuccess )
                {
                    success = _base_ctrl_t::doSelectNode( node_index );
                }
            }
        }

        return success;
    }

    CudaControllerBase::node_index_t
    CudaControllerBase::doFindAvailableNodesByCudaDeviceIndex(
        CudaControllerBase::cuda_device_index_t const idx ) const SIXTRL_NOEXCEPT
    {
        using _this_t          = SIXTRL_CXX_NAMESPACE::CudaControllerBase;
        using node_id_t        = _this_t::node_id_t;
        using node_info_base_t = _this_t::node_info_base_t;
        using node_info_t      = _this_t::node_info_t;
        using node_index_t     = _this_t::node_index_t;

        node_index_t found_node_index = node_id_t::UNDEFINED_INDEX;
        node_index_t const num_avail_nodes = this->numAvailableNodes();

        if( ( num_avail_nodes > node_index_t{ 0 } ) &&
            ( idx != node_info_t::ILLEGAL_DEV_INDEX ) )
        {
            node_index_t ii = node_index_t{ 0 };

            for( ; ii < num_avail_nodes ; ++ii )
            {
                node_info_base_t const* ptr_base = this->ptrNodeInfoBase( ii );

                node_info_t const* ptr_node_info = ( ptr_base != nullptr )
                    ? ptr_base->asDerivedNodeInfo< node_info_t >(
                        SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA ) : nullptr;

                if( ( ptr_node_info != nullptr ) &&
                    ( ptr_node_info->hasCudaDeviceIndex() ) &&
                    ( ptr_node_info->cudaDeviceIndex() == idx ) )
                {
                    SIXTRL_ASSERT( ( !ptr_node_info->hasNodeIndex() ) ||
                        ( ptr_node_info->nodeIndex() == ii ) );

                    found_node_index = ii;
                    break;
                }
            }
        }

        return found_node_index;
    }

    CudaControllerBase::node_index_t
    CudaControllerBase::doFindAvailableNodesByPciBusId(
        char const* SIXTRL_RESTRICT pci_bus_id_str ) const SIXTRL_NOEXCEPT
    {
        using _this_t          = SIXTRL_CXX_NAMESPACE::CudaControllerBase;
        using node_id_t        = _this_t::node_id_t;
        using node_info_base_t = _this_t::node_info_base_t;
        using node_info_t      = _this_t::node_info_t;
        using node_index_t     = _this_t::node_index_t;

        node_index_t found_node_index = node_id_t::UNDEFINED_INDEX;
        node_index_t const num_avail_nodes = this->numAvailableNodes();

        if( ( num_avail_nodes > node_index_t{ 0 } ) &&
            ( pci_bus_id_str != nullptr ) &&
            ( std::strlen( pci_bus_id_str ) > std::size_t{ 0 } ) )
        {
            node_index_t ii = node_index_t{ 0 };

            for( ; ii < num_avail_nodes ; ++ii )
            {
                node_info_base_t const* ptr_base = this->ptrNodeInfoBase( ii );

                node_info_t const* nodeinfo = ( ptr_base != nullptr )
                    ? ptr_base->asDerivedNodeInfo< node_info_t >(
                        SIXTRL_CXX_NAMESPACE::ARCHITECTURE_CUDA ) : nullptr;

                if( ( nodeinfo != nullptr ) && ( nodeinfo->hasPciBusId() ) &&
                    ( nodeinfo->pciBusId().compare( pci_bus_id_str ) == 0 ) )
                {
                    SIXTRL_ASSERT( ( !nodeinfo->hasNodeIndex() ) ||
                                   (  nodeinfo->nodeIndex() == ii ) );

                    found_node_index = ii;
                    break;
                }
            }
        }

        return found_node_index;
    }

    bool CudaControllerBase::doInitAllCudaNodes()
    {
        bool success = false;

        using _this_t = CudaControllerBase;
        using node_index_t     = _this_t::node_index_t;
        using node_info_base_t = _this_t::node_info_base_t;
        using node_info_t      = _this_t::node_info_t;

        node_index_t const initial_num_avail_nodes = this->numAvailableNodes();

        bool first = true;

        int num_devices = int{ -1 };
        ::cudaError_t err = ::cudaGetDeviceCount( &num_devices );

        if( ( err == ::cudaSuccess ) && ( num_devices > int{ 0 } ) )
        {
            for( int cu_idx = int{ 0 } ; cu_idx < num_devices ; ++cu_idx )
            {
                ::cudaDeviceProp cu_properties;
                err = ::cudaGetDeviceProperties( &cu_properties, cu_idx );

                if( err != ::cudaSuccess )
                {
                    continue;
                }

                std::unique_ptr< node_info_t > ptr_node_info(
                    new node_info_t( cu_idx, cu_properties ) );

                if( ptr_node_info.get() == nullptr )
                {
                    continue;
                }

                SIXTRL_ASSERT( ptr_node_info->platformId() ==
                    _this_t::node_id_t::ILLEGAL_PLATFORM_ID );

                SIXTRL_ASSERT( ptr_node_info->deviceId() ==
                    _this_t::node_id_t::ILLEGAL_DEVICE_ID );

                /* Check if this node is already present -> use first the
                 * cuda device index and then the the PCI Bus ID for
                 * eliminating duplicates
                 *
                 * WARNING: This searches linearily (!) over all existing
                 * nodes. If the number of nodes gets high, this can impose
                 * some performance problems -> replace with a hash-table
                 * or something O(log(N)) / O(1) in such a case */

                if( _this_t::node_id_t::UNDEFINED_INDEX !=
                    this->doFindAvailableNodesByCudaDeviceIndex( cu_idx ) )
                {
                    continue;
                }

                if( ( ptr_node_info->hasPciBusId() ) &&
                    ( _this_t::node_id_t::UNDEFINED_INDEX !=
                        this->doFindAvailableNodesByPciBusId(
                          ptr_node_info->pciBusId().c_str() ) ) )
                {
                    continue;
                }

                ptr_node_info->setCudaDeviceIndex( cu_idx );

                node_index_t node_index = this->doAppendAvailableNodeInfoBase(
                    std::move( ptr_node_info ) );

                if( ( node_index != _this_t::UNDEFINED_INDEX ) && ( first ) )
                {
                    this->doSetDefaultNodeIndex( node_index );
                    first = false;
                }
            }

            success = ( this->numAvailableNodes() > initial_num_avail_nodes );
        }

        return success;
    }
}

#endif /* C++, Host */

/* end: sixtracklib/cuda/internal/controller_base.cpp */
