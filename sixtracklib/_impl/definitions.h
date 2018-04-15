#ifndef SIXTRACKLIB__IMPL_DEFINITIONS_H__
#define SIXTRACKLIB__IMPL_DEFINITIONS_H__

#include "sixtracklib/_impl/namespace_begin.h"

#if !defined( _GPUCODE )
    #include <assert.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
#endif /* defined( _GPUCODE ) */

#if defined( _GPUCODE )
    
    /* ---------------------------------------------------------------- */
    /* assert: */
    
    #if !defined (SIXTRL_ASSERT )
        #define SIXTRL_ASSERT( expr )   
    #endif /* !defined( SIXTRL_ASSERT ) */
    
    /* ---------------------------------------------------------------- */
    /* Type abstracts : */
    
    #if !defined( SIXTRL_REAL_T )
        #define SIXTRL_REAL_T double 
    #endif /* !defined( SIXTRL_REAL_T ) */
    
    #if !defined( SIXTRL_FLOAT_T )
        #define SIXTRL_FLOAT_T float  
    #endif /* !defined( SIXTRL_FLOAT_T ) */
    
    #if !defined( SIXTRL_UINT64_T )
        #define SIXTRL_UINT64_T unsigned long
    #endif /* !defined( SIXTRL_UINT64_T ) */
    
    #if !defined( SIXTRL_INT64_T )
        #define SIXTRL_INT64_T long
    #endif /* !defined( SIXTRL_INT64_T ) */
    
    #if !defined( SIXTRL_UINT32_T )
        #define SIXTRL_UINT32_T unsigned int
    #endif /* !defined( SIXTRL_UINT32_T ) */
    
    #if !defined( SIXTRL_INT32_T )
        #define SIXTRL_INT32_T int
    #endif /* !defined( SIXTRL_INT32_T ) */
    
    #if !defined( SIXTRL_UINT16_T )
        #define SIXTRL_UINT16_T unsigned short int
    #endif /* !defined( SIXTRL_UINT32_T ) */
    
    #if !defined( SIXTRL_INT16_T )
        #define SIXTRL_INT16_T short int
    #endif /* !defined( SIXTRL_INT16_T ) */
    
    #if !defined( SIXTRL_UINT8_T )
        #define SIXTRL_UINT8_T unsigned char 
    #endif /* !defined( SIXTRL_UINT32_T ) */
    
    #if !defined( SIXTRL_INT8_T )
        #define SIXTRL_INT8_T char
    #endif /* !defined( SIXTRL_INT8_T ) */
    
    #if !defined( SIXTRL_SIZE_T )
        #define SIXTRL_SIZE_T  size_t
    #endif /* !defined( SIXTRL_SIZE_T ) */
    
    /* ---------------------------------------------------------------- */
    /* Type decorators -> these go in front of the SIXTRL_*_T type      */
    
    #if !defined( SIXTRL_PRIVATE_DEC )
        #define SIXTRL_PRIVATE_DEC 
    #endif /* !defined( SIXTRL_PRIVATE_DEC ) */
    
    #if !defined( SIXTRL_LOCAL_DEC )
        #define SIXTRL_LOCAL_DEC __local
    #endif /* !defined( SIXTRL_LOCAL_DEC ) */
    
    #if !defined( SIXTRL_GLOBAL_DEC )
        #define SIXTRL_GLOBAL_DEC __global
    #endif /* !defined( SIXTRL_GLOBAL_DEC ) */
    
    #if !defined( SIXTRL_CONSTANT_DEC )
        #define SIXTRL_CONSTANT_DEC __constant
    #endif /* !defined( SIXTRL_CONSTANT_DEC ) */
    
    /* ---------------------------------------------------------------- */
    /* kernel and restrict key word for kernel parameters: */
    
    #if !defined( SIXTRL_GPUKERNEL )
        #define SIXTRL_GPUKERNEL __kernel 
    #endif /* !defined( SIXTRL_GPU_KERNEL ) */
    
    #if !defined( SIXTRL_GPUKERNEL_RESTRICT )
        #define   SIXTRL_GPUKERNEL_RESTRICT restrict 
    #endif /* !defined( SIXTRL_KERNELPARAM_RESTRICT ) */
    
    #if !defined( SIXTRL_GPUKERNEL_RESTRICT_REF )
        #define   SIXTRL_GPUKERNEL_RESTRICT_REF 
    #endif /* !defined( SIXTRL_KERNELPARAM_RESTRICT_REF ) */
    
    /* ---------------------------------------------------------------- */
    /* static, inline and restrict keywords:                                    */
    
    #if !defined( SIXTRL_STATIC )
        #define SIXTRL_STATIC static
    #endif /* !defined( SIXTRL_STATIC ) */
    
    #if !defined( SIXTRL_INLINE )
        #define SIXTRL_INLINE inline 
    #endif /* !defined( SIXTRL_INLINE ) */
    
