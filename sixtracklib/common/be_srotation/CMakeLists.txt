set( SIXTRACKLIB_COMMON_BE_SROTATION_C99_HEADERS
     be_srotation.h
)

set( SIXTRACKLIB_COMMON_BE_SROTATION_CXX_HEADERS
     be_srotation.hpp
)

add_library( sixtrack_common_be_srotation INTERFACE
             ${SIXTRACKLIB_COMMON_BE_SROTATION_C99_HEADERS}
             ${SIXTRACKLIB_COMMON_BE_SROTATION_CXX_HEADERS}
)

set(  SIXTRACKL_LIBRARY_INTERFACE_SUBLIBRARIES
    ${SIXTRACKL_LIBRARY_INTERFACE_SUBLIBRARIES}
    sixtrack_common_be_srotation
    PARENT_SCOPE
)

# ----------------------------------------------------------------------------
# install :

set( SIXTRACKLIB_COMMON_BE_SROTATION_INSTALL_PATH
     include/sixtracklib/common/be_srotation )

install( FILES ${SIXTRACKLIB_COMMON_BE_SROTATION_C99_HEADERS}
         DESTINATION ${SIXTRACKLIB_COMMON_BE_SROTATION_INSTALL_PATH} )

install( FILES ${SIXTRACKLIB_COMMON_BE_SROTATION_CXX_HEADERS}
         DESTINATION ${SIXTRACKLIB_COMMON_BE_SROTATION_INSTALL_PATH} )

#end: sixtracklib/common/be_srotation/CMakeLists.txt