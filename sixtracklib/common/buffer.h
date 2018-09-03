#ifndef SIXTRACKLIB_COMMON_BUFFER_H__
#define SIXTRACKLIB_COMMON_BUFFER_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <limits.h>
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/_impl/definitions.h"
    #include "sixtracklib/_impl/modules.h"
    #include "sixtracklib/common/impl/buffer_type.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( SIXTRL_ARGPTR_DEC )
    #define SIXTRL_UNDEF_ARGPTR_DEC
    #define SIXTRL_ARGPTR_DEC
#endif /* defined( SIXTRL_ARGPTR_DEC ) */

#if !defined( SIXTRL_DATAPTR_DEC )
    #define SIXTRL_UNDEF_DATAPTR_DEC
    #define SIXTRL_DATAPTR_DEC
#endif /* defined( SIXTRL_ARGPTR_DEC ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */

struct NS(BufferGarbage);

SIXTRL_FN SIXTRL_STATIC struct NS(BufferGarbage)* NS(BufferGarbage_preset)(
    struct NS(BufferGarbage)* SIXTRL_RESTRICT garbage_range );

SIXTRL_FN SIXTRL_STATIC NS(buffer_addr_t) NS(BufferGarbage_get_begin_addr)(
    const struct NS(BufferGarbage) *const SIXTRL_RESTRICT garbage_range );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(BufferGarbage_get_size)(
    const struct NS(BufferGarbage) *const SIXTRL_RESTRICT garbage_range );

SIXTRL_FN SIXTRL_STATIC void NS(BufferGarbage_set_begin_addr)(
    struct NS(BufferGarbage)* SIXTRL_RESTRICT garbage_range,
    NS(buffer_addr_t) const begin_addr );

SIXTRL_FN SIXTRL_STATIC void NS(BufferGarbage_set_size)(
    struct NS(BufferGarbage)* SIXTRL_RESTRICT garbage_range,
    NS(buffer_size_t) const range_size );

/* ------------------------------------------------------------------------- */

struct NS(Buffer);

SIXTRL_FN SIXTRL_STATIC  NS(Buffer)* NS(Buffer_preset)(
   NS(Buffer)* SIXTRL_RESTRICT buffer );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_slot_size)(
   const NS(Buffer) *const SIXTRL_RESTRICT buffer );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(buffer_flags_t) NS(Buffer_get_flags)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_owns_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_uses_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_has_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_allow_modify_datastore_contents)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_allow_clear)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_allow_append_objects)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_allow_delete_objects)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_allow_remapping)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_allow_resize)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_uses_mempool_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_uses_special_opencl_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_uses_special_cuda_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_flags_t)
NS(Buffer_get_datastore_special_flags)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC void NS(Buffer_set_datastore_special_flags)(
    NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_flags_t) const flags );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(buffer_addr_t) NS(Buffer_get_datastore_begin_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_capacity)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_header_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_addr_t) NS(Buffer_get_data_begin_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_addr_t) NS(Buffer_get_data_end_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(buffer_addr_t) NS(Buffer_get_objects_begin_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_addr_t) NS(Buffer_get_objects_end_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_section_header_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_slots_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_num_of_slots)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_max_num_of_slots)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_objects_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC  NS(buffer_size_t) NS(Buffer_get_num_of_objects)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_max_num_of_objects)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_dataptrs_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC  NS(buffer_size_t) NS(Buffer_get_num_of_dataptrs)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_max_num_of_dataptrs)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t) NS(Buffer_get_garbage_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC  NS(buffer_size_t)
NS(Buffer_get_num_of_garbage_ranges)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t)
NS(Buffer_get_max_num_of_garbage_ranges)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC int NS(Buffer_reserve)(
    NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const new_max_num_objects,
    NS(buffer_size_t) const new_max_num_slots,
    NS(buffer_size_t) const new_max_num_dataptrs,
    NS(buffer_size_t) const new_max_num_garbage_elems );

SIXTRL_FN SIXTRL_STATIC int NS(Buffer_remap)(
    NS(Buffer)* SIXTRL_RESTRICT buffer );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( _GPUCODE )

