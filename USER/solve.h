#ifndef __SOLVE_H
#define __SOLVE_H
#include "main.h"                  // Device header
#include "arm_math.h"
#include "motorctrl.h"

typedef struct
{
	double x;
	double y;
	double theta;
	
} TGT_COOR;

typedef struct
{
	double x;
	double y;
	double theta;
	double RE_theta;
  double dist;
	double Vx;
	double Vy;
	double omega;
	
} REAL_COOR;
void Receive(void);
void Reach_TGT(void);

#endif
