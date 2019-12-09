#include "sixtracklib/common/be_rfmultipole.h"

SIXTRL_BE_ARGPTR_DEC NS(RFMultiPole) const* NS(RFMultiPole_const_from_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{
}

SIXTRL_BE_ARGPTR_DEC NS(RFMultiPole)* NS(RFMultiPole_from_buffer)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(buffer_size_t) const index )
{

}

NS(arch_status_t) NS(RFMultiPole_attributes_offsets)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT offsets_begin,
    NS(buffer_size_t) const max_num_offsets,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(RFMultiPole) *const SIXTRL_RESTRICT data,
    NS(buffer_size_t) const slot_size )
{

}

NS(arch_status_t) NS(RFMultiPole_attributes_sizes)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT sizes_begin,
    NS(buffer_size_t) const max_num_sizes,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(RFMultiPole) *const SIXTRL_RESTRICT data,
    NS(buffer_size_t) const slot_size )
{

}

NS(arch_status_t) NS(RFMultiPole_attributes_counts)(
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT counts_begin,
    NS(buffer_size_t) const max_num_counts,
    SIXTRL_BUFFER_DATAPTR_DEC const NS(RFMultiPole) *const SIXTRL_RESTRICT data )
{

}

/* ------------------------------------------------------------------------- */

bool NS(RFMultiPole_can_be_added)(
    SIXTRL_BUFFER_ARGPTR_DEC const NS(Buffer) *const SIXTRL_RESTRICT buffer,
    NS(rf_multipole_int_t) const order,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_objects,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_slots,
    SIXTRL_ARGPTR_DEC NS(buffer_size_t)* SIXTRL_RESTRICT ptr_requ_dataptrs )
{

}

SIXTRL_BE_ARGPTR_DEC NS(RFMultiPole)*
NS(RFMultiPole_new)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(rf_multipole_int_t) const order )
{

}

SIXTRL_BE_ARGPTR_DEC NS(RFMultiPole)*
NS(RFMultiPole_add)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    NS(rf_multipole_int_t) const order,
    NS(rf_multipole_real_t) const voltage,
    NS(rf_multipole_real_t) const frequency,
    NS(rf_multipole_real_t) const lag,
    SIXTRL_ARGPTR_DEC NS(rf_multipole_real_t) const* SIXTRL_RESTRICT bal_values,
    SIXTRL_ARGPTR_DEC NS(rf_multipole_real_t) const* SIXTRL_RESTRICT p_values )
{

}

SIXTRL_BE_ARGPTR_DEC NS(RFMultiPole)*
NS(RFMultiPole_add_copy)(
    SIXTRL_BUFFER_ARGPTR_DEC NS(Buffer)* SIXTRL_RESTRICT buffer,
    SIXTRL_BUFFER_ARGPTR_DEC const NS(RFMultiPole) *const SIXTRL_RESTRICT mpole )
{

}

#endif /* !defined( _GPUCODE ) */
