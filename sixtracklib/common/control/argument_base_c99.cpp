#include "sixtracklib/common/control/argument_base.h"

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

#include <cstddef>
#include <cstdlib>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/argument_base.hpp"
#include "sixtracklib/common/control/controller_base.hpp"


::NS(arch_id_t) NS(Argument_get_arch_id)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->archId() : ::NS(ARCHITECTURE_ILLEGAL);
}

bool NS(Argument_has_arch_string)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( ( arg != nullptr ) && ( arg->hasArchStr() ) );
}

char const* NS(Argument_get_arch_string)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->ptrArchStr() : nullptr;
}

::NS(controller_status_t) NS(Argument_send_again)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr )
        ? arg->send() : ::NS(CONTROLLER_STATUS_GENERAL_FAILURE);
}

::NS(controller_status_t) NS(Argument_send_buffer)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg,
    const ::NS(Buffer) *const SIXTRL_RESTRICT_REF buffer )
{
    return ( arg != nullptr )
        ? arg->send( buffer ) : ::NS(CONTROLLER_STATUS_GENERAL_FAILURE);
}

::NS(controller_status_t) NS(Argument_send_memory)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg,
    void const* SIXTRL_RESTRICT arg_begin,
    ::NS(controller_size_t) const arg_size )
{
    return ( arg != nullptr ) ? arg->send( arg_begin, arg_size )
        : ::NS(CONTROLLER_STATUS_GENERAL_FAILURE);
}

::NS(controller_status_t) NS(Argument_receive_again)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->receive()
        : ::NS(CONTROLLER_STATUS_GENERAL_FAILURE);
}

::NS(controller_status_t) NS(Argument_receive_buffer)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg,
    ::NS(Buffer)* SIXTRL_RESTRICT buf )
{
    return ( arg != nullptr )
        ? arg->receive( buf ) : ::NS(CONTROLLER_STATUS_GENERAL_FAILURE);
}

::NS(controller_status_t) NS(Argument_receive_memory)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg, void* SIXTRL_RESTRICT arg_begin,
    ::NS(controller_size_t) const arg_capacity )
{
    return ( arg != nullptr )
        ? arg->receive( arg_begin, arg_capacity )
        : ::NS(CONTROLLER_STATUS_GENERAL_FAILURE);
}

bool NS(Argument_uses_cobjects_buffer)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->usesCObjectsBuffer() : false;
}

::NS(Buffer) const* NS(Argument_get_const_cobjects_buffer)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->ptrCObjectsBuffer() : nullptr;
}

::NS(Buffer)* NS(Argument_get_cobjects_buffer)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->ptrCObjectsBuffer() : nullptr;
}


bool NS(Argument_is_using_raw_argument)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->usesRawArgument() : false;
}

void const* NS(Argument_get_const_ptr_raw_argument)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->ptrRawArgument() : nullptr;
}

void* NS(Argument_get_ptr_raw_argument)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->ptrRawArgument() : nullptr;
}

::NS(controller_size_t) NS(Argument_get_size)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->size() : ::NS(controller_size_t){ 0 };
}

::NS(controller_size_t) NS(Argument_get_capacity)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->capacity() : ::NS(controller_size_t){ 0 };
}

bool NS(Argument_has_argument_buffer)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->hasArgumentBuffer() : false;
}

bool NS(Argument_requires_argument_buffer)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->requiresArgumentBuffer() : false;
}

::NS(ControllerBase)* NS(Argument_get_ptr_base_controller)(
    ::NS(ArgumentBase)* SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->ptrBaseController() : nullptr;
}

::NS(ControllerBase) const* NS(Argument_get_const_ptr_base_controller)(
    const ::NS(ArgumentBase) *const SIXTRL_RESTRICT arg )
{
    return ( arg != nullptr ) ? arg->ptrBaseController() : nullptr;
}

#endif /* C++, Host */

/* end: sixtracklib/common/control/argument_base_c99.cpp */
