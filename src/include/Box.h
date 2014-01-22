/*
 *    Copyright (c) 2012-2014
 *      maximilian attems <attems@fias.uni-frankfurt.de>
 *      Jussi Auvinen <auvinen@fias.uni-frankfurt.de>
 *		Hannah Petersen <petersen@fias.uni-frankfurt.de>
 *    GNU General Public License (GPLv3)
 */
#ifndef SRC_INCLUDE_BOX_H_
#define SRC_INCLUDE_BOX_H_

#include <stdint.h>
#include <cmath>
#include <list>

#include "../include/CrossSections.h"
#include "../include/Modus.h"
#include "../include/Particles.h"
#include "../include/Parameters.h"


class BoxModus : public Modus {
 public:
  /* default constructor with probable values */
    BoxModus(): initial_condition_(1), length_(10.0f), temperature_(0.1f),
                number_density_initial_(0.0f) {}
    /* special class funtions */
    virtual void assign_params(std::list<Parameters> *configuration);
    virtual void print_startup();
    virtual void initial_conditions(Particles *particles);
    virtual int sanity_check(Particles *particles);
    virtual void propagate(Particles *particles);
    virtual FourVector boundary_condition(FourVector position,
                                          bool *boundary_hit);
    virtual void check_collision_geometry(Particles *particles,
                  CrossSections *cross_sections, std::list<int> *collision_list,
                  size_t *rejection_conflict);

 private:
    /* initial condition */
    int initial_condition_;
    /* Cube edge length */
    float length_;
    /* Temperature of the Boltzmann distribution for thermal initialization */
    float temperature_;
    /* initial number density of the box */
    float number_density_initial_;
};



#endif  // SRC_INCLUDE_BOX_H_
