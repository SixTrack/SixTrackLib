#ifndef SIXTRACKLIB_TESTS_TESTLIB_COMMON_TRACK_TRACK_JOB_SETUP_CXX_HPP__
#define SIXTRACKLIB_TESTS_TESTLIB_COMMON_TRACK_TRACK_JOB_SETUP_CXX_HPP__

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/track/track_job_base.hpp"
#include "sixtracklib/common/track/track_job_ctrl_arg_base.hpp"
#include "sixtracklib/common/track/track_job_nodectrl_arg_base.hpp"

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        bool TestTrackJob_setup_no_required_output(
            SIXTRL_CXX_NAMESPACE::TrackJobBaseNew& SIXTRL_RESTRICT_REF track_job,
            SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF pbuffer,
            SIXTRL_CXX_NAMESPACE::Buffer::size_type const num_psets,
            SIXTRL_CXX_NAMESPACE::Buffer::size_type const*
                SIXTRL_RESTRICT pset_indices_begin,
            SIXTRL_CXX_NAMESPACE::Buffer const& SIXTRL_RESTRICT_REF belem_buffer,
            SIXTRL_CXX_NAMESPACE::Buffer* SIXTRL_RESTRICT ptr_output_buffer );
    }
}

#endif /* SIXTRACKLIB_TESTS_TESTLIB_COMMON_TRACK_TRACK_JOB_SETUP_CXX_HPP__ */

/* end: tests/sixtracklib/testlib/common/track/track_job_setup.hpp */
