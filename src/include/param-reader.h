/*
 *    Copyright (c) 2012 maximilian attems <attems@fias.uni-frankfurt.de>
 *    GNU General Public License (GPLv3)
 */
#ifndef SRC_INCLUDE_PARAM_READER_H_
#define SRC_INCLUDE_PARAM_READER_H_

/* forward declaration */
class Box;
class Laboratory;

extern const char *sep;

/* read params file parameters */
void process_params(Box *box, Laboratory *parameters, char *paramfile);

#endif  // SRC_INCLUDE_PARAM_READER_H_
