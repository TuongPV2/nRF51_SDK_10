/*
The MIT License (MIT)

Copyright (c) 2016 Tuong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*  
 *	CAP1114 registers
 *	BSP for smartlock platform
 * 	Pham Van Tuong
 *  phamtuongbk999[at]gmail[dot]com
 *  01 Feb, 2016
 *	V1.0
 */
 #ifndef CAP1114_H
 #define CAP1114_H

 #define CAP1114_ADDR		0x28	/** 7-bit address */

 #define CAP1114_CS			0x00	/** Main Status Control */
 #define BUTTON_S_1			0x03	/** Button status 1	*/
 #define BUTTON_S_2			0x04	/** Button status 2	*/
 #define BUILD_REV			0x05	/** Build revision */
 //#define SLIDER_POS 		0x06	/** Slider Position or Volumetric Data */
 #define CAP1114_ID			0x08	/** CAP1114 vendor ID */
 //#define VOL_STEP			0x09	/** Volumetric Step */
 //#define NOISE_S_1			0x0A	/** Noise status 1*/
 //#define NOISE_S_2			0x0B	/** Noise status 2*/
 // #define LID_CLOSURE_S_1	0x0C	/** Lid Closure Status 1 */
 // #define LID_CLOSURE_S_2	0x0D	/** Lid Closure Status 2 */
 #define GPIO_STATUS		0x0E	/** GPIO Status */
 #define GROUP_STATUS		0x0F	/** Group Status */
 #define SENSOR_1_DELC		0x10	/** Stores the delta count for CS1 */
 #define SENSOR_2_DELC		0x11	/** Stores the delta count for CS2 */
 #define SENSOR_3_DELC		0x12	/** Stores the delta count for CS3 */
 #define SENSOR_4_DELC		0x13	/** Stores the delta count for CS4 */
 #define SENSOR_5_DELC		0x14	/** Stores the delta count for CS5 */
 #define SENSOR_6_DELC		0x15	/** Stores the delta count for CS6 */
 #define SENSOR_7_DELC		0x16	/** Stores the delta count for CS7 */
 #define SENSOR_8_DELC		0x17	/** Stores the delta count for CS8 */
 #define SENSOR_9_DELC		0x18	/** Stores the delta count for CS9 */
 #define SENSOR_10_DELC		0x19	/** Stores the delta count for CS10 */
 #define SENSOR_11_DELC		0x1A	/** Stores the delta count for CS11 */
 #define SENSOR_12_DELC		0x1B	/** Stores the delta count for CS12 */
 #define SENSOR_13_DELC		0x1C	/** Stores the delta count for CS13 */
 #define SENSOR_14_DELC		0x1D	/** Stores the delta count for CS14 */
 #define QUEUE_CTRL			0x1E	/** Controls how many samples must exceed */
 #define SENSITIVITY		0x1F	/** Controls the sensitivity of the threshold and delta counts */
 #define CONFIGURATION		0x20	/** Controls some recalibration and LED controls */
 #define SENSOR_EN			0x21	/** Controls whether the Capacitive Touch Sensor group and button */
 #define BUTTON_CFG			0x22	/** Controls reset delay and autorepeat delay for buttons */
 #define GROUP_CFG_1		0x23	/** Controls the detection dwell time */
 #define GROUP_CFG_2		0x24	/** Controls the detection dwell time */
 #define CALIB_EN			0x25	/** Calibration Enable */
 #define CALIB_ACTIVATE		0x26	/** Calibration Activate */
 #define INT_EN_1			0x27	/** Interrupt Enable 1 */
 #define INT_EN_2			0x28	/** Interrupt Enable 2 */
 #define SLEEP_CHN_CTRL		0x29	/** Sleep Channel Control */
 #define MULTI_PRESS_CFG	0x2A	/** Multi press configuration */
 #define LID_CLOSURE_CFG	0x2B	/** Controls Lid Closure detection and operation */
 #define LID_CLOSURE_CTRL	0x2C	/** Lid Closure Queue ctrl */
 #define LID_CLOSURE_PAT_1	0x2D	/** Lid Closure Pattern 1 */
 #define LID_CLOSURE_PAT_2	0x2E	/** Lid Closure Pattern 2 */
 #define RECALIBRATION_CFG	0x2F	/** Recalibration configuration */
 #define SENSOR_1_THRESH	0x30 	/** Sensor  1 Threshold */
 #define SENSOR_2_THRESH	0x31 	/** Sensor  2 Threshold */
 #define SENSOR_3_THRESH	0x32 	/** Sensor  3 Threshold */
 #define SENSOR_4_THRESH	0x33 	/** Sensor  4 Threshold */
 #define SENSOR_5_THRESH	0x34 	/** Sensor  5 Threshold */
 #define SENSOR_6_THRESH	0x35 	/** Sensor  6 Threshold */
 #define SENSOR_7_THRESH	0x36 	/** Sensor  7 Threshold */
 #define GROUP_THRES		0x37 	/** Group Threshold */

 #define LED_GPIO_DIR		0x70	/** LED / GPIO Direction */
 #define LED_GPIO_TYPE		0x71 	/** LED / GPIO Output */
 #define GPIO_INPUT			0x72 	/** GPIO Input */
 #define LED_OUT_CTRL_1		0x73 	/** LED Output Control 1 */
 #define LED_OUT_CTRL_2		0x74 	/** LED Output Control 2 */
 #define LED_POL_1			0x75 	/** LED Polarity 1 */
 #define LED_POL_2			0x76 	/** LED Polarity 2 */

 #define PROD_ID 			0xFD 	/** Product ID */
 #define MANUF_ID			0xFE	/** Manufacturer ID */
 #define REV_ID				0xFF 	/** Revision */

 



// enum {
// 	CAP1106,
// 	CAP1114,
// 	CAP1126,
// 	CAP1188,
// };


// struct cap11xx_hw_model {
// 	uint8_t product_id;
// 	uint32_t num_channels;
// };

// static const struct cap11xx_hw_model cap11xx_devices[] = {
// 	[CAP1106] = { .product_id = 0x55, .num_channels = 6 },
// 	[CAP1114] = { .product_id = 0x3a, .num_channels = 14 },	
// 	[CAP1126] = { .product_id = 0x53, .num_channels = 6 },
// 	[CAP1188] = { .product_id = 0x50, .num_channels = 8 },
// };





 #endif	/* CAP1114_H */

