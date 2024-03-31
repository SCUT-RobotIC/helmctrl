/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pidctl.c
 *
 * Code generated for Simulink model 'pidctl'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Jan 31 21:47:25 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 10
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "pidctl.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S202>/Chart1' */
#define IN_ADD                         ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_SUB                         ((uint8_T)3U)

/* Named constants for Chart: '<S202>/Chart2' */
#define IN_DB                          ((uint8_T)1U)

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void IfAction_speedSubsystem(real_T rtu_yaw_speed_rpm, real_T
  rtu_yaw_target, real_T *rty_Out1, DW_IfAction_speedSubsystem *localDW);
static void IfAction_speedSubsystem1(real_T rtu_yaw_speed_rpm, real_T
  rtu_yaw_target, real_T rtu_yaw_ecd, real_T rtu_yaw_last_ecd, real_T
  rtu_yaw_circle, real_T *rty_Out1, real_T *rty_yaw_circle_out,
  DW_IfAction_speedSubsystem1 *localDW);

/*
 * Output and update for action system:
 *    '<S5>/If Action_speed Subsystem'
 *    '<S6>/If Action_speed Subsystem'
 *    '<S7>/If Action_speed Subsystem'
 *    '<S8>/If Action_speed Subsystem'
 */
static void IfAction_speedSubsystem(real_T rtu_yaw_speed_rpm, real_T
  rtu_yaw_target, real_T *rty_Out1, DW_IfAction_speedSubsystem *localDW)
{
  real_T rtb_FilterCoefficient_jq;
  real_T rtb_Sum_j;
  real_T u0;

  /* Sum: '<S201>/Sum' */
  rtb_Sum_j = rtu_yaw_target - rtu_yaw_speed_rpm;

  /* Gain: '<S238>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S230>/Filter'
   *  Gain: '<S229>/Derivative Gain'
   *  Sum: '<S230>/SumD'
   */
  rtb_FilterCoefficient_jq = (rtP.Kd2006_1 * rtb_Sum_j - localDW->Filter_DSTATE)
    * 100.0;

  /* Sum: '<S244>/Sum' incorporates:
   *  DiscreteIntegrator: '<S235>/Integrator'
   *  Gain: '<S240>/Proportional Gain'
   */
  u0 = (rtP.Kp2006_1 * rtb_Sum_j + localDW->Integrator_DSTATE) +
    rtb_FilterCoefficient_jq;

  /* Saturate: '<S242>/Saturation' */
  if (u0 > 16384.0) {
    *rty_Out1 = 16384.0;
  } else if (u0 < -16384.0) {
    *rty_Out1 = -16384.0;
  } else {
    *rty_Out1 = u0;
  }

  /* End of Saturate: '<S242>/Saturation' */

  /* Update for DiscreteIntegrator: '<S230>/Filter' */
  localDW->Filter_DSTATE += 0.001 * rtb_FilterCoefficient_jq;

  /* Update for DiscreteIntegrator: '<S235>/Integrator' incorporates:
   *  Gain: '<S232>/Integral Gain'
   */
  localDW->Integrator_DSTATE += rtP.Ki2006_1 * rtb_Sum_j * 0.001;
}

/*
 * Output and update for action system:
 *    '<S5>/If Action_speed Subsystem1'
 *    '<S6>/If Action_speed Subsystem1'
 *    '<S7>/If Action_speed Subsystem1'
 *    '<S8>/If Action_speed Subsystem1'
 */
