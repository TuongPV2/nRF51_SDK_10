/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
 * @defgroup pwm_example_main main.c
 * @{
 * @ingroup pwm_example
 * 
 * @brief  Test DRV motor control and touch button
 *          Button 1: CW
 *          Button 2: CCW
 *          Button 3: change duty cycle
 * This file contains the source code for a sample application using PWM.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"
#include "nrf_gpio.h"
#include "app_error.h"
#include "bsp.h"
#include "app_pwm.h"

#ifdef BSP_BUTTON_0
    #define PIN_IN_0 BSP_BUTTON_0
#endif
#ifdef BSP_BUTTON_1
    #define PIN_IN_1 BSP_BUTTON_1
#endif
#ifdef BSP_BUTTON_2
    #define PIN_IN_2 BSP_BUTTON_2
#endif

#ifdef BSP_LED_0
    #define PIN_OUT BSP_LED_0
#endif
// #ifndef PIN_OUT
//     #error "Please indicate output pin"
// #endif

APP_PWM_INSTANCE(PWM1,1);                   // Create the instance "PWM1" using TIMER1.
APP_PWM_INSTANCE(PWM2,0);                   // Create the instance "PWM1" using TIMER1.

static volatile bool ready_flag;            // A flag indicating PWM status.
static volatile uint32_t flag = 0;            // A flag indicating PWM status.
//static uint32_t duty = 50;
void pwm1_ready_callback(uint32_t pwm_id)    // PWM callback function
{
    ready_flag = true;
}

void pwm2_ready_callback(uint32_t pwm_id)    // PWM callback function
{
    ready_flag = true;
}

void drv_ctrl_init(void)
{
    nrf_gpio_cfg_output(DRV_SLEEP);
    //nrf_gpio_cfg_output(DRV_IN1);
    nrf_gpio_pin_set(DRV_SLEEP);
    //nrf_gpio_pin_clear(DRV_IN1);
}

void in_pin_handler_fw(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    nrf_drv_gpiote_out_toggle(PIN_OUT);
    //nrf_gpio_pin_clear(DRV_SLEEP);
    //nrf_delay_ms(5);
    //nrf_gpio_pin_clear(DRV_IN1);
    //app_pwm_disable(&PWM1);
    app_pwm_channel_duty_set(&PWM1, 0, 0);
    nrf_delay_ms(1);
    flag = 1;
    app_pwm_enable(&PWM2);
}

void in_pin_handler_bw(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    nrf_drv_gpiote_out_toggle(PIN_OUT);
    app_pwm_channel_duty_set(&PWM2, 0, 0);
    //app_pwm_disable(&PWM2);
    nrf_delay_ms(1);
    flag = 2;
    app_pwm_enable(&PWM1);
}

// void in_pin_handler_duty(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
// {
//     duty += 10;
//     if (duty == 100)
//     {
//         duty = 10;
//     }

//     if (flag == 1)
//     {
//         while (app_pwm_channel_duty_set(&PWM1, 0, duty) == NRF_ERROR_BUSY);
//     }
//     if (flag == 2)
//     {
//         while (app_pwm_channel_duty_set(&PWM2, 0, duty) == NRF_ERROR_BUSY);
//     }
    
// }

/**
 * @brief Function for configuring: PIN_IN pin for input, PIN_OUT pin for output, 
 * and configures GPIOTE to give an interrupt on pin change.
 */
static void gpio_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(false);

    err_code = nrf_drv_gpiote_out_init(PIN_OUT, &out_config);
    APP_ERROR_CHECK(err_code);

    //nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(PIN_IN_0, &in_config, in_pin_handler_fw);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_gpiote_in_init(PIN_IN_1, &in_config, in_pin_handler_bw);
    APP_ERROR_CHECK(err_code);
    //err_code = nrf_drv_gpiote_in_init(PIN_IN_2, &in_config, in_pin_handler_duty);
    //APP_ERROR_CHECK(err_code);    
    nrf_drv_gpiote_in_event_enable(PIN_IN_0, true);
    nrf_drv_gpiote_in_event_enable(PIN_IN_1, true);
    //nrf_drv_gpiote_in_event_enable(PIN_IN_2, true);
}

int main(void)
{
    ret_code_t err_code;
    //flag = 2;
    // Init gpio for motor control
    drv_ctrl_init();
    // Touch button
    gpio_init();
    /* 1-channel PWM, 200Hz, output on DK LED pins. */
    app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_1CH(5000L, DRV_IN1);
    app_pwm_config_t pwm2_cfg = APP_PWM_DEFAULT_CONFIG_1CH(5000L, DRV_IN2);
    /* Switch the polarity of the second channel. */
    pwm1_cfg.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;
    pwm2_cfg.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;
    /* Initialize and enable PWM. */
    err_code = app_pwm_init(&PWM1,&pwm1_cfg,pwm1_ready_callback);
    APP_ERROR_CHECK(err_code);
    //app_pwm_enable(&PWM1);
    err_code = app_pwm_init(&PWM2,&pwm2_cfg,pwm2_ready_callback);
    APP_ERROR_CHECK(err_code);
    //app_pwm_enable(&PWM2);    

    uint32_t value;
    while(true)
    {
        for (uint8_t i = 0; i < 40; ++i)
        {
            value = (i < 20) ? (i * 5) : (100 - (i - 20) * 5);
            
            ready_flag = false;
            if (flag == 2)
            {
                while (app_pwm_channel_duty_set(&PWM1, 0, value) == NRF_ERROR_BUSY);

                while(!ready_flag);
                APP_ERROR_CHECK(app_pwm_channel_duty_set(&PWM1, 1, value));
                nrf_delay_ms(25);
            }
            if (flag == 1)
            {
                while (app_pwm_channel_duty_set(&PWM2, 0, value) == NRF_ERROR_BUSY);
                while(!ready_flag);
                APP_ERROR_CHECK(app_pwm_channel_duty_set(&PWM2, 1, value));
                nrf_delay_ms(25);            
            }
        }

    }

    
}


/** @} */
