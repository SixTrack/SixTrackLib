#ifndef SIXTRACKLIB_CUDA_CONTEXT_H__
#define SIXTRACKLIB_CUDA_CONTEXT_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"

    #if defined( __cplusplus )
        #include "sixtracklib/common/buffer.hpp"
    #endif /* defined( __cplusplus ) */

    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/context/definitions.h"
    #include "sixtracklib/cuda/internal/context_base.h"
    #include "sixtracklib/cuda/internal/argument_base.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    class CudaContext : public SIXTRL_CXX_NAMESPACE::CudaContextBase
    {
        private:

        using _base_context_t = SIXTRL_CXX_NAMESPACE::CudaContextBase;

        public:

        using node_id_t      = _base_context_t::node_id_t;
        using node_info_t    = _base_context_t::node_info_t;
        using size_type      = _base_context_t::size_type;
        using platform_id_t  = _base_context_t::platform_id_t;
        using device_id_t    = _base_context_t::device_id_t;
        using type_id_t      = _base_context_t::type_id_t;
        using ptr_arg_base_t = _base_context_t::ptr_arg_base_t;

        using buffer_t       = _base_context_t::buffer_t;
        using c_buffer_t     = _base_context_t::c_buffer_t;
        using status_t       = _base_context_t::status_t;


        SIXTRL_HOST_FN explicit CudaContext(
            char const* config_str = nullptr );

        SIXTRL_HOST_FN CudaContext( CudaContext const& other) = default;
        SIXTRL_HOST_FN CudaContext( CudaContext&& other) = default;

        SIXTRL_HOST_FN CudaContext&
        operator=( CudaContext const& other) = default;

        SIXTRL_HOST_FN CudaContext& operator=( CudaContext&& other) = default;

        SIXTRL_HOST_FN virtual ~CudaContext() = default;

        protected:

        using success_flag_arg_t = SIXTRL_CXX_NAMESPACE::CudaArgumentBase;
        using cuda_arg_buffer_t  = ::NS(cuda_arg_buffer_t);

        SIXTRL_HOST_FN virtual success_flag_t
            doGetSuccessFlagValueFromArg() override;

        SIXTRL_HOST_FN virtual void doSetSuccessFlagValueFromArg(
            success_flag_t const success_flag ) override;

        SIXTRL_HOST_FN success_flag_arg_t* doGetPtrToDerivedSuccessFlagArg();

        SIXTRL_HOST_FN success_flag_arg_t const*
        doGetPtrToDerivedSuccessFlagArg() const;
    };
}

typedef SIXTRL_CXX_NAMESPACE::CudaContext     NS(CudaContext);

#else /* !defined( __cplusplus ) */

typedef void NS(CudaContext);

#endif /* defined( __cplusplus ) */

#if defined( __cplusplus ) && ( !defined( _GPUCODE ) )
extern "C" {
#endif /* defined( __cplusplus ) && ( !defined( _GPUCODE ) */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(CudaContext)* NS(CudaContext_create)( void );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(CudaContext_delete)(
    NS(CudaContext)* SIXTRL_RESTRICT context );

#if defined( __cplusplus ) && ( !defined( _GPUCODE ) )
}
#endif /* defined( __cplusplus ) && ( !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_CUDA_CONTEXT_H__ */

/* end: sixtracklib/cuda/context.h */