SIXTRL_HOST_FN NS(Buffer)* NS(Buffer_new)(
    NS(buffer_size_t) const buffer_capacity );

SIXTRL_HOST_FN NS(Buffer)* NS(Buffer_new_detailed)(
    NS(buffer_size_t)  const initial_max_num_objects,
    NS(buffer_size_t)  const initial_max_num_slots,
    NS(buffer_size_t)  const initial_max_num_dataptrs,
    NS(buffer_size_t)  const initial_max_num_garbage_elements,
    NS(buffer_flags_t) const buffer_flags );

#endif /* !defined( _GPUCODE ) */

SIXTRL_FN SIXTRL_STATIC int NS(Buffer_init)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC unsigned char* SIXTRL_RESTRICT begin,
    NS(buffer_size_t) const data_buffer_capacity );

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC void NS(Buffer_free)(
    NS(Buffer)* SIXTRL_RESTRICT buffer );

SIXTRL_FN SIXTRL_STATIC int NS(Buffer_clear)(
    NS(Buffer)* SIXTRL_RESTRICT buffer, bool const set_data_to_zero );

#if !defined( _GPUCODE )

SIXTRL_HOST_FN SIXTRL_STATIC void NS(Buffer_delete)(
    NS(Buffer)* SIXTRL_RESTRICT buffer );

#endif /* !defined( _GPUCODE ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_FN SIXTRL_STATIC NS(buffer_size_t)
NS(Buffer_predict_required_num_slots)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const  SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const  object_size,
    NS(buffer_size_t)                   const  num_obj_dataptrs,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT counts );


SIXTRL_FN SIXTRL_STATIC bool NS(Buffer_can_add_object)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const  SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const  object_size,
    NS(buffer_size_t)                   const  num_obj_dataptrs,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT counts,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT requ_num_dataptrs );


SIXTRL_FN SIXTRL_STATIC SIXTRL_ARGPTR_DEC NS(Object)* NS(Buffer_add_object)(
    SIXTRL_ARGPTR_DEC NS(Buffer)*       SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const void *const SIXTRL_RESTRICT object_handle,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const  object_size,
    NS(object_type_id_t)                const  type_id,
    NS(buffer_size_t)                   const  num_obj_dataptrs,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT counts );

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

/* ************************************************************************* */
/* *******             Implementation of inline functions            ******* */
/* ************************************************************************* */

/* For plain C/Cxx */

#if !defined( SIXTRL_NO_INCLUDES)
    #include "sixtracklib/common/impl/buffer_type.h"
    #include "sixtracklib/common/impl/managed_buffer_minimal.h"
    #include "sixtracklib/common/impl/managed_buffer_remap.h"
    #include "sixtracklib/common/impl/managed_buffer.h"
    #include "sixtracklib/common/impl/buffer_object.h"
    #include "sixtracklib/common/impl/buffer_generic.h"

    #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
               ( SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1 )
        #include "sixtracklib/opencl/buffer.h"
    #endif /* OpenCL */

    #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
               ( SIXTRACKLIB_ENABLE_MODULE_CUDA == 1 )
        #include "sixtracklib/cuda/buffer.h"
    #endif /* Cuda */

#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

SIXTRL_INLINE NS(BufferGarbage)* NS(BufferGarbage_preset)(
    struct NS(BufferGarbage)* SIXTRL_RESTRICT garbage_range )
{
    NS(BufferGarbage_set_begin_addr)( garbage_range, 0 );
    NS(BufferGarbage_set_size)( garbage_range, 0u );