static void IfAction_speedSubsystem1(real_T rtu_yaw_speed_rpm, real_T
  rtu_yaw_target, real_T rtu_yaw_ecd, real_T rtu_yaw_last_ecd, real_T
  rtu_yaw_circle, real_T *rty_Out1, real_T *rty_yaw_circle_out,
  DW_IfAction_speedSubsystem1 *localDW)
{
  real_T rtb_FilterCoefficient_f;
  real_T rtb_FilterCoefficient_p;
  real_T rtb_Filter_aj;
  real_T rtb_Sum3_p;
  real_T rtb_Switch1;

  /* Sum: '<S202>/Sum' incorporates:
   *  Gain: '<S202>/Gain'
   *  Sum: '<S202>/Sum2'
   */
  rtb_Filter_aj = rtu_yaw_target - (8191.0 * rtu_yaw_circle + rtu_yaw_ecd);

  /* Abs: '<S202>/Abs' */
  rtb_Switch1 = fabs(rtb_Filter_aj);

  /* Switch: '<S202>/Switch2' incorporates:
   *  Constant: '<S202>/Constant'
   */
  if (!(rtb_Switch1 > 500.0)) {
    rtb_Filter_aj = 0.0;
  }

  /* End of Switch: '<S202>/Switch2' */

  /* Gain: '<S338>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S330>/Filter'
   *  Gain: '<S329>/Derivative Gain'
   *  Sum: '<S330>/SumD'
   */
  rtb_FilterCoefficient_f = (rtP.KAd2006_1 * rtb_Filter_aj -
    localDW->Filter_DSTATE) * 100.0;

  /* Switch: '<S202>/Switch1' incorporates:
   *  Constant: '<S202>/Constant'
   *  Gain: '<S202>/Multiply'
   *  Saturate: '<S342>/Saturation'
   *  Sum: '<S202>/Sum1'
   */
  if (rtb_Switch1 > 500.0) {
    /* Sum: '<S344>/Sum' incorporates:
     *  DiscreteIntegrator: '<S335>/Integrator'
     *  Gain: '<S340>/Proportional Gain'
     */
    rtb_Sum3_p = (rtP.KAp2006_1 * rtb_Filter_aj + localDW->Integrator_DSTATE) +
      rtb_FilterCoefficient_f;

    /* Saturate: '<S342>/Saturation' */
    if (rtb_Sum3_p > 16384.0) {
      rtb_Sum3_p = 16384.0;
    } else if (rtb_Sum3_p < -16384.0) {
      rtb_Sum3_p = -16384.0;
    }

    rtb_Switch1 = 0.5 * rtb_Sum3_p - rtu_yaw_speed_rpm;
  } else {
    rtb_Switch1 = 0.0;
  }

  /* End of Switch: '<S202>/Switch1' */

  /* Gain: '<S290>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S282>/Filter'
   *  Gain: '<S281>/Derivative Gain'
   *  Sum: '<S282>/SumD'
   */
  rtb_FilterCoefficient_p = (rtP.Kd2006_1 * rtb_Switch1 -
    localDW->Filter_DSTATE_f) * 100.0;

  /* Sum: '<S296>/Sum' incorporates:
   *  DiscreteIntegrator: '<S287>/Integrator'
   *  Gain: '<S292>/Proportional Gain'
   */
  rtb_Sum3_p = (rtP.Kp2006_1 * rtb_Switch1 + localDW->Integrator_DSTATE_j) +
    rtb_FilterCoefficient_p;

  /* Saturate: '<S294>/Saturation' */
  if (rtb_Sum3_p > 16384.0) {
    *rty_Out1 = 16384.0;
  } else if (rtb_Sum3_p < -16384.0) {
    *rty_Out1 = -16384.0;
  } else {
    *rty_Out1 = rtb_Sum3_p;
  }

  /* End of Saturate: '<S294>/Saturation' */

  /* Sum: '<S202>/Sum3' */
  rtb_Sum3_p = rtu_yaw_ecd - rtu_yaw_last_ecd;

  /* Chart: '<S202>/Chart1' */
  if (localDW->is_active_c3_pidctl == 0U) {
    localDW->is_active_c3_pidctl = 1U;
    localDW->is_c3_pidctl = IN_IDLE;
  } else {
    switch (localDW->is_c3_pidctl) {
     case IN_ADD:
      if (rtb_Sum3_p <= -5000.0) {
        localDW->is_c3_pidctl = IN_SUB;
        localDW->u2 = -1.0;
      } else if ((rtb_Sum3_p < 5000.0) && (rtb_Sum3_p > -5000.0)) {
        localDW->is_c3_pidctl = IN_IDLE;
      }
      break;

     case IN_IDLE:
      if (rtb_Sum3_p >= 5000.0) {
        localDW->is_c3_pidctl = IN_ADD;
        localDW->u2 = 1.0;
      } else if (rtb_Sum3_p <= -5000.0) {
        localDW->is_c3_pidctl = IN_SUB;
        localDW->u2 = -1.0;
      } else {
        localDW->u2 = 0.0;
      }
      break;

     default:
      /* case IN_SUB: */
      if (rtb_Sum3_p >= 5000.0) {
        localDW->is_c3_pidctl = IN_ADD;
        localDW->u2 = 1.0;
      } else if ((rtb_Sum3_p < 5000.0) && (rtb_Sum3_p > -5000.0)) {
        localDW->is_c3_pidctl = IN_IDLE;
      }
      break;
    }
  }

  /* End of Chart: '<S202>/Chart1' */

  /* Sum: '<S202>/Sum4' */
  *rty_yaw_circle_out = localDW->u2 + rtu_yaw_circle;

  /* Chart: '<S202>/Chart2' */
  if (localDW->is_active_c4_pidctl == 0U) {
    localDW->is_active_c4_pidctl = 1U;
    localDW->is_c4_pidctl = IN_DB;
  } else if (localDW->is_c4_pidctl != IN_DB) {
    /* case IN_NDB: */
    localDW->is_c4_pidctl = IN_DB;
  }

  /* End of Chart: '<S202>/Chart2' */

  /* Update for DiscreteIntegrator: '<S335>/Integrator' incorporates:
   *  Gain: '<S332>/Integral Gain'
   */
  localDW->Integrator_DSTATE += rtP.KAi2006_1 * rtb_Filter_aj * 0.001;

  /* Update for DiscreteIntegrator: '<S330>/Filter' */
  localDW->Filter_DSTATE += 0.001 * rtb_FilterCoefficient_f;

  /* Update for DiscreteIntegrator: '<S282>/Filter' */
  localDW->Filter_DSTATE_f += 0.001 * rtb_FilterCoefficient_p;

  /* Update for DiscreteIntegrator: '<S287>/Integrator' incorporates:
   *  Gain: '<S284>/Integral Gain'
   */
  localDW->Integrator_DSTATE_j += rtP.Ki2006_1 * rtb_Switch1 * 0.001;
}

