#include "sixtracklib/opencl/context.h"

#if !defined( __CUDACC__ )

#include <chrono>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iterator>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/generated/path.h"
#include "sixtracklib/common/internal/compute_arch.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/particles.h"
#include "sixtracklib/opencl/internal/base_context.h"

#if defined( __cplusplus )

namespace SIXTRL_CXX_NAMESPACE
{
    ClContext::ClContext() :
        ClContextBase(),
        m_tracking_program_id( ClContextBase::program_id_t{ -1 } ),
        m_tracking_kernel_id( ClContextBase::kernel_id_t{ -1 } )
    {
        this->doInitDefaultProgramsPrivImpl();
    }

    ClContext::ClContext( ClContext::size_type const node_index ) :
        ClContextBase(),
        m_tracking_program_id( ClContextBase::program_id_t{ -1 } ),
        m_tracking_kernel_id( ClContextBase::kernel_id_t{ -1 } )
    {
        using base_t = ClContextBase;

        this->doInitDefaultProgramsPrivImpl();

        if( ( node_index < this->numAvailableNodes() ) &&
            ( base_t::doSelectNode( node_index ) ) )
        {
            base_t::doInitDefaultKernels();
            this->doInitDefaultKernelsPrivImpl();
        }
    }

    ClContext::ClContext( ClContext::node_id_t const node_id ) :
        ClContextBase(),
        m_tracking_program_id( ClContextBase::program_id_t{ -1 } ),
        m_tracking_kernel_id( ClContextBase::kernel_id_t{ -1 } )
    {
        using base_t = ClContextBase;
        using size_t = base_t::size_type;

        this->doInitDefaultProgramsPrivImpl();

        size_t const node_index = this->findAvailableNodesIndex(
            NS(ComputeNodeId_get_platform_id)( &node_id ),
            NS(ComputeNodeId_get_device_id)( &node_id ) );

        if( ( node_index < this->numAvailableNodes() ) &&
            ( base_t::doSelectNode( node_index ) ) )
        {
            base_t::doInitDefaultKernels();
            this->doInitDefaultKernelsPrivImpl();
        }
    }

    ClContext::ClContext( char const* node_id_str ) :
        ClContextBase(),
        m_tracking_program_id( ClContextBase::program_id_t{ -1 } ),
        m_tracking_kernel_id( ClContextBase::kernel_id_t{ -1 } )
    {
        using base_t = ClContextBase;
        using size_t = base_t::size_type;

        this->doInitDefaultProgramsPrivImpl();

        size_t node_index = this->findAvailableNodesIndex( node_id_str );

        if( node_index >= this->numAvailableNodes() )
        {
            node_id_t const default_node_id = this->defaultNodeId();

            platform_id_t const platform_index =
                NS(ComputeNodeId_get_platform_id)( &default_node_id );

            device_id_t const device_index =
                NS(ComputeNodeId_get_device_id)( &default_node_id );

            node_index = this->findAvailableNodesIndex(
                platform_index, device_index );
        }

        if( ( node_index < this->numAvailableNodes() ) &&
            ( base_t::doSelectNode( node_index ) ) )
        {
            base_t::doInitDefaultKernels();
            this->doInitDefaultKernelsPrivImpl();
        }
    }

    ClContext::ClContext(
        ClContext::platform_id_t const platform_idx,
        ClContext::device_id_t const device_idx ) :
        ClContextBase(),
        m_tracking_program_id( ClContextBase::program_id_t{ -1 } ),
        m_tracking_kernel_id( ClContextBase::kernel_id_t{ -1 } )
    {
        using base_t = ClContextBase;
        using size_t = base_t::size_type;

        this->doInitDefaultProgramsPrivImpl();

        size_t const node_index =
            this->findAvailableNodesIndex( platform_idx, device_idx );

        if( ( node_index < this->numAvailableNodes() ) &&
            ( base_t::doSelectNode( node_index ) ) )
        {
            base_t::doInitDefaultKernels();
            this->doInitDefaultKernelsPrivImpl();
        }
    }

    ClContext::~ClContext() SIXTRL_NOEXCEPT
    {

    }

    bool ClContext::hasTrackingKernel() const SIXTRL_NOEXCEPT
    {
        return ( ( this->hasSelectedNode() ) &&
                 ( this->m_tracking_kernel_id >= kernel_id_t{ 0 } ) &&
                 ( static_cast< size_type >( this->m_tracking_kernel_id ) <
                   this->numAvailableKernels() ) );
    }

    ClContext::kernel_id_t ClContext::trackingKernelId() const SIXTRL_NOEXCEPT
    {
        return ( this->hasTrackingKernel() )
            ? this->m_tracking_kernel_id
            : kernel_id_t{ - 1 };
    }