    return garbage_range;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_addr_t) NS(BufferGarbage_get_begin_addr)(
    const struct NS(BufferGarbage) *const SIXTRL_RESTRICT garbage_range )
{
    return ( garbage_range != SIXTRL_NULLPTR )
        ? garbage_range->begin_addr : ( NS(buffer_addr_t) )0u;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_size_t) NS(BufferGarbage_get_size)(
    const struct NS(BufferGarbage) *const SIXTRL_RESTRICT garbage_range )
{
    return ( garbage_range != SIXTRL_NULLPTR )
        ? garbage_range->size : ( NS(buffer_size_t) )0u;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(BufferGarbage_set_begin_addr)(
    struct NS(BufferGarbage)* SIXTRL_RESTRICT garbage_range,
    NS(buffer_addr_t) const begin_addr )
{
    if( garbage_range != SIXTRL_NULLPTR )
    {
        garbage_range->begin_addr = begin_addr;
    }

    return;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE void NS(BufferGarbage_set_size)(
    struct NS(BufferGarbage)* SIXTRL_RESTRICT garbage_range,
    NS(buffer_size_t) const range_size )
{
    if( garbage_range != SIXTRL_NULLPTR )
    {
        garbage_range->size = range_size;
    }

    return;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(Buffer)* NS(Buffer_preset)( NS(Buffer)* SIXTRL_RESTRICT buf )
{
    if( buf != SIXTRL_NULLPTR )
    {
        buf->data_addr        = ( NS(buffer_addr_t)  )0u;
        buf->data_size        = ( NS(buffer_size_t)  )0u;
        buf->header_size      = NS(BUFFER_DEFAULT_HEADER_SIZE);
        buf->data_capacity    = ( NS(buffer_size_t)  )0u;

        buf->slot_length      = NS(BUFFER_DEFAULT_SLOT_SIZE);

        buf->object_addr      = ( NS(buffer_addr_t)  )0u;
        buf->num_objects      = ( NS(buffer_size_t)  )0u;

        buf->datastore_flags  = ( NS(buffer_flags_t) )0;
        buf->datastore_addr   = ( NS(buffer_addr_t)  )0u;
    }

    return buf;
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_slot_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( buffer != SIXTRL_NULLPTR )
        ? buffer->slot_length : ( NS(buffer_size_t) )0u;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_STATIC SIXTRL_FN bool NS(Buffer_check_for_flags)(
    const NS(Buffer)  *const SIXTRL_RESTRICT buffer,
    NS(buffer_flags_t) const flags_to_check )
{
    return ( ( buffer != SIXTRL_NULLPTR ) &&
        ( ( buffer->datastore_flags & flags_to_check ) == flags_to_check ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_flags_t) NS(Buffer_get_flags)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( buffer != SIXTRL_NULLPTR)
        ? buffer->datastore_flags : NS(BUFFER_FLAGS_NONE);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_owns_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer, NS(BUFFER_OWNS_DATASTORE) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_uses_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( ( NS(Buffer_has_datastore)( buffer ) ) &&
        ( NS(Buffer_check_for_flags)(
            buffer, NS(BUFFER_USES_DATASTORE) ) ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_has_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( ( buffer != SIXTRL_NULLPTR ) &&
             ( buffer->datastore_addr != ( NS(buffer_addr_t) )0u ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_allow_modify_datastore_contents)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return (
        ( NS(Buffer_allow_clear)( buffer ) ) &&
        ( ( NS(Buffer_allow_append_objects)( buffer ) ) ||
          ( NS(Buffer_allow_delete_objects)( buffer ) ) ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_allow_clear)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer,
        NS(BUFFER_DATASTORE_ALLOW_CLEAR) | NS(BUFFER_USES_DATASTORE) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_allow_append_objects)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer,
        NS(BUFFER_DATASTORE_ALLOW_APPENDS) | NS(BUFFER_USES_DATASTORE) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_allow_delete_objects)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer,
        NS(BUFFER_DATASTORE_ALLOW_DELETES)  | NS(BUFFER_USES_DATASTORE) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_allow_remapping)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer,
        NS(BUFFER_DATASTORE_ALLOW_REMAPPING) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE bool NS(Buffer_allow_resize)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer,
        NS(BUFFER_DATASTORE_ALLOW_RESIZE) |
        NS(BUFFER_USES_DATASTORE) | NS(BUFFER_OWNS_DATASTORE) );
}

SIXTRL_INLINE bool NS(Buffer_uses_mempool_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer,
        NS(BUFFER_USES_DATASTORE) |
        NS(BUFFER_DATASTORE_MEMPOOL) );
}

SIXTRL_INLINE bool NS(Buffer_uses_special_opencl_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer,
        NS(BUFFER_USES_DATASTORE) |
        NS(BUFFER_DATASTORE_OPENCL) );
}

SIXTRL_INLINE bool NS(Buffer_uses_special_cuda_datastore)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return NS(Buffer_check_for_flags)( buffer,
        NS(BUFFER_USES_DATASTORE) |
        NS(BUFFER_DATASTORE_CUDA) );
}

SIXTRL_INLINE NS(buffer_flags_t)
NS(Buffer_get_datastore_special_flags)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef NS(buffer_flags_t) flags_t;

    flags_t   flags = buffer->datastore_flags;
    flags &=  NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK);
    flags >>= NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS);

    return flags;
}

