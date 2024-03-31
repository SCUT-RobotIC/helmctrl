#ifndef MOTORCTRL_H
#define MOTORCTRL_H
#include "main.h"
#include "can.h"
#include "dma.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "pidctl.h"
#include "arm_math.h"
#include "bsp_can.h"
typedef struct
{
	int dir;
	double thetal;
	double thetan;
	double thetas;
	double err;
	double err1;
	double err2;
	
} ang_dir;

void cala_d(int i);
void ctrlmotor(double Vx, double Vy, double omega,int dir1,int dir2,int dir3,int dir4,int flag) ;
void pid3508(double p, double i, double d);
void pid2006(double p, double i, double d);
void Apid2006(double p, double i, double d);
#endif
