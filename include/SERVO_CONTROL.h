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

enum {
    OUTPUT_CHANNEL_MOT_L,
    OUTPUT_CHANNEL_MOT_R,
    OUTPUT_CHANNEL_SERVO_L,
    OUTPUT_CHANNEL_SERVO_R,
    OUTPUT_CHANNEL_LED_MOT_L,
    OUTPUT_CHANNEL_LED_MOT_R,   
};

void pwmServoInit(pwm_servo_init_t config);
void pwmSetOutput(uint8_t channel,uint16_t speed);
void pwmChangeLimits(uint8_t channel,uint8_t minPwm,uint8_t maxPwm);

#endif