SIXTRL_INLINE void NS(Buffer_set_datastore_special_flags)(
    NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_flags_t) const flags )
{
    typedef NS(buffer_flags_t) flags_t;

    flags_t const temp = ( flags & (
        NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK) >>
        NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS) ) ) <<
            NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS);

    buffer->datastore_flags &= ~( NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK) );
    buffer->datastore_flags |= temp;

    return;
}

SIXTRL_INLINE NS(buffer_addr_t) NS(Buffer_get_datastore_begin_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef NS(buffer_addr_t) address_t;

    return ( NS(Buffer_has_datastore)( buffer ) )
         ? ( buffer->datastore_addr )
         : ( address_t )0u;
}

/* -------------------------------------------------------------------------- */

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( buffer != SIXTRL_NULLPTR )
        ? ( buffer->data_size ) : ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_capacity)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( buffer != SIXTRL_NULLPTR )
        ? ( buffer->data_capacity ) : ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_header_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    return ( buffer != SIXTRL_NULLPTR )
        ? ( buffer->header_size ) : ( NS(buffer_size_t) )0u;
}

SIXTRL_INLINE NS(buffer_addr_t) NS(Buffer_get_data_begin_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    NS(buffer_addr_t) const begin_addr = ( buffer != SIXTRL_NULLPTR )
        ? ( buffer->data_addr ) : ( NS(buffer_addr_t ) )0u;

    SIXTRL_ASSERT(
        ( NS(Buffer_get_slot_size)( buffer ) > ( NS(buffer_size_t) )0u ) &&
        ( ( begin_addr % NS(Buffer_get_slot_size)( buffer ) ) == 0u ) );

    return begin_addr;
}

SIXTRL_INLINE NS(buffer_addr_t) NS(Buffer_get_data_end_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    NS(buffer_addr_t) end_addr = NS(Buffer_get_data_begin_addr)( buffer );

    if( end_addr != ( NS(buffer_size_t) )0u )
    {
        end_addr += NS(Buffer_get_size)( buffer );
    }

    SIXTRL_ASSERT(
        ( NS(Buffer_get_slot_size)( buffer ) > ( NS(buffer_size_t) )0u ) &&
        ( ( end_addr % NS(Buffer_get_slot_size)( buffer ) ) == 0u ) );

    return end_addr;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


SIXTRL_INLINE NS(buffer_addr_t) NS(Buffer_get_objects_begin_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    NS(buffer_addr_t) const begin_addr = ( buffer != SIXTRL_NULLPTR )
        ? ( buffer->object_addr ) : ( NS(buffer_addr_t ) )0u;

    SIXTRL_ASSERT(
        ( NS(Buffer_get_slot_size)( buffer ) > ( NS(buffer_size_t) )0u ) &&
        ( ( begin_addr % NS(Buffer_get_slot_size)( buffer ) ) == 0u ) );

    return begin_addr;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_addr_t) NS(Buffer_get_objects_end_addr)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef NS(buffer_size_t) buf_size_t;
    typedef NS(buffer_addr_t) address_t;

    SIXTRL_STATIC_VAR buf_size_t const ZERO_SIZE = ( buf_size_t )0u;

    address_t end_addr = NS(Buffer_get_objects_begin_addr)( buffer );

    if( end_addr != ZERO_SIZE )
    {
        buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );
        buf_size_t const obj_size  = NS(ManagedBuffer_get_slot_based_length)(
            sizeof( NS(Object) ), slot_size );

        SIXTRL_ASSERT( buffer    != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( slot_size != ZERO_SIZE );
        SIXTRL_ASSERT( obj_size  != ZERO_SIZE );

        end_addr += obj_size * buffer->num_objects;

        SIXTRL_ASSERT( ( end_addr % slot_size ) == 0u );
        SIXTRL_ASSERT( end_addr < NS(Buffer_get_data_end_addr)( buffer ) );
    }

    return end_addr;
}

