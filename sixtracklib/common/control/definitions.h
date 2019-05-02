#ifndef SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__
#define SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++, Host */

typedef SIXTRL_INT32_T   NS(controller_status_t);
typedef SIXTRL_UINT64_T  NS(controller_size_t);
typedef SIXTRL_UINT64_T  NS(controller_success_flag_t);

typedef SIXTRL_UINT64_T  NS(arch_id_t);
typedef SIXTRL_UINT64_T  NS(arch_size_t);

typedef SIXTRL_INT64_T   NS(node_platform_id_t);
typedef SIXTRL_INT64_T   NS(node_device_id_t);
typedef SIXTRL_UINT32_T  NS(node_index_t);

/* Predefined  context type id's: limit them to 0x0000 - 0x01FF */
/* For userdefined type id's, the range 0x0200 - 0x03FF is reserved */

#if !defined( SIXTRL_ARCHITECTURE_ID_BITMASK )
    #define SIXTRL_ARCHITECTURE_ID_BITMASK 0x000003FF
#endif /* !defined( SIXTRL_ARCHITECTURE_ID_BITMASK) */

#if !defined( SIXTRL_ARCHITECTURE_ID_OFFSET )
    #define SIXTRL_ARCHITECTURE_ID_OFFSET 0
#endif /* !defined( SIXTRL_ARCHITECTURE_ID_OFFSET) */

/* Then reserve 8 bits to encode up to 256 variants for any specific
 * type_id */

#if !defined( SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK )
    #define SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK 0x000FF000
#endif /* !defined( SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK ) */

#if !defined( SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET )
    #define SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET 10
#endif /* !defined( SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET ) */

/* ------------------------------------------------------------------------ */

#if !defined( SIXTRL_ARCHITECTURE_ILLEGAL)
    #define SIXTRL_ARCHITECTURE_ILLEGAL 0x000003FF
#endif /* !defined( SIXTRL_ARCHITECTURE_ILLEGAL) */

#if !defined( SIXTRL_ARCHITECTURE_NONE)
    #define SIXTRL_ARCHITECTURE_NONE 0x00000000
#endif /* !defined( SIXTRL_ARCHITECTURE_NONE) */

#if !defined( SIXTRL_ARCHITECTURE_CPU)
    #define SIXTRL_ARCHITECTURE_CPU 0x00000001
#endif /* !defined( SIXTRL_ARCHITECTURE_CPU) */

#if !defined(SIXTRL_ARCHITECTURE_CPU_STR)
    #define SIXTRL_ARCHITECTURE_CPU_STR "cpu"
#endif /* !defined(SIXTRL_ARCHITECTURE_CPU_STR) */

#if !defined( SIXTRL_ARCHITECTURE_OPENCL)
    #define SIXTRL_ARCHITECTURE_OPENCL 0x00000002
#endif /* !defined( SIXTRL_ARCHITECTURE_OPENCL) */

#if !defined(SIXTRL_ARCHITECTURE_OPENCL_STR)
    #define SIXTRL_ARCHITECTURE_OPENCL_STR "opencl"
#endif /* !defined(SIXTRL_ARCHITECTURE_OPENCL_STR) */

#if !defined( SIXTRL_ARCHITECTURE_CUDA)
    #define SIXTRL_ARCHITECTURE_CUDA 0x00000003
#endif /* !defined( SIXTRL_ARCHITECTURE_CUDA) */

#if !defined(SIXTRL_ARCHITECTURE_CUDA_STR)
    #define SIXTRL_ARCHITECTURE_CUDA_STR "cuda"
#endif /* !defined(SIXTRL_ARCHITECTURE_CUDA_STR) */

/* ------------------------------------------------------------------------- */

#if !defined(SIXTRL_CONTROLLER_STATUS_SUCCESS)
    #define SIXTRL_CONTROLLER_STATUS_SUCCESS 0
#endif /* !defined(SIXTRL_CONTROLLER_STATUS_SUCCESS) */

#if !defined(SIXTRL_CONTROLLER_STATUS_GENERAL_FAILURE)
    #define SIXTRL_CONTROLLER_STATUS_GENERAL_FAILURE -1
#endif /* !defined(SIXTRL_CONTROLLER_STATUS_GENERAL_FAILURE) */

