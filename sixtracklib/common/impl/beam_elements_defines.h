#ifndef SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_DEFINES_H__
#define SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_DEFINES_H__

#if !defined( SIXTRL_BE_ARGPTR_DEC )
    #define SIXTRL_BE_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_ARGPTR_DEC )
        #define  SIXTRL_BE_ARGPTR_DEC SIXTRL_ARGPTR_DEC
    #else /* defined( SIXTRL_ARGPTR_DEC ) */
        #define  SIXTRL_BE_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_BE_ARGPTR_DEC ) */

#if !defined( SIXTRL_BE_DATAPTR_DEC )
    #define SIXTRL_BE_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_DATAPTR_DEC )
        #define  SIXTRL_BE_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* defined( SIXTRL_DATAPTR_DEC ) */
        #define  SIXTRL_BE_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_BE_DATAPTR_DEC ) */

#if !defined( SIXTRL_BE_BUFFER_ARGPTR_DEC )
    #define SIXTRL_BE_BUFFER_ARGPTR_DEC_UNDEF
    #if defined( SIXTRL_ARGPTR_DEC )
        #define SIXTRL_BE_BUFFER_ARGPTR_DEC SIXTRL_ARGPTR_DEC
    #else /* defined( SIXTRL_ARGPTR_DEC ) */
        #define SIXTRL_BE_BUFFER_ARGPTR_DEC
    #endif /* defined( SIXTRL_ARGPTR_DEC ) */
#endif /* !defined( SIXTRL_BE_BUFFER_ARGPTR_DEC ) */

#if !defined( SIXTRL_BE_BUFFER_DATAPTR_DEC )
    #define SIXTRL_BE_BUFFER_DATAPTR_DEC_UNDEF
    #if defined( SIXTRL_DATAPTR_DEC )
        #define SIXTRL_BE_BUFFER_DATAPTR_DEC SIXTRL_DATAPTR_DEC
    #else /* defined( SIXTRL_DATAPTR_DEC ) */
        #define SIXTRL_BE_BUFFER_DATAPTR_DEC
    #endif /* defined( SIXTRL_DATAPTR_DEC ) */
#endif /* !defined( SIXTRL_BE_BUFFER_DATAPTR_DEC ) */

#endif /* SIXTRACKLIB_COMMON_IMPL_BEAM_ELEMENTS_DEFINES_H__ */

/* end: sixtracklib/common/impl/beam_elements_defines.h */
