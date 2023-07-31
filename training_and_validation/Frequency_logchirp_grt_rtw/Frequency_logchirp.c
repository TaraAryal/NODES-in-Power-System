/*
 * Frequency_logchirp.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Frequency_logchirp".
 *
 * Model version              : 1.28
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Mon Jul 31 12:14:00 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Frequency_logchirp.h"
#include "Frequency_logchirp_private.h"

/* Block signals (default storage) */
B_Frequency_logchirp_T Frequency_logchirp_B;

/* Continuous states */
X_Frequency_logchirp_T Frequency_logchirp_X;

/* Block states (default storage) */
DW_Frequency_logchirp_T Frequency_logchirp_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Frequency_logchirp_T Frequency_logchirp_Y;

/* Periodic continuous states */
PeriodicIndX_Frequency_logchirp_T Frequency_logchirp_PeriodicIndX;
PeriodicRngX_Frequency_logchirp_T Frequency_logchirp_PeriodicRngX;

/* Real-time model */
static RT_MODEL_Frequency_logchirp_T Frequency_logchirp_M_;
RT_MODEL_Frequency_logchirp_T *const Frequency_logchirp_M =
  &Frequency_logchirp_M_;

/* State reduction function */
void local_stateReduction(real_T* x, int_T* p, int_T n, real_T* r)
{
  int_T i, j;
  for (i = 0, j = 0; i < n; ++i, ++j) {
    int_T k = p[i];
    real_T lb = r[j++];
    real_T xk = x[k]-lb;
    real_T rk = r[j]-lb;
    int_T q = (int_T) floor(xk/rk);
    if (q) {
      x[k] = xk-q*rk+lb;
    }
  }
}

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
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Frequency_logchirp_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  Frequency_logchirp_output();
  Frequency_logchirp_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  Frequency_logchirp_output();
  Frequency_logchirp_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  Frequency_logchirp_output();
  Frequency_logchirp_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  local_stateReduction(rtsiGetContStates(si), rtsiGetPeriodicContStateIndices(si),
                       1,
                       rtsiGetPeriodicContStateRanges(si));
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model output function */
void Frequency_logchirp_output(void)
{
  real_T u;
  if (rtmIsMajorTimeStep(Frequency_logchirp_M)) {
    /* set solver stop time */
    if (!(Frequency_logchirp_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Frequency_logchirp_M->solverInfo,
                            ((Frequency_logchirp_M->Timing.clockTickH0 + 1) *
        Frequency_logchirp_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Frequency_logchirp_M->solverInfo,
                            ((Frequency_logchirp_M->Timing.clockTick0 + 1) *
        Frequency_logchirp_M->Timing.stepSize0 +
        Frequency_logchirp_M->Timing.clockTickH0 *
        Frequency_logchirp_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Frequency_logchirp_M)) {
    Frequency_logchirp_M->Timing.t[0] = rtsiGetT
      (&Frequency_logchirp_M->solverInfo);
  }

  /* Integrator: '<Root>/deltaomega 1' */
  Frequency_logchirp_B.deltaomega1 = Frequency_logchirp_X.deltaomega1_CSTATE;

  /* Outport: '<Root>/deltaomega' */
  Frequency_logchirp_Y.deltaomega = Frequency_logchirp_B.deltaomega1;

  /* Integrator: '<Root>/Original w' */
  Frequency_logchirp_B.Originalw = Frequency_logchirp_X.Originalw_CSTATE;

  /* Outport: '<Root>/deltaomegadot' */
  Frequency_logchirp_Y.deltaomegadot = Frequency_logchirp_B.Originalw;

  /* Integrator: '<Root>/Integrator1' */
  Frequency_logchirp_B.Integrator1 = Frequency_logchirp_X.Integrator1_CSTATE;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/time interval for  each range1'
   */
  Frequency_logchirp_B.log_signal_chirp = rt_powd_snf(10.0,
    (Frequency_logchirp_B.Integrator1 - floor(Frequency_logchirp_B.Integrator1 /
    Frequency_logchirp_P.timeintervalforeachrange1_Value) *
     Frequency_logchirp_P.timeintervalforeachrange1_Value) * (1.0 /
    Frequency_logchirp_P.timeintervalforeachrange1_Value * log10
    (Frequency_logchirp_P.Constant2_Value / Frequency_logchirp_P.Constant1_Value)))
    * Frequency_logchirp_P.Constant1_Value;
  if (rtmIsMajorTimeStep(Frequency_logchirp_M)) {
    /* Outport: '<Root>/inputpower1' incorporates:
     *  Delay: '<Root>/Delay'
     */
    Frequency_logchirp_Y.inputpower1 = Frequency_logchirp_DW.Delay_DSTATE[0];
  }

  /* MATLAB Function: '<Root>/chirp signal  generator1' incorporates:
   *  Constant: '<Root>/Chirp_amplitude2'
   *  Integrator: '<Root>/Integrator2'
   */
  u = cos(Frequency_logchirp_X.Integrator2_CSTATE);
  if (u < 0.0) {
    u = -1.0;
  } else if (u > 0.0) {
    u = 1.0;
  } else if (u == 0.0) {
    u = 0.0;
  } else {
    u = (rtNaN);
  }

  Frequency_logchirp_B.square_chirp =
    Frequency_logchirp_P.Chirp_amplitude2_Value * u;

  /* End of MATLAB Function: '<Root>/chirp signal  generator1' */
  if (rtmIsMajorTimeStep(Frequency_logchirp_M)) {
  }

  /* Gain: '<Root>/Gain' */
  Frequency_logchirp_B.Gain = Frequency_logchirp_P.Gain_Gain *
    Frequency_logchirp_B.log_signal_chirp;

  /* MATLAB Function: '<Root>/MATLAB Function2' incorporates:
   *  Clock: '<Root>/Clock2'
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant5'
   */
  if (Frequency_logchirp_M->Timing.t[0] <= 0.0) {
    Frequency_logchirp_B.fo = Frequency_logchirp_P.Constant3_Value;
  } else {
    Frequency_logchirp_B.fo = Frequency_logchirp_P.Constant5_Value;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function2' */

  /* MATLAB Function: '<Root>/State Space Equation1' incorporates:
   *  Outport: '<Root>/inputpower1'
   *  SignalConversion generated from: '<S3>/ SFunction '
   */
  Frequency_logchirp_B.dotx[0] = Frequency_logchirp_B.Originalw;
  Frequency_logchirp_B.dotx[1] = (-33.358333333333327 *
    Frequency_logchirp_B.deltaomega1 - 5.005 * Frequency_logchirp_B.Originalw) -
    1.6666666666666665 * Frequency_logchirp_Y.inputpower1;
}

/* Model update function */
void Frequency_logchirp_update(void)
{
  int_T idxDelay;
  if (rtmIsMajorTimeStep(Frequency_logchirp_M)) {
    /* Update for Delay: '<Root>/Delay' */
    for (idxDelay = 0; idxDelay < 249; idxDelay++) {
      Frequency_logchirp_DW.Delay_DSTATE[idxDelay] =
        Frequency_logchirp_DW.Delay_DSTATE[idxDelay + 1];
    }

    Frequency_logchirp_DW.Delay_DSTATE[249] = Frequency_logchirp_B.square_chirp;

    /* End of Update for Delay: '<Root>/Delay' */
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(Frequency_logchirp_M)!=-1) &&
        !((rtmGetTFinal(Frequency_logchirp_M)-
           (((Frequency_logchirp_M->Timing.clockTick1+
              Frequency_logchirp_M->Timing.clockTickH1* 4294967296.0)) * 0.02)) >
          (((Frequency_logchirp_M->Timing.clockTick1+
             Frequency_logchirp_M->Timing.clockTickH1* 4294967296.0)) * 0.02) *
          (DBL_EPSILON))) {
      rtmSetErrorStatus(Frequency_logchirp_M, "Simulation finished");
    }
  }

  if (rtmIsMajorTimeStep(Frequency_logchirp_M)) {
    rt_ertODEUpdateContinuousStates(&Frequency_logchirp_M->solverInfo);
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
  if (!(++Frequency_logchirp_M->Timing.clockTick0)) {
    ++Frequency_logchirp_M->Timing.clockTickH0;
  }

  Frequency_logchirp_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Frequency_logchirp_M->solverInfo);

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
    Frequency_logchirp_M->Timing.clockTick1++;
    if (!Frequency_logchirp_M->Timing.clockTick1) {
      Frequency_logchirp_M->Timing.clockTickH1++;
    }
  }
}

/* Derivatives for root system: '<Root>' */
void Frequency_logchirp_derivatives(void)
{
  XDot_Frequency_logchirp_T *_rtXdot;
  _rtXdot = ((XDot_Frequency_logchirp_T *) Frequency_logchirp_M->derivs);

  /* Derivatives for Integrator: '<Root>/deltaomega 1' */
  _rtXdot->deltaomega1_CSTATE = Frequency_logchirp_B.dotx[0];

  /* Derivatives for Integrator: '<Root>/Original w' */
  _rtXdot->Originalw_CSTATE = Frequency_logchirp_B.dotx[1];

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = Frequency_logchirp_B.fo;

  /* Derivatives for Integrator: '<Root>/Integrator2' */
  _rtXdot->Integrator2_CSTATE = Frequency_logchirp_B.Gain;
}

/* Model initialize function */
void Frequency_logchirp_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Frequency_logchirp_M, 0,
                sizeof(RT_MODEL_Frequency_logchirp_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Frequency_logchirp_M->solverInfo,
                          &Frequency_logchirp_M->Timing.simTimeStep);
    rtsiSetTPtr(&Frequency_logchirp_M->solverInfo, &rtmGetTPtr
                (Frequency_logchirp_M));
    rtsiSetStepSizePtr(&Frequency_logchirp_M->solverInfo,
                       &Frequency_logchirp_M->Timing.stepSize0);
    rtsiSetdXPtr(&Frequency_logchirp_M->solverInfo,
                 &Frequency_logchirp_M->derivs);
    rtsiSetContStatesPtr(&Frequency_logchirp_M->solverInfo, (real_T **)
                         &Frequency_logchirp_M->contStates);
    rtsiSetNumContStatesPtr(&Frequency_logchirp_M->solverInfo,
      &Frequency_logchirp_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Frequency_logchirp_M->solverInfo,
      &Frequency_logchirp_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Frequency_logchirp_M->solverInfo,
      &Frequency_logchirp_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Frequency_logchirp_M->solverInfo,
      &Frequency_logchirp_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Frequency_logchirp_M->solverInfo, (&rtmGetErrorStatus
      (Frequency_logchirp_M)));
    rtsiSetRTModelPtr(&Frequency_logchirp_M->solverInfo, Frequency_logchirp_M);
  }

  rtsiSetSimTimeStep(&Frequency_logchirp_M->solverInfo, MAJOR_TIME_STEP);
  Frequency_logchirp_M->intgData.y = Frequency_logchirp_M->odeY;
  Frequency_logchirp_M->intgData.f[0] = Frequency_logchirp_M->odeF[0];
  Frequency_logchirp_M->intgData.f[1] = Frequency_logchirp_M->odeF[1];
  Frequency_logchirp_M->intgData.f[2] = Frequency_logchirp_M->odeF[2];
  Frequency_logchirp_M->intgData.f[3] = Frequency_logchirp_M->odeF[3];
  Frequency_logchirp_M->contStates = ((X_Frequency_logchirp_T *)
    &Frequency_logchirp_X);
  Frequency_logchirp_M->periodicContStateIndices = ((int_T*)
    Frequency_logchirp_PeriodicIndX);
  Frequency_logchirp_M->periodicContStateRanges = ((real_T*)
    Frequency_logchirp_PeriodicRngX);
  rtsiSetSolverData(&Frequency_logchirp_M->solverInfo, (void *)
                    &Frequency_logchirp_M->intgData);
  rtsiSetSolverName(&Frequency_logchirp_M->solverInfo,"ode4");
  rtmSetTPtr(Frequency_logchirp_M, &Frequency_logchirp_M->Timing.tArray[0]);
  rtmSetTFinal(Frequency_logchirp_M, 310.0);
  Frequency_logchirp_M->Timing.stepSize0 = 0.02;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    Frequency_logchirp_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Frequency_logchirp_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Frequency_logchirp_M->rtwLogInfo, (NULL));
    rtliSetLogT(Frequency_logchirp_M->rtwLogInfo, "tout");
    rtliSetLogX(Frequency_logchirp_M->rtwLogInfo, "");
    rtliSetLogXFinal(Frequency_logchirp_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Frequency_logchirp_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Frequency_logchirp_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Frequency_logchirp_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Frequency_logchirp_M->rtwLogInfo, 1);
    rtliSetLogY(Frequency_logchirp_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Frequency_logchirp_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Frequency_logchirp_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Frequency_logchirp_B), 0,
                sizeof(B_Frequency_logchirp_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Frequency_logchirp_X, 0,
                  sizeof(X_Frequency_logchirp_T));
  }

  /* Periodic continuous states */
  {
    (void) memset((void*) Frequency_logchirp_PeriodicIndX, 0,
                  1*sizeof(int_T));
    (void) memset((void*) Frequency_logchirp_PeriodicRngX, 0,
                  2*sizeof(real_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Frequency_logchirp_DW, 0,
                sizeof(DW_Frequency_logchirp_T));

  /* external outputs */
  (void)memset(&Frequency_logchirp_Y, 0, sizeof(ExtY_Frequency_logchirp_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Frequency_logchirp_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Frequency_logchirp_M), Frequency_logchirp_M->Timing.stepSize0,
    (&rtmGetErrorStatus(Frequency_logchirp_M)));

  {
    int32_T i;

    /* InitializeConditions for Delay: '<Root>/Delay' */
    for (i = 0; i < 250; i++) {
      Frequency_logchirp_DW.Delay_DSTATE[i] =
        Frequency_logchirp_P.Delay_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<Root>/Delay' */

    /* InitializeConditions for Integrator: '<Root>/deltaomega 1' */
    Frequency_logchirp_X.deltaomega1_CSTATE =
      Frequency_logchirp_P.deltaomega1_IC;

    /* InitializeConditions for Integrator: '<Root>/Original w' */
    Frequency_logchirp_X.Originalw_CSTATE = Frequency_logchirp_P.Originalw_IC;

    /* InitializeConditions for Integrator: '<Root>/Integrator1' */
    Frequency_logchirp_X.Integrator1_CSTATE =
      Frequency_logchirp_P.Integrator1_IC;

    /* InitializeConditions for Integrator: '<Root>/Integrator2' */
    Frequency_logchirp_X.Integrator2_CSTATE =
      Frequency_logchirp_P.Integrator2_IC;

    /* InitializeConditions for root-level periodic continuous states */
    {
      int_T rootPeriodicContStateIndices[1] = { 3 };

      real_T rootPeriodicContStateRanges[2] = { 0.0001, 6.2831853071795862 };

      (void) memcpy((void*)Frequency_logchirp_PeriodicIndX,
                    rootPeriodicContStateIndices,
                    1*sizeof(int_T));
      (void) memcpy((void*)Frequency_logchirp_PeriodicRngX,
                    rootPeriodicContStateRanges,
                    2*sizeof(real_T));
    }
  }
}

/* Model terminate function */
void Frequency_logchirp_terminate(void)
{
  /* (no terminate code required) */
}
