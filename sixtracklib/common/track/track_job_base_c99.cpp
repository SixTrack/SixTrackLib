#include "sixtracklib/common/track/track_job_base.h"

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/control/node_id.hpp"
#include "sixtracklib/common/control/arch_base.hpp"
#include "sixtracklib/common/track/definitions.h"
#include "sixtracklib/common/track/track_job_base.hpp"

namespace st = SIXTRL_CXX_NAMESPACE;

::NS(TrackJobBaseNew)* NS(TrackJobNew_create)(
    char const* SIXTRL_RESTRICT arch_str,
    char const* SIXTRL_RESTRICT config_str )
{
    return st::TrackJobNew_create( arch_str, config_str );
}

::NS(TrackJobBaseNew)* NS(TrackJobNew_new)(
    char const* SIXTRL_RESTRICT arch_str,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    char const* SIXTRL_RESTRICT config_str )
{
    return st::TrackJobNew_new(
        arch_str, particles_buffer, beam_elem_buffer, config_str );
}

::NS(TrackJobBaseNew)* NS(TrackJobNew_new_with_output)(
    char const* SIXTRL_RESTRICT arch_str,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    ::NS(buffer_size_t) const dump_elem_by_elem_turns,
    char const* SIXTRL_RESTRICT config_str )
{
    return st::TrackJobNew_new(
        arch_str, particles_buffer, beam_elem_buffer, output_buffer,
            dump_elem_by_elem_turns, config_str );
}

::NS(TrackJobBaseNew)* NS(TrackJobNew_new_detailed)(
    char const* SIXTRL_RESTRICT arch_str,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(buffer_size_t) const num_particle_sets,
    ::NS(buffer_size_t) const* SIXTRL_RESTRICT pset_indices_begin,
    ::NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    ::NS(buffer_size_t) const dump_elem_by_elem_turns,
    char const* SIXTRL_RESTRICT config_str )
{
    return st::TrackJobNew_new( arch_str, particles_buffer,
        num_particle_sets, pset_indices_begin, beam_elem_buffer, output_buffer,
            dump_elem_by_elem_turns, config_str );
}

/* ------------------------------------------------------------------------- */

void NS(TrackJobNew_delete)( ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    if( job != nullptr ) delete job;
}

::NS(track_status_t) NS(TrackJobNew_track_until)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(buffer_size_t) const until_turn )
{
    return ( job != nullptr )
        ? job->trackUntil( until_turn ) : ::NS(TRACK_STATUS_GENERAL_FAILURE);
}

::NS(track_status_t) NS(TrackJobNew_track_elem_by_elem)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(buffer_size_t) const until_turn )
{
    return ( job != nullptr )
        ? job->trackElemByElem( until_turn )
        : ::NS(TRACK_STATUS_GENERAL_FAILURE);
}

::NS(track_status_t) NS(TrackJobNew_track_line)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(buffer_size_t) const belem_begin_index,
    ::NS(buffer_size_t) const belem_end_index,
    bool const finish_turn )
{
    return ( job != nullptr )
        ? job->trackLine( belem_begin_index, belem_end_index, finish_turn )
        : ::NS(TRACK_STATUS_GENERAL_FAILURE);
}

/* ------------------------------------------------------------------------- */

::NS(track_job_collect_flag_t) NS(TrackJobNew_collect)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->collect() : ::NS(TRACK_JOB_COLLECT_NONE);
}

::NS(track_job_collect_flag_t) NS(TrackJobNew_collect_detailed)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(track_job_collect_flag_t) const flags )
{
    return ( job != nullptr )
        ? job->collect( flags ) : ::NS(TRACK_JOB_COLLECT_NONE);
}

::NS(arch_status_t) NS(TrackJobNew_collect_particles)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->collectParticles() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(TrackJobNew_collect_beam_elements)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->collectBeamElements() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(TrackJobNew_collect_output)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->collectOutput() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(TrackJobNew_collect_debug_flag)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->collectDebugFlag() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

void NS(TrackJobNew_enable_collect_particles)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    if( job != nullptr ) job->enableCollectParticles();
}

void NS(TrackJobNew_disable_collect_particles)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    if( job != nullptr ) job->disableCollectParticles();
}

