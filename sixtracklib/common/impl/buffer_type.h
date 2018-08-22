#ifndef SIXTRACKL_COMMON_IMPL_BUFFER_TYPE_H__
#define SIXTRACKL_COMMON_IMPL_BUFFER_TYPE_H__

#if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
    #if defined( __cplusplus )
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
    #else /* defined( __cplusplus ) */
        #include <stddef.h>
        #include <stdint.h>
        #include <stdlib.h>
        #include <limits.h>
    #endif /* defined( __cplusplus ) */
#endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/_impl/definitions.h"
#endif /* !defined( SIXTRL_NO_INCLUDES ) */

#if !defined( _GPUCODE )

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

/* ------------------------------------------------------------------------- */

typedef SIXTRL_UINT64_T NS(buffer_addr_t);
typedef SIXTRL_INT64_T  NS(buffer_addr_diff_t);
typedef SIXTRL_UINT64_T NS(buffer_size_t);
typedef SIXTRL_UINT64_T NS(buffer_flags_t);

typedef SIXTRL_UINT64_T NS(object_type_id_t);

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_NONE) = ( NS(object_type_id_t) )0x00000000;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_PARTICLE) = ( NS(object_type_id_t) )0x00000001;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_DRIFT) = ( NS(object_type_id_t) )0x00000002;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_DRIFT_EXACT) = ( NS(object_type_id_t) )0x00000003;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_MULTIPOLE) = ( NS(object_type_id_t) )0x00000004;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_CAVITY) = ( NS(object_type_id_t) )0x00000005;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_XYSHIFT) = ( NS(object_type_id_t) )0x00000006;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_SROTATION) = ( NS(object_type_id_t) )0x00000007;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_BEAM_BEAM_4D) = ( NS(object_type_id_t) )0x00000008;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_BEAM_BEAM_6D) = ( NS(object_type_id_t) )0x00000009;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_LINE) = ( NS(object_type_id_t) )0x00000100;

SIXTRL_STATIC_VAR NS(object_type_id_t) const
    NS(OBJECT_TYPE_INVALID) = ( NS(object_type_id_t) )0xffffffff;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_FLAGS_NONE)                   = ( NS(buffer_flags_t) )0x00000000;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_USES_DATASTORE)               = ( NS(buffer_flags_t) )0x00000001;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_OWNS_DATASTORE)               = ( NS(buffer_flags_t) )0x00000002;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_ALLOW_APPENDS)      = ( NS(buffer_flags_t) )0x00000004;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_ALLOW_CLEAR)        = ( NS(buffer_flags_t) )0x00000008;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_ALLOW_DELETES)      = ( NS(buffer_flags_t) )0x00000010;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_ALLOW_REMAPPING)    = ( NS(buffer_flags_t) )0x00000020;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_ALLOW_RESIZE)       = ( NS(buffer_flags_t) )0x00000040;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_MEMPOOL)            = ( NS(buffer_flags_t) )0x00010000;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_OPENCL)             = ( NS(buffer_flags_t) )0x00020000;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_CUDA)               = ( NS(buffer_flags_t) )0x00040000;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK) = ( NS(buffer_flags_t) )0xff000000;

SIXTRL_STATIC_VAR NS(buffer_flags_t) const
    NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS) = ( NS(buffer_flags_t) )24u;

/* ------------------------------------------------------------------------- */

SIXTRL_STATIC_VAR NS(buffer_size_t)  const
    NS(BUFFER_DEFAULT_SLOT_SIZE)            = ( NS(buffer_size_t) )8u;

SIXTRL_STATIC_VAR NS(buffer_size_t) const
    NS(BUFFER_DEFAULT_HEADER_SIZE)          = ( NS(buffer_size_t) )64u;

