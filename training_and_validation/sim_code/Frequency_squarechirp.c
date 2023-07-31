/*
 * Frequency_squarechirp.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Frequency_squarechirp".
 *
 * Model version              : 1.29
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Mon Jul 31 12:14:46 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Frequency_squarechirp.h"
#include "Frequency_squarechirp_private.h"

/* Block signals (default storage) */
B_Frequency_squarechirp_T Frequency_squarechirp_B;

/* Continuous states */
X_Frequency_squarechirp_T Frequency_squarechirp_X;

/* Block states (default storage) */
DW_Frequency_squarechirp_T Frequency_squarechirp_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Frequency_squarechirp_T Frequency_squarechirp_Y;

/* Real-time model */
static RT_MODEL_Frequency_squarechirp_T Frequency_squarechirp_M_;
RT_MODEL_Frequency_squarechirp_T *const Frequency_squarechirp_M =
  &Frequency_squarechirp_M_;

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Frequency_squarechirp_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  Frequency_squarechirp_output();
  Frequency_squarechirp_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  Frequency_squarechirp_output();
  Frequency_squarechirp_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  Frequency_squarechirp_output();
  Frequency_squarechirp_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void Frequency_squarechirp_output(void)
{
  if (rtmIsMajorTimeStep(Frequency_squarechirp_M)) {
    /* set solver stop time */
    if (!(Frequency_squarechirp_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Frequency_squarechirp_M->solverInfo,
                            ((Frequency_squarechirp_M->Timing.clockTickH0 + 1) *
        Frequency_squarechirp_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Frequency_squarechirp_M->solverInfo,
                            ((Frequency_squarechirp_M->Timing.clockTick0 + 1) *
        Frequency_squarechirp_M->Timing.stepSize0 +
        Frequency_squarechirp_M->Timing.clockTickH0 *
        Frequency_squarechirp_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Frequency_squarechirp_M)) {
    Frequency_squarechirp_M->Timing.t[0] = rtsiGetT
      (&Frequency_squarechirp_M->solverInfo);
  }

  /* Integrator: '<Root>/deltaomega 1' */
  Frequency_squarechirp_B.deltaomega1 =
    Frequency_squarechirp_X.deltaomega1_CSTATE;

  /* Outport: '<Root>/deltaomega' */
  Frequency_squarechirp_Y.deltaomega = Frequency_squarechirp_B.deltaomega1;

  /* Integrator: '<Root>/Original w' */
  Frequency_squarechirp_B.Originalw = Frequency_squarechirp_X.Originalw_CSTATE;

  /* Outport: '<Root>/deltaomegadot' */
  Frequency_squarechirp_Y.deltaomegadot = Frequency_squarechirp_B.Originalw;
  if (rtmIsMajorTimeStep(Frequency_squarechirp_M)) {
    /* Outport: '<Root>/inputpower1' incorporates:
     *  Delay: '<Root>/Delay'
     */
    Frequency_squarechirp_Y.inputpower1 = Frequency_squarechirp_DW.Delay_DSTATE
      [0];

    /* DiscretePulseGenerator: '<Root>/Pulse Generator1' */
    Frequency_squarechirp_B.PulseGenerator1 =
      (Frequency_squarechirp_DW.clockTickCounter <
       Frequency_squarechirp_P.PulseGenerator1_Duty) &&
      (Frequency_squarechirp_DW.clockTickCounter >= 0) ?
      Frequency_squarechirp_P.PulseGenerator1_Amp : 0.0;

    /* DiscretePulseGenerator: '<Root>/Pulse Generator1' */
    if (Frequency_squarechirp_DW.clockTickCounter >=
        Frequency_squarechirp_P.PulseGenerator1_Period - 1.0) {
      Frequency_squarechirp_DW.clockTickCounter = 0;
    } else {
      Frequency_squarechirp_DW.clockTickCounter++;
    }
  }

  /* MATLAB Function: '<Root>/State Space Equation1' incorporates:
   *  Outport: '<Root>/inputpower1'
   *  SignalConversion generated from: '<S1>/ SFunction '
   */
  Frequency_squarechirp_B.dotx[0] = Frequency_squarechirp_B.Originalw;
  Frequency_squarechirp_B.dotx[1] = (-33.358333333333327 *
    Frequency_squarechirp_B.deltaomega1 - 5.005 *
    Frequency_squarechirp_B.Originalw) - 1.6666666666666665 *
    Frequency_squarechirp_Y.inputpower1;
}

/* Model update function */
void Frequency_squarechirp_update(void)
{
  int_T idxDelay;
  if (rtmIsMajorTimeStep(Frequency_squarechirp_M)) {
    /* Update for Delay: '<Root>/Delay' */
    for (idxDelay = 0; idxDelay < 249; idxDelay++) {
      Frequency_squarechirp_DW.Delay_DSTATE[idxDelay] =
        Frequency_squarechirp_DW.Delay_DSTATE[idxDelay + 1];
    }

    Frequency_squarechirp_DW.Delay_DSTATE[249] =
      Frequency_squarechirp_B.PulseGenerator1;

    /* End of Update for Delay: '<Root>/Delay' */
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(Frequency_squarechirp_M)!=-1) &&
        !((rtmGetTFinal(Frequency_squarechirp_M)-
           (((Frequency_squarechirp_M->Timing.clockTick1+
              Frequency_squarechirp_M->Timing.clockTickH1* 4294967296.0)) * 0.02))
          > (((Frequency_squarechirp_M->Timing.clockTick1+
               Frequency_squarechirp_M->Timing.clockTickH1* 4294967296.0)) *
             0.02) * (DBL_EPSILON))) {
      rtmSetErrorStatus(Frequency_squarechirp_M, "Simulation finished");
    }
  }

  if (rtmIsMajorTimeStep(Frequency_squarechirp_M)) {
    rt_ertODEUpdateContinuousStates(&Frequency_squarechirp_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Frequency_squarechirp_M->Timing.clockTick0)) {
    ++Frequency_squarechirp_M->Timing.clockTickH0;
  }

  Frequency_squarechirp_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Frequency_squarechirp_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.02s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.02, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    Frequency_squarechirp_M->Timing.clockTick1++;
    if (!Frequency_squarechirp_M->Timing.clockTick1) {
      Frequency_squarechirp_M->Timing.clockTickH1++;
    }
  }
}

