#include "sixtracklib/common/impl/track_single.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "sixtracklib/common/single_particle.h"
#include "sixtracklib/common/restrict.h"

/* -------------------------------------------------------------------------- */

extern int Drift_track_single( 
    struct SingleParticle* SIXTRL_RESTRICT particles, double length );

extern int DriftExact_track_single(
    struct SingleParticle* SIXTRL_RESTRICT particles, double length );

/* -------------------------------------------------------------------------- */

int Drift_track_single(
    struct SingleParticle* SIXTRL_RESTRICT p, double length )
{
    double const rpp = p->rpp;
    double const px  = p->px * rpp;
    double const py  = p->py * rpp;
    
    p->x     += px * length;
    p->y     += py * length;
    p->sigma += length * (1.0 - p->rvv * ( 1.0 + ( px * px + py * py ) / 2.0 ));
    p->s     += length;
    
    return 1;
}

int DriftExact_track_single(
    struct SingleParticle* SIXTRL_RESTRICT particle, double length )
{
    double const  opd  = 1.0 + particle->delta;
    double        px   = particle->px;
    double        py   = particle->py;
    double const lpzi  = length / sqrt( opd * opd - px * px - py * py );
    double const beta0 = particle->beta0;
    double const lbzi  = ( beta0 * beta0 * particle->psigma + 1.0 ) * lpzi;
    
    particle->x     += px * lpzi;
    particle->y     += py * lpzi;
    particle->sigma += length - lbzi;
    particle->s     += length;
    
    return 1;
}

/* -------------------------------------------------------------------------- */

/* end: sixtracklib/common/details/track_single.c */