bool NS(TrackJobNew_is_collecting_particles)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->isCollectingParticles() : false;
}

void NS(TrackJobNew_enable_collect_beam_elements)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    if( job != nullptr ) job->enableCollectBeamElements();
}

void NS(TrackJobNew_disable_collect_beam_elements)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    if( job != nullptr ) job->disableCollectBeamElements();
}

bool NS(TrackJobNew_is_collecting_beam_elements)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->isCollectingBeamElements() : false;
}

void NS(TrackJobNew_enable_collect_output)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    if( job != nullptr ) job->enableCollectOutput();
}

void NS(TrackJobNew_disable_collect_output)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    if( job != nullptr ) job->disableCollectOutput();
}

bool NS(TrackJobNew_is_collecting_output)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->isCollectingOutput() : false;
}

::NS(track_job_collect_flag_t) NS(TrackJobNew_get_collect_flags)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->collectFlags() : ::NS(TRACK_JOB_COLLECT_DEFAULT_FLAGS);
}

void NS(TrackJobNew_set_collect_flags)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(track_job_collect_flag_t) const flags )
{
    if( job != nullptr ) job->setCollectFlags( flags );
}

bool NS(TrackJobNew_requires_collecting)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->requiresCollecting() : false;
}

/* ------------------------------------------------------------------------- */

bool NS(TrackJobNew_can_fetch_particle_addresses)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( ( job != nullptr ) && ( job->canFetchParticleAddresses() ) );
}
    
bool NS(TrackJobNew_has_particle_addresses)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( ( job != nullptr ) && ( job->hasParticleAddresses() ) );
}

::NS(arch_status_t) NS(TrackJobNew_fetch_particle_addresses)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) 
        ? job->fetchParticleAddresses() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}
        
::NS(arch_status_t) NS(TrackJobNew_clear_particle_addresses)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(buffer_size_t) const particle_set_index )
{
    return ( job != nullptr ) 
        ? job->clearParticleAddresses( particle_set_index ) 
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}
        
::NS(arch_status_t) NS(TrackJobNew_clear_all_particle_addresses)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) 
        ? job->clearAllParticleAddresses() 
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}
    
::NS(ParticlesAddr) const* NS(TrackJobNew_get_particle_addresses)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job,
    ::NS(buffer_size_t) const particle_set_index )
{
    return ( job != nullptr ) ? job->particleAddresses() : nullptr;
}

::NS(Buffer) const* NS(TrackJobNew_get_ptr_particle_addresses_buffer)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrCParticleAddressesBuffer() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(TrackJobNew_is_in_debug_mode)(
    const NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( ( job != nullptr ) && ( job->isInDebugMode() ) );
}

::NS(arch_status_t) NS(TrackJobNew_enable_debug_mode)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->enableDebugMode() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(TrackJobNew_disable_debug_mode)(
    NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->disableDebugMode() : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

/* ------------------------------------------------------------------------- */

void NS(TrackJobNew_clear)( NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    if( job != nullptr ) job->clear();
}

::NS(arch_status_t) NS(TrackJobNew_reset)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT ptr_output_buffer )
{
    return ( job != nullptr )
        ? job->reset( particles_buffer, beam_elem_buffer, ptr_output_buffer )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(TrackJobNew_reset_particle_set)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(buffer_size_t) const particle_set_index,
    ::NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT output_buffer )
{
    return ( job != nullptr ) ? job->reset( particles_buffer,
            particle_set_index, beam_elem_buffer, output_buffer )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}


::NS(arch_status_t) NS(TrackJobNew_reset_with_output)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    ::NS(buffer_size_t) const dump_elem_by_elem_turns )
{
    return ( job != nullptr )
        ? job->reset( particles_buffer, beam_elem_buffer, output_buffer,
                      dump_elem_by_elem_turns )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t)  NS(TrackJobNew_reset_detailed)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(buffer_size_t) const num_particle_sets,
    ::NS(buffer_size_t) const* SIXTRL_RESTRICT particle_set_indices_begin,
    ::NS(Buffer)* SIXTRL_RESTRICT beam_elem_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
    ::NS(buffer_size_t) const dump_elem_by_elem_turns )
{
    return ( job != nullptr ) ? job->reset( particles_buffer, num_particle_sets,
            particle_set_indices_begin, beam_elem_buffer, output_buffer,
                dump_elem_by_elem_turns )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t)  NS(TrackJobNew_select_particle_set)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(buffer_size_t) const particle_set_index )
{
    return ( job != nullptr )
        ? job->selectParticleSet( particle_set_index )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

::NS(arch_status_t) NS(TrackJobNew_assign_output_buffer)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    ::NS(Buffer)* SIXTRL_RESTRICT ptr_output_buffer )
{
    return ( job != nullptr )
        ? job->assignOutputBuffer( ptr_output_buffer )
        : ::NS(ARCH_STATUS_GENERAL_FAILURE);
}

