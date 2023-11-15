/*
Filename:       Frequency_logchirp_interface.c
Written by:     Niranjan Bhujel
Date:           Nov-15-2023 11:53:14
*/

#include <stdio.h>
#include "sim_code/Frequency_logchirp.h"
#include "Frequency_logchirp_interface.h"


EXPORT void initialize(real_T *inputpower1, real_T *deltaomega, real_T *deltaomegadot)
{
    // freopen (NULL_DEVICE, "w", stdout);
    
    Frequency_logchirp_initialize();
    Frequency_logchirp_output();
    
    inputpower1[0] = Frequency_logchirp_Y.inputpower1;
    deltaomega[0] = Frequency_logchirp_Y.deltaomega;
    deltaomegadot[0] = Frequency_logchirp_Y.deltaomegadot;
}

EXPORT void one_step(real_T *inputpower1, real_T *deltaomega, real_T *deltaomegadot)
{
    // freopen (NULL_DEVICE, "w", stdout);
    
    Frequency_logchirp_update();
    Frequency_logchirp_output();
    
    inputpower1[0] = Frequency_logchirp_Y.inputpower1;
    
    deltaomega[0] = Frequency_logchirp_Y.deltaomega;
    
    deltaomegadot[0] = Frequency_logchirp_Y.deltaomegadot;
    
}

EXPORT void terminate()
{
    Frequency_logchirp_terminate();
}