#ifndef SIXTRACKLIB_CUDA_CONTROLLER_HPP__
#define SIXTRACKLIB_CUDA_CONTROLLER_HPP__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus ) && !defined( _GPUCODE ) && \
       !defined( __CUDA_ARCH__ )
        #include <cstddef>
        #include <cstdlib>
    #endif /* C++, Host */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_controller_base.h"
    #include "sixtracklib/cuda/definitions.h"
    #include "sixtracklib/cuda/control/argument_base.hpp"
    #if defined( __cplusplus ) && !defined( _GPUCODE ) && \
       !defined( __CUDA_ARCH__ )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* C++, Host */
    #include "sixtracklib/common/buffer.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
namespace SIXTRL_CXX_NAMESPACE
{
    class CudaController : public SIXTRL_CXX_NAMESPACE::NodeControllerBase
    {
        private:

        using _base_controller_t = SIXTRL_CXX_NAMESPACE::NodeControllerBase;

        public:

        using node_info_t         = SIXTRL_CXX_NAMESPACE::CudaNodeInfo;
        using kernel_config_t     = SIXTRL_CXX_NAMESPACE::CudaKernelConfig;
        using cuda_device_index_t = node_info_t::cuda_dev_index_t;

        SIXTRL_HOST_FN explicit CudaController(
            char const* config_str = nullptr );