/* ========================================================================= */

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_section_header_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const* ptr_to_raw_t;

    return NS(ManagedBuffer_get_section_header_length)(
        ( ptr_to_raw_t )( uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ),
            NS(Buffer_get_slot_size)( buffer ) );
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_slots_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )3u;

    return NS(ManagedBuffer_get_section_size)( ( ptr_to_raw_t )( uintptr_t
        )NS(Buffer_get_data_begin_addr)( buffer ), SECTION_ID,
            NS(Buffer_get_slot_size)( buffer ) );
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_num_of_slots)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )3u;

    return NS(ManagedBuffer_get_section_num_entities)(
        ( ptr_to_raw_t )( uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ),
            SECTION_ID, NS(Buffer_get_slot_size)( buffer ) );
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_max_num_of_slots)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )3u;

    return NS(ManagedBuffer_get_section_max_num_entities)( ( ptr_to_raw_t )(
        uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ), SECTION_ID,
            NS(Buffer_get_slot_size)( buffer ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_objects_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )4u;

    return NS(ManagedBuffer_get_section_size)( ( ptr_to_raw_t )( uintptr_t
        )NS(Buffer_get_data_begin_addr)( buffer ), SECTION_ID,
            NS(Buffer_get_slot_size)( buffer ) );
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_num_of_objects)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )4u;

    #if !defined( NDEBUG )
    buf_size_t const cmp_num_objects = ( buffer != SIXTRL_NULLPTR )
        ? ( buffer->num_objects ) : ( buf_size_t )0u;
    #endif /* !defined( NDEBUG ) */

    buf_size_t const num_objects = NS(ManagedBuffer_get_section_num_entities)(
        ( ptr_to_raw_t )( uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ),
            SECTION_ID, NS(Buffer_get_slot_size)( buffer ) );

    #if !defined( NDEBUG )
    SIXTRL_ASSERT( num_objects == cmp_num_objects );
    #endif /* !defined( NDEBUG ) */

    return num_objects;
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_max_num_of_objects)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )4u;

    return NS(ManagedBuffer_get_section_max_num_entities)( ( ptr_to_raw_t )(
        uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ), SECTION_ID,
            NS(Buffer_get_slot_size)( buffer ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_dataptrs_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )5u;

    return NS(ManagedBuffer_get_section_size)( ( ptr_to_raw_t )( uintptr_t
        )NS(Buffer_get_data_begin_addr)( buffer ), SECTION_ID,
            NS(Buffer_get_slot_size)( buffer ) );
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_num_of_dataptrs)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )5u;

    return NS(ManagedBuffer_get_section_num_entities)(
        ( ptr_to_raw_t )( uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ),
            SECTION_ID, NS(Buffer_get_slot_size)( buffer ) );
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_max_num_of_dataptrs)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )5u;

    return NS(ManagedBuffer_get_section_max_num_entities)( ( ptr_to_raw_t )(
        uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ), SECTION_ID,
            NS(Buffer_get_slot_size)( buffer ) );
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_garbage_size)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )6u;

    return NS(ManagedBuffer_get_section_size)( ( ptr_to_raw_t )( uintptr_t
        )NS(Buffer_get_data_begin_addr)( buffer ), SECTION_ID,
            NS(Buffer_get_slot_size)( buffer ) );
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_num_of_garbage_ranges)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )6u;

    return NS(ManagedBuffer_get_section_num_entities)(
        ( ptr_to_raw_t )( uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ),
            SECTION_ID, NS(Buffer_get_slot_size)( buffer ) );
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_get_max_num_of_garbage_ranges)(
    const NS(Buffer) *const SIXTRL_RESTRICT buffer )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char const*  ptr_to_raw_t;
    typedef NS(buffer_size_t)                       buf_size_t;

    SIXTRL_STATIC_VAR buf_size_t const SECTION_ID = ( buf_size_t )6u;

    return NS(ManagedBuffer_get_section_max_num_entities)( ( ptr_to_raw_t )(
        uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ), SECTION_ID,
            NS(Buffer_get_slot_size)( buffer ) );
}

