/*
 *    Copyright (c) 2012 maximilian attems <attems@fias.uni-frankfurt.de>
 *    GNU General Public License (GPLv3)
 */
#ifndef SRC_INCLUDE_PARAM_READER_H_
#define SRC_INCLUDE_PARAM_READER_H_

#include <list>

#include "../include/Parameters.h"

extern const char *sep;

/* read params file parameters */
void process_config(Parameters, char *path);

#endif  // SRC_INCLUDE_PARAM_READER_H_
