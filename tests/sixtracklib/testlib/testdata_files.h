#ifndef SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TESTDATA_FILES_H__
#define SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TESTDATA_FILES_H__

#if !defined( _GPUCODE )

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

#include "sixtracklib/_impl/definitions.h"

/* ************************************************************************ */
/* ****                                                                **** */
/* ****        Tabulated values for mathematically functions           **** */
/* ****                                                                **** */
/* ************************************************************************ */

static char const NS(PATH_TO_TEST_FADDEEVA_ERRFN_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_faddeeva_errorfn_data.bin";


/* ************************************************************************ */
/* ****                                                                **** */
/* ****        Randomly Generated Tracking Test-Data Files             **** */
/* ****                                                                **** */
/* ************************************************************************ */

static char const NS(PATH_TO_TEST_TRACKING_STAMP_FILE)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_tracking.generated";

static char const NS(PATH_TO_TEST_TRACKING_DRIFT_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_tracking_drift_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_DRIFT_EXACT_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_tracking_drift_exact_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_MULTIPOLE_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_tracking_multipole_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_BEAM_BEAM_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_tracking_beam_beam_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_CAVITY_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_tracking_cavity_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_ALIGN_DATA)[] =
    "/home/martin/git/sixtracklib/tests/testdata/test_tracking_align_data.bin";

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_TESTS_SIXTRACKLIB_TESTLIB_TESTDATA_FILES_H__ */

/* end: tests/sixtracklib/testlib/testdata_files.h */
