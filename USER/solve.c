#include "solve.h"                  // Device header

TGT_COOR TC;
REAL_COOR RC;
double factors[3];
double deadband=50;
void Receive(){
	RC.theta=0;
	RC.x=0;
	RC.y=0;
	TC.x=0;
	TC.y=0;
	TC.theta=0;
}
void Reach_TGT(){
	RC.dist=sqrt(pow(TC.y-RC.y,2)+pow((TC.x-RC.x),2));
	if(RC.dist<deadband)
	{
		RC.dist=0;
	}
	RC.RE_theta=TC.theta-RC.theta;
	if(fabs(RC.RE_theta)<1)
	{
		RC.RE_theta=0;
	}
	RC.Vx=RC.dist*cos(RC.RE_theta)*factors[0];
	RC.Vy=RC.dist*sin(RC.RE_theta)*factors[0];
	RC.omega=RC.RE_theta*factors[1];
}//最后把RC.Vx，RC.Vy，RC.omege三个参数放进main接收就行
