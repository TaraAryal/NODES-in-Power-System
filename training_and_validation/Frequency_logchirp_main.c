/*
Filename:       Frequency_logchirp_main.c
Written by:     Niranjan Bhujel
Date:           2023-07-31
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Frequency_logchirp_interface.h"
#define BILLION 1000000000.0

#define STEP_TIME 0.02

int main(int argc, char const *argv[])
{
    double STOP_TIME;
    int DECIMATION;

    if (argc==1)
    {
        printf("Stop time not specified.\n");
        return 1;
    }
    else if (argc > 2)
    {
        STOP_TIME = atof(argv[1]);
        DECIMATION = atoi(argv[2]);
    }
    else
    {
        STOP_TIME = atof(argv[1]);
        DECIMATION = 1;
    }

    if (STOP_TIME==-1)
    {
        printf("Stop time not specified.\n");
        return 1;
    }
    
    struct timespec START_WTIME, STOP_WTIME;

    // Input variables
    
    // Output variables
    double inputpower1[1], deltaomega[1], deltaomegadot[1];

    FILE *fpt;
    fpt = fopen("Frequency_logchirp_out.csv", "w+");
    fprintf(
        fpt, 
        "time, inputpower1[0], deltaomega[0], deltaomegadot[0]\n");

    clock_gettime(CLOCK_REALTIME, &START_WTIME);

    // Assign input values to the input variables


    // Call to initialize function
    int _t_INDEX_=0, _t_INDEX_PREV_=0, _t_INDEX_MAX=(int) (STOP_TIME/STEP_TIME);
    initialize( inputpower1, deltaomega, deltaomegadot);

    // write initial value
    fprintf(
        fpt,
        "%f, %f, %f, %f\n",
        _t_INDEX_*STEP_TIME, inputpower1[0], deltaomega[0], deltaomegadot[0]);
    
    while (_t_INDEX_*STEP_TIME < STOP_TIME)
    {
        // Assign input values to the input variables

        
        // Run one time-step
        one_step( inputpower1, deltaomega, deltaomegadot);
        _t_INDEX_++;

        if (_t_INDEX_ % DECIMATION == 0)
        {
            fprintf(
                fpt,
                "%f, %f, %f, %f\n",
                _t_INDEX_*STEP_TIME, inputpower1[0], deltaomega[0], deltaomegadot[0]);
        }
    
        if ((double)(_t_INDEX_ - _t_INDEX_PREV_)/_t_INDEX_MAX*100 >= 5)
        {
            clock_gettime(CLOCK_REALTIME, &STOP_WTIME);
            printf("%.f %% complete. Total time elapsed: %f !!!\n", (double)_t_INDEX_/_t_INDEX_MAX*100, (STOP_WTIME.tv_sec - START_WTIME.tv_sec) + (STOP_WTIME.tv_nsec - START_WTIME.tv_nsec) / BILLION);
            _t_INDEX_PREV_ = _t_INDEX_;
        }
    }
    
    fclose(fpt);
    
    return 0;
}