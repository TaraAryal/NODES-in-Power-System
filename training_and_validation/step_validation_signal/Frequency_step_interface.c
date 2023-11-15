/*
Filename:       Frequency_step_interface.c
Written by:     Niranjan Bhujel
Date:           Nov-15-2023 12:05:43
*/

#include <stdio.h>
#include "sim_code/Frequency_step.h"
#include "Frequency_step_interface.h"


EXPORT void initialize(real_T *inputpower1, real_T *deltaomega, real_T *deltaomegadot)
{
    // freopen (NULL_DEVICE, "w", stdout);
    
    Frequency_step_initialize();
    Frequency_step_output();
    
    inputpower1[0] = Frequency_step_Y.inputpower1;
    deltaomega[0] = Frequency_step_Y.deltaomega;
    deltaomegadot[0] = Frequency_step_Y.deltaomegadot;
}

EXPORT void one_step(real_T *inputpower1, real_T *deltaomega, real_T *deltaomegadot)
{
    // freopen (NULL_DEVICE, "w", stdout);
    
    Frequency_step_update();
    Frequency_step_output();
    
    inputpower1[0] = Frequency_step_Y.inputpower1;
    
    deltaomega[0] = Frequency_step_Y.deltaomega;
    
    deltaomegadot[0] = Frequency_step_Y.deltaomegadot;
    
}

EXPORT void terminate()
{
    Frequency_step_terminate();
}