#else /* !defined( _GPUCODE ) */
    
    /* ----------------------------------------------------------------- */
    /* assert */
    
    #if !defined (SIXTRL_ASSERT )
        #define SIXTRL_ASSERT( expr ) assert( ( expr ) )  
    #endif /* !defined( SIXTRL_ASSERT ) */
    
    /* ---------------------------------------------------------------- */
    /* Types */
    
    #if !defined( SIXTRL_REAL_T )
        #define SIXTRL_REAL_T double 
    #endif /* !defined( SIXTRL_REAL_T ) */
    
    typedef SIXTRL_REAL_T NS(real_t);
    
    #if !defined( SIXTRL_FLOAT_T )
        #define SIXTRL_FLOAT_T float 
    #endif /* !defined( SIXTRL_FLOAT_T ) */
    
    typedef SIXTRL_FLOAT_T NS(float_t);
    
    #if !defined( SIXTRL_UINT64_T )
        #define SIXTRL_UINT64_T uint64_t
    #endif /* !defined( SIXTRL_UINT64_T ) */
    
    typedef SIXTRL_UINT64_T NS(uint64_t);
    
    #if !defined( SIXTRL_INT64_T )
        #define SIXTRL_INT64_T int64_t
    #endif /* !defined( SIXTRL_INT64_T ) */
    
    typedef SIXTRL_INT64_T NS(int64_t);
    
    #if !defined( SIXTRL_UINT32_T )
        #define SIXTRL_UINT32_T uint32_t
    #endif /* !defined( SIXTRL_UINT32_T ) */
    
    typedef SIXTRL_UINT32_T NS(uint32_t);
    
    #if !defined( SIXTRL_INT32_T )
        #define SIXTRL_INT32_T int
    #endif /* !defined( SIXTRL_INT32_T ) */
    
    typedef SIXTRL_INT32_T NS(int32_t);
    
    #if !defined( SIXTRL_UINT16_T )
        #define SIXTRL_UINT16_T uint16_t
    #endif /* !defined( SIXTRL_UINT16_T ) */
    
    typedef SIXTRL_UINT16_T NS(uint16_t);
    
    #if !defined( SIXTRL_INT16_T )
        #define SIXTRL_INT16_T int16_t
    #endif /* !defined( SIXTRL_INT16_T ) */
    
    typedef SIXTRL_INT16_T NS(int16_t);
    
    #if !defined( SIXTRL_UINT8_T )
        #define SIXTRL_UINT8_T uint8_t
    #endif /* !defined( SIXTRL_UINT8_T ) */
    
    typedef SIXTRL_UINT8_T NS(uint8_t);
    
    #if !defined( SIXTRL_INT8_T )
        #define SIXTRL_INT8_T int8_t
    #endif /* !defined( SIXTRL_INT8_T ) */
    
    typedef SIXTRL_INT8_T NS(int8_t);
    
    #if !defined( SIXTRL_SIZE_T )
        #define SIXTRL_SIZE_T  size_t
    #endif /* !defined( SIXTRL_SIZE_T ) */
    
    typedef SIXTRL_SIZE_T NS(size_t);
    
    /* ---------------------------------------------------------------- */
    /* Type decorators -> these go in front of the SIXTRL_*_T type      */
    
    #if !defined( SIXTRL_PRIVATE_DEC )
        #define SIXTRL_PRIVATE_DEC 
    #endif /* !defined( SIXTRL_PRIVATE_DEC ) */
    
    #if !defined( SIXTRL_LOCAL_DEC )
        #define SIXTRL_LOCAL_DEC 
    #endif /* !defined( SIXTRL_LOCAL_DEC ) */
    
    #if !defined( SIXTRL_GLOBAL_DEC )
        #define SIXTRL_GLOBAL_DEC 
    #endif /* !defined( SIXTRL_GLOBAL_DEC ) */
    
    #if !defined( SIXTRL_CONSTANT_DEC )
        #define SIXTRL_CONSTANT_DEC 
    #endif /* !defined( SIXTRL_CONSTANT_DEC ) */
    
    /* ---------------------------------------------------------------- */
    /* static, inline and restrict keywords: */
    
    #if !defined( SIXTRL_STATIC )
        #define SIXTRL_STATIC static
    #endif /* !defined( SIXTRL_STATIC ) */
    
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
    
    #if !defined( SIXTRL_INLINE )
        #define SIXTRL_INLINE inline 
    #endif /* !defined( SIXTRL_INLINE ) */
    
    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    
    #if defined( SIXTRL_RESTRICT )
        #undef  SIXTRL_RESTRICT
    #endif /* SIXTRL_RESTRICT */

    #if defined( SIXTRL_RESTRICT_REF )
        #undef  SIXTRL_RESTRICT_REF
    #endif /* SIXTRL_RESTRICT_REF */

    
    #ifdef __cplusplus

        #if ( ( defined( __clang__ ) ) || \
            ( ( ( defined( __GNUC__ ) ) && ( __GNUC__ >= 3 ) ) ) )
        
            #define SIXTRL_RESTRICT     __restrict__
            #define SIXTRL_RESTRICT_REF __restrict__
        
        #elif ( defined( _MSC_VER ) && _MSC_VER >= 1600 )
        
            #define SIXTRL_RESTRICT __restrict
        
        #endif /* ( defined( _MSC_VER ) && _MSC_VER >= 1600 ) */
        
    #else /* __cplusplus */
        
        #if ( ( defined( __clang__ ) ) || \
            ( ( ( defined( __GNUC__ ) ) && ( __GNUC__ >= 3 ) ) ) )
        
            #if ( __STDC_VERSION__ >= 199901L )
                #define SIXTRL_RESTRICT restrict /* TODO: Check if clang supports this! */
            #else
                #define SIXTRL_RESTRICT __restrict__
            #endif /* C99 support */
        
        #endif /* gcc/mingw or clang */
        
    #endif /*defined( __cplusplus ) */

    #ifndef SIXTRL_RESTRICT 
        #define SIXTRL_RESTRICT
    #endif /* SIXTRL_RESTRICT */

    #ifndef SIXTRL_RESTRICT_REF
        #define SIXTRL_RESTRICT_REF
    #endif /* SIXTRL_RESTRICT_REF */
        
    /* ---------------------------------------------------------------- */
    /* kernel and restrict key word for kernel parameters: */
    
    #if !defined( SIXTRL_GPUKERNEL )
        #define SIXTRL_GPUKERNEL 
    #endif /* !defined( SIXTRL_GPU_KERNEL ) */
    
    #if !defined( SIXTRL_GPUKERNEL_RESTRICT )
        #define   SIXTRL_GPUKERNEL_RESTRICT SIXTRL_RESTRICT
    #endif /* !defined( SIXTRL_KERNELPARAM_RESTRICT ) */
    
    #if !defined( SIXTRL_GPUKERNEL_RESTRICT_REF )
        #define   SIXTRL_GPUKERNEL_RESTRICT_REF SIXTRL_RESTRICT_REF
    #endif /* !defined( SIXTRL_KERNELPARAM_RESTRICT_REF ) */
    
