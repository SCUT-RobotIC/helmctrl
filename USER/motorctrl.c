#include "motorctrl.h"
ang_dir MotorSignal[4];
double mult=1;
void ctrlmotor(double Vx, double Vy, double omega,int dir1,int dir2,int dir3,int dir4,int flag) {
	while((fabs(sqrt(pow((Vy-omega*sqrt(2)/2),2)+pow((Vx-omega*sqrt(2)/2),2))*mult)>8191)||
				(fabs(sqrt(pow((Vy+omega*sqrt(2)/2),2)+pow((Vx-omega*sqrt(2)/2),2))*mult)>8191)||
				(fabs(sqrt(pow((Vy+omega*sqrt(2)/2),2)+pow((Vx+omega*sqrt(2)/2),2))*mult)>8191)||
				(fabs(sqrt(pow((Vy-omega*sqrt(2)/2),2)+pow((Vx+omega*sqrt(2)/2),2))*mult)>8191))
	  mult=0.98*mult;
	
	if(flag==1){
			rtU.tspd0= sqrt(pow((Vy-omega*sqrt(2)/2),2)+pow((Vx-omega*sqrt(2)/2),2))*mult;
			rtU.tspd1 =sqrt(pow((Vy+omega*sqrt(2)/2),2)+pow((Vx-omega*sqrt(2)/2),2))*mult;	
			rtU.tspd2= sqrt(pow((Vy+omega*sqrt(2)/2),2)+pow((Vx+omega*sqrt(2)/2),2))*mult;	
			rtU.tspd3 =sqrt(pow((Vy-omega*sqrt(2)/2),2)+pow((Vx+omega*sqrt(2)/2),2))*mult;	
	}
	     else{
			  rtU.tspd0=0;
				rtU.tspd1=0;
				rtU.tspd2=0;
				rtU.tspd3=0;
	       }
	if(dir1==1)
		rtU.tspd0=-rtU.tspd0;
  if(dir2==1)
		rtU.tspd1=-rtU.tspd1;
	if(dir3==1)
		rtU.tspd2=-rtU.tspd2;
	if(dir4==1)
		rtU.tspd3=-rtU.tspd3;
}

void cala_d(int i){
		if((MotorSignal[i].thetan<=180&&MotorSignal[i].thetan>90)||(MotorSignal[i].thetan<-90&&MotorSignal[i].thetan>-180))
				MotorSignal[i].dir=1;
			else
				MotorSignal[i].dir=0;
 if(MotorSignal[i].thetan<-90&&MotorSignal[i].thetan>-180)
		 {
			 MotorSignal[i].thetan=MotorSignal[i].thetan+180;

		 }
		 else if(MotorSignal[i].thetan<=180&&MotorSignal[i].thetan>90)
		 {
			 MotorSignal[i].thetan=MotorSignal[i].thetan-180;

		 }

		 MotorSignal[i].err=MotorSignal[i].thetan-MotorSignal[i].thetal;
      if(MotorSignal[i].thetan-MotorSignal[i].thetal<0)
			{
				MotorSignal[i].err1=MotorSignal[i].err+180;
				MotorSignal[i].err2=MotorSignal[i].err;
				
			}
			else if(MotorSignal[i].thetal-MotorSignal[i].thetan<=0)
			{
				MotorSignal[i].err1=MotorSignal[i].err-180;
				MotorSignal[i].err2=MotorSignal[i].err;
				
			}
			if(fabs(MotorSignal[i].err1)>=fabs(MotorSignal[i].err2)){
				MotorSignal[i].err=MotorSignal[i].err2;
			}
			else{
				MotorSignal[i].err=MotorSignal[i].err1;
        MotorSignal[i].dir=1-MotorSignal[i].dir;
			}
			MotorSignal[i].thetas+=MotorSignal[i].err;
			

			if(((int)MotorSignal[i].thetas%360<=270&&(int)MotorSignal[i].thetas%360>=90)||((int)MotorSignal[i].thetas%360<=-90&&(int)MotorSignal[i].thetas%360>=-270)){
					MotorSignal[i].dir=1-MotorSignal[i].dir;
				}

}

void pid3508(double p, double i, double d) {
		rtP.Kp3508_1= p ;
		rtP.Ki3508_1= i;
		rtP.Kd3508_1= d ;
		
		rtP.Kp3508_2=  p ;
		rtP.Ki3508_2=  i ;
		rtP.Kd3508_2=  d ;
		
		rtP.Kp3508_3=  p ;
		rtP.Ki3508_3=  i ;
		rtP.Kd3508_3=  d ;
		
		rtP.Kp3508_4= p ;
		rtP.Ki3508_4= i ;
		rtP.Kd3508_4= d ;
}
void pid2006(double p, double i, double d) {
		rtP.Kp2006_1= p ;
		rtP.Ki2006_1= i;
		rtP.Kd2006_1= d ;
//		
//		rtP.Kp2006_2=  p ;
//		rtP.Ki2006_2=  i ;
//		rtP.Kd2006_2=  d ;
//		
//		rtP.Kp2006_3=  p ;
//		rtP.Ki2006_3=  i ;
//		rtP.Kd2006_3=  d ;
//		
//		rtP.Kp2006_4= p ;
//		rtP.Ki2006_4= i ;
//		rtP.Kd2006_4= d ;
}
void Apid2006(double p, double i, double d) {
		rtP.KAp2006_1= p ;
		rtP.KAi2006_1= i;
		rtP.KAd2006_1= d ;
//		
//		rtP.KAp2006_2=  p ;
//		rtP.KAi2006_2=  i ;
//		rtP.KAd2006_2=  d ;
//		
//		rtP.KAp2006_3=  p ;
//		rtP.KAi2006_3=  i ;
//		rtP.KAd2006_3=  d ;
//		
//		rtP.KAp2006_4= p ;
//		rtP.KAi2006_4= i ;
//		rtP.KAd2006_4= d ;
}
