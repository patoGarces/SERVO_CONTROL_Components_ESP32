#ifndef __SERVO_CONTROL_H__
#define __SERVO_CONTROL_H__

#include "stdio.h"

typedef struct {
    uint8_t hsPwm1Gpio;
    uint8_t hsPwm2Gpio;
    uint8_t lsPwm1Gpio;
    uint8_t lsPwm2Gpio;
    uint8_t lsPwm3Gpio;
    uint8_t lsPwm4Gpio;
} pwm_servo_init_t;

void pwmServoInit(pwm_servo_init_t config);
void pwmSetOutput(uint8_t channel,uint16_t speed);
void pwmChangeLimits(uint8_t channel,uint8_t minPwm,uint8_t maxPwm);

#endif
