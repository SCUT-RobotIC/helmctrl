#ifndef CALCULATE_H
#define CALCULATE_H

#include "main.h"


//重定义数组位
#define LX_LSB      0
#define LX_MSB      1
#define LY_LSB      2
#define LY_MSB      3
#define RX_LSB      4
#define RX_MSB      5
#define RY_LSB      6
#define RY_MSB      7
#define LP_LSB      8
#define LP_MSB      9
#define RP_LSB      10
#define RP_MSB      11
#define BOT1        12
#define BOT2        13

//重定义结构体
typedef struct struct_message {
  uint8_t header;
  uint8_t parity;
  uint8_t data[14];
  uint8_t footer;
} DataPacket;

//结构体
extern DataPacket DataRe;
//摇杆变量
extern int16_t lx ,ly,rx,ry,lp,rp;
//按键，开关
extern uint8_t B1,B2;
//校验位
extern uint8_t Cal_Parity;

uint8_t CalculateParity(const uint8_t* data, int dataSize);

void CAL_MESSAGE(void);

#endif