/* Model step function */
void pidctl_step(void)
{
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_e;
  real_T rtb_FilterCoefficient_f;
  real_T rtb_FilterCoefficient_k;
  real_T rtb_IntegralGain;
  real_T rtb_IntegralGain_h;
  real_T rtb_IntegralGain_k;
  real_T rtb_Sum3;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/aspd0'
   *  Inport: '<Root>/tspd0'
   */
  rtb_Sum3 = rtU.tspd0 - rtU.aspd0;

  /* Gain: '<S91>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S83>/Filter'
   *  Gain: '<S82>/Derivative Gain'
   *  Sum: '<S83>/SumD'
   */
  rtb_FilterCoefficient = (rtP.Kd3508_1 * rtb_Sum3 - rtDW.Filter_DSTATE) * 100.0;

  /* Outport: '<Root>/Out0' incorporates:
   *  DiscreteIntegrator: '<S88>/Integrator'
   *  Gain: '<S93>/Proportional Gain'
   *  Sum: '<S97>/Sum'
   */
  rtY.Out0 = (rtP.Kp3508_1 * rtb_Sum3 + rtDW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Gain: '<S85>/Integral Gain' */
  rtb_IntegralGain = rtP.Ki3508_1 * rtb_Sum3;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/aspd1'
   *  Inport: '<Root>/tspd1'
   */
  rtb_Sum3 = rtU.tspd1 - rtU.aspd1;

  /* Gain: '<S43>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S35>/Filter'
   *  Gain: '<S34>/Derivative Gain'
   *  Sum: '<S35>/SumD'
   */
  rtb_FilterCoefficient_f = (rtP.Kd3508_2 * rtb_Sum3 - rtDW.Filter_DSTATE_p) *
    100.0;

  /* Outport: '<Root>/Out1' incorporates:
   *  DiscreteIntegrator: '<S40>/Integrator'
   *  Gain: '<S45>/Proportional Gain'
   *  Sum: '<S49>/Sum'
   */
  rtY.Out1 = (rtP.Kp3508_2 * rtb_Sum3 + rtDW.Integrator_DSTATE_h) +
    rtb_FilterCoefficient_f;

  /* Gain: '<S37>/Integral Gain' */
  rtb_IntegralGain_k = rtP.Ki3508_2 * rtb_Sum3;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Inport: '<Root>/aspd2'
   *  Inport: '<Root>/tspd2'
   */
  rtb_Sum3 = rtU.tspd2 - rtU.aspd2;

  /* Gain: '<S139>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S131>/Filter'
   *  Gain: '<S130>/Derivative Gain'
   *  Sum: '<S131>/SumD'
   */
  rtb_FilterCoefficient_e = (rtP.Kd3508_3 * rtb_Sum3 - rtDW.Filter_DSTATE_b) *
    100.0;

  /* Outport: '<Root>/Out2' incorporates:
   *  DiscreteIntegrator: '<S136>/Integrator'
   *  Gain: '<S141>/Proportional Gain'
   *  Sum: '<S145>/Sum'
   */
  rtY.Out2 = (rtP.Kp3508_3 * rtb_Sum3 + rtDW.Integrator_DSTATE_i) +
    rtb_FilterCoefficient_e;

  /* Gain: '<S133>/Integral Gain' */
  rtb_IntegralGain_h = rtP.Ki3508_3 * rtb_Sum3;

  /* Sum: '<Root>/Sum3' incorporates:
   *  Inport: '<Root>/aspd3'
   *  Inport: '<Root>/tspd3'
   */
  rtb_Sum3 = rtU.tspd3 - rtU.aspd3;

  /* Gain: '<S187>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S179>/Filter'
   *  Gain: '<S178>/Derivative Gain'
   *  Sum: '<S179>/SumD'
   */
  rtb_FilterCoefficient_k = (rtP.Kd3508_4 * rtb_Sum3 - rtDW.Filter_DSTATE_bi) *
    100.0;

  /* Outport: '<Root>/Out3' incorporates:
   *  DiscreteIntegrator: '<S184>/Integrator'
   *  Gain: '<S189>/Proportional Gain'
   *  Sum: '<S193>/Sum'
   */
  rtY.Out3 = (rtP.Kp3508_4 * rtb_Sum3 + rtDW.Integrator_DSTATE_m) +
    rtb_FilterCoefficient_k;

  /* SwitchCase: '<S5>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_circle0'
   *  Inport: '<Root>/yaw_ecd0'
   *  Inport: '<Root>/yaw_last_ecd0'
   *  Inport: '<Root>/yaw_speed_rpm0'
   *  Inport: '<Root>/yaw_status0'
   *  Inport: '<Root>/yaw_target0'
   *  Outport: '<Root>/yaw_ANG_OUT0'
   *  Outport: '<Root>/yaw_SPD_OUT0'
   *  Outport: '<Root>/yaw_circle_out0'
   */
  switch ((int32_T)rtU.yaw_status0) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S5>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S201>/Action Port'
     */
    IfAction_speedSubsystem(rtU.yaw_speed_rpm0, rtU.yaw_target0,
      &rtY.yaw_SPD_OUT0, &rtDW.IfAction_speedSubsystem_g);

    /* End of Outputs for SubSystem: '<S5>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S5>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S202>/Action Port'
     */
    IfAction_speedSubsystem1(rtU.yaw_speed_rpm0, rtU.yaw_target0, rtU.yaw_ecd0,
      rtU.yaw_last_ecd0, rtU.yaw_circle0, &rtY.yaw_ANG_OUT0,
      &rtY.yaw_circle_out0, &rtDW.IfAction_speedSubsystem1_i);

    /* End of Outputs for SubSystem: '<S5>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S5>/Switch Case' */

  /* SwitchCase: '<S6>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_circle1'
   *  Inport: '<Root>/yaw_ecd1'
   *  Inport: '<Root>/yaw_last_ecd1'
   *  Inport: '<Root>/yaw_speed_rpm1'
   *  Inport: '<Root>/yaw_status1'
   *  Inport: '<Root>/yaw_target1'
   *  Outport: '<Root>/yaw_ANG_OUT1'
   *  Outport: '<Root>/yaw_SPD_OUT1'
   *  Outport: '<Root>/yaw_circle_out1'
   */
  switch ((int32_T)rtU.yaw_status1) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S6>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S352>/Action Port'
     */
    IfAction_speedSubsystem(rtU.yaw_speed_rpm1, rtU.yaw_target1,
      &rtY.yaw_SPD_OUT1, &rtDW.IfAction_speedSubsystem_b);

    /* End of Outputs for SubSystem: '<S6>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S6>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S353>/Action Port'
     */
    IfAction_speedSubsystem1(rtU.yaw_speed_rpm1, rtU.yaw_target1, rtU.yaw_ecd1,
      rtU.yaw_last_ecd1, rtU.yaw_circle1, &rtY.yaw_ANG_OUT1,
      &rtY.yaw_circle_out1, &rtDW.IfAction_speedSubsystem1_m);

    /* End of Outputs for SubSystem: '<S6>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S6>/Switch Case' */

  /* SwitchCase: '<S7>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_circle2'
   *  Inport: '<Root>/yaw_ecd2'
   *  Inport: '<Root>/yaw_last_ecd2'
   *  Inport: '<Root>/yaw_speed_rpm2'
   *  Inport: '<Root>/yaw_status2'
   *  Inport: '<Root>/yaw_target2'
   *  Outport: '<Root>/yaw_ANG_OUT2'
   *  Outport: '<Root>/yaw_SPD_OUT2'
   *  Outport: '<Root>/yaw_circle_out2'
   */
  switch ((int32_T)rtU.yaw_status2) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S7>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S503>/Action Port'
     */
    IfAction_speedSubsystem(rtU.yaw_speed_rpm2, rtU.yaw_target2,
      &rtY.yaw_SPD_OUT2, &rtDW.IfAction_speedSubsystem_d);

    /* End of Outputs for SubSystem: '<S7>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S7>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S504>/Action Port'
     */
    IfAction_speedSubsystem1(rtU.yaw_speed_rpm2, rtU.yaw_target2, rtU.yaw_ecd2,
      rtU.yaw_last_ecd2, rtU.yaw_circle2, &rtY.yaw_ANG_OUT2,
      &rtY.yaw_circle_out2, &rtDW.IfAction_speedSubsystem1_h);

    /* End of Outputs for SubSystem: '<S7>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S7>/Switch Case' */

  /* SwitchCase: '<S8>/Switch Case' incorporates:
   *  Inport: '<Root>/yaw_circle3'
   *  Inport: '<Root>/yaw_ecd3'
   *  Inport: '<Root>/yaw_last_ecd3'
   *  Inport: '<Root>/yaw_speed_rpm3'
   *  Inport: '<Root>/yaw_status3'
   *  Inport: '<Root>/yaw_target3'
   *  Outport: '<Root>/yaw_ANG_OUT3'
   *  Outport: '<Root>/yaw_SPD_OUT3'
   *  Outport: '<Root>/yaw_circle_out3'
   */
  switch ((int32_T)rtU.yaw_status3) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S8>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S654>/Action Port'
     */
    IfAction_speedSubsystem(rtU.yaw_speed_rpm3, rtU.yaw_target3,
      &rtY.yaw_SPD_OUT3, &rtDW.IfAction_speedSubsystem_n);

    /* End of Outputs for SubSystem: '<S8>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S8>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S655>/Action Port'
     */
    IfAction_speedSubsystem1(rtU.yaw_speed_rpm3, rtU.yaw_target3, rtU.yaw_ecd3,
      rtU.yaw_last_ecd3, rtU.yaw_circle3, &rtY.yaw_ANG_OUT3,
      &rtY.yaw_circle_out3, &rtDW.IfAction_speedSubsystem1_d);

    /* End of Outputs for SubSystem: '<S8>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S8>/Switch Case' */

  /* Update for DiscreteIntegrator: '<S88>/Integrator' */
  rtDW.Integrator_DSTATE += 0.001 * rtb_IntegralGain;

  /* Update for DiscreteIntegrator: '<S83>/Filter' */
  rtDW.Filter_DSTATE += 0.001 * rtb_FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S40>/Integrator' */
  rtDW.Integrator_DSTATE_h += 0.001 * rtb_IntegralGain_k;

  /* Update for DiscreteIntegrator: '<S35>/Filter' */
  rtDW.Filter_DSTATE_p += 0.001 * rtb_FilterCoefficient_f;

  /* Update for DiscreteIntegrator: '<S136>/Integrator' */
  rtDW.Integrator_DSTATE_i += 0.001 * rtb_IntegralGain_h;

  /* Update for DiscreteIntegrator: '<S131>/Filter' */
  rtDW.Filter_DSTATE_b += 0.001 * rtb_FilterCoefficient_e;

  /* Update for DiscreteIntegrator: '<S184>/Integrator' incorporates:
   *  Gain: '<S181>/Integral Gain'
   */
  rtDW.Integrator_DSTATE_m += rtP.Ki3508_4 * rtb_Sum3 * 0.001;

  /* Update for DiscreteIntegrator: '<S179>/Filter' */
  rtDW.Filter_DSTATE_bi += 0.001 * rtb_FilterCoefficient_k;
}

/* Model initialize function */
void pidctl_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