#endif /* defined( _GPUCODE ) */



#if !defined( SIXTRACKLIB_COPY_VALUES )
    #if defined( _GPUCODE ) 
        #define SIXTRACKLIB_COPY_VALUES( T, dest, source, n )             \
        /* ----------------------------------------------------------- */ \
        /* ---- Inside SIXTRACKLIB_COPY_VALUES (ELEMENTWISE)       --- */ \
        /* ----------------------------------------------------------- */ \
        \
        SIXTRL_SIZE_T __ii = 0; \
        do{ *( ( dest ) + __ii ) = *( ( source ) + __ii ) } while( __ii < ( n ) )
        
    #elif !defined( _GPUCODE )
        #define SIXTRACKLIB_COPY_VALUES( T, dest, source, n )                 \
            /* ----------------------------------------------------------- */ \
            /* ----  Inside SIXTRACKLIB_COPY_VALUES (MEMCPY BASED)    ---- */ \
            /* ----------------------------------------------------------- */ \
            \
            assert( ( ( dest ) != 0 ) && ( ( source ) != 0 ) &&           \
                    ( ( n ) > ( SIXTRL_SIZE_T )( 0u ) ) );                \
            memcpy( ( dest ), ( source ), sizeof( T ) * ( n ) )

    #endif /* defined( _GPUCODE ) */
#endif /* defined( SIXTRACKLIB_COPY_VALUES ) */

            
#endif /* SIXTRACKLIB__IMPL_DEFINITIONS_H__ */
            
/* end: sixtracklib/_impl/definitions.h */