#if !defined( _GPUCODE )

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_ID_BITMASK) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ID_BITMASK;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_ID_OFFSET) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ID_OFFSET;

SIXTRL_STATIC_VAR NS(arch_id_t) const
    NS(ARCHITECTURE_ID_VARIANT_BITMASK) = ( NS(arch_id_t)
        )SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK;

SIXTRL_STATIC_VAR NS(arch_id_t) const
    NS(ARCHITECTURE_ID_VARIANT_OFFSET) = ( NS(arch_id_t)
        )SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_ILLEGAL) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_ILLEGAL;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_NONE) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_NONE;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_CPU) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CPU;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_OPENCL) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_OPENCL;

SIXTRL_STATIC_VAR NS(arch_id_t) const NS(ARCHITECTURE_CUDA) =
    ( NS(arch_id_t) )SIXTRL_ARCHITECTURE_CUDA;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(controller_status_t) const NS(CONTROLLER_STATUS_SUCCESS) =
    ( NS(controller_status_t) )SIXTRL_CONTROLLER_STATUS_SUCCESS;

SIXTRL_STATIC_VAR NS(controller_status_t) const
    NS(CONTROLLER_STATUS_GENERAL_FAILURE) =
        ( NS(controller_status_t) )SIXTRL_CONTROLLER_STATUS_GENERAL_FAILURE;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC_VAR NS(node_platform_id_t) const NS(NODE_ILLEGAL_PATFORM_ID) =
    ( NS(node_platform_id_t) )-1;

SIXTRL_STATIC_VAR NS(node_device_id_t) const NS(NODE_ILLEGAL_DEVICE_ID) =
    ( NS(node_device_id_t) )-1;

SIXTRL_STATIC_VAR NS(node_index_t) const NS(NODE_UNDEFINED_INDEX) =
    ( NS(node_index_t) )0xFFFFFFFF;


#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}

namespace SIXTRL_CXX_NAMESPACE
{
    typedef ::NS(arch_id_t)                 arch_id_t;
    typedef ::NS(controller_status_t)       controller_status_t;
    typedef ::NS(controller_success_flag_t) controller_success_flag_t;
    typedef ::NS(controller_size_t)         controller_size_t;

    typedef ::NS(arch_id_t)                 arch_id_t;
    typedef ::NS(arch_size_t)               arch_size_t;

    typedef ::NS(node_platform_id_t)        node_platform_id_t;
    typedef ::NS(node_device_id_t)          node_device_id_t;
    typedef ::NS(node_index_t)              node_index_t;

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ID_BITMASK = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_ID_BITMASK );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ID_OFFSET = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_ID_OFFSET );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ID_VARIANT_BITMASK = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_ID_VARIANT_BITMASK );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ID_VARIANT_OFFSET = static_cast< arch_id_t
            >( SIXTRL_ARCHITECTURE_ID_VARIANT_OFFSET );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_ILLEGAL = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_ILLEGAL );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_NONE = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_NONE );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_CPU = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_CPU );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_OPENCL = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_OPENCL );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST arch_id_t
        ARCHITECTURE_CUDA = static_cast< arch_id_t >(
            SIXTRL_ARCHITECTURE_CUDA );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST controller_status_t
        CONTROLLER_STATUS_SUCCESS = static_cast< controller_status_t >(
            SIXTRL_CONTROLLER_STATUS_SUCCESS );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST controller_status_t
        CONTROLLER_STATUS_GENERAL_FAILURE = static_cast< controller_status_t >(
            SIXTRL_CONTROLLER_STATUS_GENERAL_FAILURE );

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_platform_id_t
        NODE_ILLEGAL_PATFORM_ID = static_cast< node_platform_id_t >( -1 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_device_id_t
        NODE_ILLEGAL_DEVICE_ID = static_cast< node_device_id_t >( -1 );

    SIXTRL_STATIC_VAR SIXTRL_CONSTEXPR_OR_CONST node_index_t
        NODE_UNDEFINED_INDEX = static_cast< node_index_t >( 0xFFFFFFFF );
}

#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTROL_DEFINITIONS_H__ */

/* end: sixtracklib/common/control/definitions.h */