/* ------------------------------------------------------------------------- */

::NS(track_job_type_t) NS(TrackJobNew_get_arch_id)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->archId() : ::NS(ARCHITECTURE_ILLEGAL);
}

char const* NS(TrackJobNew_get_arch_string)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrArchStr() : nullptr;
}

bool NS(TrackJobNew_has_config_str)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->hasConfigStr() : false;
}

char const* NS(TrackJobNew_get_config_str)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->configStr().c_str() : nullptr;
}

/* ------------------------------------------------------------------------- */

NS(buffer_size_t) NS(TrackJobNew_get_num_particle_sets)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->numParticleSets() : ::NS(buffer_size_t){ 0 };
}

NS(buffer_size_t) const* NS(TrackJobNew_get_particle_set_indices_begin)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->particleSetIndicesBegin() : nullptr;
}

NS(buffer_size_t) const* NS(TrackJobNew_get_particle_set_indices_end)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->particleSetIndicesEnd() : nullptr;
}

NS(buffer_size_t) NS(TrackJobNew_get_particle_set_index)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job,
    ::NS(buffer_size_t) const n )
{
    SIXTRL_ASSERT( job != nullptr );
    return job->particleSetIndex( n );
}

/* ------------------------------------------------------------------------- */

::NS(buffer_size_t) NS(TrackJobNew_get_total_num_of_particles)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->totalNumParticles() : ::NS(buffer_size_t){ 0 };
}

NS(particle_index_t) NS(TrackJobNew_get_min_particle_id)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    using index_t = ::NS(particle_index_t);
    return ( job != nullptr ) ? job->minParticleId() : index_t{ -1 };
}

NS(particle_index_t) NS(TrackJobNew_get_max_particle_id)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    using index_t = ::NS(particle_index_t);
    return ( job != nullptr ) ? job->maxParticleId() : index_t{ -1 };
}

NS(particle_index_t) NS(TrackJobNew_get_min_element_id)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    using index_t = ::NS(particle_index_t);
    return ( job != nullptr ) ? job->minElementId() : index_t{ -1 };
}

NS(particle_index_t) NS(TrackJobNew_get_max_element_id)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    using index_t = ::NS(particle_index_t);
    return ( job != nullptr ) ? job->maxElementId() : index_t{ -1 };
}

NS(particle_index_t) NS(TrackJobNew_get_min_initial_turn_id)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    using index_t = ::NS(particle_index_t);
    return ( job != nullptr ) ? job->minInitialTurnId() : index_t{ -1 };
}

NS(particle_index_t) NS(TrackJobNew_get_max_initial_turn_id)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    using index_t = ::NS(particle_index_t);
    return ( job != nullptr ) ? job->maxInitialTurnId() : index_t{ -1 };
}

/* ------------------------------------------------------------------------- */

NS(Buffer)* NS(TrackJobNew_get_particles_buffer)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrCParticlesBuffer() : nullptr;
}

NS(Buffer) const* NS(TrackJobNew_get_const_particles_buffer)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrCParticlesBuffer() : nullptr;
}

::NS(Buffer)* NS(TrackJobNew_get_beam_elements_buffer)(
    ::NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrCBeamElementsBuffer() : nullptr;
}

::NS(Buffer) const* NS(TrackJobNew_get_const_beam_elements_buffer)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrCBeamElementsBuffer() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(TrackJobNew_has_output_buffer)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->hasOutputBuffer() : false;
}

bool NS(TrackJobNew_owns_output_buffer)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ownsOutputBuffer() : false;
}

