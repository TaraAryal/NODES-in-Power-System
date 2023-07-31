/*
Filename:       Frequency_squarechirp_interface.c
Written by:     Niranjan Bhujel
Date:           2023-07-31
*/


#include <stdio.h>
#include "sim_code/Frequency_squarechirp.h"
#include "Frequency_squarechirp_interface.h"

#if defined(_WIN32) || defined(_WIN64)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__linux__)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif

EXPORT void initialize(double *inputpower1, double *deltaomega, double *deltaomegadot)
{
    // freopen ("nul", "w", stdout);
    
    Frequency_squarechirp_initialize();
    Frequency_squarechirp_output();
    
    inputpower1[0] = Frequency_squarechirp_Y.inputpower1;
    deltaomega[0] = Frequency_squarechirp_Y.deltaomega;
    deltaomegadot[0] = Frequency_squarechirp_Y.deltaomegadot;
}

EXPORT void one_step(double *inputpower1, double *deltaomega, double *deltaomegadot)
{
    // freopen ("nul", "w", stdout);
    
    Frequency_squarechirp_update();
    Frequency_squarechirp_output();
    
    inputpower1[0] = Frequency_squarechirp_Y.inputpower1;
    
    deltaomega[0] = Frequency_squarechirp_Y.deltaomega;
    
    deltaomegadot[0] = Frequency_squarechirp_Y.deltaomegadot;
    
}