/* Derivatives for root system: '<Root>' */
void Frequency_squarechirp_derivatives(void)
{
  XDot_Frequency_squarechirp_T *_rtXdot;
  _rtXdot = ((XDot_Frequency_squarechirp_T *) Frequency_squarechirp_M->derivs);

  /* Derivatives for Integrator: '<Root>/deltaomega 1' */
  _rtXdot->deltaomega1_CSTATE = Frequency_squarechirp_B.dotx[0];

  /* Derivatives for Integrator: '<Root>/Original w' */
  _rtXdot->Originalw_CSTATE = Frequency_squarechirp_B.dotx[1];
}

/* Model initialize function */
void Frequency_squarechirp_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Frequency_squarechirp_M, 0,
                sizeof(RT_MODEL_Frequency_squarechirp_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Frequency_squarechirp_M->solverInfo,
                          &Frequency_squarechirp_M->Timing.simTimeStep);
    rtsiSetTPtr(&Frequency_squarechirp_M->solverInfo, &rtmGetTPtr
                (Frequency_squarechirp_M));
    rtsiSetStepSizePtr(&Frequency_squarechirp_M->solverInfo,
                       &Frequency_squarechirp_M->Timing.stepSize0);
    rtsiSetdXPtr(&Frequency_squarechirp_M->solverInfo,
                 &Frequency_squarechirp_M->derivs);
    rtsiSetContStatesPtr(&Frequency_squarechirp_M->solverInfo, (real_T **)
                         &Frequency_squarechirp_M->contStates);
    rtsiSetNumContStatesPtr(&Frequency_squarechirp_M->solverInfo,
      &Frequency_squarechirp_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Frequency_squarechirp_M->solverInfo,
      &Frequency_squarechirp_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Frequency_squarechirp_M->solverInfo,
      &Frequency_squarechirp_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Frequency_squarechirp_M->solverInfo,
      &Frequency_squarechirp_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Frequency_squarechirp_M->solverInfo,
                          (&rtmGetErrorStatus(Frequency_squarechirp_M)));
    rtsiSetRTModelPtr(&Frequency_squarechirp_M->solverInfo,
                      Frequency_squarechirp_M);
  }

  rtsiSetSimTimeStep(&Frequency_squarechirp_M->solverInfo, MAJOR_TIME_STEP);
  Frequency_squarechirp_M->intgData.y = Frequency_squarechirp_M->odeY;
  Frequency_squarechirp_M->intgData.f[0] = Frequency_squarechirp_M->odeF[0];
  Frequency_squarechirp_M->intgData.f[1] = Frequency_squarechirp_M->odeF[1];
  Frequency_squarechirp_M->intgData.f[2] = Frequency_squarechirp_M->odeF[2];
  Frequency_squarechirp_M->intgData.f[3] = Frequency_squarechirp_M->odeF[3];
  Frequency_squarechirp_M->contStates = ((X_Frequency_squarechirp_T *)
    &Frequency_squarechirp_X);
  rtsiSetSolverData(&Frequency_squarechirp_M->solverInfo, (void *)
                    &Frequency_squarechirp_M->intgData);
  rtsiSetSolverName(&Frequency_squarechirp_M->solverInfo,"ode4");
  rtmSetTPtr(Frequency_squarechirp_M, &Frequency_squarechirp_M->Timing.tArray[0]);
  rtmSetTFinal(Frequency_squarechirp_M, 310.0);
  Frequency_squarechirp_M->Timing.stepSize0 = 0.02;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    Frequency_squarechirp_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Frequency_squarechirp_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Frequency_squarechirp_M->rtwLogInfo, (NULL));
    rtliSetLogT(Frequency_squarechirp_M->rtwLogInfo, "tout");
    rtliSetLogX(Frequency_squarechirp_M->rtwLogInfo, "");
    rtliSetLogXFinal(Frequency_squarechirp_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Frequency_squarechirp_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Frequency_squarechirp_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Frequency_squarechirp_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Frequency_squarechirp_M->rtwLogInfo, 1);
    rtliSetLogY(Frequency_squarechirp_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Frequency_squarechirp_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Frequency_squarechirp_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Frequency_squarechirp_B), 0,
                sizeof(B_Frequency_squarechirp_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Frequency_squarechirp_X, 0,
                  sizeof(X_Frequency_squarechirp_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Frequency_squarechirp_DW, 0,
                sizeof(DW_Frequency_squarechirp_T));

  /* external outputs */
  (void)memset(&Frequency_squarechirp_Y, 0, sizeof(ExtY_Frequency_squarechirp_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Frequency_squarechirp_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Frequency_squarechirp_M),
    Frequency_squarechirp_M->Timing.stepSize0, (&rtmGetErrorStatus
    (Frequency_squarechirp_M)));

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator1' */
  Frequency_squarechirp_DW.clockTickCounter = 0;

  {
    int32_T i;

    /* InitializeConditions for Delay: '<Root>/Delay' */
    for (i = 0; i < 250; i++) {
      Frequency_squarechirp_DW.Delay_DSTATE[i] =
        Frequency_squarechirp_P.Delay_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<Root>/Delay' */

    /* InitializeConditions for Integrator: '<Root>/deltaomega 1' */
    Frequency_squarechirp_X.deltaomega1_CSTATE =
      Frequency_squarechirp_P.deltaomega1_IC;

    /* InitializeConditions for Integrator: '<Root>/Original w' */
    Frequency_squarechirp_X.Originalw_CSTATE =
      Frequency_squarechirp_P.Originalw_IC;
  }
}

/* Model terminate function */
void Frequency_squarechirp_terminate(void)
{
  /* (no terminate code required) */
}
