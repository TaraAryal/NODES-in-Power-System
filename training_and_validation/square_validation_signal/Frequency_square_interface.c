/*
Filename:       Frequency_square_interface.c
Written by:     Niranjan Bhujel
Date:           Nov-15-2023 12:03:55
*/

#include <stdio.h>
#include "sim_code/Frequency_square.h"
#include "Frequency_square_interface.h"


EXPORT void initialize(real_T *inputpower1, real_T *deltaomega, real_T *deltaomegadot)
{
    // freopen (NULL_DEVICE, "w", stdout);
    
    Frequency_square_initialize();
    Frequency_square_output();
    
    inputpower1[0] = Frequency_square_Y.inputpower1;
    deltaomega[0] = Frequency_square_Y.deltaomega;
    deltaomegadot[0] = Frequency_square_Y.deltaomegadot;
}

EXPORT void one_step(real_T *inputpower1, real_T *deltaomega, real_T *deltaomegadot)
{
    // freopen (NULL_DEVICE, "w", stdout);
    
    Frequency_square_update();
    Frequency_square_output();
    
    inputpower1[0] = Frequency_square_Y.inputpower1;
    
    deltaomega[0] = Frequency_square_Y.deltaomega;
    
    deltaomegadot[0] = Frequency_square_Y.deltaomegadot;
    
}

EXPORT void terminate()
{
    Frequency_square_terminate();
}