    bool ClContext::setTrackingKernelId(
        ClContext::kernel_id_t const kernel_id )
    {
        bool success = false;

        if( ( this->hasSelectedNode() ) &&
            ( kernel_id >= kernel_id_t{ 0 } ) &&
            ( static_cast< size_type >( kernel_id ) <
              this->numAvailableKernels() ) )
        {
            program_id_t const tracking_program_id =
                this->programIdByKernelId( kernel_id );

            if( ( tracking_program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( tracking_program_id ) <
                  this->numAvailablePrograms() ) )
            {
                this->m_tracking_kernel_id  = kernel_id;
                this->m_tracking_program_id = tracking_program_id;
                success = true;
            }
        }

        return success;
    }

    int ClContext::track(
        ClArgument& particles_arg, ClArgument& beam_elements_arg,
        ClContext::num_turns_t num_turns  )
    {
        return this->track( this->trackingKernelId(),
                            particles_arg, beam_elements_arg, num_turns );
    }

    int ClContext::track( kernel_id_t const track_kernel_id,
               NS(ClArgument)& particles_arg,
               NS(ClArgument)& beam_elements_arg,
               num_turns_t const num_turns )
    {
        int success = -1;

        SIXTRL_ASSERT( particles_arg.context() == this );
        SIXTRL_ASSERT( particles_arg.usesCObjectBuffer() );

        NS(Buffer)* particles_buffer = particles_arg.ptrCObjectBuffer();
        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)( particles_buffer ) );

        SIXTRL_ASSERT( beam_elements_arg.context() == this );
        SIXTRL_ASSERT( beam_elements_arg.usesCObjectBuffer() );

        SIXTRL_ASSERT( !NS(Buffer_needs_remapping)(
            beam_elements_arg.ptrCObjectBuffer() ) );

        SIXTRL_ASSERT( this->kernelNumArgs( track_kernel_id ) == 4u );

        size_type const total_num_particles =
            NS(Particles_buffer_get_total_num_of_particles)( particles_buffer);

        uint64_t num_turns_arg = static_cast< uint64_t >( num_turns );

        SIXTRL_ASSERT( total_num_particles > size_type{ 0 } );

        this->assignKernelArgument( track_kernel_id, 0u, particles_arg );
        this->assignKernelArgument( track_kernel_id, 1u, beam_elements_arg );
        this->assignKernelArgumentValue( track_kernel_id, 2u, num_turns_arg );

        this->assignKernelArgumentClBuffer(
            track_kernel_id, 3u, particles_arg.internalSuccessFlagBuffer() );

        if( this->runKernel( track_kernel_id, total_num_particles ) )
        {
            cl::CommandQueue* ptr_queue = this->openClQueue();
            SIXTRL_ASSERT( ptr_queue != nullptr );

            int32_t success_flag = int32_t{ 0 };
            cl_int cl_ret = ptr_queue->enqueueReadBuffer(
                particles_arg.internalSuccessFlagBuffer(), CL_TRUE, 0,
                sizeof( success_flag ), &success_flag );

            if( cl_ret == CL_SUCCESS )
            {
                success = ( int )success_flag;
            }

            ptr_queue->finish();
        }

        return success;
    }

    bool ClContext::doInitDefaultPrograms()
    {
        return ( ( ClContextBase::doInitDefaultPrograms() ) &&
                 ( this->doInitDefaultProgramsPrivImpl() ) );
    }

    bool ClContext::doInitDefaultKernels()
    {
        return ( ( ClContextBase::doInitDefaultKernels() ) &&
                 ( this->doInitDefaultKernelsPrivImpl() ) );
    }

    bool ClContext::doInitDefaultProgramsPrivImpl()
    {
        bool success = false;

        std::string path_to_track_kernel_program( NS(PATH_TO_BASE_DIR) );
        path_to_track_kernel_program += "sixtracklib/opencl/kernels/";
        path_to_track_kernel_program +=
             "track_particles_priv_particles_optimized_kernel.cl";

        std::string track_compile_options = "-D_GPUCODE=1";
        track_compile_options += " -DSIXTRL_BUFFER_ARGPTR_DEC=__private";
        track_compile_options += " -DSIXTRL_BUFFER_DATAPTR_DEC=__global";
        track_compile_options += " -DSIXTRL_PARTICLE_ARGPTR_DEC=__private";
        track_compile_options += " -DSIXTRL_PARTICLE_DATAPTR_DEC=__private";
        #if !defined( SIXTRL_DISABLE_BEAM_BEAM )
        track_compile_options += " -DSIXTRL_DISABLE_BEAM_BEAM=1";
        #endif /* !defined( SIXTRL_DISABLE_BEAM_BEAM ) */
        track_compile_options += " -I";
        track_compile_options += NS(PATH_TO_SIXTRL_INCLUDE_DIR);

        program_id_t const track_program_id = this->addProgramFile(
            path_to_track_kernel_program, track_compile_options );

        if( track_program_id >= program_id_t{ 0 } )
        {
            this->m_tracking_program_id = track_program_id;
            success = true;
        }

        return success;
    }

    bool ClContext::doInitDefaultKernelsPrivImpl()
    {
        bool success = false;

        if( this->hasSelectedNode() )
        {
            if( ( this->m_tracking_program_id >= program_id_t{ 0 } ) &&
                ( static_cast< size_type >( this->m_tracking_program_id ) <
                  this->numAvailablePrograms() ) )
            {
                std::string kernel_name( SIXTRL_C99_NAMESPACE_PREFIX_STR );
                kernel_name += "Track_particles_beam_elements_"
                               "priv_particles_optimized_opencl";

                kernel_id_t const tracking_kernel_id = this->enableKernel(
                    kernel_name.c_str(), this->m_tracking_program_id );

                if( tracking_kernel_id >= kernel_id_t{ 0 } )
                {
                    success = this->setTrackingKernelId( tracking_kernel_id );
                }
            }
        }

        return success;
    }
}