/* ------------------------------------------------------------------------- */

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#else

    #if !defined( NS(OBJECT_TYPE_NONE)         )
        #define NS(OBJECT_TYPE_NONE)         0x00000000
    #endif /* !defined( NS(OBJECT_TYPE_NONE)         ) */

    #if !defined( NS(OBJECT_TYPE_PARTICLE)     )
        #define NS(OBJECT_TYPE_PARTICLE)     0x00000001
    #endif /* !defined( NS(OBJECT_TYPE_PARTICLE)     ) */

    #if !defined( NS(OBJECT_TYPE_DRIFT)        )
        #define NS(OBJECT_TYPE_DRIFT)        0x00000002
    #endif /* !defined( NS(OBJECT_TYPE_DRIFT)        ) */

    #if !defined( NS(OBJECT_TYPE_DRIFT_EXACT)  )
        #define NS(OBJECT_TYPE_DRIFT_EXACT)  0x00000003
    #endif /* !defined( NS(OBJECT_TYPE_DRIFT_EXACT)  ) */

    #if !defined( NS(OBJECT_TYPE_MULTIPOLE)    )
        #define NS(OBJECT_TYPE_MULTIPOLE)    0x00000004
    #endif /* !defined( NS(OBJECT_TYPE_MULTIPOLE)    ) */

    #if !defined( NS(OBJECT_TYPE_CAVITY)       )
        #define NS(OBJECT_TYPE_CAVITY)       0x00000005
    #endif /* !defined( NS(OBJECT_TYPE_CAVITY)       ) */

    #if !defined( NS(OBJECT_TYPE_XYSHIFT)      )
        #define NS(OBJECT_TYPE_XYSHIFT)      0x00000006
    #endif /* !defined( NS(OBJECT_TYPE_XYSHIFT)      ) */

    #if !defined( NS(OBJECT_TYPE_SROTATION)    )
        #define NS(OBJECT_TYPE_SROTATION)    0x00000007
    #endif /* !defined( NS(OBJECT_TYPE_SROTATION)    ) */

    #if !defined( NS(OBJECT_TYPE_BEAM_BEAM_4D) )
        #define NS(OBJECT_TYPE_BEAM_BEAM_4D) 0x00000008
    #endif /* !defined( NS(OBJECT_TYPE_BEAM_BEAM_4D) ) */

    #if !defined( NS(OBJECT_TYPE_BEAM_BEAM_6D) )
        #define NS(OBJECT_TYPE_BEAM_BEAM_6D) 0x00000009
    #endif /* !defined( NS(OBJECT_TYPE_BEAM_BEAM_6D) ) */

    #if !defined( NS(OBJECT_TYPE_LINE)         )
        #define NS(OBJECT_TYPE_LINE)         0x00000100
    #endif /* !defined( NS(OBJECT_TYPE_LINE)         ) */

    #if !defined( NS(OBJECT_TYPE_INVALID)      )
        #define NS(OBJECT_TYPE_INVALID)      0xffffffff
    #endif /* !defined( NS(OBJECT_TYPE_INVALID)      ) */

    /* --------------------------------------------------------------------- */

   #if !defined( NS(BUFFER_FLAGS_NONE) )
       #define NS(BUFFER_FLAGS_NONE)                        0x00000000
   #endif /* !defined( NS(BUFFER_FLAGS_NONE) ) */

   #if !defined( NS(BUFFER_USES_DATASTORE) )
       #define NS(BUFFER_USES_DATASTORE)                    0x00000001
   #endif /* !defined( NS(BUFFER_USES_DATASTORE) ) */

   #if !defined( NS(BUFFER_OWNS_DATASTORE) )
       #define NS(BUFFER_OWNS_DATASTORE)                    0x00000002
   #endif /* !defined( NS(BUFFER_OWNS_DATASTORE) ) */

   #if !defined( NS(BUFFER_DATASTORE_ALLOW_APPENDS) )
       #define NS(BUFFER_DATASTORE_ALLOW_APPENDS)           0x00000004
   #endif /* !defined( NS(BUFFER_DATASTORE_ALLOW_APPENDS) ) */

   #if !defined( NS(BUFFER_DATASTORE_ALLOW_CLEAR) )
       #define NS(BUFFER_DATASTORE_ALLOW_CLEAR)             0x00000008
   #endif /* !defined( NS(BUFFER_DATASTORE_ALLOW_CLEAR) ) */

   #if !defined( NS(BUFFER_DATASTORE_ALLOW_DELETES) )
       #define NS(BUFFER_DATASTORE_ALLOW_DELETES)           0x00000010
   #endif /* !defined( NS(BUFFER_DATASTORE_ALLOW_DELETES) ) */

   #if !defined( NS(BUFFER_DATASTORE_ALLOW_REMAPPING) )
       #define NS(BUFFER_DATASTORE_ALLOW_REMAPPING)         0x00000020
    #endif /* !defined( NS(BUFFER_DATASTORE_ALLOW_REMAPPING) ) */

   #if !defined( NS(BUFFER_DATASTORE_ALLOW_RESIZE) )
       #define NS(BUFFER_DATASTORE_ALLOW_RESIZE)            0x00000040
   #endif /* !defined( NS(BUFFER_DATASTORE_ALLOW_RESIZE) ) */

    #if !defined( NS(BUFFER_DATASTORE_MEMPOOL) )
        #define NS(BUFFER_DATASTORE_MEMPOOL)                0x00010000
    #endif /* !defined( NS(BUFFER_DATASTORE_MEMPOOL) ) */

    #if !defined( NS(BUFFER_DATASTORE_OPENCL) )
        #define NS(BUFFER_DATASTORE_OPENCL)                 0x00020000
    #endif /* !defined( NS(BUFFER_DATASTORE_OPENCL) ) */

    #if !defined( NS(BUFFER_DATASTORE_CUDA) )
        #define NS(BUFFER_DATASTORE_CUDA)                   0x00040000
    #endif /* !defined( NS(BUFFER_DATASTORE_CUDA) ) */

    #if !defined( NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK) )
        #define NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK)     0xff000000
    #endif /* !defined( NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK) ) */

    #if !defined( NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS) )
        #define NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS)     24u
    #endif /* !defined( NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS) ) */

    #if !defined( NS(BUFFER_DEFAULT_SLOT_SIZE) )
        #define NS(BUFFER_DEFAULT_SLOT_SIZE) 8u
    #endif /* NS(BUFFER_DEFAULT_SLOT_SIZE) */

    #if !defined( NS(BUFFER_DEFAULT_HEADER_SIZE ) )
        #define NS(BUFFER_DEFAULT_HEADER_SIZE)              64u
    #endif /* !defined( NS(BUFFER_DEFAULT_HEADER_SIZE) ) */

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

