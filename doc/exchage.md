# Tracking Data Exchange Conventions

## Particles

Particle coordinates are given in right handed local reference frame with the axis referred named (`X`,`Y`,`S`) where the largest projection of the momentum is in `S`. Dimensions are in SI except for energy in GeV and momentum GeV/c.

Coordinates quantities

* partid: 
* turn: 
* state:
* elemid:
* s:
* x:
* px:
* y:
* py:
* tau: s/beta0 - ct
* sigma: s  - beta0 c t 
* m0, P0, E0, gamma0, beta0
* m/m0
* q/q0

Particles data is exchanged a dictionary where quantities can be scalars or vectors of the same shape

# Elements

Elements exchanged in the following format:
  `<name type arguments>`

Elemement lists are exchanged with
  `[ name | (label,name) ] ....`

where the second form uses label for lookup and name for physical properties.


Elements types are:

* drift: l[m]
* driftexact: l[m]
* multipole: knl[m^-n] ksl[m^-n] l hxl hyl
* cavity: volt[V] freq[Hz] lag[degree]
* align: dx[V] dy[Hz] angle[degree]



