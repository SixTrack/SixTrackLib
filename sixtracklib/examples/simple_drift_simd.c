#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <xmmintrin.h>
#include <emmintrin.h>

#include "sixtracklib/sixtracklib.h"

int main( int argc, char* argv[] )
{
    st_block_size_t ii = 0;
    st_block_num_elements_t jj = 0;
    
    st_block_num_elements_t NUM_ELEMS     = 100;
    st_block_num_elements_t NUM_PARTICLES = 100000;
    size_t NUM_TURNS     = 100;
    
    struct timeval tstart;
    struct timeval tstop;
    
    st_ParticlesContainer particles_buffer;
    st_Particles          particles;    
    st_BeamElements       beam_elements;
    
    int ret = 0;
    
    /* first: init the pseudo random number generator for the particle
     * values randomization - choose a constant seed to have reproducible
     * results! */
    
    uint64_t seed = UINT64_C( 20180420 );
    st_Random_init_genrand64( seed );
    
    if( argc >= 1 )
    {
        printf( "\r\n\r\nUsage: %s NUM_PARTICLES  NUM_ELEMS  NUM_TURNS\r\n", argv[ 0 ] );        
    }
    
    if( argc < 2 )
    {
        printf( "run with default values .... "
                "(npart = %8lu, nelem = %8lu, nturns = %8lu)\r\n",
                NUM_PARTICLES, NUM_ELEMS, NUM_TURNS );
    }
    else if( argc >= 4 )
    {
        st_block_num_elements_t const temp_num_part = atoi( argv[ 1 ] );
        st_block_num_elements_t const temp_num_elem = atoi( argv[ 2 ] );
        size_t const temp_num_turn = atoi( argv[ 3 ] );
        
        if( temp_num_part > 0 ) NUM_PARTICLES = temp_num_part;
        if( temp_num_elem > 0 ) NUM_ELEMS     = temp_num_elem;
        if( temp_num_turn > 0 ) NUM_TURNS     = temp_num_turn;                
    }
    
    #if defined( __AVX__ )
    printf( "Info: using avx  implementation\r\n" );
    #elif defined( __SSE2__ )    
    printf( "Info: using sse2 implementation\r\n" );
    #else
    #error Undefined/illegal architecture selected for this example -> check your compiler flags
    #endif /* CPU architecture */
    
    printf( "\r\n" "starting :                   "
                "(npart = %8lu, nelem = %8lu, nturns = %8lu)\r\n",
                NUM_PARTICLES, NUM_ELEMS, NUM_TURNS );
    
    st_ParticlesContainer_preset( &particles_buffer );    
    st_ParticlesContainer_reserve_num_blocks( &particles_buffer, 1u );
    st_ParticlesContainer_reserve_for_data( &particles_buffer, 20000000u );
    
    ret = st_ParticlesContainer_add_particles( 
        &particles_buffer, &particles, NUM_PARTICLES );
    
    if( ret == 0 )
    {
        st_Particles_random_init( &particles );
    }
    else
    {
        printf( "Error initializing particles!\r\n" );
        st_ParticlesContainer_free( &particles_buffer );
        
        return 0;
    }
    
    st_BeamElements_preset( &beam_elements );
    st_BeamElements_reserve_num_blocks( &beam_elements, NUM_ELEMS );
    st_BeamElements_reserve_for_data( &beam_elements, NUM_ELEMS * sizeof( st_Drift ) );
            
    for( jj = 0 ; jj < NUM_ELEMS ; ++jj )
    {
        double LENGTH = 0.05 + 0.005 * jj;
        st_element_id_t const ELEMENT_ID = ( st_element_id_t )jj;
        
        
        st_Drift next_drift = 
            st_BeamElements_add_drift( &beam_elements, LENGTH, ELEMENT_ID );
        
        if( st_Drift_get_type_id( &next_drift ) != st_BLOCK_TYPE_DRIFT )
        {
            printf( "Error initializing drift #%lu\r\n", jj );
            break;
        }
    }
    
    /* track over a number of turns and measure the wall-time for the tracking: */
    
    gettimeofday( &tstart, 0 );
    
    for( ii = 0 ; ii < NUM_TURNS ; ++ii )
    {
        ret |= st_Track_beam_elements( &particles, 0, NUM_PARTICLES, 
                                       &beam_elements, 0, 0 );
    }
    
    gettimeofday( &tstop, 0 );
    
    double const usec_dist = 1e-6 * ( ( tstop.tv_sec >= tstart.tv_sec ) ?
        ( tstop.tv_usec - tstart.tv_usec ) : ( 1000000 - tstart.tv_usec ) );
    
    double const delta_time = ( double )( tstop.tv_sec - tstart.tv_sec ) + usec_dist;
    printf( "time elapsed    : %16.8fs \r\n", delta_time );
    printf( "time / particle : %16.8f [us/Part]\r\n", 
                ( delta_time / NUM_PARTICLES ) * 1e6 );
    
    /* cleanup: */
              
    st_ParticlesContainer_free( &particles_buffer );
    st_BeamElements_free( &beam_elements );
    
    return 0;
}

/* end:  sixtracklib/examples/simple_drift.c */
