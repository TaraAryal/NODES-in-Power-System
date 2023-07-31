/*
 * Frequency_squarechirp_data.c
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

/* Block parameters (default storage) */
P_Frequency_squarechirp_T Frequency_squarechirp_P = {
  /* Expression: 0.0
   * Referenced by: '<Root>/Delay'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/deltaomega 1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Original w'
   */
  0.0,

  /* Expression: 0.1
   * Referenced by: '<Root>/Pulse Generator1'
   */
  0.1,

  /* Computed Parameter: PulseGenerator1_Period
   * Referenced by: '<Root>/Pulse Generator1'
   */
  50.0,

  /* Computed Parameter: PulseGenerator1_Duty
   * Referenced by: '<Root>/Pulse Generator1'
   */
  25.0,

  /* Expression: 0
   * Referenced by: '<Root>/Pulse Generator1'
   */
  0.0
};
