#ifndef __SERVO_CONTROL_H__
#define __SERVO_CONTROL_H__

#include "stdio.h"

#define GPIO_CHANNEL_1  18
#define GPIO_CHANNEL_2  0
#define GPIO_CHANNEL_3  19
#define GPIO_CHANNEL_4  21
#define GPIO_CHANNEL_5  0
#define GPIO_CHANNEL_6  0

// #define GPIO_MOT_L_STEP     21           // TODO: eliminar
// #define GPIO_MOT_L_DIR      19
// #define GPIO_MOT_R_STEP     18
// #define GPIO_MOT_R_DIR      5
// #define GPIO_MOT_ENABLE     14
// #define GPIO_MICRO_STEP     12

void pwmServoInit(void);
void setChannelOutput(uint8_t channel,int8_t speed);
void changeLimitsPwm(uint8_t channel,uint8_t minPwm,uint8_t maxPwm);


#endif
