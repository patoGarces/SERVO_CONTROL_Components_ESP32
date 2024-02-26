#include <stdio.h>
#include "include/SERVO_CONTROL.h"
#include "rom/ets_sys.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define CPU_CONTROL     1

#define TAG "SERVO_CONTROL"

#define SPEED_MODE_TIMER        LEDC_LOW_SPEED_MODE
#define TIMER_HIGH_FREQ_OUTPUT  LEDC_TIMER_0
#define TIMER_LOW_FREQ_OUTPUT   LEDC_TIMER_1
#define TIMER_HIGH_FREQUENCY    400
#define TIMER_LOW_FREQUENCY     50

// pwm duty range for dji ph2 esc
#define MIN_ESC_DJI_DUTY         42
#define MAX_ESC_DJI_DUTY         71

// pwm duty range for generic servos
#define MIN_SERVO_DUTY         5
#define MAX_SERVO_DUTY         10

#define MIN_LIMIT_PWM_INDEX   0
#define MAX_LIMIT_PWM_INDEX   1

uint8_t limitsPwm[6][2] = {
    {MIN_ESC_DJI_DUTY,MAX_ESC_DJI_DUTY},
    {MIN_ESC_DJI_DUTY,MAX_ESC_DJI_DUTY},
    {MIN_SERVO_DUTY,MAX_SERVO_DUTY},
    {MIN_SERVO_DUTY,MAX_SERVO_DUTY},
    {MIN_SERVO_DUTY,MAX_SERVO_DUTY},
    {MIN_SERVO_DUTY,MAX_SERVO_DUTY},
};

void pwmServoInit(uint8_t _hsPwm1Gpio,uint8_t _hsPwm2Gpio,uint8_t _lsPwm1Gpio,uint8_t _lsPwm2Gpio,uint8_t _lsPwm3Gpio,uint8_t _lsPwm4Gpio) {

    ledc_timer_config_t timerConfig = {
        .speed_mode = SPEED_MODE_TIMER,
        .timer_num = TIMER_HIGH_FREQ_OUTPUT,
        .clk_cfg = LEDC_USE_RC_FAST_CLK,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = TIMER_HIGH_FREQUENCY,
    };
    ledc_timer_config(&timerConfig);

    timerConfig.timer_num = TIMER_LOW_FREQ_OUTPUT,
    timerConfig.freq_hz = TIMER_LOW_FREQUENCY,
    ledc_timer_config(&timerConfig);

    ledc_channel_config_t channelConfig = {
        .gpio_num = _hsPwm1Gpio,
        .speed_mode = SPEED_MODE_TIMER,
        .channel = LEDC_CHANNEL_0,
        .intr_type =  LEDC_INTR_DISABLE,
        .timer_sel = TIMER_HIGH_FREQ_OUTPUT,
        .duty = 0,
        .hpoint = 0,
    };
    ledc_channel_config(&channelConfig);

    channelConfig.gpio_num = _hsPwm2Gpio;
    channelConfig.channel = LEDC_CHANNEL_1;
    ledc_channel_config(&channelConfig);   

    channelConfig.timer_sel = TIMER_LOW_FREQ_OUTPUT;

    channelConfig.gpio_num = _lsPwm1Gpio;
    channelConfig.channel = LEDC_CHANNEL_2;
    ledc_channel_config(&channelConfig);   

    channelConfig.gpio_num = _lsPwm2Gpio;
    channelConfig.channel = LEDC_CHANNEL_3;
    ledc_channel_config(&channelConfig);

    channelConfig.gpio_num = _lsPwm3Gpio;
    channelConfig.channel = LEDC_CHANNEL_4;
    ledc_channel_config(&channelConfig);  

    channelConfig.gpio_num = _lsPwm4Gpio;
    channelConfig.channel = LEDC_CHANNEL_5;
    ledc_channel_config(&channelConfig);      

    ledc_timer_resume(SPEED_MODE_TIMER,TIMER_HIGH_FREQ_OUTPUT);
    ledc_timer_resume(SPEED_MODE_TIMER,TIMER_LOW_FREQ_OUTPUT);
}


void setChannelOutput(uint8_t channel,int8_t speed){
    if( speed >= 0 && speed <= 100 ){
        float duty = limitsPwm[channel][MIN_LIMIT_PWM_INDEX] + ((float) speed * (limitsPwm[channel][MAX_LIMIT_PWM_INDEX]-limitsPwm[channel][MIN_LIMIT_PWM_INDEX])) / 100.00;  
        duty = (duty*1024) / 100.00 ; 
        ledc_set_duty(SPEED_MODE_TIMER,channel,duty);
        ledc_update_duty(SPEED_MODE_TIMER,channel);
    }
}

void changeLimitsPwm(uint8_t channel,uint8_t minPwm,uint8_t maxPwm){
    limitsPwm[channel][MIN_LIMIT_PWM_INDEX] = minPwm;
    limitsPwm[channel][MAX_LIMIT_PWM_INDEX] = maxPwm;
}