        SIXTRL_HOST_FN explicit CudaController(
            cuda_device_index_t const node_index,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN explicit CudaController(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN CudaController(
            platform_id_t const platform_id, device_id_t const device_id,
            char const* SIXTRL_RESTRICT config_str = nullptr );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN explicit CudaController(
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN CudaController(
            cuda_device_index_t const node_index,
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN CudaController(
            node_id_t const& SIXTRL_RESTRICT_REF node_id,
            std::string const& SIXTRL_RESTRICT_REF config_str );

        SIXTRL_HOST_FN CudaController(
            platform_id_t const platform_id, device_id_t const device_id,
            std::string const& SIXTRL_RESTRICT_REF config_str );

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN CudaController( CudaController const& other) = default;
        SIXTRL_HOST_FN CudaController( CudaController&& other) = default;

        SIXTRL_HOST_FN CudaController&
        operator=( CudaController const& other) = default;

        SIXTRL_HOST_FN CudaController& operator=(
            CudaController&& other) = default;

        SIXTRL_HOST_FN virtual ~CudaController() = default;

        /* ================================================================= */

        SIXTRL_HOST_FN node_info_t const* ptrNodeInfo(
            size_type const index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const* ptrNodeInfo(
            platform_id_t const platform_idx,
            device_id_t const device_idx ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const* ptrNodeInfo(
            node_id_t const& node_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const* ptrNodeInfo(
            char const* SIXTRL_RESTRICT node_id_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_info_t const* ptrNodeInfo(
            std::string const& SIXTRL_RESTRICT_REF node_id_str
            ) const SIXTRL_NOEXCEPT;

        /* ---------------------------------------------------------------- */

        SIXTRL_HOST_FN bool selectNodeByCudaIndex(
            cuda_device_index_t const cuda_device_index );

        SIXTRL_HOST_FN bool selectNodeByPciBusId(
            std::string const& SIXTRL_RESTRICT_REF pci_bus_id );

        SIXTRL_HOST_FN bool selectNodeByPciBusId(
            char const* SIXTRL_RESTRICT pci_bus_id );

        /* ================================================================ */

        SIXTRL_HOST_FN kernel_config_t const*
        ptrKernelConfig( kernel_id_t const kernel_id ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_t const* ptrKernelConfig(
            std::string const& SIXTRL_RESTRICT_REF kernel_name
        ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_t const* ptrKernelConfig(
            char const* SIXTRL_RESTRICT kernel_name ) const SIXTRL_NOEXCEPT;

        /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

        SIXTRL_HOST_FN kernel_config_t*
        ptrKernelConfig( kernel_id_t const kernel_id ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_t* ptrKernelConfig(
            std::string const& SIXTRL_RESTRICT_REF kname ) SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN kernel_config_t* ptrKernelConfig(
            char const* SIXTRL_RESTRICT kernel_name ) SIXTRL_NOEXCEPT;

        /* ----------------------------------------------------------------- */

        SIXTRL_HOST_FN kernel_id_t addCudaKernelConfig(
            kernel_config_t const& kernel_config );

        SIXTRL_HOST_FN kernel_id_t addCudaKernelConfig(
            std::string const& kernel_name,
            size_type const num_arguments,
            size_type const grid_dim = size_type{ 1 },
            size_type const shared_mem_per_block = size_type{ 0 },
            size_type const max_blocks_limit = size_type{ 0 },
            char const* SIXTRL_RESTRICT config_str = nullptr );

        SIXTRL_HOST_FN kernel_id_t addCudaKernelConfig(
            char const* SIXTRL_RESTRICT kernel_name,
            size_type const num_arguments,
            size_type const grid_dim = size_type{ 1 },
            size_type const shared_mem_per_block = size_type{ 0 },
            size_type const max_blocks_limit = size_type{ 0 },
            char const* SIXTRL_RESTRICT config_str = nullptr );

        protected:

        using cuda_arg_buffer_t  = ::NS(cuda_arg_buffer_t);
        using cuda_const_arg_buffer_t = ::NS(cuda_const_arg_buffer_t);

         SIXTRL_HOST_FN virtual status_t doSend(
            ptr_arg_base_t SIXTRL_RESTRICT destination,
            const void *const SIXTRL_RESTRICT source,
            size_type const source_length ) override;

        SIXTRL_HOST_FN virtual status_t doReceive(
            void* SIXTRL_RESTRICT destination,
            size_type const dest_capacity,
            ptr_arg_base_t SIXTRL_RESTRICT source ) override;

        SIXTRL_HOST_FN virtual status_t doRemapCObjectsBuffer(
            ptr_arg_base_t SIXTRL_RESTRICT arg,
            size_type const arg_size,
            ptr_arg_base_t SIXTRL_RESTRICT remap_debug_flag_arg ) override;

        SIXTRL_HOST_FN virtual bool
            doSelectNode( node_index_t const node_index ) override;

        SIXTRL_HOST_FN virtual bool doChangeSelectedNode(
            node_index_t const current_selected_node_idx,
            node_index_t const new_selected_node_index ) override;

        SIXTRL_HOST_FN node_index_t doFindAvailableNodesByCudaDeviceIndex(
            cuda_device_index_t const cuda_device_index ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t doFindAvailableNodesByPciBusId(
            char const* SIXTRL_RESTRICT pci_bus_id_str ) const SIXTRL_NOEXCEPT;

        SIXTRL_HOST_FN node_index_t doGetNodeIndexFromConfigString(
            char const* SIXTRL_RESTRICT select_str );

        SIXTRL_HOST_FN void doInitCudaController();
        SIXTRL_HOST_FN bool doInitAllCudaNodes();
        SIXTRL_HOST_FN void doEnableCudaController();

        SIXTRL_HOST_FN kernel_id_t doAppendCudaKernelConfig(
            ptr_cuda_kernel_config_t&& ptr_kernel_conf ) SIXTRL_NOEXCEPT;

        private:

         SIXTRL_HOST_FN static status_t PerformSendOperation(
            cuda_arg_buffer_t SIXTRL_RESTRICT destination,
            cuda_const_arg_buffer_t SIXTRL_RESTRICT source_begin,
            size_type const source_length );

        SIXTRL_HOST_FN static status_t PerformReceiveOperation(
            cuda_arg_buffer_t SIXTRL_RESTRICT destination,
            size_type const destination_capacity,
            cuda_const_arg_buffer_t SIXTRL_RESTRICT source_begin,
            size_type const source_length );

        SIXTRL_HOST_FN bool doSelectNodeCudaImpl( node_index_t const idx );

        SIXTRL_HOST_FN status_t doRemapCObjectsBufferCudaBaseImpl(
            ptr_arg_base_t SIXTRL_RESTRICT arg, size_type const arg_size
            ptr_arg_base_t SIXTRL_RESTRICT debug_flag_arg );
    };
}

extern "C" { typedef SIXTRL_CXX_NAMESPACE::CudaController NS(CudaController); }

#else /* C++, Host */

typedef void NS(CudaController);

#endif /* C++, Host */

#endif /* SIXTRACKLIB_CUDA_CONTROLLER_HPP__ */

/* end: sixtracklib/cuda/controller.hpp */