/* ========================================================================= */

SIXTRL_INLINE int NS(Buffer_reserve)(
    NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const max_num_objects,
    NS(buffer_size_t) const max_num_slots,
    NS(buffer_size_t) const max_num_dataptrs,
    NS(buffer_size_t) const max_num_garbage_elems )
{
    int success = -1;

    if( NS(Buffer_uses_datastore)( buffer ) )
    {
        #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
             SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1

        if( NS(Buffer_uses_special_opencl_datastore)( buffer ) )
        {
            success = NS(Buffer_reserve_opencl)( buffer, max_num_objects,
                max_num_slots, max_num_dataptrs, max_num_garbage_elems );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_OPENCL */

        #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
             SIXTRACKLIB_ENABLE_MODULE_CUDA == 1

        if( NS(Buffer_uses_special_cuda_datastore)( buffer ) )
        {
            success = NS(Buffer_reserve_cuda)( buffer, max_num_objects,
                max_num_slots, max_num_dataptrs, max_num_garbage_elems );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_CUDA */

        {
            success = NS(Buffer_reserve_generic)( buffer, max_num_objects,
                max_num_slots, max_num_dataptrs, max_num_garbage_elems );
        }
    }

    return success;
}

SIXTRL_INLINE int NS(Buffer_remap)( NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    int success = -1;

    if( ( NS(Buffer_has_datastore)( buffer ) ) &&
        ( NS(Buffer_allow_remapping)( buffer ) ) )
    {
        #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
             SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1

        if( NS(Buffer_uses_special_opencl_datastore)( buffer ) )
        {
            success = NS(Buffer_remap_opencl)( buffer );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_OPENCL */

        #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
             SIXTRACKLIB_ENABLE_MODULE_CUDA == 1

        if( NS(Buffer_uses_special_cuda_datastore)( buffer ) )
        {
            success = NS(Buffer_remap_cuda)( buffer );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_CUDA */

        {
            success = NS(Buffer_remap_generic)( buffer );
        }
    }

    return success;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE int NS(Buffer_init)(
    SIXTRL_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC unsigned char* SIXTRL_RESTRICT begin,
    NS(buffer_size_t) const data_buffer_capacity )
{
    typedef NS(buffer_size_t)               buf_size_t;
    typedef NS(buffer_addr_t)               address_t;
    typedef SIXTRL_ARGPTR_DEC address_t*    ptr_to_addr_t;

    SIXTRL_STATIC_VAR buf_size_t const ZERO_SIZE = ( buf_size_t )0u;

    int success = -1;

    buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

    if( ( buffer == SIXTRL_NULLPTR ) || ( slot_size == ZERO_SIZE ) )
    {
        return success;
    }

    if( begin != SIXTRL_NULLPTR )
    {
        ptr_to_addr_t ptr_header = ( ptr_to_addr_t )begin;

        SIXTRL_ASSERT( ( ( ( uintptr_t )begin ) % slot_size ) == 0u );

        if( ptr_header[ 0 ] == ( address_t )0u )
        {
            success = NS(Buffer_init_on_flat_memory)(
                buffer, begin, data_buffer_capacity );
        }
        else
        {
            success = NS(Buffer_init_from_data)(
                buffer, begin, data_buffer_capacity );
        }
    }

    return success;
}

/* ------------------------------------------------------------------------- */

SIXTRL_INLINE int NS(Buffer_clear)(
    NS(Buffer)* SIXTRL_RESTRICT buffer, bool const set_data_to_zero )
{
    int success = -1;

    if( ( NS(Buffer_has_datastore)( buffer ) ) &&
        ( NS(Buffer_allow_clear)(   buffer ) ) )
    {
        #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
             SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1

        if( NS(Buffer_uses_special_opencl_datastore)( buffer ) )
        {
            success = NS(Buffer_clear_opencl)( buffer );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_OPENCL */

        #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
            SIXTRACKLIB_ENABLE_MODULE_CUDA == 1

        if( NS(Buffer_uses_special_cuda_datastore)( buffer ) )
        {
            success = NS(Buffer_clear_cuda)( buffer );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_CUDA */

        {
            success = NS(Buffer_clear_generic)( buffer, set_data_to_zero );
        }
    }

    return success;
}

SIXTRL_INLINE void NS(Buffer_free)( NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    if( NS(Buffer_owns_datastore)( buffer ) )
    {
        #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
             SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1

        if( NS(Buffer_uses_special_opencl_datastore)( buffer ) )
        {
            NS(Buffer_free_opencl)( buffer );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_OPENCL */

        #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
             SIXTRACKLIB_ENABLE_MODULE_CUDA == 1

        if( NS(Buffer_uses_special_cuda_datastore)( buffer ) )
        {
            NS(Buffer_free_cuda)( buffer );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_CUDA */

        {
            NS(Buffer_free_generic)( buffer );
        }
    }

    return;
}

SIXTRL_INLINE NS(buffer_size_t) NS(Buffer_predict_required_num_slots)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const  SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const  object_size,
    NS(buffer_size_t)                   const  num_obj_dataptrs,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT obj_attr_sizes,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT obj_attr_counts )
{
    typedef SIXTRL_ARGPTR_DEC unsigned char* ptr_to_raw_t;

    return NS(ManagedBuffer_predict_required_num_slots)(
        ( ptr_to_raw_t )( uintptr_t )NS(Buffer_get_data_begin_addr)( buffer ),
        object_size, num_obj_dataptrs, obj_attr_sizes, obj_attr_counts,
            NS(Buffer_get_slot_size)( buffer ) );
}

SIXTRL_INLINE bool NS(Buffer_can_add_object)(
    SIXTRL_ARGPTR_DEC const NS(Buffer) *const  SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const  object_size,
    NS(buffer_size_t)                   const  num_obj_dataptrs,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT obj_attr_sizes,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT obj_attr_counts,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_num_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_num_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_num_dataptrs)
{
    bool success = false;

    typedef NS(buffer_size_t) buf_size_t;

    if( ( NS(Buffer_allow_append_objects)( buffer ) ) &&
        ( object_size > ( buf_size_t )0u ) )
    {
        buf_size_t requ_num_objects  = ( buf_size_t )0u;
        buf_size_t requ_num_slots    = ( buf_size_t )0u;
        buf_size_t requ_num_dataptrs = ( buf_size_t )0u;

        buf_size_t const max_num_slots =
            NS(Buffer_get_max_num_of_slots)( buffer );

        buf_size_t const max_num_objects =
            NS(Buffer_get_max_num_of_objects)( buffer );

        buf_size_t const max_num_dataptrs =
            NS(Buffer_get_max_num_of_dataptrs)( buffer );

        buf_size_t const slot_size = NS(Buffer_get_slot_size)( buffer );

        if( ptr_requ_num_objects == SIXTRL_NULLPTR )
        {
            ptr_requ_num_objects  = &requ_num_objects;
        }

        if( ptr_requ_num_slots == SIXTRL_NULLPTR )
        {
            ptr_requ_num_slots =  &requ_num_slots;
        }

        if( ptr_requ_num_dataptrs == SIXTRL_NULLPTR )
        {
            ptr_requ_num_dataptrs =  &requ_num_dataptrs;
        }

        SIXTRL_ASSERT( ptr_requ_num_objects  != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( ptr_requ_num_slots    != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( ptr_requ_num_dataptrs != SIXTRL_NULLPTR );
        SIXTRL_ASSERT( slot_size != ( buf_size_t )0u );

        *ptr_requ_num_objects  =
            NS(Buffer_get_num_of_objects)( buffer ) + ( buf_size_t )1u;

        *ptr_requ_num_dataptrs =
            NS(Buffer_get_num_of_dataptrs)( buffer ) + num_obj_dataptrs;

        *ptr_requ_num_slots = NS(Buffer_get_num_of_slots)( buffer ) +
            NS(Buffer_predict_required_num_slots)( buffer, object_size,
                num_obj_dataptrs, obj_attr_sizes, obj_attr_counts );

        if( ( max_num_objects  >= *ptr_requ_num_objects  ) &&
            ( max_num_slots    >= *ptr_requ_num_slots    ) &&
            ( max_num_dataptrs >= *ptr_requ_num_dataptrs ) )
        {
            success = true;
        }
        else
        {
            *ptr_requ_num_objects =
                ( *ptr_requ_num_objects <= max_num_objects )
                    ? ( buf_size_t )0u
                    : ( max_num_objects - *ptr_requ_num_objects );

            *ptr_requ_num_slots =
                ( *ptr_requ_num_slots <= max_num_slots )
                    ? ( buf_size_t )0u
                    : ( max_num_slots - *ptr_requ_num_slots );

            *ptr_requ_num_dataptrs =
                ( *ptr_requ_num_dataptrs <= max_num_dataptrs )
                    ? ( buf_size_t )0u
                    : ( max_num_dataptrs - *ptr_requ_num_dataptrs );
        }
    }

    return success;
}

SIXTRL_INLINE SIXTRL_ARGPTR_DEC NS(Object)* NS(Buffer_add_object)(
    SIXTRL_ARGPTR_DEC NS(Buffer)*       SIXTRL_RESTRICT buffer,
    SIXTRL_ARGPTR_DEC const void *const SIXTRL_RESTRICT obj_handle,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const  obj_size,
    NS(object_type_id_t)                const  type_id,
    NS(buffer_size_t)                   const  num_obj_dataptrs,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT offsets,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT sizes,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t) const* SIXTRL_RESTRICT counts )
{
    SIXTRL_ARGPTR_DEC NS(Object)* ptr_added_object = SIXTRL_NULLPTR;

    if( ( NS(Buffer_has_datastore)( buffer ) ) &&
        ( NS(Buffer_allow_append_objects)( buffer ) ) )
    {
        typedef SIXTRL_ARGPTR_DEC NS(Object)* ptr_to_obj_t;

        #if defined( SIXTRACKLIB_ENABLE_MODULE_OPENCL ) && \
                     SIXTRACKLIB_ENABLE_MODULE_OPENCL == 1

        if( NS(Buffer_uses_special_opencl_datastore)( buffer ) )
        {
            ptr_added_object = ( ptr_to_obj_t )( uintptr_t
                )NS(Buffer_add_object_opencl)( buffer, obj_handle, obj_size,
                    type_id, num_obj_dataptrs, offsets, sizes, counts );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_OPENCL */


        #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
                     SIXTRACKLIB_ENABLE_MODULE_CUDA == 1

        if( NS(Buffer_uses_special_cuda_datastore)( buffer ) )
        {
            ptr_added_object = ( ptr_to_obj_t )( uintptr_t
                )NS(Buffer_add_object_cuda)( buffer, obj_handle, obj_size,
                    type_id, num_obj_dataptrs, offsets, sizes, counts );
        }
        else
        #endif /* SIXTRACKLIB_ENABLE_MODULE_CUDA */

        {
            ptr_added_object = ( ptr_to_obj_t )( uintptr_t
                )NS(Buffer_add_object_generic)( buffer, obj_handle, obj_size,
                    type_id, num_obj_dataptrs, offsets, sizes, counts );
        }
    }

    return ptr_added_object;
}

#if !defined( _GPUCODE )

SIXTRL_INLINE void NS(Buffer_delete)( NS(Buffer)* SIXTRL_RESTRICT buffer )
{
    NS(Buffer_free)( buffer );
    free( buffer );
    buffer = SIXTRL_NULLPTR;

    return;
}

#endif /* !defined( _GPUCODE ) */

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#if defined( SIXTRL_UNDEF_ARGPTR_DEC )
    #undef SIXTRL_UNDEF_ARGPTR_DEC
    #undef SIXTRL_ARGPTR_DEC
#endif /* defined( SIXTRL_UNDEF_ARGPTR_DEC ) */

#if defined( SIXTRL_UNDEF_DATAPTR_DEC )
    #undef SIXTRL_UNDEF_DATAPTR_DEC
    #undef SIXTRL_DATAPTR_DEC
#endif /* defined( SIXTRL_UNDEF_DATAPTR_DEC ) */

#endif /* SIXTRACKLIB_COMMON_BUFFER_H__ */

/* end: sixtracklib/common/buffer.h */
