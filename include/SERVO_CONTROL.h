#ifndef __SERVO_CONTROL_H__
#define __SERVO_CONTROL_H__

#include "stdio.h"

void pwmServoInit(uint8_t _hsPwm1Gpio,uint8_t _hsPwm2Gpio,uint8_t _lsPwm1Gpio,uint8_t _lsPwm2Gpio,uint8_t _lsPwm3Gpio,uint8_t _lsPwm4Gpio);
void pwmSetOutput(uint8_t channel,int8_t speed);
void pwmChangeLimits(uint8_t channel,uint8_t minPwm,uint8_t maxPwm);

#endif
