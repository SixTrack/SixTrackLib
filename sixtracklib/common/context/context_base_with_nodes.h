#ifndef SIXTRACKLIB_COMMON_CONTEXT_NODE_BASE_H__
#define SIXTRACKLIB_COMMON_CONTEXT_NODE_BASE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/context/compute_arch.h"
    #include "sixtracklib/common/context/context_base.h"
    #include "sixtracklib/common/context/context_base_with_nodes.hpp"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
extern "C" {
#endif /* C++, Host */

#if !defined( __CUDA_ARCH ) && !defined( _GPUCODE )

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_size_t)
NS(Context_get_num_available_nodes)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(Context_get_available_nodes_info_begin)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(Context_get_available_nodes_info_end)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_id_t)
NS(Context_get_default_node_id)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(Context_get_default_node_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_is_node_available_by_index)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_size_t) const node_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_is_node_available_by_node_id)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_node_id_t) const node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(Context_is_node_available_by_platform_device_ids)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_platform_id_t) const platform_index,
    NS(context_device_id_t) const device_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_is_node_available)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    char const* SIXTRL_RESTRICT node_id_str );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_is_default_node)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    char const* node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_is_default_node_by_node_id)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_node_id_t) const node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(Context_is_default_node_by_platform_device_ids)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_platform_id_t) const platform_index,
    NS(context_device_id_t) const device_index );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_is_default_node_by_index)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_size_t) const node_index );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_id_t) const*
NS(Context_get_ptr_available_nodes_id_by_index)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_size_t) const index );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(Context_get_ptr_available_nodes_info_by_index)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(Context_get_ptr_available_nodes_info_by_platform_device_ids)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_platform_id_t) const platform_idx,
    NS(context_device_id_t) const device_idx );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(Context_get_ptr_available_nodes_info_by_node_id)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_node_id_t) const node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(Context_get_ptr_available_nodes_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    char const* SIXTRL_RESTRICT node_id_str );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_has_selected_node)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_id_t) const*
NS(Context_get_ptr_selected_node_id)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN NS(context_node_info_t) const*
NS(Context_get_ptr_selected_node_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN char const* NS(Context_selected_node_id_str)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(Context_get_copy_of_selected_node_id_str)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    char* SIXTRL_RESTRICT node_id_str, NS(context_size_t) const max_length );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_select_node_by_node_id)(
    NS(ContextBase)* SIXTRL_RESTRICT ctx,
    NS(context_node_id_t) const node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN bool
NS(Context_select_node_by_platform_device_ids)(
    NS(ContextBase)* SIXTRL_RESTRICT ctx,
    NS(context_platform_id_t) const platform_idx,
    NS(context_device_id_t)  const device_idx );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Context_select_node)(
    NS(ContextBase)* SIXTRL_RESTRICT ctx,
    const char *const SIXTRL_RESTRICT node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN bool NS(Contet_select_node_by_index)(
    NS(ContextBase)* SIXTRL_RESTRICT ctx,
    NS(context_size_t) const index );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_out_all_nodes_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_out_nodes_info_by_index)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_out_nodes_info_by_node_id)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    NS(context_node_id_t) const node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_out_nodes_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_out_selected_nodes_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- */

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_all_nodes_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_nodes_info_by_index)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    NS(context_size_t) const index );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_nodes_info_by_node_id)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    NS(context_node_id_t) const node_id );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_nodes_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp,
    char const* SIXTRL_RESTRICT node_id_str );

SIXTRL_EXTERN SIXTRL_HOST_FN void NS(Context_print_selected_nodes_info)(
    const NS(ContextBase) *const SIXTRL_RESTRICT ctx,
    SIXTRL_ARGPTR_DEC FILE* SIXTRL_RESTRICT fp );

#endif /* !defined( __CUDA_ARCH ) && !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
}
#endif /* C++, Host */

#endif /* SIXTRACKLIB_COMMON_CONTEXT_NODE_BASE_H__ */

/* end: sixtracklib/common/context/context_node_base.h */