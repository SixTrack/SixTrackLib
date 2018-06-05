#ifndef SIXTRACKLIB_OPENCL_TRACK_PARTICLES_KERNEL_CL__
#define SIXTRACKLIB_OPENCL_TRACK_PARTICLES_KERNEL_CL__

#if defined( _GPUCODE )

void __kernel Track_particles_kernel_opencl(
    unsigned long const num_of_turns, 
    __global unsigned char* SIXTRL_RESTRICT particles_data_buffer,
    __global unsigned char* SIXTRL_RESTRICT beam_elements_data_buffer, 
    __global unsigned char* SIXTRL_RESTRICT elem_by_elem_data_buffer )
{
   size_t const global_id = get_global_id( 0 );
    
    NS(block_size_t) num_particle_blocks     = 0;
    NS(block_size_t) num_beam_elements       = 0;
    NS(block_size_t) num_elem_by_elem_blocks = 0;
    
    NS(Blocks) particles_buffer;
    NS(Blocks) beam_elements;
    NS(Blocks) elem_by_elem_buffer;
    
    NS(Particles)* particles = 0;
    
    int ret = 0;
    
    NS(Blocks_preset)( &particles_buffer );
    ret = NS(Blocks_unserialize)( &particles_buffer, particles_data_buffer );
    
    num_particle_blocks = NS(Blocks_get_num_of_blocks)( &particles_buffer );
    
    NS(Blocks_preset)( &beam_elements );
    ret |= NS(Blocks_unserialize)( &beam_elements, beam_elements_data_buffer );
    
    num_beam_elements = NS(Blocks_get_num_of_blocks)( &beam_elements );
    
    NS(Blocks_preset)( &elem_by_elem_buffer );
    
    ret |= NS(Blocks_unserialize)( 
        &elem_by_elem_buffer, elem_by_elem_data_buffer );
    
    elem_by_elem_blocks = NS(Blocks_get_num_of_blocks)( &elem_by_elem_buffer );
    
    particles = NS(Blocks_get_particles)( 
        NS(Blocks_get_const_block_infos_begin)( &particles_buffer ) );
    
    if( ( ret == 0 ) && ( num_beam_elements != 0u ) && 
        ( num_of_turns != 0 ) && ( num_particle_blocks == 1u ) &&
        ( global_id < NS(Particles_get_num_particles)( particles ) ) )
    {
        unsigned long ii = 0;
        
        if( ( elem_by_elem_blocks != 0 ) && 
            ( elem_by_elem_blocks >= ( num_of_turns * num_beam_elements ) ) )
        {
            NS(BlockInfo)* io_info_it =
                NS(Blocks_get_const_block_infos_begin)( &elem_by_elem_buffer );
            
            for( ; ii < num_of_turns ; ++ii, 
                    io_info_it = io_info_it + num_beam_elements )
            {
                ret |= NS(Track_beam_elements_particle)( 
                        particles, global_id, &beam_elements, io_info_it );
            }
        }
        else
        {
            for( ; ii < num_of_turns ; ++ii )
            {
                ret |= NS(Track_beam_elements_particle)( 
                        particles, global_id, &beam_elements, 0 );
            }
        }
    }
    
    return;
}
    
#endif /* defined( _GPUCODE ) */
    
#endif /* SIXTRACKLIB_OPENCL_TRACK_PARTICLES_KERNEL_CL__ */

/* end: sixtracklib/opencl/track_particles_kernel.cl */
