/*
Filename:       Frequency_logchirp_interface.h
Written by:     Niranjan Bhujel
Date:           2023-07-31
*/


#ifndef Frequency_logchirp_interface_h
#define Frequency_logchirp_interface_h

#include "sim_code/Frequency_logchirp.h"

void initialize(double *inputpower1, double *deltaomega, double *deltaomegadot);

void one_step(double *inputpower1, double *deltaomega, double *deltaomegadot);

#endif