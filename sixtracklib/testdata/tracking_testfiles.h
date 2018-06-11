#ifndef SIXTRACKLIB_TESTDATA_TRACKING_TESTFILES_H__
#define SIXTRACKLIB_TESTDATA_TRACKING_TESTFILES_H__

#if !defined( _GPUCODE )

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

#include "sixtracklib/_impl/definitions.h"

static char const NS(PATH_TO_TEST_TRACKING_DRIFT_DATA)[] = 
    "/home/martin/git/sixtracklib/build/testdata/test_tracking_drift_data.bin";

static char const NS(PATH_TO_TEST_TRACKING_DRIFT_EXACT_DATA)[] = 
    "/home/martin/git/sixtracklib/build/testdata/test_tracking_drift_exact_data.bin";
    
static char const NS(PATH_TO_TEST_TRACKING_MULTIPOLE_DATA)[] = 
    "/home/martin/git/sixtracklib/build/testdata/test_tracking_multipole_data.bin";
    
#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#endif /* !defined( _GPUCODE ) */

#endif /* SIXTRACKLIB_TESTDATA_TRACKING_TESTFILES_H__ */

/* end: sixtracklib/testdata/tracking_testfiles.h */
