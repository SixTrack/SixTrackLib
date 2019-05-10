#include "sixtracklib/common/track/track_job_ctrl_arg_base.hpp"

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
        #include "sixtracklib/common/control/definitions.h"
        #include "sixtracklib/common/buffer.hpp"
        #include "sixtracklib/common/buffer.h"
        #include "sixtracklib/common/particles.h"
        #include "sixtracklib/common/output/output_buffer.h"
        #include "sixtracklib/common/output/elem_by_elem_config.h"
        #include "sixtracklib/common/control/controller_base.hpp"
        #include "sixtracklib/common/control/controller_on_nodes_base.hpp"
        #include "sixtracklib/common/control/argument_base.hpp"
        #include "sixtracklib/common/track/definitions.h"
        #include "sixtracklib/common/track/track_job_base.hpp"
    #endif /* defined( __cplusplus ) */

#endif /* C++, Host */

#if defined( __cplusplus ) && !defined( _GPUCODE )

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    TrackJobCtrlArgBase::status_t
    TrackJobCtrlArgBase::resetDebugFlag(
        TrackJobCtrlArgBase::debug_flag_t const flag_value );
    {
        using status_t = TrackJobCtrlArgBase::status_t;
        using debug_flag_t = TrackJobCtrlArgBase::debug_flag_t;
        using size_t = TrackJobCtrlArgBase::size_type;

        status_t status = st::CONTROLLER_STATUS_GENERAL_FAILURE;
        size_t const flag_size = sizeof( debug_flag_t );

        if( ( this->doGetPtrLastDebugFlag() != nullptr ) &&
            ( this->ptrDebugFlagArgBase() != nullptr ) &&
            ( this->ptrDebugFlagArgBase()->usesRawArgument() ) &&
            ( this->ptrDebugFlagArgBase()->size() == flag_size ) )
        {
            this->doSetLastDebugFlag( flag_value );

            status = this->ptrDebugFlagArgBase()->send(
                this->doGetPtrLastDebugFlag(), flag_size );
        }

        return status;
    }

    TrackJobCtrlArgBase::status_t
    TrackJobCtrlArgBase::prepareDebugFlagForUse()
    {
        using debug_flag_t = TrackJobCtrlArgBase::debug_flag_t;
        using status_t = TrackJobCtrlArgBase::status_t;

        status_t status = this->resetDebugFlag(
            ::NS(CONTROLLER_DEBUG_FLAG_NOT_OK) );

        if( ( status == st::CONTROLLER_STATUS_SUCCESS ) &&
            ( this->lastDebugFlag() != flag ) )
        {
            status = st::CONTROLLER_STATUS_GENERAL_FAILURE;
        }

        return status;
    }

    TrackJobCtrlArgBase::status_t
    TrackJobCtrlArgBase::evaluateDebugFlagAfterUse()
    {
        using debug_flag_t = TrackJobCtrlArgBase::debug_flag_t;

        return ( ( this->collectDebugFlag() ) ||
                 ( this->lastDebugFlag() == ::NS(CONTROLLER_DEBUG_FLAG_OK) ) )
            ? st::CONTROLLER_STATUS_SUCCESS
            : st::CONTROLLER_STATUS_GENERAL_FAILURE;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobCtrlArgBase::hasAssignOutputToBeamMonitorsKernel(
        ) const SIXTRL_NOEXCEPT
    {
        using base_ctrl_t = TrackJobCtrlArgBase::controller_base_t;
        return ( base_ctrl_t::ILLEGAL_KERNEL_ID ==
            this->m_assign_output_bemon_kernel_id );
    }

    TrackJobCtrlArgBase::kernel_id_t
    TrackJobCtrlArgBase::assignOutputToBeamMonitorsKernelId(
        ) const SIXTRL_NOEXCEPT
    {
        return this->m_assign_output_bemon_kernel_id;
    }

    void TrackJobCtrlArgBase::setAssignOutputToBeamMonitorsKernelId(
        TrackJobCtrlArgBase::kernel_id_t const id ) SIXTRL_NOEXCEPT
    {
        this->m_assign_output_bemon_kernel_id = id;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobCtrlArgBase::hasTrackUntilKernel() const SIXTRL_NOEXCEPT
    {
        using base_ctrl_t = TrackJobCtrlArgBase::controller_base_t;
        return ( base_ctrl_t::ILLEGAL_KERNEL_ID ==
            this->m_track_until_kernel_id );
    }

    TrackJobCtrlArgBase::kernel_id_t
    TrackJobCtrlArgBase::trackUntilKernelId() const SIXTRL_NOEXCEPT
    {
        return this->m_track_until_kernel_id;
    }

    void TrackJobCtrlArgBase::setTrackUntilKernelId(
        TrackJobCtrlArgBase::kernel_id_t const id ) SIXTRL_NOEXCEPT
    {
        this->m_track_until_kernel_id = id;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobCtrlArgBase::hasTrackLineKernel() const SIXTRL_NOEXCEPT
    {
        using base_ctrl_t = TrackJobCtrlArgBase::controller_base_t;
        return ( base_ctrl_t::ILLEGAL_KERNEL_ID ==
            this->m_track_line_kernel_id );
    }

    TrackJobCtrlArgBase::kernel_id_t
    TrackJobCtrlArgBase::trackLineKernelId() const SIXTRL_NOEXCEPT
    {
        return this->m_track_line_kernel_id;
    }

    void TrackJobCtrlArgBase::setTrackLineKernelId(
        TrackJobCtrlArgBase::kernel_id_t const id ) SIXTRL_NOEXCEPT
    {
        this->m_track_line_kernel_id = id;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobCtrlArgBase::hasTrackElemByElemKernel() const SIXTRL_NOEXCEPT
    {
        using base_ctrl_t = TrackJobCtrlArgBase::controller_base_t;
        return ( base_ctrl_t::ILLEGAL_KERNEL_ID ==
            this->m_track_elem_by_elem_kernel_id );
    }

    TrackJobCtrlArgBase::kernel_id_t
    TrackJobCtrlArgBase::trackElemByElemKernelId() const SIXTRL_NOEXCEPT
    {
        return this->m_track_elem_by_elem_kernel_id;
    }

    void TrackJobCtrlArgBase::setTrackElemByElemKernelId(
        TrackJobCtrlArgBase::kernel_id_t const id ) SIXTRL_NOEXCEPT
    {
        this->m_track_elem_by_elem_kernel_id = id;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobCtrlArgBase::hasFetchParticlesAddressesKernel()
        const SIXTRL_NOEXCEPT
    {
        using base_ctrl_t = TrackJobCtrlArgBase::controller_base_t;
        return ( base_ctrl_t::ILLEGAL_KERNEL_ID ==
            this->m_fetch_particles_addr_kernel_id );
    }

    TrackJobCtrlArgBase::kernel_id_t
    TrackJobCtrlArgBase::fetchParticlesAddressesKernelId(
        ) const SIXTRL_NOEXCEPT
    {
        return this->m_fetch_particles_addr_kernel_id;
    }

    void TrackJobCtrlArgBase::setFetchParticlesAddressesKernelId(
        TrackJobCtrlArgBase::kernel_id_t const id ) SIXTRL_NOEXCEPT
    {
        this->m_fetch_particles_addr_kernel_id = id;
    }

    /* --------------------------------------------------------------------- */

    TrackJobCtrlArgBase::TrackJobCtrlArgBase(
        TrackJobCtrlArgBase::arch_id_t const arch_id,
        char const* SIXTRL_RESTRICT arch_str,
        char const* SIXTRL_RESTRICT config_str ) :
        st::TrackJobBaseNew( arch_id, arch_str, config_str ),
        m_stored_controller( nullptr ),
        m_stored_particles_arg( nullptr ),
        m_stored_beam_elements_arg( nullptr ),
        m_stored_output_arg( nullptr ),
        m_stored_debug_flag_arg( nullptr ),
        m_assign_output_bemon_kernel_id(
            st::ControllerBase::ILLEGAL_KERNEL_ID ),
        m_track_until_kernel_id( st::ControllerBase::ILLEGAL_KERNEL_ID ),
        m_track_line_kernel_id( st::ControllerBase::ILLEGAL_KERNEL_ID ),
        m_track_elem_by_elem_kernel_id(
            st::ControllerBase::ILLEGAL_KERNEL_ID ),
        m_fetch_particles_addr_kernel_id(
            st::ControllerBase::ILLEGAL_KERNEL_ID )
    {

    }

    TrackJobCtrlArgBase::TrackJobCtrlArgBase(
        TrackJobCtrlArgBase const& other ) :
        st::TrackJobBaseNew( other ),
        m_stored_controller( nullptr ),
        m_stored_particles_arg( nullptr ),
        m_stored_beam_elements_arg( nullptr ),
        m_stored_output_arg( nullptr ),
        m_stored_debug_flag_arg( nullptr ),
        m_assign_output_bemon_kernel_id(
            other.m_assign_output_bemon_kernel_id ),
        m_track_until_kernel_id( other.m_track_until_kernel_id ),
        m_track_line_kernel_id( other.m_track_line_kernel_id ),
        m_track_elem_by_elem_kernel_id( other.m_track_elem_by_elem_kernel_id ),
        m_fetch_particles_addr_kernel_id(
            other.m_fetch_particles_addr_kernel_id )
    {
//         using base_ctrl_t = TrackJobCtrlArgBase::controller_base_t;
//         using base_arg_t  = TrackJobCtrlArgBase::argument_base_t;

//         using stored_ctrl_base_t = TrackJobCtrlArgBase::stored_ctrl_base_t;
//         using stored_arg_base_t  = TrackJobCtrlArgBase::stored_arg_base_t;

        /* TODO: Implement copying of arguments and controller !!!! */
    }

    TrackJobCtrlArgBase::TrackJobCtrlArgBase(
        TrackJobCtrlArgBase&& other ) SIXTRL_NOEXCEPT :
        st::TrackJobBaseNew( std::move( other ) ),
        m_stored_controller( std::move( other.m_stored_controller ) ),
        m_stored_particles_arg( std::move( other.m_stored_particles_arg ) ),
        m_stored_beam_elements_arg(
            std::move( other.m_stored_beam_elements_arg ) ),
        m_stored_output_arg( std::move( other.m_stored_output_arg ) ),
        m_stored_debug_flag_arg(
            std::move( other.m_stored_debug_flag_arg ) ),
        m_assign_output_bemon_kernel_id( std::move(
            other.m_assign_output_bemon_kernel_id ) ),
        m_track_until_kernel_id( std::move( other.m_track_until_kernel_id ) ),
        m_track_line_kernel_id( std::move( other.m_track_line_kernel_id ) ),
        m_track_elem_by_elem_kernel_id( std::move(
            other.m_track_elem_by_elem_kernel_id ) ),
        m_fetch_particles_addr_kernel_id(
            std::move( other.m_fetch_particles_addr_kernel_id ) )
    {
        other.doClearCtrlArgBaseImpl();
    }

    TrackJobCtrlArgBase& TrackJobCtrlArgBase::operator=(
        TrackJobCtrlArgBase const& rhs )
    {
        if( ( this != &rhs ) && ( this->isArchCompatibleWith( rhs ) ) )
        {
            this->m_stored_controller.reset( nullptr );

            this->m_stored_particles_arg.reset( nullptr );
            this->m_stored_beam_elements_arg.reset( nullptr );
            this->m_stored_output_arg.reset( nullptr );
            this->m_stored_debug_flag_arg.reset( nullptr );

            this->m_assign_output_bemon_kernel_id =
                rhs.m_assign_output_bemon_kernel_id;

            this->m_track_until_kernel_id = rhs.m_track_until_kernel_id;
            this->m_track_line_kernel_id  = rhs.m_track_line_kernel_id;

            this->m_track_elem_by_elem_kernel_id =
                rhs.m_track_elem_by_elem_kernel_id;

            this->m_fetch_particles_addr_kernel_id =
                rhs.m_fetch_particles_addr_kernel_id;

            /* TODO: Implement copying of arguments and controller */
        }

        return *this;
    }

    TrackJobCtrlArgBase& TrackJobCtrlArgBase::operator=(
        TrackJobCtrlArgBase&& rhs ) SIXTRL_NOEXCEPT
    {
        if( ( this != &rhs ) && ( this->isArchCompatibleWith( rhs ) ) )
        {
            this->m_stored_controller = std::move( rhs.m_stored_controller );

            this->m_stored_particles_arg =
                std::move( rhs.m_stored_particles_arg );

            this->m_stored_beam_elements_arg =
                std::move( rhs.m_stored_beam_elements_arg );

            this->m_stored_output_arg = std::move( rhs.m_stored_output_arg );

            this->m_stored_debug_flag_arg =
                std::move( rhs.m_stored_debug_flag_arg );

            this->m_assign_output_bemon_kernel_id =
                std::move( rhs.m_assign_output_bemon_kernel_id );

            this->m_track_until_kernel_id =
                std::move( rhs.m_track_until_kernel_id );

            this->m_track_line_kernel_id =
                std::move( rhs.m_track_line_kernel_id );

            this->m_track_elem_by_elem_kernel_id =
                std::move( rhs.m_track_elem_by_elem_kernel_id );

            this->m_fetch_particles_addr_kernel_id =
                std::move( rhs.m_fetch_particles_addr_kernel_id );
        }

        return *this;
    }

    void TrackJobCtrlArgBase::doClear()
    {
        this->doClearCtrlArgBaseImpl();
        st::TrackJobBaseNew::doClear();
    }

    TrackJobCtrlArgBase::collect_flag_t TrackJobCtrlArgBase::doCollect(
        TrackJobCtrlArgBase::collect_flag_t const flags )
    {
        using _this_t = st::TrackJobCtrlArgBase;
        using _base_t = st::TrackJobBaseNew;
        using collect_flag_t = _this_t::collect_flag_t;
        using status_t = _this_t::status_t;

        collect_flag_t result = st::TRACK_JOB_COLLECT_NONE;

        if( ( _base_t::IsCollectFlagSet(
                flags, st::TRACK_JOB_COLLECT_PARTICLES ) ) &&
            ( this->ptrParticlesArgBase() != nullptr ) &&
            ( this->ptrParticlesArgBase()->usesCObjectsBuffer() ) &&
            ( this->ptrCParticlesBuffer() != nullptr ) )
        {
            status_t const status = this->ptrParticlesArgBase()->receive(
                this->ptrCParticlesBuffer() );

            if( status == st::CONTROLLER_STATUS_SUCCESS )
            {
                result |= st::TRACK_JOB_COLLECT_PARTICLES;
            }
        }

        if( ( _base_t::IsCollectFlagSet(
                flags, st::TRACK_JOB_COLLECT_BEAM_ELEMENTS ) ) &&
            ( this->ptrBeamElementsArgBase() != nullptr ) &&
            ( this->ptrBeamElementsArgBase()->usesCObjectsBuffer() ) &&
            ( this->ptrCBeamElementsBuffer() != nullptr ) )
        {
            status_t const status = this->ptrBeamElementsArgBase()->receive(
                this->ptrCBeamElementsBuffer() );

            if( status == st::CONTROLLER_STATUS_SUCCESS )
            {
                result |= st::TRACK_JOB_COLLECT_BEAM_ELEMENTS;
            }
        }

        if( ( _base_t::IsCollectFlagSet(
                flags, st::TRACK_JOB_COLLECT_OUTPUT ) ) &&
            ( this->ptrOutputArgBase() != nullptr ) &&
            ( this->ptrOutputArgBase()->usesCObjectsBuffer() ) &&
            ( this->ptrCOutputBuffer() != nullptr ) )
        {
            status_t const status = this->ptrOutputArgBase()->receive(
                this->ptrCOutputBuffer() );

            if( status == st::CONTROLLER_STATUS_SUCCESS )
            {
                result |= st::TRACK_JOB_COLLECT_OUTPUT;
            }
        }

        if( ( _base_t::IsCollectFlagSet(
                flags, st::TRACK_JOB_COLLECT_DEBUG_FLAG ) ) &&
            ( this->ptrDebugFlagArgBase() != nullptr ) &&
            ( this->ptrDebugFlagArgBase()->usesRawArgument() ) &&
            ( this->doGetPtrLastDebugFlag() != nullptr ) )
        {
            using debug_flag_t = _base_t::debug_flag_t;

            status_t const status = this->ptrDebugFlagArgBase()->receive(
                this->doGetPtrLastDebugFlag(), sizeof( debug_flag_t ) );

            if( status == st::CONTROLLER_STATUS_SUCCESS )
            {
                result |= st::TRACK_JOB_COLLECT_DEBUG_FLAG;
            }
        }

        if( ( _base_t::IsCollectFlagSet(
                flags, st::TRACK_JOB_COLLECT_PARTICLES_ADDR ) ) &&
            ( this->ptrParticlesArgBase() != nullptr ) &&
            ( this->ptrParticlesArgBase()->usesCxxObjectsBuffer() ) &&
            ( this->doGetPtrParticlesAddrBuffer() != nullptr ) &&
            ( this->doGetPtrParticlesAddrBuffer() ==
              this->ptrParticlesArgBase()->ptrCObjectsCxxBuffer() ) )
        {
            status_t const status = this->ptrParticlesArgBase()->receive(
                this->ptrCObjectsCxxBuffer() );

            if( status == st::CONTROLLER_STATUS_SUCCESS )
            {
                result |= st::TRACK_JOB_COLLECT_PARTICLES_ADDR;
            }
        }

        return result;
    }

    /* --------------------------------------------------------------------- */

    bool TrackJobCtrlArgBase::doPrepareController(
        char const* SIXTRL_RESTRICT )
    {
        return true;
    }

    bool TrackJobCtrlArgBase::doPrepareDefaultKernels(
        char const* SIXTRL_RESTRICT )
    {
        return true;
    }

    /* --------------------------------------------------------------------- */

    TrackJobCtrlArgBase::controller_base_t const*
    TrackJobCtrlArgBase::ptrControllerBase() const SIXTRL_NOEXCEPT
    {
        return this->m_stored_controller.get();
    }

    TrackJobCtrlArgBase::controller_base_t*
    TrackJobCtrlArgBase::ptrControllerBase() SIXTRL_NOEXCEPT
    {
        return this->m_stored_controller.get();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    TrackJobCtrlArgBase::argument_base_t const*
    TrackJobCtrlArgBase::ptrParticlesArg() const SIXTRL_NOEXCEPT
    {
        return this->m_stored_particles_arg.get();
    }

    TrackJobCtrlArgBase::argument_base_t*
    TrackJobCtrlArgBase::ptrParticlesArgBase() SIXTRL_NOEXCEPT
    {
        return this->m_stored_particles_arg.get();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    TrackJobCtrlArgBase::argument_base_t const*
    TrackJobCtrlArgBase::ptrBeamElementsArg() const SIXTRL_NOEXCEPT
    {
        return this->m_stored_beam_elements_arg.get();
    }

    TrackJobCtrlArgBase::argument_base_t*
    TrackJobCtrlArgBase::ptrBeamElementsArgBase() SIXTRL_NOEXCEPT
    {
        return this->m_stored_beam_elements_arg.get();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    TrackJobCtrlArgBase::argument_base_t const*
    TrackJobCtrlArgBase::ptrOutputArg() const SIXTRL_NOEXCEPT
    {
        return this->m_stored_output_arg.get();
    }

    TrackJobCtrlArgBase::argument_base_t*
    TrackJobCtrlArgBase::ptrOutputArgBase() SIXTRL_NOEXCEPT
    {
        return this->m_stored_output_arg.get();
    }

    /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

    TrackJobCtrlArgBase::argument_base_t const*
    TrackJobCtrlArgBase::ptrDebugFlagArgBase() const SIXTRL_NOEXCEPT
    {
        return this->m_stored_debug_flag_arg.get();
    }

    TrackJobCtrlArgBase::argument_base_t*
    TrackJobCtrlArgBase::ptrDebugFlagArgBase() SIXTRL_NOEXCEPT
    {
        return this->m_stored_debug_flag_arg.get();
    }

    /* --------------------------------------------------------------------- */

    void TrackJobCtrlArgBase::doUpdateStoredController(
        TrackJobCtrlArgBase::stored_ctrl_base_t&&
            ptr_controller_base ) SIXTRL_NOEXCEPT
    {
        this->m_stored_controller = std::move( ptr_controller_base );
    }

    void TrackJobCtrlArgBase::doUpdateStoredParticlesArg(
        TrackJobCtrlArgBase::stored_arg_base_t&&
            ptr_particles_arg ) SIXTRL_NOEXCEPT
    {
        this->m_stored_particles_arg = std::move( ptr_particles_arg );
    }

    void TrackJobCtrlArgBase::doUpdateStoredBeamElementsArg(
        TrackJobCtrlArgBase::stored_arg_base_t&&
            ptr_beam_elem_arg ) SIXTRL_NOEXCEPT
    {
        this->m_stored_beam_elements_arg = std::move( ptr_beam_elem_arg );
    }

    void TrackJobCtrlArgBase::doUpdateStoredOutputArg(
        TrackJobCtrlArgBase::stored_arg_base_t&&
            ptr_output_arg ) SIXTRL_NOEXCEPT
    {
        this->m_stored_output_arg = std::move( ptr_output_arg );
    }

    void TrackJobCtrlArgBase::doUpdateStoredDebugFlagArg(
        TrackJobCtrlArgBase::stored_arg_base_t&&
            ptr_debug_flag_arg ) SIXTRL_NOEXCEPT
    {
        this->m_stored_debug_flag_arg = std::move( ptr_debug_flag_arg );
    }

    /* --------------------------------------------------------------------- */

    void TrackJobCtrlArgBase::doClearCtrlArgBaseImpl() SIXTRL_NOEXCEPT
    {
        using base_ctrl_t = st::TrackJobCtrlArgBase::controller_base_t;

        this->m_assign_output_bemon_kernel_id = base_ctrl_t::ILLEGAL_KERNEL_ID;
        this->m_track_until_kernel_id = base_ctrl_t::ILLEGAL_KERNEL_ID;
        this->m_track_line_kernel_id = base_ctrl_t::ILLEGAL_KERNEL_ID;
        this->m_track_elem_by_elem_kernel_id = base_ctrl_t::ILLEGAL_KERNEL_ID;
        this->m_fetch_particles_addr_kernel_id =
            base_ctrl_t::ILLEGAL_KERNEL_ID;

        this->m_stored_particles_arg.reset( nullptr );
        this->m_stored_beam_elements_arg.reset( nullptr );
        this->m_stored_output_arg.reset( nullptr );
        this->m_stored_debug_flag_arg.reset( nullptr );
        this->m_stored_controller.reset( nullptr );

        return;
    }
}

#endif /* C++, Host */

/* end: sixtracklib/common/track/track_job_ctrl_arg_base.cpp */
