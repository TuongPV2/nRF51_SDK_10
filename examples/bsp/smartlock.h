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
#ifndef SMARTLOCK_H
#define SMARTLOCK_H

/********************************* LEDs ***************************************/
#define LEDS_NUMBER    6

#define LED_START      29
#define LED_1          29
#define LED_2          4
#define LED_3          5
#define LED_4          6
#define LED_5          7
#define LED_6          16
#define LED_STOP       16

#define LEDS_LIST {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6}

#define BSP_LED_0      LED_1
#define BSP_LED_1      LED_2
#define BSP_LED_2      LED_3
#define BSP_LED_3      LED_4
#define BSP_LED_3      LED_5
#define BSP_LED_3      LED_6

#define BSP_LED_0_MASK (1<<BSP_LED_0)
#define BSP_LED_1_MASK (1<<BSP_LED_1)
#define BSP_LED_2_MASK (1<<BSP_LED_2)
#define BSP_LED_3_MASK (1<<BSP_LED_3)
#define BSP_LED_3_MASK (1<<BSP_LED_4)
#define BSP_LED_3_MASK (1<<BSP_LED_5)

#define LEDS_MASK      (BSP_LED_0_MASK | BSP_LED_1_MASK | BSP_LED_2_MASK | BSP_LED_3_MASK | BSP_LED_4_MASK | BSP_LED_5_MASK)
/* all LEDs are lit when GPIO is low */
#define LEDS_INV_MASK  LEDS_MASK

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

/******************************* UART *****************************************/
//#define RX_PIN_NUMBER  11
//#define TX_PIN_NUMBER  9
//#define CTS_PIN_NUMBER 10
//#define RTS_PIN_NUMBER 8
//#define HWFC           true
#define HWFC           false


/********************************** SPI0 **************************************/
#define NFC_SS_PIN  	12	/** EN.  */
#define NFC_SCK_PIN 	13	/** CLK  */
#define NFC_MOSI_PIN	14	/** MOSI */
#define NFC_MISO_PIN	15	/** MISO */

/******************************** I2C *****************************************/
#define I2C0_DATA		8 	/** SDA  */
#define I2C0_CLK		9 	/** SCL  */
#define I2C0_RST		10 	/** SCL  */
#define I2C0_ALERT		11 	/** SCL  */ 

/****************************** Motor control *********************************/
#define ENCODER_1		3	/** Connect to  Encoder */
#define ENCODER_2		2	/** Connect to  Encoder */

#define DRV_SLEEP		28	/** Turn off DRV8837 */
#define DRV_IN1			25	/** Drv's PWM input */
#define DRV_IN2			24	/** Drv's PWM input */


#define VBAT_SEN		1	/** ADC <--- Voltage sensing */

// Low frequency clock source to be used by the SoftDevice
#define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM

#endif // SMARTLOCK_H
