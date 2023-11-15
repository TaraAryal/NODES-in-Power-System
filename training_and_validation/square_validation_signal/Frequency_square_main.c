/*
Filename:       Frequency_square_main.c
Written by:     Niranjan Bhujel
Date:           Nov-15-2023 12:03:55
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Frequency_square_interface.h"
// other includes below here

#define STEP_TIME 0.02

int main(int argc, char const *argv[])
{
    double STOP_TIME;

    if (argc==1)
    {
        printf("Stop time not specified.\n");
        return 1;
    }
    else
    {
        STOP_TIME = atof(argv[1]);
    }
    
    clock_t START_CPUTIME, STOP_CPUTIME;

    // Input variables
    
    // Output variables
    real_T inputpower1[1];
    real_T deltaomega[1];
    real_T deltaomegadot[1];
    

    START_CPUTIME = clock();

    // Some variables to keep track of simulation progress
    int _t_INDEX_=0, _t_INDEX_PREV_=0, _t_INDEX_MAX=(int) (STOP_TIME/STEP_TIME);


    // Assign input values to the input variables

    // Call to initialize function
    initialize( inputpower1, deltaomega, deltaomegadot);

    while (_t_INDEX_*STEP_TIME < STOP_TIME)
    {
        // Assign input values to the input variables

        
        // Run one time-step
        one_step( inputpower1, deltaomega, deltaomegadot);
        _t_INDEX_++;
    
        if ((double)(_t_INDEX_ - _t_INDEX_PREV_)/_t_INDEX_MAX*100 >= 5)
        {
            STOP_CPUTIME = clock();
            printf("%.f %% complete. Total time elapsed: %f !!!\n", (double)_t_INDEX_/_t_INDEX_MAX*100, (double) (STOP_CPUTIME - START_CPUTIME) / CLOCKS_PER_SEC);
            _t_INDEX_PREV_ = _t_INDEX_;
        }
    }
    
    terminate();
    
    return 0;
}