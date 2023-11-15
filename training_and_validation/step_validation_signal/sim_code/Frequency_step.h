/*
* Frequency_step.h
*
* Academic License - for use in teaching, academic research, and meeting
* course requirements at degree granting institutions only.  Not for
* government, commercial, or other organizational use.
*
* Code generation for model "Frequency_step".
*
* Model version              : 1.31
* Simulink Coder version : 9.6 (R2021b) 14-May-2021
* C source code generated on : Wed Nov 15 12:05:13 2023
*
* Target selection: grt.tlc
* Note: GRT includes extra infrastructure and instrumentation for prototyping
* Embedded hardware selection: Intel->x86-64 (Windows64)
* Code generation objectives: Unspecified
* Validation result: Not run
*/

#ifndef RTW_HEADER_Frequency_step_h_
#define RTW_HEADER_Frequency_step_h_
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef Frequency_step_COMMON_INCLUDES_
#define Frequency_step_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* Frequency_step_COMMON_INCLUDES_ */

#include "Frequency_step_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
real_T deltaomega1;                  /* '<Root>/deltaomega 1' */
real_T Originalw;                    /* '<Root>/Original w' */
real_T Step;                         /* '<Root>/Step' */
real_T dotx[2];                      /* '<Root>/State Space Equation1' */
} B_Frequency_step_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
real_T Delay_DSTATE[250];            /* '<Root>/Delay' */
} DW_Frequency_step_T;

/* Continuous states (default storage) */
typedef struct {
real_T deltaomega1_CSTATE;           /* '<Root>/deltaomega 1' */
real_T Originalw_CSTATE;             /* '<Root>/Original w' */
} X_Frequency_step_T;

/* State derivatives (default storage) */
typedef struct {
real_T deltaomega1_CSTATE;           /* '<Root>/deltaomega 1' */
real_T Originalw_CSTATE;             /* '<Root>/Original w' */
} XDot_Frequency_step_T;

/* State disabled  */
typedef struct {
boolean_T deltaomega1_CSTATE;        /* '<Root>/deltaomega 1' */
boolean_T Originalw_CSTATE;          /* '<Root>/Original w' */
} XDis_Frequency_step_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
real_T *y;                           /* output */
real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
real_T inputpower1;                  /* '<Root>/inputpower1' */
real_T deltaomega;                   /* '<Root>/deltaomega' */
real_T deltaomegadot;                /* '<Root>/deltaomegadot' */
} ExtY_Frequency_step_T;

/* Parameters (default storage) */
struct P_Frequency_step_T_ {
real_T Delay_InitialCondition;       /* Expression: 0.0
* Referenced by: '<Root>/Delay'
*/
real_T deltaomega1_IC;               /* Expression: 0
* Referenced by: '<Root>/deltaomega 1'
*/
real_T Originalw_IC;                 /* Expression: 0
* Referenced by: '<Root>/Original w'
*/
real_T Step_Time;                    /* Expression: 20
* Referenced by: '<Root>/Step'
*/
real_T Step_Y0;                      /* Expression: 0
* Referenced by: '<Root>/Step'
*/
real_T Step_YFinal;                  /* Expression: 0.2
* Referenced by: '<Root>/Step'
*/
};

/* Real-time Model Data Structure */
struct tag_RTM_Frequency_step_T {
const char_T *errorStatus;
RTWLogInfo *rtwLogInfo;
RTWSolverInfo solverInfo;
X_Frequency_step_T *contStates;
int_T *periodicContStateIndices;
real_T *periodicContStateRanges;
real_T *derivs;
boolean_T *contStateDisabled;
boolean_T zCCacheNeedsReset;
boolean_T derivCacheNeedsReset;
boolean_T CTOutputIncnstWithState;
real_T odeY[2];
real_T odeF[4][2];
ODE4_IntgData intgData;

/*
* Sizes:
* The following substructure contains sizes information
* for many of the model attributes such as inputs, outputs,
* dwork, sample times, etc.
*/
struct {
int_T numContStates;
int_T numPeriodicContStates;
int_T numSampTimes;
} Sizes;

/*
* Timing:
* The following substructure contains information regarding
* the timing information for the model.
*/
struct {
uint32_T clockTick0;
uint32_T clockTickH0;
time_T stepSize0;
uint32_T clockTick1;
uint32_T clockTickH1;
time_T tFinal;
SimTimeStep simTimeStep;
boolean_T stopRequestedFlag;
time_T *t;
time_T tArray[2];
} Timing;
};

/* Block parameters (default storage) */
extern P_Frequency_step_T Frequency_step_P;

/* Block signals (default storage) */
extern B_Frequency_step_T Frequency_step_B;

/* Continuous states (default storage) */
extern X_Frequency_step_T Frequency_step_X;

/* Block states (default storage) */
extern DW_Frequency_step_T Frequency_step_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Frequency_step_T Frequency_step_Y;

/* Model entry point functions */
extern void Frequency_step_initialize(void);
extern void Frequency_step_output(void);
extern void Frequency_step_update(void);
extern void Frequency_step_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Frequency_step_T *const Frequency_step_M;

/*-
* The generated code includes comments that allow you to trace directly
* back to the appropriate location in the model.  The basic format
* is <system>/block_name, where system is the system number (uniquely
* assigned by Simulink) and block_name is the name of the block.
*
* Use the MATLAB hilite_system command to trace the generated code back
* to the model.  For example,
*
* hilite_system('<S3>')    - opens system 3
* hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
*
* Here is the system hierarchy for this model
*
* '<Root>' : 'Frequency_step'
* '<S1>'   : 'Frequency_step/State Space Equation1'
*/
#endif                                 /* RTW_HEADER_Frequency_step_h_ */