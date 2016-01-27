/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
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
#ifndef DEVBOARD_H
#define DEVBOARD_H

/********************************* LEDs ***************************************/
// LEDs definitions for DEVELOPEMENT BOARD
#define LEDS_NUMBER    1
#define LED_START      28
#define LED_1          14   // Dung tam chan 14 de debug
#define LEDS_LIST {LED_1}
#define BSP_LED_0      LED_1
#define BSP_LED_0_MASK (1<<BSP_LED_0)
#define LEDS_MASK      (BSP_LED_0_MASK)
/* all LEDs are lit when GPIO is low */
#define LEDS_INV_MASK  LEDS_MASK

#define COLOR_SEL1      19
#define COLOR_SEL2      18
/*****************************TOUCH BUTTONs ***********************************/
// Touch BUTTONs definitions for DEVELOPEMENT BOARD
#define BUTTONS_NUMBER 3
#define BUTTON_START   21
#define BUTTON_1       21	/* Touch button 1*/
#define BUTTON_2       22	/* Touch button 1*/
#define BUTTON_3       23	/* Touch button 1*/
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP
#define BUTTONS_LIST { BUTTON_1, BUTTON_2, BUTTON_3}

#define BSP_BUTTON_0   BUTTON_1
#define BSP_BUTTON_1   BUTTON_2
#define BSP_BUTTON_2   BUTTON_3

#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)
#define BSP_BUTTON_1_MASK (1<<BSP_BUTTON_1)
#define BSP_BUTTON_2_MASK (1<<BSP_BUTTON_2)
//#define BUTTONS_MASK   0x00000100   // -> 8

/****************************** Motor control *********************************/
#define ENCODER_1		3	/** Connect to  Encoder */
#define ENCODER_2		2	/** Connect to  Encoder */

#define DRV_SLEEP		28	/** Turn off DRV8837 */
#define DRV_IN1			25	/** Drv's PWM input */
#define DRV_IN2			24	/** Drv's PWM input */

/******************************* UART *****************************************/
#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  26
#define HWFC           false

#define VBAT_SEN		1	/** ADC <--- Voltage sensing */

// Low frequency clock source to be used by the SoftDevice
#define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM

#endif // DEVBOARD_H