typedef struct NS(Object)
{
    NS(buffer_addr_t)    begin_addr       SIXTRL_ALIGN( 8u );
    NS(object_type_id_t) type_id          SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    size             SIXTRL_ALIGN( 8u );
}
NS(Object);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

typedef struct NS(BufferGarbage)
{
    NS(buffer_addr_t)    begin_addr       SIXTRL_ALIGN( 8u );
    NS(buffer_addr_t)    size             SIXTRL_ALIGN( 8u );
}
NS(BufferGarbage);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

typedef struct NS(Buffer)
{
    NS(buffer_addr_t)    data_addr        SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    data_size        SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    header_size      SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    data_capacity    SIXTRL_ALIGN( 8u );

    NS(buffer_size_t)    slot_length      SIXTRL_ALIGN( 8u );

    NS(buffer_addr_t)    object_addr      SIXTRL_ALIGN( 8u );
    NS(buffer_size_t)    num_objects      SIXTRL_ALIGN( 8u );

    NS(buffer_flags_t)   datastore_flags  SIXTRL_ALIGN( 8u );
    NS(buffer_addr_t)    datastore_addr   SIXTRL_ALIGN( 8u );
}
NS(Buffer);

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined( __cplusplus )

namespace SIXTRL_NAMESPACE
{
    using object_type_id_t = NS(object_type_id_t);
    using buffer_addr_t    = NS(buffer_addr_t);
    using buffer_size_t    = NS(buffer_size_t);
    using buffer_flags_t   = NS(buffer_flags_t);

    using Buffer     = ::NS(Buffer);
    using Object     = ::NS(Object);

    /* --------------------------------------------------------------------- */

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_NONE         = NS(OBJECT_TYPE_NONE);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_PARTICLE     = NS(OBJECT_TYPE_PARTICLE);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_DRIFT        = NS(OBJECT_TYPE_DRIFT);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_DRIFT_EXACT  = NS(OBJECT_TYPE_DRIFT_EXACT);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_MULTIPOLE    = NS(OBJECT_TYPE_MULTIPOLE);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_CAVITY       = NS(OBJECT_TYPE_CAVITY);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_XYSHIFT      = NS(OBJECT_TYPE_XYSHIFT);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_SROTATION    = NS(OBJECT_TYPE_SROTATION);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_BEAM_BEAM_4D = NS(OBJECT_TYPE_BEAM_BEAM_4D);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_BEAM_BEAM_6D = NS(OBJECT_TYPE_BEAM_BEAM_6D);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_LINE         = NS(OBJECT_TYPE_LINE);

    static SIXTRL_CONSTEXPR_OR_CONST object_type_id_t
        OBJECT_TYPE_INVALID      = NS(OBJECT_TYPE_INVALID);

    /* --------------------------------------------------------------------- */

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_FLAGS_NONE = NS(BUFFER_FLAGS_NONE);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_USES_DATASTORE = NS(BUFFER_USES_DATASTORE);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_OWNS_DATASTORE = NS(BUFFER_OWNS_DATASTORE);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_APPENDS = NS(BUFFER_DATASTORE_ALLOW_APPENDS);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_CLEAR = NS(BUFFER_DATASTORE_ALLOW_CLEAR);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_DELETES = NS(BUFFER_DATASTORE_ALLOW_DELETES);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_REMAPPING =
            NS(BUFFER_DATASTORE_ALLOW_REMAPPING);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_ALLOW_RESIZE =
            NS(BUFFER_DATASTORE_ALLOW_RESIZE);

    /* --------------------------------------------------------------------- */

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_MEMPOOL = NS(BUFFER_DATASTORE_MEMPOOL);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_OPENCL = NS(BUFFER_DATASTORE_OPENCL);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_CUDA = NS(BUFFER_DATASTORE_CUDA);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_SPECIAL_FLAGS_MASK =
            NS(BUFFER_DATASTORE_SPECIAL_FLAGS_MASK);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_flags_t
        BUFFER_DATASTORE_SPECIAL_FLAGS_BITS =
            NS(BUFFER_DATASTORE_SPECIAL_FLAGS_BITS);

    /* --------------------------------------------------------------------- */

    static SIXTRL_CONSTEXPR_OR_CONST buffer_size_t
        BUFFER_DEFAULT_SLOT_SIZE   = NS(BUFFER_DEFAULT_SLOT_SIZE);

    static SIXTRL_CONSTEXPR_OR_CONST buffer_size_t
        BUFFER_DEFAULT_HEADER_SIZE = NS(BUFFER_DEFAULT_HEADER_SIZE);
}

#endif /* defined( __cplusplus ) */

#endif /* SIXTRACKL_COMMON_IMPL_BUFFER_TYPE_H__ */

/* end: sixtracklib/common/impl/buffer_type.h */