bool NS(TrackJobNew_has_elem_by_elem_output)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->hasElemByElemOutput() : false;
}

bool NS(TrackJobNew_has_beam_monitor_output)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->hasBeamMonitorOutput() : false;
}

::NS(buffer_size_t) NS(TrackJobNew_get_beam_monitor_output_buffer_offset)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    SIXTRL_ASSERT( job != nullptr );
    return job->beamMonitorsOutputBufferOffset();
}

::NS(buffer_size_t) NS(TrackJobNew_get_elem_by_elem_output_buffer_offset)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    SIXTRL_ASSERT( job != nullptr );
    return job->elemByElemOutputBufferOffset();
}

::NS(buffer_size_t) NS(TrackJobNew_get_num_elem_by_elem_turns)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->numElemByElemTurns() : ::NS(buffer_size_t){ 0 };
}

::NS(Buffer)* NS(TrackJobNew_get_output_buffer)(
    NS(TrackJobBaseNew)* SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrCOutputBuffer() : nullptr;
}

::NS(Buffer) const* NS(TrackJobNew_get_const_output_buffer)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrCOutputBuffer() : nullptr;
}

/* ------------------------------------------------------------------------- */

bool NS(TrackJobNew_has_beam_monitors)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->hasBeamMonitors() : false;
}

::NS(buffer_size_t) NS(TrackJobNew_get_num_beam_monitors)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->numBeamMonitors() : ::NS(buffer_size_t){ 0 };
}

::NS(buffer_size_t) const* NS(TrackJobNew_get_beam_monitor_indices_begin)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->beamMonitorIndicesBegin() : nullptr;
}

::NS(buffer_size_t) const* NS(TrackJobNew_get_beam_monitor_indices_end)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->beamMonitorIndicesEnd() : nullptr;
}

::NS(buffer_size_t) NS(TrackJobNew_get_beam_monitor_index)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job,
    NS(buffer_size_t) const n )
{
    return ( job != nullptr )
        ? job->beamMonitorIndex( n ) : ::NS(buffer_size_t){ 0 };
}

/* ------------------------------------------------------------------------- */

bool NS(TrackJobNew_has_elem_by_elem_config)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->hasElemByElemConfig() : false;
}

NS(ElemByElemConfig) const* NS(TrackJobNew_get_elem_by_elem_config)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->ptrElemByElemConfig() : nullptr;
}

bool NS(TrackJobNew_is_elem_by_elem_config_rolling)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->elemByElemRolling() : false;
}

bool NS(TrackJobNew_get_default_elem_by_elem_config_rolling_flag)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr ) ? job->defaultElemByElemRolling() : false;
}

void NS(TrackJobNew_set_default_elem_by_elem_config_rolling_flag)(
    NS(TrackJobBaseNew)* SIXTRL_RESTRICT job, bool const is_rolling_flag )
{
    if( job != nullptr )
    {
        job->setDefaultElemByElemRolling( is_rolling_flag );
    }

    return;
}

NS(elem_by_elem_order_t) NS(TrackJobNew_get_elem_by_elem_config_order)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->elemByElemOrder() : ::NS(ELEM_BY_ELEM_ORDER_INVALID);
}

NS(elem_by_elem_order_t) NS(TrackJobNew_get_default_elem_by_elem_config_order)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( job != nullptr )
        ? job->defaultElemByElemOrder()
        : ::NS(ELEM_BY_ELEM_ORDER_INVALID);
}

void NS(TrackJobNew_set_default_elem_by_elem_config_order)(
    NS(TrackJobBaseNew)* SIXTRL_RESTRICT job,
    NS(elem_by_elem_order_t) const order )
{
    if( job != nullptr )
    {
        job->setDefaultElemByElemOrder( order );
    }

    return;
}

/* ------------------------------------------------------------------------- */

bool NS(TrackJobNew_uses_controller)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( ( job != nullptr ) && ( job->usesController() ) );
}

bool NS(TrackJobNew_uses_arguments)(
    const ::NS(TrackJobBaseNew) *const SIXTRL_RESTRICT job )
{
    return ( ( job != nullptr ) && ( job->usesArguments() ) );
}

#endif /* C++, Host */

/* end: sixtracklib/common/track/track_job_base_c99.cpp */
