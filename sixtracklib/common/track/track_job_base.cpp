#include "sixtracklib/common/track/track_job_base.hpp"

#if defined( __cplusplus ) && !defined( _GPUCODE ) && !defined( __CUDA_ARCH__ )
    #if !defined( SIXTRL_NO_SYSTEM_INCLUDES )
        #include <algorithm>
        #include <cstddef>
        #include <cstdint>
        #include <cstdlib>
        #include <memory>
        #include <string>
        #include <vector>
    #endif /* !defined( SIXTRL_NO_SYSTEM_INCLUDES ) */

#if !defined( SIXTRL_NO_INCLUDES )
    #include "sixtracklib/common/definitions.h"
    #include "sixtracklib/common/be_monitor/be_monitor.h"
    #include "sixtracklib/common/be_monitor/output_buffer.h"
    #include "sixtracklib/common/beam_elements.h"
    #include "sixtracklib/common/buffer.hpp"
    #include "sixtracklib/common/buffer.h"
    #include "sixtracklib/common/particles/definitions.h"
    #include "sixtracklib/common/particles/particles_addr.hpp"
    #include "sixtracklib/common/particles.h"
    #include "sixtracklib/common/output/output_buffer.h"
    #include "sixtracklib/common/output/elem_by_elem_config.h"
    #include "sixtracklib/common/control/definitions.h"
    #include "sixtracklib/common/control/node_id.hpp"
    #include "sixtracklib/common/control/arch_info.hpp"
    #include "sixtracklib/common/control/arch_base.hpp"
    #include "sixtracklib/common/track/definitions.h"

    #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
        SIXTRACKLIB_ENABLE_MODULE_CUDA == 1

    #include "sixtracklib/cuda/track_job.hpp"

    #endif /* CUDA */