#endif /* defined( __cplusplus ) */

/* ========================================================================= */

SIXTRL_HOST_FN NS(ClContext)* NS(ClContext_create)()
{
    return new SIXTRL_CXX_NAMESPACE::ClContext;
}

SIXTRL_HOST_FN NS(ClContext)* NS(ClContext_new)( const char* node_id_str )
{
    return new SIXTRL_CXX_NAMESPACE::ClContext( node_id_str );
}

SIXTRL_HOST_FN void NS(ClContext_delete)( NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    delete ctx;
}

SIXTRL_HOST_FN void NS(ClContext_clear)( NS(ClContext)* SIXTRL_RESTRICT ctx )
{
    if( ctx != nullptr ) ctx->clear();
    return;
}

SIXTRL_HOST_FN bool NS(ClContext_has_tracking_kernel)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->hasTrackingKernel() : false;
}


SIXTRL_HOST_FN int NS(ClContext_get_tracking_kernel_id)(
    const NS(ClContext) *const SIXTRL_RESTRICT ctx )
{
    return ( ctx != nullptr ) ? ctx->trackingKernelId() : -1;
}

SIXTRL_HOST_FN bool NS(ClContext_set_tracking_kernel_id)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const tracking_kernel_id )
{
    return ( ctx != nullptr )
        ? ctx->setTrackingKernelId( tracking_kernel_id ) : false;
}

/* ------------------------------------------------------------------------- */

SIXTRL_HOST_FN int NS(ClContext_track)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg )
{
    return ( ( ctx != nullptr ) && ( particles_arg != nullptr ) &&
             ( beam_elements_arg != nullptr ) )
        ? ctx->track( *particles_arg, *beam_elements_arg )
        : -1;
}

SIXTRL_HOST_FN int NS(ClContext_track_num_turns)(
    NS(ClContext)* SIXTRL_RESTRICT ctx,
    NS(ClArgument)* SIXTRL_RESTRICT particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg,
    NS(context_num_turns_t) const num_turns )
{
    return ( ( ctx != nullptr ) && ( particles_arg != nullptr ) &&
             ( beam_elements_arg != nullptr ) )
        ? ctx->track( *particles_arg, *beam_elements_arg, num_turns )
        : -1;
}

SIXTRL_HOST_FN int NS(ClContext_execute_tracking_kernel)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(ClArgument)* SIXTRL_RESTRICT particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg )
{
    return ( ( ctx != nullptr ) && ( particles_arg != nullptr ) &&
             ( beam_elements_arg != nullptr ) )
        ? ctx->track( kernel_id, *particles_arg, *beam_elements_arg )
        : -1;
}

SIXTRL_HOST_FN int NS(ClContext_execute_tracking_kernel_num_turns)(
    NS(ClContext)* SIXTRL_RESTRICT ctx, int const kernel_id,
    NS(ClArgument)* SIXTRL_RESTRICT particles_arg,
    NS(ClArgument)* SIXTRL_RESTRICT beam_elements_arg,
    NS(context_num_turns_t) const num_turns )
{
    return ( ( ctx != nullptr ) && ( particles_arg != nullptr ) &&
             ( beam_elements_arg != nullptr ) )
        ? ctx->track( kernel_id, *particles_arg, *beam_elements_arg, num_turns )
        : -1;
}

#endif /* !defined( __CUDACC__ ) */

/* end: sixtracklib/opencl/internal/context.cpp */
