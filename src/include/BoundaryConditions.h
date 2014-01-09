/*
 *
 *    Copyright (c) 2013-2014
 *      Hannah Petersen <petersen@fias.uni-frankfurt.de>
 *      
 *    GNU General Public License (GPLv3)
 *
 */
 
 
#ifndef BOUNDARYCONDITIONS_H
#define BOUNDARYCONDITIONS_H

#include <iostream>
#include <stdint.h>
#include <cmath>
#include <list>
#include "../include/Parameters.h"
#include "../include/Particles.h"

/* forward declartions */
class Particles;
class CrossSections;

class BoundaryConditions
{
public:
 /* default constructor with probable values */
   BoundaryConditions(): steps(10000), output_interval(100), testparticles(1),
   eps(0.001f), cross_section(10.0f), seed(1), energy_initial(0.0f) {}
    /* special funtion should be called by specific subclass */
    virtual void assign_params(std::list<Parameters> *configuration);
    virtual void print_startup();
    virtual void initial_conditions(Particles *p __attribute__((unused))) { return; }
    virtual float energy_total(Particles *particles);
    virtual int prepare_evolution(Particles *particles);
    virtual void check_collision_geometry(Particles *particles, CrossSections *cross_sections, std::list<int> *collision_list, size_t *rejection_conflict);
    virtual void propagate(Particles *particles);
    virtual FourVector boundary_condition(FourVector position, bool *boundary_hit);
    
 public:
    /* number of steps */
    int steps;
    /* number of steps before giving measurables */
    int output_interval;
    /* number of test particle */
    int testparticles;
    /* temporal time step */
    float eps;
    /* cross section of the elastic scattering */
    float cross_section;
    /* initial seed for random generator */
    int64_t seed;
    /* initial total energy of the system */
    float energy_initial;
    
    
 };



#endif // BOUNDARYCONDITIONS_H