#endif /* !defined( SIXTRL_NO_INCLUDES ) */

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    TrackJobBaseNew::size_type
    TrackJobBaseNew::DefaultNumParticleSetIndices() SIXTRL_NOEXCEPT
    {
        return st::TRACK_JOB_DEFAULT_NUM_PARTICLE_SETS;
    }

    TrackJobBaseNew::size_type const*
    TrackJobBaseNew::DefaultParticleSetIndicesBegin() SIXTRL_NOEXCEPT
    {
        return &st::TRACK_JOB_DEFAULT_PARTICLE_SET_INDICES[ 0 ];
    }

    TrackJobBaseNew::size_type const*
    TrackJobBaseNew::DefaultParticleSetIndicesEnd() SIXTRL_NOEXCEPT
    {
        TrackJobBaseNew::size_type const* end_ptr =
            TrackJobBaseNew::DefaultParticleSetIndicesBegin();

        std::advance( end_ptr, st::TRACK_JOB_DEFAULT_NUM_PARTICLE_SETS );
        return end_ptr;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::clear()
    {
        this->doClear();
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::collect_flag_t TrackJobBaseNew::collect()
    {
        return this->doCollect( this->m_collect_flags );
    }

    TrackJobBaseNew::collect_flag_t TrackJobBaseNew::collect(
        TrackJobBaseNew::collect_flag_t const flags )
    {
        return this->doCollect( flags & st::TRACK_JOB_COLLECT_ALL );
    }

    bool TrackJobBaseNew::collectParticles()
    {
        return st::TrackJobBaseNew::IsCollectFlagSet(
            this->doCollect( st::TRACK_JOB_COLLECT_PARTICLES ),
                st::TRACK_JOB_COLLECT_PARTICLES );
    }

    bool TrackJobBaseNew::collectBeamElements()
    {
        return st::TrackJobBaseNew::IsCollectFlagSet(
            this->doCollect( st::TRACK_JOB_COLLECT_BEAM_ELEMENTS ),
                st::TRACK_JOB_COLLECT_BEAM_ELEMENTS );
    }

    bool TrackJobBaseNew::collectOutput()
    {
        return TrackJobBaseNew::IsCollectFlagSet(
            this->doCollect( st::TRACK_JOB_COLLECT_OUTPUT ),
                st::TRACK_JOB_COLLECT_OUTPUT );
    }

    bool TrackJobBaseNew::collectSuccessFlag()
    {
        return TrackJobBaseNew::IsCollectFlagSet(
            this->doCollect( st::TRACK_JOB_COLLECT_SUCCESS_FLAG ),
                st::TRACK_JOB_COLLECT_SUCCESS_FLAG );
    }

    void TrackJobBaseNew::enableCollectParticles()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |= st::TRACK_JOB_COLLECT_PARTICLES;
    }

    void TrackJobBaseNew::disableCollectParticles() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBaseNew::UnsetCollectFlag(
            this->m_collect_flags, st::TRACK_JOB_COLLECT_PARTICLES );
    }

    bool TrackJobBaseNew::isCollectingParticles() const SIXTRL_NOEXCEPT
    {
        return TrackJobBaseNew::IsCollectFlagSet( this->m_collect_flags,
            st::TRACK_JOB_COLLECT_PARTICLES );
    }

    void TrackJobBaseNew::enableCollectBeamElements()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |= st::TRACK_JOB_COLLECT_BEAM_ELEMENTS;
    }

    void TrackJobBaseNew::disableCollectBeamElements() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBaseNew::UnsetCollectFlag(
            this->m_collect_flags, st::TRACK_JOB_COLLECT_BEAM_ELEMENTS );
    }

    bool TrackJobBaseNew::isCollectingBeamElements() const SIXTRL_NOEXCEPT
    {
        return TrackJobBaseNew::IsCollectFlagSet( this->m_collect_flags,
                st::TRACK_JOB_COLLECT_BEAM_ELEMENTS );
    }

    void TrackJobBaseNew::enableCollectOutput()  SIXTRL_NOEXCEPT
    {
        this->m_collect_flags |= st::TRACK_JOB_COLLECT_OUTPUT;
    }

    void TrackJobBaseNew::disableCollectOutput() SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = TrackJobBaseNew::UnsetCollectFlag(
            this->m_collect_flags, st::TRACK_JOB_COLLECT_OUTPUT );
    }

    bool TrackJobBaseNew::isCollectingOutput() const SIXTRL_NOEXCEPT
    {
        return TrackJobBaseNew::IsCollectFlagSet( this->m_collect_flags,
                st::TRACK_JOB_COLLECT_OUTPUT );
    }

    TrackJobBaseNew::collect_flag_t
    TrackJobBaseNew::collectFlags() const SIXTRL_NOEXCEPT
    {
        return this->m_collect_flags;
    }

    void TrackJobBaseNew::setCollectFlags(
        TrackJobBaseNew::collect_flag_t const flags ) SIXTRL_NOEXCEPT
    {
        this->m_collect_flags = ( flags & st::TRACK_JOB_COLLECT_ALL );
    }

    bool TrackJobBaseNew::requiresCollecting() const SIXTRL_NOEXCEPT
    {
        return this->m_requires_collect;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::status_t TrackJobBaseNew::fetchParticleAddresses()
    {
        return this->doFetchParticleAddresses();
    }

    bool TrackJobBaseNew::hasParticleAddresses() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( !this->m_has_particle_addresses ) ||
            ( ( this->m_has_particle_addresses ) &&
              ( this->doGetPtrParticlesAddrBuffer() == nullptr ) ) );

        return this->m_has_particle_addresses;
    }

    TrackJobBaseNew::particles_addr_t const*
    TrackJobBaseNew::particleAddresses(
        TrackJobBaseNew::size_type const index ) const SIXTRL_NOEXCEPT
    {
        using ptr_paddr_t = TrackJobBaseNew::particles_addr_t const*;
        ptr_paddr_t ptr_paddr = nullptr;

        if( ( this->doGetPtrParticlesAddrBuffer() != nullptr ) &&
            ( this->doGetPtrParticlesAddrBuffer()->getNumObjects() > index ) &&
            ( this->hasParticleAddresses() ) )
        {
            ptr_paddr = ::NS(ParticlesAddr_buffer_get_const_particle_addr)(
                this->doGetPtrParticlesAddrBuffer()->getCApiPtr(), index );
        }

        return ptr_paddr;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::track_status_t TrackJobBaseNew::trackUntil(
        TrackJobBaseNew::size_type const until_turn )
    {
        return this->doTrackUntilTurn( until_turn );
    }

    TrackJobBaseNew::track_status_t TrackJobBaseNew::trackElemByElem(
        TrackJobBaseNew::size_type const until_turn_elem_by_elem )
    {
        return this->doTrackElemByElem( until_turn_elem_by_elem );
    }

    TrackJobBaseNew::track_status_t TrackJobBaseNew::trackLine(
        TrackJobBaseNew::size_type const be_begin_index,
        TrackJobBaseNew::size_type const be_end_index,
        bool const finish_turn )
    {
        return this->doTrackLine( be_begin_index, be_end_index, finish_turn );
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBaseNew::reset(
        TrackJobBaseNew::buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
        TrackJobBaseNew::buffer_t& SIXTRL_RESTRICT_REF be_buffer,
        TrackJobBaseNew::buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        size_type const until_turn_elem_by_elem  )
    {
        using c_buffer_t = TrackJobBaseNew::c_buffer_t;

        this->doClear();

        c_buffer_t* ptr_pb  = particles_buffer.getCApiPtr();
        c_buffer_t* ptr_eb  = be_buffer.getCApiPtr();
        c_buffer_t* ptr_out = ( ptr_output_buffer != nullptr ) ?
            ptr_output_buffer->getCApiPtr() : nullptr;

        bool const success = this->doReset(
            ptr_pb, ptr_eb, ptr_out, until_turn_elem_by_elem );

        if( success )
        {
            this->doSetPtrParticleBuffer( &particles_buffer );
            this->doSetPtrBeamElementsBuffer( &be_buffer );

            if( ( ptr_out != nullptr ) && ( this->hasOutputBuffer() ) )
            {
                this->doSetPtrOutputBuffer( ptr_output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBaseNew::reset(
        TrackJobBaseNew::buffer_t& SIXTRL_RESTRICT_REF particles_buffer,
        TrackJobBaseNew::size_type const pset_index,
        TrackJobBaseNew::buffer_t& SIXTRL_RESTRICT_REF be_buffer,
        TrackJobBaseNew::buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBaseNew::size_type const until_turn_elem_by_elem  )
    {
        using size_t = TrackJobBaseNew::size_type;
        size_t const pset_indices[] = { pset_index, size_t{ 0 } };

        return TrackJobBaseNew::reset( particles_buffer, &pset_indices[ 0 ],
            &pset_indices[ 1 ], be_buffer, ptr_output_buffer,
                until_turn_elem_by_elem );
    }

    bool TrackJobBaseNew::reset(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBaseNew::size_type const until_turn_elem_by_elem  )
    {
        this->doClear();

        bool const success = this->doReset( particles_buffer, be_buffer,
                ptr_output_buffer, until_turn_elem_by_elem );

        if( success )
        {
            this->doSetPtrCParticleBuffer( particles_buffer );
            this->doSetPtrCBeamElementsBuffer( be_buffer );

            if( ( ptr_output_buffer != nullptr ) &&
                ( this->hasOutputBuffer() ) )
            {
                this->doSetPtrCOutputBuffer( ptr_output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBaseNew::reset(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBaseNew::size_type const particle_set_index,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBaseNew::size_type const until_turn_elem_by_elem  )
    {
        return TrackJobBaseNew::reset( particles_buffer,
            TrackJobBaseNew::size_type{ 1 }, &particle_set_index, be_buffer,
                ptr_output_buffer, until_turn_elem_by_elem );
    }

    bool TrackJobBaseNew::reset(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBaseNew::size_type const num_particle_sets,
        TrackJobBaseNew::size_type const* SIXTRL_RESTRICT pset_indices_begin,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT be_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT ptr_out_buffer,
        TrackJobBaseNew::size_type const until_turn_elem_by_elem  )
    {
        TrackJobBaseNew::size_type const* pset_end = pset_indices_begin;

        if( ( pset_end != nullptr ) &&
            ( num_particle_sets > TrackJobBaseNew::size_type{ 0 } ) )
        {
            std::advance( pset_end, num_particle_sets );
        }

        return this->reset( particles_buffer, pset_indices_begin, pset_end,
            be_buffer, ptr_out_buffer, until_turn_elem_by_elem );
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBaseNew::selectParticleSet(
        TrackJobBaseNew::size_type const particle_set_index )
    {
        using buffer_t   = TrackJobBaseNew::buffer_t;
        using c_buffer_t = TrackJobBaseNew::c_buffer_t;
        using size_t = TrackJobBaseNew::size_type;

        bool success = false;

        buffer_t*   ptr_particles_buffer   = this->ptrOutputBuffer();
        buffer_t*   ptr_beam_elem_buffer   = this->ptrBeamElementsBuffer();

        c_buffer_t* ptr_c_particles_buffer = this->ptrCParticlesBuffer();
        c_buffer_t* ptr_c_beam_elem_buffer = this->ptrCBeamElementsBuffer();

        if( ( ptr_c_particles_buffer != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( ptr_c_particles_buffer ) ) &&
            ( static_cast< size_t >( ::NS(Buffer_get_num_of_objects)(
                ptr_c_particles_buffer ) ) > particle_set_index ) &&
            ( ptr_c_beam_elem_buffer != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( ptr_c_beam_elem_buffer ) ) )
        {
            buffer_t* ptr_output_buffer = nullptr;
            c_buffer_t* ptr_c_output_buffer = nullptr;

            if( ( this->hasOutputBuffer() ) && ( !this->ownsOutputBuffer() ) )
            {
                ptr_output_buffer   = this->ptrOutputBuffer();
                ptr_c_output_buffer = this->ptrCOutputBuffer();

                SIXTRL_ASSERT( ::NS(Buffer_needs_remapping)(
                    ptr_c_output_buffer ) );
            }

            if( ( ptr_particles_buffer != nullptr ) &&
                ( ptr_beam_elem_buffer != nullptr ) )
            {
                SIXTRL_ASSERT(
                    ( ( ptr_output_buffer != nullptr ) &&
                      ( ptr_c_output_buffer != nullptr ) ) ||
                    ( ( ptr_output_buffer == nullptr ) &&
                      ( ptr_c_output_buffer == nullptr ) ) );

                SIXTRL_ASSERT(
                    ( ptr_particles_buffer->getCApiPtr() ==
                      ptr_c_particles_buffer ) &&
                    ( ptr_beam_elem_buffer->getCApiPtr() ==
                      ptr_c_beam_elem_buffer ) );

                if( ptr_c_output_buffer != nullptr )
                {
                    ::NS(Buffer_clear)( ptr_c_output_buffer, true );
                }

                size_t particle_set_indices[ 1 ] = { size_t{ 0 } };
                particle_set_indices[ 0 ] = particle_set_index;

                success = this->reset( *ptr_particles_buffer,
                    &particle_set_indices[ 0 ], &particle_set_indices[ 1 ],
                        *ptr_beam_elem_buffer, ptr_output_buffer,
                            this->untilTurnElemByElem() );
            }
            else if( ( ptr_c_particles_buffer != nullptr ) &&
                     ( ptr_c_beam_elem_buffer != nullptr ) )
            {
                if( ptr_c_output_buffer != nullptr )
                {
                    ::NS(Buffer_clear)( ptr_c_output_buffer, true );
                }

                success = this->reset( ptr_c_particles_buffer, size_t{ 1 },
                    &particle_set_index, ptr_c_beam_elem_buffer,
                        ptr_c_output_buffer, this->untilTurnElemByElem() );
            }
        }

        return success;
    }

    bool TrackJobBaseNew::assignOutputBuffer(
        TrackJobBaseNew::buffer_t& SIXTRL_RESTRICT_REF output_buffer )
    {
        bool success = false;

        if( this->doAssignNewOutputBuffer( output_buffer.getCApiPtr() ) )
        {
            if( this->hasOutputBuffer() )
            {
                SIXTRL_ASSERT( output_buffer.getCApiPtr() ==
                    this->ptrCOutputBuffer() );

                this->doSetPtrOutputBuffer( &output_buffer );
            }

            success = true;
        }

        return success;
    }

    bool TrackJobBaseNew::assignOutputBuffer(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer )
    {
        return this->doAssignNewOutputBuffer( ptr_output_buffer );
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::size_type
    TrackJobBaseNew::numParticleSets() const SIXTRL_NOEXCEPT
    {
        return this->m_particle_set_indices.size();
    }

    TrackJobBaseNew::size_type const*
    TrackJobBaseNew::particleSetIndicesBegin() const SIXTRL_NOEXCEPT
    {
        return this->m_particle_set_indices.data();
    }

    TrackJobBaseNew::size_type const*
    TrackJobBaseNew::particleSetIndicesEnd() const SIXTRL_NOEXCEPT
    {
        TrackJobBaseNew::size_type const* ptr =
            this->particleSetIndicesBegin();

        SIXTRL_ASSERT( ptr != nullptr );
        std::advance( ptr, this->numParticleSets() );
        return ptr;
    }

    TrackJobBaseNew::size_type
    TrackJobBaseNew::particleSetIndex(
        TrackJobBaseNew::size_type const idx ) const
    {
        return this->m_particle_set_indices.at( idx );
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::num_particles_t
    TrackJobBaseNew::totalNumParticles() const SIXTRL_NOEXCEPT
    {
        return this->m_total_num_particles;
    }

    TrackJobBaseNew::particle_index_t
    TrackJobBaseNew::minParticleId() const SIXTRL_NOEXCEPT
    {
        return this->m_min_particle_id;
    }

    TrackJobBaseNew::particle_index_t
    TrackJobBaseNew::maxParticleId() const SIXTRL_NOEXCEPT
    {
        return this->m_max_particle_id;
    }

    TrackJobBaseNew::particle_index_t
    TrackJobBaseNew::minElementId()  const SIXTRL_NOEXCEPT
    {
        return this->m_min_element_id;
    }

    TrackJobBaseNew::particle_index_t
    TrackJobBaseNew::maxElementId()  const SIXTRL_NOEXCEPT
    {
        return this->m_max_element_id;
    }

    TrackJobBaseNew::particle_index_t
    TrackJobBaseNew::minInitialTurnId() const SIXTRL_NOEXCEPT
    {
        return this->m_min_initial_turn_id;
    }

    TrackJobBaseNew::particle_index_t
    TrackJobBaseNew::maxInitialTurnId() const SIXTRL_NOEXCEPT
    {
        return this->m_max_initial_turn_id;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::success_flag_t
    TrackJobBaseNew::lastSuccessFlag() const SIXTRL_NOEXCEPT
    {
        return this->m_success_flag;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::buffer_t*
    TrackJobBaseNew::ptrParticlesBuffer() SIXTRL_NOEXCEPT
    {
        return const_cast< st::TrackJobBaseNew::buffer_t* >( static_cast<
            st::TrackJobBaseNew const& >( *this ).ptrParticlesBuffer() );
    }

    TrackJobBaseNew::buffer_t const*
    TrackJobBaseNew::ptrParticlesBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( this->m_ptr_particles_buffer == nullptr ) ||
            ( this->m_ptr_particles_buffer->getCApiPtr() ==
              this->m_ptr_c_particles_buffer ) );

        return this->m_ptr_particles_buffer;
    }

    TrackJobBaseNew::c_buffer_t*
    TrackJobBaseNew::ptrCParticlesBuffer() SIXTRL_NOEXCEPT
    {
        return const_cast< st::TrackJobBaseNew::c_buffer_t* >( static_cast<
            st::TrackJobBaseNew const& >( *this ).ptrCParticlesBuffer() );
    }

    TrackJobBaseNew::c_buffer_t const*
    TrackJobBaseNew::ptrCParticlesBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( this->m_ptr_particles_buffer == nullptr ) ||
            ( this->m_ptr_particles_buffer->getCApiPtr() ==
              this->m_ptr_c_particles_buffer ) );

        return this->m_ptr_c_particles_buffer;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::buffer_t*
    TrackJobBaseNew::ptrBeamElementsBuffer() SIXTRL_NOEXCEPT
    {
        return const_cast< st::TrackJobBaseNew::buffer_t* >( static_cast<
            st::TrackJobBaseNew const& >( *this ).ptrBeamElementsBuffer() );
    }

    TrackJobBaseNew::buffer_t const*
    TrackJobBaseNew::ptrBeamElementsBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( this->m_ptr_beam_elem_buffer == nullptr ) ||
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() ==
              this->m_ptr_c_beam_elem_buffer ) );

        return this->m_ptr_beam_elem_buffer;
    }

    TrackJobBaseNew::c_buffer_t*
    TrackJobBaseNew::ptrCBeamElementsBuffer() SIXTRL_NOEXCEPT
    {
        return const_cast< st::TrackJobBaseNew::c_buffer_t* >( static_cast<
            st::TrackJobBaseNew const& >( *this ).ptrCBeamElementsBuffer() );
    }

    TrackJobBaseNew::c_buffer_t const*
    TrackJobBaseNew::ptrCBeamElementsBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( this->m_ptr_beam_elem_buffer == nullptr ) ||
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() ==
              this->m_ptr_c_beam_elem_buffer ) );

        return this->m_ptr_c_beam_elem_buffer;
    }

    /* ---------------------------------------------------------------- */

    bool TrackJobBaseNew::hasOutputBuffer() const SIXTRL_NOEXCEPT
    {
        return ( this->ptrCOutputBuffer() != nullptr );
    }

    bool TrackJobBaseNew::ownsOutputBuffer() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( this->m_my_output_buffer.get() == nullptr ) ||
            ( ( this->m_my_output_buffer.get() ==
                this->m_ptr_output_buffer ) &&
              ( this->m_my_output_buffer->getCApiPtr() ==
                this->m_ptr_c_output_buffer ) ) );

        return ( ( this->ptrOutputBuffer() != nullptr ) &&
                 ( this->m_my_output_buffer.get() != nullptr ) );
    }

    bool TrackJobBaseNew::hasElemByElemOutput() const SIXTRL_NOEXCEPT
    {
        return this->m_has_elem_by_elem_output;
    }

    bool TrackJobBaseNew::hasBeamMonitorOutput() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( (  !this->m_has_beam_monitor_output ) ||
            ( ( this->m_has_beam_monitor_output ) &&
              ( this->m_ptr_c_output_buffer != nullptr ) ) );

        return this->m_has_beam_monitor_output;
    }

    TrackJobBaseNew::size_type
    TrackJobBaseNew::beamMonitorsOutputBufferOffset() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( ( this->hasOutputBuffer() ) &&
              ( ::NS(Buffer_get_size)( this->ptrCOutputBuffer() ) >
                this->m_be_mon_output_buffer_offset ) ) ||
            ( this->m_be_mon_output_buffer_offset ==
                TrackJobBaseNew::size_type{ 0 } ) );

        return this->m_be_mon_output_buffer_offset;
    }

    TrackJobBaseNew::size_type
    TrackJobBaseNew::elemByElemOutputBufferOffset() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT( ( ( this->hasOutputBuffer() ) &&
              ( ::NS(Buffer_get_size)( this->ptrCOutputBuffer() ) >
                this->m_elem_by_elem_output_offset ) ) ||
            ( this->m_elem_by_elem_output_offset ==
                TrackJobBaseNew::size_type{ 0 } ) );

        return this->m_elem_by_elem_output_offset;
    }

    TrackJobBaseNew::particle_index_t
    TrackJobBaseNew::untilTurnElemByElem() const SIXTRL_NOEXCEPT
    {
        return this->m_until_turn_elem_by_elem;
    }

    TrackJobBaseNew::size_type
    TrackJobBaseNew::numElemByElemTurns() const SIXTRL_NOEXCEPT
    {
        using index_t = TrackJobBaseNew::particle_index_t;
        using size_t  = TrackJobBaseNew::size_type;

        if( ( this->m_until_turn_elem_by_elem > this->m_min_initial_turn_id ) &&
            ( this->m_min_initial_turn_id >= index_t{ 0 } ) )
        {
            return static_cast< size_t >( this->m_until_turn_elem_by_elem -
                this->m_min_initial_turn_id );
        }

        return size_t{ 0 };
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    TrackJobBaseNew::buffer_t*
    TrackJobBaseNew::ptrOutputBuffer() SIXTRL_RESTRICT
    {
        return const_cast< st::TrackJobBaseNew::buffer_t* >( static_cast<
            st::TrackJobBaseNew const& >( *this ).ptrOutputBuffer() );
    }

    TrackJobBaseNew::buffer_t const*
    TrackJobBaseNew::ptrOutputBuffer() const SIXTRL_RESTRICT
    {
        SIXTRL_ASSERT( ( this->m_ptr_output_buffer == nullptr ) ||
            ( this->m_ptr_output_buffer->getCApiPtr() ==
              this->m_ptr_c_output_buffer ) );

        return this->m_ptr_output_buffer;
    }

    TrackJobBaseNew::c_buffer_t*
    TrackJobBaseNew::ptrCOutputBuffer() SIXTRL_RESTRICT
    {
        return const_cast< st::TrackJobBaseNew::c_buffer_t* >( static_cast<
            st::TrackJobBaseNew const& >( *this ).ptrCOutputBuffer() );
    }

    TrackJobBaseNew::c_buffer_t const*
    TrackJobBaseNew::ptrCOutputBuffer() const SIXTRL_RESTRICT
    {
        SIXTRL_ASSERT( ( this->m_ptr_output_buffer == nullptr ) ||
            ( this->m_ptr_output_buffer->getCApiPtr() ==
              this->m_ptr_c_output_buffer ) );

        return this->m_ptr_c_output_buffer;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBaseNew::hasBeamMonitors() const SIXTRL_NOEXCEPT
    {
        return !this->m_beam_monitor_indices.empty();
    }

    TrackJobBaseNew::size_type
    TrackJobBaseNew::numBeamMonitors() const SIXTRL_NOEXCEPT
    {
        return this->m_beam_monitor_indices.size();
    }

    TrackJobBaseNew::size_type const*
    TrackJobBaseNew::beamMonitorIndicesBegin() const SIXTRL_NOEXCEPT
    {
        return this->m_beam_monitor_indices.data();
    }

    TrackJobBaseNew::size_type const*
    TrackJobBaseNew::beamMonitorIndicesEnd() const SIXTRL_NOEXCEPT
    {
        TrackJobBaseNew::size_type const* ptr = this->beamMonitorIndicesBegin();
        if( ptr != nullptr ) std::advance( ptr, this->numBeamMonitors() );
        return ptr;
    }

    TrackJobBaseNew::size_type TrackJobBaseNew::beamMonitorIndex(
        TrackJobBaseNew::size_type const idx ) const
    {
        return this->m_beam_monitor_indices.at( idx );
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBaseNew::hasElemByElemConfig() const SIXTRL_NOEXCEPT
    {
        SIXTRL_ASSERT(
            ( this->m_my_elem_by_elem_config.get() == nullptr ) ||
            ( this->m_ptr_c_output_buffer != nullptr ) );

        return ( ::NS(ElemByElemConfig_is_active)(
            this->m_my_elem_by_elem_config.get() ) );
    }

    TrackJobBaseNew::elem_by_elem_config_t const*
    TrackJobBaseNew::ptrElemByElemConfig() const SIXTRL_NOEXCEPT
    {
        return const_cast< st::TrackJobBaseNew::elem_by_elem_config_t* >(
            static_cast< st::TrackJobBaseNew const& >(
                *this ).ptrElemByElemConfig() );
    }

    TrackJobBaseNew::elem_by_elem_config_t*
    TrackJobBaseNew::ptrElemByElemConfig() SIXTRL_NOEXCEPT
    {
        return this->m_my_elem_by_elem_config.get();
    }

    bool TrackJobBaseNew::elemByElemRolling() const SIXTRL_NOEXCEPT
    {
        return NS(ElemByElemConfig_is_rolling)( this->ptrElemByElemConfig() );
    }

    bool TrackJobBaseNew::defaultElemByElemRolling() const SIXTRL_NOEXCEPT
    {
        return this->m_default_elem_by_elem_rolling;
    }

    void TrackJobBaseNew::setDefaultElemByElemRolling(
        bool const is_rolling ) SIXTRL_NOEXCEPT
    {
        this->m_default_elem_by_elem_rolling = is_rolling;
    }

    TrackJobBaseNew::elem_by_elem_order_t
    TrackJobBaseNew::elemByElemOrder() const SIXTRL_NOEXCEPT
    {
        return ::NS(ElemByElemConfig_get_order)(
            this->m_my_elem_by_elem_config.get() );
    }

    TrackJobBaseNew::elem_by_elem_order_t
    TrackJobBaseNew::defaultElemByElemOrder() const SIXTRL_NOEXCEPT
    {
        return this->m_default_elem_by_elem_order;
    }

    void TrackJobBaseNew::setDefaultElemByElemOrder(
        TrackJobBaseNew::elem_by_elem_order_t const order ) SIXTRL_NOEXCEPT
    {
        this->m_default_elem_by_elem_order = order;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::TrackJobBaseNew(
        TrackJobBaseNew::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT arch_str,
        char const* SIXTRL_RESTRICT config_str ) :
        st::ArchBase( arch_id, arch_str, config_str ),
        m_particle_set_indices(), m_beam_monitor_indices(),
        m_my_output_buffer( nullptr ),
        m_my_particles_addr_buffer( new TrackJobBaseNew::buffer_t ),
        m_my_elem_by_elem_config( nullptr ),
        m_ptr_particles_buffer( nullptr ),
        m_ptr_beam_elem_buffer( nullptr ), m_ptr_output_buffer( nullptr ),
        m_ptr_c_particles_buffer( nullptr ),
        m_ptr_c_beam_elem_buffer( nullptr ), m_ptr_c_output_buffer( nullptr ),
        m_be_mon_output_buffer_offset( TrackJobBaseNew::size_type{ 0 } ),
        m_elem_by_elem_output_offset( TrackJobBaseNew::size_type{ 0 } ),
        m_total_num_particles( TrackJobBaseNew::num_particles_t{ 0 } ),
        m_default_elem_by_elem_order( ::NS(ELEM_BY_ELEM_ORDER_DEFAULT) ),
        m_min_particle_id( TrackJobBaseNew::particle_index_t{ 0 } ),
        m_max_particle_id( TrackJobBaseNew::particle_index_t{ 0 } ),
        m_min_element_id( TrackJobBaseNew::particle_index_t{ 0 } ),
        m_max_element_id( TrackJobBaseNew::particle_index_t{ 0 } ),
        m_min_initial_turn_id( TrackJobBaseNew::particle_index_t{ 0 } ),
        m_max_initial_turn_id( TrackJobBaseNew::particle_index_t{ 0 } ),
        m_until_turn_elem_by_elem( TrackJobBaseNew::size_type{ 0 } ),
        m_collect_flags( st::TRACK_JOB_COLLECT_DEFAULT_FLAGS ),
        m_default_elem_by_elem_rolling( true ),
        m_has_beam_monitor_output( false ), m_has_elem_by_elem_output( false ),
        m_has_particle_addresses( false ), m_requires_collect( true ),
        m_uses_controller( false ), m_uses_arguments( false )
    {
        this->doInitDefaultParticleSetIndices();
        this->doInitDefaultBeamMonitorIndices();
    }

    TrackJobBaseNew::TrackJobBaseNew( TrackJobBaseNew const& other ) :
        st::ArchBase( other ),
        m_particle_set_indices( other.m_particle_set_indices ),
        m_beam_monitor_indices( other.m_beam_monitor_indices ),
        m_my_output_buffer( nullptr ),
        m_my_particles_addr_buffer( nullptr ),
        m_my_elem_by_elem_config( nullptr ),
        m_ptr_particles_buffer( other.m_ptr_particles_buffer ),
        m_ptr_beam_elem_buffer( other.m_ptr_beam_elem_buffer ),
        m_ptr_output_buffer( nullptr ),
        m_ptr_c_particles_buffer( other.m_ptr_c_particles_buffer ),
        m_ptr_c_beam_elem_buffer( other.m_ptr_c_beam_elem_buffer ),
        m_ptr_c_output_buffer( nullptr ),
        m_be_mon_output_buffer_offset( other.m_be_mon_output_buffer_offset ),
        m_elem_by_elem_output_offset( other.m_elem_by_elem_output_offset ),
        m_total_num_particles( other.m_total_num_particles ),
        m_default_elem_by_elem_order( other.m_default_elem_by_elem_order ),
        m_min_particle_id( other.m_min_particle_id ),
        m_max_particle_id( other.m_max_particle_id ),
        m_min_element_id( other.m_min_element_id ),
        m_max_element_id( other.m_max_element_id ),
        m_min_initial_turn_id( other.m_min_initial_turn_id ),
        m_max_initial_turn_id( other.m_max_initial_turn_id ),
        m_until_turn_elem_by_elem( other.m_until_turn_elem_by_elem ),
        m_collect_flags( other.m_collect_flags ),
        m_default_elem_by_elem_rolling( other.m_default_elem_by_elem_rolling ),
        m_has_beam_monitor_output( other.m_has_beam_monitor_output ),
        m_has_elem_by_elem_output( other.m_has_elem_by_elem_output ),
        m_has_particle_addresses( other.m_has_particle_addresses ),
        m_requires_collect( other.m_requires_collect ),
        m_uses_controller( other.m_uses_controller ),
        m_uses_arguments( other.m_uses_arguments )
    {
        using elem_by_elem_config_t = TrackJobBaseNew::elem_by_elem_config_t;

        if( other.ownsOutputBuffer() )
        {
            this->m_my_output_buffer.reset( new
                TrackJobBaseNew::buffer_t( *other.ptrOutputBuffer() ) );

            this->m_ptr_output_buffer = this->m_my_output_buffer.get();
            this->m_ptr_c_output_buffer =
                ( this->m_ptr_output_buffer != nullptr )
                    ? this->m_ptr_output_buffer->getCApiPtr() : nullptr;
        }
        else if( other.hasOutputBuffer() )
        {
            this->m_ptr_output_buffer = other.m_ptr_output_buffer;
            this->m_ptr_c_output_buffer = other.m_ptr_c_output_buffer;
        }

        if( other.m_my_particles_addr_buffer.get() != nullptr )
        {
            this->m_my_particles_addr_buffer.reset(
                new TrackJobBaseNew::buffer_t(
                    *other.doGetPtrParticlesAddrBuffer() ) );
        }
        else
        {
            this->m_my_particles_addr_buffer.reset(
                new TrackJobBaseNew::buffer_t );
        }

        if( other.m_my_elem_by_elem_config.get() != nullptr )
        {
            this->m_my_elem_by_elem_config.reset(
                new elem_by_elem_config_t );

            *this->m_my_elem_by_elem_config =  *other.ptrElemByElemConfig();
        }
    }

    TrackJobBaseNew::TrackJobBaseNew(
        TrackJobBaseNew&& other ) SIXTRL_NOEXCEPT :
        st::ArchBase( std::move( other ) ),
        m_particle_set_indices( std::move( other.m_particle_set_indices ) ),
        m_beam_monitor_indices( std::move( other.m_beam_monitor_indices ) ),
        m_my_output_buffer( std::move( other.m_my_output_buffer ) ),
        m_my_particles_addr_buffer(
            std::move( other.m_my_particles_addr_buffer ) ),
        m_my_elem_by_elem_config( std::move( other.m_my_elem_by_elem_config ) ),
        m_ptr_particles_buffer( std::move( other.m_ptr_particles_buffer ) ),
        m_ptr_beam_elem_buffer( std::move( other.m_ptr_beam_elem_buffer ) ),
        m_ptr_output_buffer( std::move( other.m_ptr_output_buffer ) ),
        m_ptr_c_particles_buffer( std::move( other.m_ptr_c_particles_buffer )),
        m_ptr_c_beam_elem_buffer( std::move( other.m_ptr_c_beam_elem_buffer ) ),
        m_ptr_c_output_buffer( std::move( other.m_ptr_c_output_buffer ) ),
        m_be_mon_output_buffer_offset(
            std::move( other.m_be_mon_output_buffer_offset ) ),
        m_elem_by_elem_output_offset(
            std::move( other.m_elem_by_elem_output_offset ) ),
        m_total_num_particles( std::move( other.m_total_num_particles ) ),
        m_default_elem_by_elem_order(
            std::move( other.m_default_elem_by_elem_order ) ),
        m_min_particle_id( std::move( other.m_min_particle_id ) ),
        m_max_particle_id( std::move( other.m_max_particle_id ) ),
        m_min_element_id( std::move( other.m_min_element_id ) ),
        m_max_element_id( std::move( other.m_max_element_id ) ),
        m_min_initial_turn_id( std::move( other.m_min_initial_turn_id ) ),
        m_max_initial_turn_id( std::move( other.m_max_initial_turn_id ) ),
        m_until_turn_elem_by_elem( std::move(
            other.m_until_turn_elem_by_elem ) ),
        m_collect_flags( std::move( other.m_collect_flags ) ),
        m_default_elem_by_elem_rolling(
            std::move( other.m_default_elem_by_elem_rolling ) ),
        m_has_beam_monitor_output(
            std::move( other.m_has_beam_monitor_output ) ),
        m_has_elem_by_elem_output(
            std::move( other.m_has_elem_by_elem_output ) ),
        m_has_particle_addresses(
            std::move( other.m_has_particle_addresses ) ),
        m_requires_collect( std::move( other.m_requires_collect ) ),
        m_uses_controller( std::move( other.m_uses_controller ) ),
        m_uses_arguments( std::move( other.m_uses_arguments ) )
    {
        other.doClearBaseImpl();
    }

    TrackJobBaseNew& TrackJobBaseNew::operator=( TrackJobBaseNew const& rhs )
    {
        if( ( this != &rhs ) && ( this->isArchCompatibleWith( rhs ) ) )
        {
            st::ArchBase::operator=( rhs );

            this->m_particle_set_indices = rhs.m_particle_set_indices;
            this->m_beam_monitor_indices = rhs.m_beam_monitor_indices;

            /* TODO: Implement (re-)assigning of output buffers for beam-
             *       monitors after copying the outputbuffer! */

            if( rhs.ownsOutputBuffer() )
            {
                if( this->ownsOutputBuffer() )
                {
                    SIXTRL_ASSERT( this->m_my_output_buffer.get() != nullptr );
                    this->m_my_output_buffer->deepCopyFrom(
                        rhs.ptrCOutputBuffer() );

                    this->m_ptr_output_buffer = this->m_my_output_buffer.get();

                    if( this->m_ptr_output_buffer != nullptr )
                    {
                        this->m_ptr_c_output_buffer =
                            this->m_ptr_output_buffer->getCApiPtr();
                    }
                }
                else
                {
                    this->m_ptr_output_buffer = rhs.m_ptr_output_buffer;
                    this->m_ptr_c_output_buffer = rhs.m_ptr_c_output_buffer;
                }
            }
            else if( rhs.hasOutputBuffer() )
            {
                if( this->ownsOutputBuffer() )
                {
                    this->m_my_output_buffer.reset( nullptr );
                }

                this->m_ptr_output_buffer = rhs.m_ptr_output_buffer;
                this->m_ptr_c_output_buffer = rhs.m_ptr_c_output_buffer;
            }

            if( rhs.m_my_particles_addr_buffer.get() != nullptr )
            {
                this->m_my_particles_addr_buffer.reset(
                    new TrackJobBaseNew::buffer_t(
                        *rhs.m_my_particles_addr_buffer ) );
            }
            else
            {
                this->m_my_particles_addr_buffer.reset(
                    new TrackJobBaseNew::buffer_t );
            }

            if( rhs.m_my_elem_by_elem_config.get() != nullptr )
            {
                this->m_my_elem_by_elem_config.reset(
                    new elem_by_elem_config_t );

                *this->m_my_elem_by_elem_config = *rhs.ptrElemByElemConfig();
            }
            else if( this->m_my_elem_by_elem_config.get() != nullptr )
            {
                this->m_my_elem_by_elem_config.reset( nullptr );
            }

            this->m_ptr_particles_buffer = rhs.m_ptr_particles_buffer;
            this->m_ptr_beam_elem_buffer = rhs.m_ptr_beam_elem_buffer;

            this->m_ptr_c_particles_buffer = rhs.m_ptr_c_particles_buffer;
            this->m_ptr_c_beam_elem_buffer = rhs.m_ptr_c_beam_elem_buffer;

            this->m_be_mon_output_buffer_offset =
                rhs.m_be_mon_output_buffer_offset;

            this->m_elem_by_elem_output_offset =
                rhs.m_elem_by_elem_output_offset;

            this->m_total_num_particles = rhs.m_total_num_particles;

            this->m_default_elem_by_elem_order =
                rhs.m_default_elem_by_elem_order;

            this->m_min_particle_id = rhs.m_min_particle_id;
            this->m_max_particle_id = rhs.m_max_particle_id;
            this->m_min_element_id  = rhs.m_min_element_id;
            this->m_max_element_id  = rhs.m_max_element_id;
            this->m_min_initial_turn_id = rhs.m_min_initial_turn_id;
            this->m_max_initial_turn_id = rhs.m_max_initial_turn_id;
            this->m_until_turn_elem_by_elem = rhs.m_until_turn_elem_by_elem;
            this->m_collect_flags = rhs.m_collect_flags;

            this->m_default_elem_by_elem_rolling =
                rhs.m_default_elem_by_elem_rolling;

            this->m_has_beam_monitor_output = rhs.m_has_beam_monitor_output;
            this->m_has_elem_by_elem_output = rhs.m_has_elem_by_elem_output;
            this->m_has_particle_addresses  = rhs.m_has_particle_addresses;

            this->m_requires_collect = rhs.m_requires_collect;
            this->m_uses_controller = rhs.m_uses_controller;
            this->m_uses_arguments = rhs.m_uses_arguments;
        }

        return *this;
    }

    TrackJobBaseNew& TrackJobBaseNew::operator=(
        TrackJobBaseNew&& rhs ) SIXTRL_NOEXCEPT
    {
        if( this != &rhs )
        {
            st::ArchBase::operator=( std::move( rhs ) );

            this->m_particle_set_indices =
                std::move( rhs.m_particle_set_indices );

            this->m_beam_monitor_indices =
                std::move( rhs.m_beam_monitor_indices );

            this->m_my_output_buffer = std::move( rhs.m_my_output_buffer );

            this->m_my_particles_addr_buffer =
                std::move( rhs.m_my_particles_addr_buffer );

            this->m_my_elem_by_elem_config =
                std::move( rhs.m_my_elem_by_elem_config );

            this->m_ptr_particles_buffer =
                std::move( rhs.m_ptr_particles_buffer );

            this->m_ptr_beam_elem_buffer =
                std::move( rhs.m_ptr_beam_elem_buffer );

            this->m_ptr_output_buffer = std::move( rhs.m_ptr_output_buffer );

            this->m_ptr_c_particles_buffer =
                std::move( rhs.m_ptr_c_particles_buffer );

            this->m_ptr_c_beam_elem_buffer =
                std::move( rhs.m_ptr_c_beam_elem_buffer );

            this->m_be_mon_output_buffer_offset = std::move(
                rhs.m_be_mon_output_buffer_offset );

            this->m_elem_by_elem_output_offset = std::move(
                rhs.m_elem_by_elem_output_offset );

            this->m_total_num_particles =
                std::move( rhs.m_total_num_particles );

            this->m_default_elem_by_elem_order = std::move(
                rhs.m_default_elem_by_elem_order );

            this->m_min_particle_id = std::move( rhs.m_min_particle_id );
            this->m_max_particle_id = std::move( rhs.m_max_particle_id );
            this->m_min_element_id  = std::move( rhs.m_min_element_id );
            this->m_max_element_id  = std::move( rhs.m_max_element_id );

            this->m_min_initial_turn_id =
                std::move( rhs.m_min_initial_turn_id );

            this->m_max_initial_turn_id =
                std::move( rhs.m_max_initial_turn_id );

            this->m_until_turn_elem_by_elem =
                std::move( rhs.m_until_turn_elem_by_elem );

            this->m_collect_flags = std::move( rhs.m_collect_flags );

            this->m_default_elem_by_elem_rolling =
                std::move( rhs.m_default_elem_by_elem_rolling );

            this->m_has_beam_monitor_output =
                std::move( rhs.m_has_beam_monitor_output );

            this->m_has_elem_by_elem_output =
                std::move( rhs.m_has_elem_by_elem_output );

            this->m_has_particle_addresses =
                std::move( rhs.m_has_particle_addresses );

            this->m_requires_collect = std::move( rhs.m_requires_collect );
            this->m_uses_controller = std::move( rhs.m_uses_controller );
            this->m_uses_arguments = std::move( rhs.m_uses_arguments );

            rhs.doClearBaseImpl();
        }

        return *this;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::doClear()
    {
        this->doClearBaseImpl();
    }

    TrackJobBaseNew::collect_flag_t TrackJobBaseNew::doCollect(
        TrackJobBaseNew::collect_flag_t const )
    {
        return st::TRACK_JOB_COLLECT_NONE;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobBaseNew::doPrepareParticlesStructures(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT pb )
    {
        bool success = false;

        using _this_t         = TrackJobBaseNew;
        using size_t          = _this_t::size_type;
        using p_index_t       = _this_t::particle_index_t;
        using buffer_t        = _this_t::buffer_t;
        using paddr_t         = _this_t::particles_addr_t;
        using num_particles_t = _this_t::num_particles_t;

        SIXTRL_STATIC_VAR size_t const ZERO = size_t{ 0 };
        SIXTRL_STATIC_VAR size_t const ONE  = size_t{ 1 };

        size_t const nn = this->numParticleSets();
        size_t const num_psets = ::NS(Buffer_get_num_of_objects)( pb );

        if( ( pb != nullptr ) && ( ( nn > ZERO ) || ( nn == ZERO ) ) &&
            ( !::NS(Buffer_needs_remapping)( pb ) ) && ( num_psets >= nn ) )
        {
            int ret = int{ -1 };

            size_t const first_index = ( nn > ZERO )
                ? this->particleSetIndex( ZERO ) : ZERO;

            p_index_t min_part_id, max_part_id, min_elem_id, max_elem_id,
                      min_turn_id, max_turn_id;

            if( ( nn <= ONE ) && ( first_index == ZERO ) )
            {
                ret = ::NS(Particles_get_min_max_attributes)(
                        ::NS(Particles_buffer_get_const_particles)( pb, ZERO ),
                        &min_part_id, &max_part_id, &min_elem_id, &max_elem_id,
                        &min_turn_id, &max_turn_id );
            }
            else if( nn > ZERO )
            {
                ret =
                ::NS(Particles_buffer_get_min_max_attributes_of_particles_set)(
                    pb, nn, this->particleSetIndicesBegin(),
                    &min_part_id, &max_part_id, &min_elem_id, &max_elem_id,
                    &min_turn_id, &max_turn_id );
            }

            if( ( ret == int{ 0 } ) &&
                ( this->doGetPtrParticlesAddrBuffer() != nullptr ) )
            {
                buffer_t& paddr_buffer = *this->doGetPtrParticlesAddrBuffer();

                if( paddr_buffer.getNumObjects() > size_t{ 0 }  )
                {
                    paddr_buffer.clear( true );
                }

                for( size_t ii = size_t{ 0 } ; ii < num_psets ; ++ii )
                {
                    paddr_t* paddr = ::NS(ParticlesAddr_new)(
                        paddr_buffer.getCApiPtr(), size_t{ 0 } );

                    if( paddr == nullptr )
                    {
                        ret = -2;
                        break;
                    }
                }
            }

            if( ret == int{ 0 } )
            {
                num_particles_t const total_num_particles =
                ::NS(Particles_buffer_get_total_num_of_particles_on_particle_sets)(
                    pb, this->numParticleSets(),
                        this->particleSetIndicesBegin() );

                this->doSetTotalNumParticles( total_num_particles );

                this->doSetMinParticleId( min_part_id );
                this->doSetMaxParticleId( max_part_id );

                this->doSetMinElementId( min_elem_id );
                this->doSetMaxElementId( max_elem_id );

                this->doSetMinInitialTurnId( min_turn_id );
                this->doSetMaxInitialTurnId( max_turn_id );

                success = true;
            }
        }

        return success;
    }

    bool TrackJobBaseNew::doPrepareBeamElementsStructures(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT belems )
    {
        bool success = false;

        using size_t        = TrackJobBaseNew::size_type;
        using p_index_t     = TrackJobBaseNew::particle_index_t;
        using buf_size_t    = ::NS(buffer_size_t);
        using obj_ptr_t     = SIXTRL_BUFFER_OBJ_ARGPTR_DEC ::NS(Object)*;
        using ptr_t         = SIXTRL_BE_ARGPTR_DEC NS(BeamMonitor)*;

        SIXTRL_STATIC_VAR size_t const ZERO = size_t{ 0 };
        SIXTRL_STATIC_VAR uintptr_t const UZERO = uintptr_t{ 0 };

        if( ( belems != nullptr ) &&
            ( !::NS(Buffer_needs_remapping)( belems ) ) &&
            ( ::NS(Buffer_get_num_of_objects)( belems ) > ZERO ) &&
            ( ::NS(BeamElements_is_beam_elements_buffer)( belems ) ) )
        {
            int ret = -1;

            p_index_t const start_be_id = p_index_t{ 0 };
            buf_size_t  num_e_by_e_objs = buf_size_t{ 0 };
            p_index_t min_elem_id = this->minElementId();
            p_index_t max_elem_id = this->maxElementId();

            ret = ::NS(ElemByElemConfig_find_min_max_element_id_from_buffer)(
                belems, &min_elem_id, &max_elem_id, &num_e_by_e_objs,
                    start_be_id );

            if( ret == 0 )
            {
                buf_size_t num_be_monitors = buf_size_t{ 0 };
                std::vector< size_t > be_mon_indices( num_e_by_e_objs, ZERO );

                ret = ::NS(BeamMonitor_get_beam_monitor_indices_from_buffer)(
                    belems, be_mon_indices.size(), be_mon_indices.data(),
                        &num_be_monitors );

                SIXTRL_ASSERT( num_be_monitors <= be_mon_indices.size() );

                auto ind_end = be_mon_indices.begin();

                if( num_be_monitors > buf_size_t{ 0 } )
                {
                    std::advance( ind_end, num_be_monitors );
                }

                this->doSetBeamMonitorIndices( be_mon_indices.begin(),ind_end);
                SIXTRL_ASSERT( num_be_monitors == this->numBeamMonitors() );

                this->doSetMinElementId( min_elem_id );
                this->doSetMaxElementId( max_elem_id );
            }

            success = ( ret == 0 );

            if( ( success ) && ( this->numBeamMonitors() > ZERO ) &&
                ( this->ptrCParticlesBuffer() != nullptr ) &&
                ( this->minParticleId() <= this->maxParticleId() ) )
            {
                auto it  = this->beamMonitorIndicesBegin();
                auto end = this->beamMonitorIndicesEnd();

                p_index_t const min_part_id = this->minParticleId();
                p_index_t const max_part_id = this->maxParticleId();

                for( ; it != end ; ++it )
                {
                    obj_ptr_t obj = ::NS(Buffer_get_object)( belems, *it );
                    uintptr_t const addr = static_cast< uintptr_t >(
                        ::NS(Object_get_begin_addr)( obj ) );

                    if( ( obj != nullptr ) && ( addr != UZERO ) &&
                        ( ::NS(Object_get_type_id)( obj ) ==
                          ::NS(OBJECT_TYPE_BEAM_MONITOR) ) )
                    {
                        ptr_t m = reinterpret_cast< ptr_t >( addr );
                        ::NS(BeamMonitor_set_min_particle_id)( m,min_part_id );
                        ::NS(BeamMonitor_set_max_particle_id)( m,max_part_id );
                    }
                    else
                    {
                        success = false;
                        break;
                    }
                }
            }
        }

        return success;
    }

    bool TrackJobBaseNew::doPrepareOutputStructures(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT beam_elements_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer,
        TrackJobBaseNew::size_type const until_turn_elem_by_elem )
    {
        bool success = false;

        using size_t                 = TrackJobBaseNew::size_type;
        using buffer_t               = TrackJobBaseNew::buffer_t;
        using c_buffer_t             = TrackJobBaseNew::c_buffer_t;
        using buf_size_t             = ::NS(buffer_size_t);
        using elem_by_elem_config_t  = TrackJobBaseNew::elem_by_elem_config_t;
        using ptr_output_buffer_t    = TrackJobBaseNew::ptr_output_buffer_t;
        using par_index_t            = TrackJobBaseNew::particle_index_t;

        using ptr_elem_by_elem_config_t =
            TrackJobBaseNew::ptr_elem_by_elem_config_t;

        SIXTRL_ASSERT( particles_buffer != nullptr );
        SIXTRL_ASSERT( !::NS(Buffer_needs_remapping)( particles_buffer ) );

        SIXTRL_ASSERT( ( ::NS(Buffer_get_num_of_objects)( particles_buffer ) ==
            size_t{ 0 } ) || ( ::NS(Buffer_is_particles_buffer)(
                particles_buffer ) ) );

        SIXTRL_ASSERT( beam_elements_buffer != nullptr );
        SIXTRL_ASSERT( !::NS(Buffer_needs_remapping)( beam_elements_buffer ) );

        SIXTRL_ASSERT( ::NS(Buffer_get_num_of_objects)( beam_elements_buffer )
            > size_t{ 0 } );

        SIXTRL_ASSERT( ::NS(BeamElements_is_beam_elements_buffer)(
            beam_elements_buffer ) );

        c_buffer_t* output_buffer = ptr_output_buffer;

        if( output_buffer == nullptr )
        {
            if( !this->hasOutputBuffer() )
            {
                SIXTRL_ASSERT( !this->ownsOutputBuffer() );
                ptr_output_buffer_t managed_output_buffer( new buffer_t );

                SIXTRL_ASSERT(  managed_output_buffer.get() != nullptr );
                output_buffer = managed_output_buffer.get()->getCApiPtr();
                SIXTRL_ASSERT( output_buffer != nullptr );

                this->doUpdateStoredOutputBuffer(
                    std::move( managed_output_buffer ) );

                SIXTRL_ASSERT( managed_output_buffer.get() == nullptr );
                SIXTRL_ASSERT( this->ownsOutputBuffer() );
                SIXTRL_ASSERT( this->ptrCOutputBuffer() == output_buffer );
            }
            else
            {
                output_buffer = this->ptrCOutputBuffer();
            }

            SIXTRL_ASSERT( this->hasOutputBuffer() );
        }
        else
        {
            if( !this->hasOutputBuffer() )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
            else if( !this->ownsOutputBuffer() )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
            else if( ( this->ownsOutputBuffer() ) &&
                     ( this->ptrCOutputBuffer() != nullptr ) &&
                     ( this->ptrCOutputBuffer() != output_buffer ) )
            {
                ptr_output_buffer_t dummy( nullptr );
                this->doUpdateStoredOutputBuffer( std::move( dummy ) );
                this->doSetPtrCOutputBuffer( output_buffer );
            }
            else
            {
                return success;
            }
        }

        if( output_buffer != nullptr )
        {
            SIXTRL_STATIC_VAR const size_t ZERO = size_t{ 0 };
            SIXTRL_ASSERT( !::NS(Buffer_needs_remapping)( output_buffer ) );

            SIXTRL_ASSERT(
                ( ::NS(Buffer_get_num_of_objects)( output_buffer ) == ZERO )||
                ( ::NS(Buffer_is_particles_buffer)( output_buffer ) ) );

            buf_size_t  elem_by_elem_out_idx_offset = buf_size_t{ 0 };
            buf_size_t  be_monitor_out_idx_offset   = buf_size_t{ 0 };
            par_index_t max_elem_by_elem_turn_id    = par_index_t{ 0 };

            int ret = ::NS(OutputBuffer_prepare_detailed)(
                beam_elements_buffer, output_buffer,
                this->minParticleId(), this->maxParticleId(),
                this->minElementId(),  this->maxElementId(),
                this->minInitialTurnId(), this->maxInitialTurnId(),
                until_turn_elem_by_elem,
                &elem_by_elem_out_idx_offset, &be_monitor_out_idx_offset,
                &max_elem_by_elem_turn_id );

            if( ( ret == 0 ) && ( until_turn_elem_by_elem > ZERO ) &&
                ( this->minInitialTurnId() >= par_index_t{ 0 } ) &&
                ( max_elem_by_elem_turn_id >= this->minInitialTurnId() ) &&
                ( until_turn_elem_by_elem > static_cast< buf_size_t >(
                    this->minInitialTurnId() ) ) )
            {
                ptr_elem_by_elem_config_t conf( new elem_by_elem_config_t );
                ::NS(ElemByElemConfig_preset)( conf.get() );

                ret = ::NS(ElemByElemConfig_init_detailed)(
                    conf.get(), this->defaultElemByElemOrder(),
                    this->minParticleId(), this->maxParticleId(),
                    this->minElementId(),  this->maxElementId(),
                    this->minInitialTurnId(), max_elem_by_elem_turn_id,
                    this->defaultElemByElemRolling() );

                if( ret == 0 )
                {
                    this->doUpdateStoredElemByElemConfig( std::move( conf ) );
                    this->doSetUntilTurnElemByElem(
                        until_turn_elem_by_elem );

                    SIXTRL_ASSERT( this->hasElemByElemConfig() );
                }
            }
            else if( ret == 0 )
            {
                ptr_elem_by_elem_config_t dummy( nullptr );
                this->doUpdateStoredElemByElemConfig( std::move( dummy ) );
                this->doSetUntilTurnElemByElem( ZERO );

                ret = ( !this->hasElemByElemConfig() ) ? 0 : -1;
            }

            if( ret == 0 )
            {
                this->doSetBeamMonitorOutputBufferOffset(
                    be_monitor_out_idx_offset );

                this->doSetElemByElemOutputIndexOffset(
                    elem_by_elem_out_idx_offset );
            }

            success = ( ret == 0 );
        }

        return success;
    }

    bool TrackJobBaseNew::doAssignOutputBufferToBeamMonitors(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT output_buffer )
    {
        using size_t   = TrackJobBaseNew::size_type;
        using config_t = TrackJobBaseNew::elem_by_elem_config_t;

        size_t const num_be_monitors  = this->numBeamMonitors();
        size_t const be_mon_offset    = this->beamMonitorsOutputBufferOffset();
        size_t const elem_elem_offset = this->elemByElemOutputBufferOffset();
        config_t* elem_conf = this->ptrElemByElemConfig();

        size_t const num_out_objects  =
            ::NS(Buffer_get_num_of_objects)( output_buffer );

        bool success = false;

        if( ( output_buffer != nullptr ) && ( beam_elem_buffer != nullptr ) )
        {
            this->doSetBeamMonitorOutputEnabledFlag( false );
            this->doSetElemByElemOutputEnabledFlag( false );

            success = true;

            if( elem_conf != nullptr )
            {
                success = false;

                if( ( elem_elem_offset < num_out_objects ) &&
                    ( ( ( num_be_monitors == size_t{ 0 } ) &&
                        ( be_mon_offset >= elem_elem_offset ) ) ||
                      ( ( num_be_monitors > size_t{ 0 } ) &&
                        ( be_mon_offset >  elem_elem_offset ) ) ) &&
                    ( 0 == ::NS(ElemByElemConfig_assign_output_buffer)(
                        elem_conf, output_buffer, elem_elem_offset ) ) )
                {
                    this->doSetElemByElemOutputEnabledFlag( true );
                    success = true;
                }
            }

            if( ( success ) && ( num_be_monitors > size_t{ 0 } ) )
            {
                success = false;

                if( ( be_mon_offset < num_out_objects ) &&
                    ( ( ( elem_conf == nullptr ) &&
                        ( elem_elem_offset <= be_mon_offset ) ) ||
                      ( ( elem_conf != nullptr ) &&
                        ( elem_elem_offset < be_mon_offset ) ) ) &&
                    ( 0 == ::NS(BeamMonitor_assign_output_buffer_from_offset)(
                        beam_elem_buffer, output_buffer,
                        this->minInitialTurnId(), be_mon_offset ) ) )
                {
                    this->doSetBeamMonitorOutputEnabledFlag( true );
                    success = true;
                }
            }
        }

        return success;
    }

    bool TrackJobBaseNew::doReset(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT particles_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT beam_elem_buffer,
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT output_buffer,
        TrackJobBaseNew::size_type const until_turn_elem_by_elem )
    {
        bool success = false;

        if( ( this->doPrepareParticlesStructures( particles_buffer ) ) &&
            ( this->doPrepareBeamElementsStructures( beam_elem_buffer ) ) )
        {
            success = true;

            bool const requ_buffer =
            ::NS(OutputBuffer_required_for_tracking_of_particle_sets)(
                particles_buffer, this->numParticleSets(),
                    this->particleSetIndicesBegin(), beam_elem_buffer,
                        until_turn_elem_by_elem );

            if( requ_buffer )
            {
                success = this->doPrepareOutputStructures( particles_buffer,
                    beam_elem_buffer, output_buffer, until_turn_elem_by_elem );
            }

            if( ( success ) && ( this->hasOutputBuffer() ) && ( requ_buffer ) )
            {
                success = this->doAssignOutputBufferToBeamMonitors(
                    beam_elem_buffer, this->ptrCOutputBuffer() );
            }

            if( ( success ) && ( output_buffer != nullptr ) &&
                ( !this->ownsOutputBuffer() ) )
            {
                this->doSetPtrCOutputBuffer( output_buffer );
            }
        }

        return success;
    }

    bool TrackJobBaseNew::doAssignNewOutputBuffer(
        c_buffer_t* SIXTRL_RESTRICT ptr_output_buffer )
    {
        bool success = false;

        using _this_t = TrackJobBaseNew;
        using flags_t = _this_t::output_buffer_flag_t;

        flags_t const flags =
            ::NS(OutputBuffer_required_for_tracking_of_particle_sets)(
            this->ptrCParticlesBuffer(), this->numParticleSets(),
                this->particleSetIndicesBegin(),
                this->ptrCBeamElementsBuffer(), this->numElemByElemTurns() );

        bool const requires_output_buffer =
            ::NS(OutputBuffer_requires_output_buffer)( flags );

        if( requires_output_buffer )
        {
            success = this->doPrepareOutputStructures(
                this->ptrCParticlesBuffer(), this->ptrCBeamElementsBuffer(),
                ptr_output_buffer, this->numElemByElemTurns() );
        }

        if( ( success ) &&
            ( ::NS(OutputBuffer_requires_beam_monitor_output)( flags ) ) &&
            ( this->hasOutputBuffer() ) && ( this->hasBeamMonitorOutput() ) )
        {
            success = this->doAssignOutputBufferToBeamMonitors(
                this->ptrCBeamElementsBuffer(), this->ptrCOutputBuffer() );
        }

        return success;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::status_t TrackJobBaseNew::doFetchParticleAddresses()
    {
        return st::CONTROLLER_STATUS_GENERAL_FAILURE;
    }

    TrackJobBaseNew::track_status_t
    TrackJobBaseNew::doTrackUntilTurn( TrackJobBaseNew::size_type const )
    {
        return st::TRACK_STATUS_GENERAL_FAILURE;
    }

    TrackJobBaseNew::track_status_t TrackJobBaseNew::doTrackElemByElem(
        TrackJobBaseNew::size_type const until_turn_elem_by_elem )
    {
        return st::TRACK_STATUS_GENERAL_FAILURE;
    }

    TrackJobBaseNew::track_status_t TrackJobBaseNew::doTrackLine(
        TrackJobBaseNew::size_type const, TrackJobBaseNew::size_type const,
            bool const )
    {
        return st::TRACK_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::doSetPtrParticleBuffer(
        TrackJobBaseNew::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ptr_buffer != nullptr )
        {
            this->m_ptr_c_particles_buffer = ptr_buffer->getCApiPtr();
        }
        else if( ( this->m_ptr_particles_buffer != nullptr ) &&
                 ( this->m_ptr_c_particles_buffer ==
                   this->m_ptr_particles_buffer->getCApiPtr() ) )
        {
            this->m_ptr_c_particles_buffer = nullptr;
        }

        this->m_ptr_particles_buffer = ptr_buffer;
        return;
    }

    void TrackJobBaseNew::doSetPtrBeamElementsBuffer(
        TrackJobBaseNew::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_particles_buffer   != nullptr ) &&
            ( this->m_ptr_c_particles_buffer ==
              this->m_ptr_particles_buffer->getCApiPtr() ) &&
            ( this->m_ptr_particles_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_particles_buffer = nullptr;
        }

        this->m_ptr_c_particles_buffer = ptr_buffer;
        return;
    }

    void TrackJobBaseNew::doSetPtrOutputBuffer(
        TrackJobBaseNew::buffer_t* SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ptr_buffer != nullptr )
        {
            this->m_ptr_c_output_buffer = ptr_buffer->getCApiPtr();
        }
        else if( ( this->m_ptr_output_buffer != nullptr ) &&
                 ( this->m_ptr_c_output_buffer ==
                   this->m_ptr_output_buffer->getCApiPtr() ) )
        {
            this->m_ptr_c_output_buffer = nullptr;
        }

        this->m_ptr_output_buffer = ptr_buffer;
    }

    void TrackJobBaseNew::doSetPtrCParticleBuffer( TrackJobBaseNew::c_buffer_t*
        SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_particles_buffer   != nullptr ) &&
            ( this->m_ptr_c_particles_buffer ==
              this->m_ptr_particles_buffer->getCApiPtr() ) &&
            ( this->m_ptr_particles_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_particles_buffer = nullptr;
        }

        this->m_ptr_c_particles_buffer = ptr_buffer;
        return;
    }

    void TrackJobBaseNew::doSetPtrCBeamElementsBuffer(
        TrackJobBaseNew::c_buffer_t* SIXTRL_RESTRICT
            ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_beam_elem_buffer != nullptr ) &&
            ( this->m_ptr_c_beam_elem_buffer ==
              this->m_ptr_beam_elem_buffer->getCApiPtr() ) &&
            ( this->m_ptr_beam_elem_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_beam_elem_buffer = nullptr;
        }

        this->m_ptr_c_beam_elem_buffer = ptr_buffer;
        return;
    }

    void TrackJobBaseNew::doSetPtrCOutputBuffer( TrackJobBaseNew::c_buffer_t*
        SIXTRL_RESTRICT ptr_buffer ) SIXTRL_NOEXCEPT
    {
        if( ( this->m_ptr_output_buffer != nullptr ) &&
            ( this->m_ptr_c_output_buffer ==
              this->m_ptr_output_buffer->getCApiPtr() ) &&
            ( this->m_ptr_output_buffer->getCApiPtr() != ptr_buffer ) )
        {
            this->m_ptr_output_buffer = nullptr;
        }

        this->m_ptr_c_output_buffer = ptr_buffer;
        return;
    }

    void TrackJobBaseNew::doSetBeamMonitorOutputBufferOffset(
        TrackJobBaseNew::size_type const
            output_buffer_offset ) SIXTRL_NOEXCEPT
    {
        this->m_be_mon_output_buffer_offset = output_buffer_offset;
    }

    void TrackJobBaseNew::doSetElemByElemOutputIndexOffset(
        TrackJobBaseNew::size_type const
            elem_by_elem_output_offset ) SIXTRL_NOEXCEPT
    {
        this->m_elem_by_elem_output_offset = elem_by_elem_output_offset;
    }

    void TrackJobBaseNew::doSetUntilTurnElemByElem(
        TrackJobBaseNew::particle_index_t
            const until_turn_elem_by_elem ) SIXTRL_NOEXCEPT
    {
        this->m_until_turn_elem_by_elem = until_turn_elem_by_elem;
    }

    void TrackJobBaseNew::doSetRequiresCollectFlag(
        bool const requires_collect_flag ) SIXTRL_NOEXCEPT
    {
        this->m_requires_collect = requires_collect_flag;
    }

    void TrackJobBaseNew::doSetBeamMonitorOutputEnabledFlag(
        bool const has_beam_monitor_output ) SIXTRL_NOEXCEPT
    {
        this->m_has_beam_monitor_output = has_beam_monitor_output;
    }

    void TrackJobBaseNew::doSetElemByElemOutputEnabledFlag(
        bool const has_elem_by_elem_output ) SIXTRL_NOEXCEPT
    {
        this->m_has_elem_by_elem_output = has_elem_by_elem_output;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::doInitDefaultParticleSetIndices()
    {
        using size_t = TrackJobBaseNew::size_type;
        this->m_particle_set_indices.clear();
        this->m_particle_set_indices.push_back( size_t{ 0 } );
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::doInitDefaultBeamMonitorIndices()
    {
        this->m_beam_monitor_indices.clear();
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::doSetTotalNumParticles(
        TrackJobBaseNew::num_particles_t const total_pnum ) SIXTRL_NOEXCEPT
    {
        this->m_total_num_particles = total_pnum;
    }

    void TrackJobBaseNew::doSetMinParticleId(
        TrackJobBaseNew::particle_index_t const min_part_id ) SIXTRL_NOEXCEPT
    {
         this->m_min_particle_id = min_part_id;
    }

    void TrackJobBaseNew::doSetMaxParticleId(
        TrackJobBaseNew::particle_index_t const max_part_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_particle_id = max_part_id;
    }

    void TrackJobBaseNew::doSetMinElementId(
        TrackJobBaseNew::particle_index_t const min_elem_id ) SIXTRL_NOEXCEPT
    {
        this->m_min_element_id = min_elem_id;
    }

    void TrackJobBaseNew::doSetMaxElementId(
        TrackJobBaseNew::particle_index_t const max_elem_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_element_id = max_elem_id;
    }

    void TrackJobBaseNew::doSetMinInitialTurnId(
        TrackJobBaseNew::particle_index_t const
            min_initial_turn_id ) SIXTRL_NOEXCEPT
    {
        this->m_min_initial_turn_id = min_initial_turn_id;
    }

    void TrackJobBaseNew::doSetMaxInitialTurnId( particle_index_t const
        max_initial_turn_id ) SIXTRL_NOEXCEPT
    {
        this->m_max_initial_turn_id = max_initial_turn_id;
    }

    /* --------------------------------------------------------------------- */

    TrackJobBaseNew::buffer_t const*
        TrackJobBaseNew::doGetPtrParticlesAddrBuffer() const SIXTRL_NOEXCEPT
    {
        return this->m_my_particles_addr_buffer.get();
    }

    TrackJobBaseNew::buffer_t*
    TrackJobBaseNew::doGetPtrParticlesAddrBuffer() SIXTRL_NOEXCEPT
    {
        return this->m_my_particles_addr_buffer.get();
    }

    void TrackJobBaseNew::doUpdateStoredParticlesAddrBuffer(
        TrackJobBaseNew::ptr_particles_addr_buffer_t&&
            ptr_buffer ) SIXTRL_NOEXCEPT
    {
        this->m_my_particles_addr_buffer = std::move( ptr_buffer );
    }

    void TrackJobBaseNew::doSetHasParticleAddressesFlag(
            bool const has_particle_addresses ) SIXTRL_NOEXCEPT
    {
        this->m_has_particle_addresses = has_particle_addresses;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::doUpdateStoredOutputBuffer(
        TrackJobBaseNew::ptr_output_buffer_t&& ptr_out_buffer ) SIXTRL_NOEXCEPT
    {
        this->doSetPtrOutputBuffer( ptr_out_buffer.get() );
        this->m_my_output_buffer = std::move( ptr_out_buffer );
    }

    void TrackJobBaseNew::doUpdateStoredElemByElemConfig(
        TrackJobBaseNew::ptr_elem_by_elem_config_t&& ptr_conf ) SIXTRL_NOEXCEPT
    {
        this->m_my_elem_by_elem_config = std::move( ptr_conf );
    }

    void TrackJobBaseNew::doSetUsesControllerFlag(
        bool const uses_controller_flag ) SIXTRL_NOEXCEPT
    {
        this->m_uses_controller = uses_controller_flag;
    }

    void TrackJobBaseNew::doSetUsesArgumentsFlag(
        bool const arguments_flag ) SIXTRL_NOEXCEPT
    {
        this->m_uses_arguments = arguments_flag;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::doSetLastSuccessFlag( TrackJobBaseNew::success_flag_t
        const last_success_flag_value ) SIXTRL_NOEXCEPT
    {
        this->m_success_flag = last_success_flag_value;
    }

    TrackJobBaseNew::success_flag_t const*
    TrackJobBaseNew::doGetPtrLastSuccessFlag() const SIXTRL_NOEXCEPT
    {
        return &this->m_success_flag;
    }

    TrackJobBaseNew::success_flag_t*
    TrackJobBaseNew::doGetPtrLastSuccessFlag() SIXTRL_NOEXCEPT
    {
        return &this->m_success_flag;
    }

    /* --------------------------------------------------------------------- */

    void TrackJobBaseNew::doClearBaseImpl() SIXTRL_NOEXCEPT
    {
        this->doInitDefaultParticleSetIndices();
        this->doInitDefaultBeamMonitorIndices();

        this->m_my_output_buffer.reset( nullptr );
        this->m_my_particles_addr_buffer.reset( nullptr );
        this->m_my_elem_by_elem_config.reset( nullptr );

        this->m_ptr_particles_buffer         = nullptr;
        this->m_ptr_beam_elem_buffer         = nullptr;
        this->m_ptr_output_buffer            = nullptr;

        this->m_ptr_c_particles_buffer       = nullptr;
        this->m_ptr_c_beam_elem_buffer       = nullptr;
        this->m_ptr_c_output_buffer          = nullptr;

        this->m_be_mon_output_buffer_offset  = TrackJobBaseNew::size_type{ 0 };
        this->m_elem_by_elem_output_offset   = TrackJobBaseNew::size_type{ 0 };

        this->m_total_num_particles          =
            TrackJobBaseNew::num_particles_t{ 0 };

        this->m_default_elem_by_elem_order   =
            ::NS(ELEM_BY_ELEM_ORDER_DEFAULT);

        ::NS(Particles_init_min_max_attributes_for_find)(
            &this->m_min_particle_id, &this->m_max_particle_id,
            &this->m_min_element_id,  &this->m_max_element_id,
            &this->m_min_initial_turn_id, &this->m_max_initial_turn_id );

        this->m_until_turn_elem_by_elem      = TrackJobBaseNew::size_type{ 0 };

        this->m_default_elem_by_elem_rolling = true;
        this->m_has_beam_monitor_output      = false;
        this->m_has_elem_by_elem_output      = false;
        this->m_has_particle_addresses       = false;

        return;
    }

    /* ********************************************************************* */

    TrackJobBaseNew* TrackJobNew_create(
        TrackJobBaseNew::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT conf_str )
    {
        TrackJobBaseNew* ptr_track_job = nullptr;

        switch( arch_id )
        {
            case st::ARCHITECTURE_CUDA:
            {
                #if defined( SIXTRACKLIB_ENABLE_MODULE_CUDA ) && \
                    SIXTRACKLIB_ENABLE_MODULE_CUDA == 1
                std::string const node_id_str =
                    st::NodeId_extract_node_id_str_from_config_str( conf_str );

                ptr_track_job = new st::CudaTrackJob( ( !node_id_str.empty() )
                    ? node_id_str.c_str() : nullptr, conf_str );
                #endif /* CUDA */

                break;
            }

            default:
            {
                ptr_track_job = nullptr;
            }
        };

        return ptr_track_job;
    }

    TrackJobBaseNew* TrackJobNew_create(
        char const* SIXTRL_RESTRICT arch_str,
        char const* SIXTRL_RESTRICT config_str )
    {
        return st::TrackJobNew_create(
            st::ArchInfo_arch_string_to_arch_id( arch_str ), config_str );
    }

    TrackJobBaseNew* TrackJobNew_new(
        char const* SIXTRL_RESTRICT arch_str,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT belements_buffer,
        char const* SIXTRL_RESTRICT config_str )
    {
        return st::TrackJobNew_new(
            st::ArchInfo_arch_string_to_arch_id( arch_str ), particles_buffer,
                belements_buffer, config_str );
    }

    TrackJobBaseNew* TrackJobNew_new(
        ::NS(arch_id_t) const arch_id,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT belements_buffer,
        char const* SIXTRL_RESTRICT config_str )
    {
        TrackJobBaseNew* ptr_track_job =
            st::TrackJobNew_create( arch_id, config_str );

        if( ptr_track_job != nullptr )
        {
            if( !ptr_track_job->reset( particles_buffer, belements_buffer ) )
            {
                delete ptr_track_job;
                ptr_track_job = nullptr;
            }
        }

        return ptr_track_job;
    }

    TrackJobBaseNew* TrackJobNew_new(
        char const* SIXTRL_RESTRICT arch_str,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT belements_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
        ::NS(buffer_size_t) const until_turn_elem_by_elem,
        char const* SIXTRL_RESTRICT config_str )
    {
        return st::TrackJobNew_new(
            st::ArchInfo_arch_string_to_arch_id( arch_str ), particles_buffer,
                belements_buffer, output_buffer, until_turn_elem_by_elem,
                    config_str );
    }

    TrackJobBaseNew* TrackJobNew_new(
        ::NS(arch_id_t) const arch_id,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT belements_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
        ::NS(buffer_size_t) const until_turn_elem_by_elem,
        char const* SIXTRL_RESTRICT config_str )
    {
        TrackJobBaseNew* ptr_track_job =
            st::TrackJobNew_create( arch_id, config_str );

        if( ptr_track_job != nullptr )
        {
            if( !ptr_track_job->reset( particles_buffer, belements_buffer,
                    output_buffer, until_turn_elem_by_elem ) )
            {
                delete ptr_track_job;
                ptr_track_job = nullptr;
            }
        }

        return ptr_track_job;
    }

    TrackJobBaseNew* TrackJobNew_new(
        char const* SIXTRL_RESTRICT arch_str,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(buffer_size_t) const num_psets,
        ::NS(buffer_size_t) const* SIXTRL_RESTRICT pset_indices_begin,
        ::NS(Buffer)* SIXTRL_RESTRICT belements_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
        ::NS(buffer_size_t) const until_turn_elem_by_elem,
        char const* SIXTRL_RESTRICT config_str )
    {
        return st::TrackJobNew_new(
            st::ArchInfo_arch_string_to_arch_id( arch_str ), particles_buffer,
                num_psets, pset_indices_begin, belements_buffer,
                    output_buffer, until_turn_elem_by_elem, config_str );
    }

    TrackJobBaseNew* TrackJobNew_new(
        ::NS(arch_id_t) const SIXTRL_RESTRICT arch_id,
        ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
        ::NS(buffer_size_t) const num_psets,
        ::NS(buffer_size_t) const* SIXTRL_RESTRICT pset_indices_begin,
        ::NS(Buffer)* SIXTRL_RESTRICT belements_buffer,
        ::NS(Buffer)* SIXTRL_RESTRICT output_buffer,
        ::NS(buffer_size_t) const until_turn_elem_by_elem,
        const char *const SIXTRL_RESTRICT config_str )
    {
        TrackJobBaseNew* ptr_track_job =
            st::TrackJobNew_create( arch_id, config_str );

        if( ptr_track_job != nullptr )
        {
            if( !ptr_track_job->reset( particles_buffer, num_psets,
                    pset_indices_begin, belements_buffer,
                        output_buffer, until_turn_elem_by_elem ) )
            {
                delete ptr_track_job;
                ptr_track_job = nullptr;
            }
        }

        return ptr_track_job;
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    TrackJobBaseNew* TrackJobNew_create(
        SIXTRL_CXX_NAMESPACE::arch_id_t const arch_id,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return st::TrackJobNew_create( arch_id, config_str.c_str() );
    }

    TrackJobBaseNew* TrackJobNew_create(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        std::string const& SIXTRL_RESTRICT_REF conf_str )
    {
        return st::TrackJobNew_create(
            st::ArchInfo_arch_string_to_arch_id( arch_str ), conf_str.c_str());
    }

    TrackJobBaseNew* TrackJobNew_new(
        SIXTRL_CXX_NAMESPACE::arch_id_t const arch_id,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Buffer& SIXTRL_RESTRICT_REF belements_buffer,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        TrackJobBaseNew* ptr_track_job =
            st::TrackJobNew_create( arch_id, config_str );

        if( ptr_track_job != nullptr )
        {
            if( !ptr_track_job->reset( particles_buffer, belements_buffer ) )
            {
                delete ptr_track_job;
                ptr_track_job = nullptr;
            }
        }

        return ptr_track_job;
    }

    TrackJobBaseNew* TrackJobNew_new(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Buffer& SIXTRL_RESTRICT_REF belements_buffer,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return st::TrackJobNew_new(
            st::ArchInfo_arch_string_to_arch_id( arch_str ), particles_buffer,
                belements_buffer, config_str );
    }

    TrackJobBaseNew* TrackJobNew_new(
        SIXTRL_CXX_NAMESPACE::arch_id_t const arch_id,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Buffer& SIXTRL_RESTRICT_REF belements_buffer,
        Buffer* SIXTRL_RESTRICT output_buffer,
        Buffer::size_type const until_turn_elem_by_elem,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        TrackJobBaseNew* ptr_track_job =
            st::TrackJobNew_create( arch_id, config_str );

        if( ptr_track_job != nullptr )
        {
            if( !ptr_track_job->reset( particles_buffer, belements_buffer,
                    output_buffer, until_turn_elem_by_elem ) )
            {
                delete ptr_track_job;
                ptr_track_job = nullptr;
            }
        }

        return ptr_track_job;
    }

    TrackJobBaseNew* TrackJobNew_new(
        std::string const& SIXTRL_RESTRICT_REF arch_str,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Buffer::size_type const num_psets,
        Buffer::size_type const* SIXTRL_RESTRICT pset_indices_begin,
        Buffer& SIXTRL_RESTRICT_REF belements_buffer,
        Buffer* SIXTRL_RESTRICT output_buffer,
        Buffer::size_type const until_turn_elem_by_elem,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        return st::TrackJobNew_new(
            st::ArchInfo_arch_string_to_arch_id( arch_str ), particles_buffer,
                num_psets, pset_indices_begin, belements_buffer, output_buffer,
                    until_turn_elem_by_elem, config_str );
    }

    TrackJobBaseNew* TrackJobNew_new(
        SIXTRL_CXX_NAMESPACE::arch_id_t const arch_id,
        Buffer& SIXTRL_RESTRICT_REF particles_buffer,
        Buffer::size_type const num_psets,
        Buffer::size_type const* SIXTRL_RESTRICT pset_indices_begin,
        Buffer& SIXTRL_RESTRICT_REF belements_buffer,
        Buffer* SIXTRL_RESTRICT output_buffer,
        Buffer::size_type const until_turn_elem_by_elem,
        std::string const& SIXTRL_RESTRICT_REF config_str )
    {
        using size_t = TrackJobBaseNew::size_type;

        TrackJobBaseNew* ptr_track_job =
            st::TrackJobNew_create( arch_id, config_str );

        if( ptr_track_job != nullptr )
        {
            size_t const* pset_indices_end = pset_indices_begin;

            if( ( pset_indices_end != nullptr ) &&
                ( num_psets > size_t{ 0 } ) )
            {
                std::advance( pset_indices_end, num_psets );
            }

            if( !ptr_track_job->reset( particles_buffer, pset_indices_begin,
                    pset_indices_end, belements_buffer, output_buffer,
                        until_turn_elem_by_elem ) )
            {
                delete ptr_track_job;
                ptr_track_job = nullptr;
            }
        }

        return ptr_track_job;
    }
}

#endif /* C++,  Host */

/* end: sixtracklib/common/track/track_job_base.cpp */
