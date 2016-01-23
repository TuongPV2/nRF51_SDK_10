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

/********************************** BUTTONs ***********************************/
#define BUTTONS_NUMBER 2

#define BUTTON_START   19
#define BUTTON_1       19
//#define BUTTON_2       18
//#define BUTTON_3       19
//#define BUTTON_4       20
//#define BUTTON_STOP    20
//#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_LIST {BUTTON_1, BUTTON_2}

#define BSP_BUTTON_0   BUTTON_1
#define BSP_BUTTON_1   BUTTON_2
//#define BSP_BUTTON_2   BUTTON_3
//#define BSP_BUTTON_3   BUTTON_4

#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)
#define BSP_BUTTON_1_MASK (1<<BSP_BUTTON_1)
//#define BSP_BUTTON_2_MASK (1<<BSP_BUTTON_2)
//#define BSP_BUTTON_3_MASK (1<<BSP_BUTTON_3)

#define BUTTONS_MASK   0x001E0000   // -> 20.19.18.17
                                    // Need to changed to 19.18

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

/****************************** Cap. Touchs ***********************************/
#define CTOUCH_1		21	/** Read output of TTP223 */
#define CTOUCH_2		22	/** Read output of TTP223 */
#define CTOUCH_3		23	/** Read output of TTP223 */


#define VBAT_SEN		1	/** ADC <--- Voltage sensing */

// Low frequency clock source to be used by the SoftDevice
#define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM

#endif // DEVBOARD_H
