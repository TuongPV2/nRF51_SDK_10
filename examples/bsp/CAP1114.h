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
 ##ifndef CAP1114_H
 #define CAP1114_H

 #define CAP1114_CS			0x00	/** Main Status Control */
 #define BUTTON_S_1			0x03	/** Button status 1	*/
 #define BUTTON_S_2			0x04	/** Button status 2	*/
 #define BUILD_REV			0x05	/** Build revision */
 #define SLIDER_POS 		0x06	/** Slider Position or Volumetric Data */
 #define CAP1114_ID			0x08	/** CAP1114 vendor ID */
 #define VOL_STEP			0x09	/** Volumetric Step */
 #define NOISE_S_1			0x0A	/** Noise status 1*/
 #define NOISE_S_2			0x0B	/** Noise status 2*/
 #define LID_CLOSURE_S_1	0x0C	/** Lid Closure Status 1 */
 #define LID_CLOSURE_S_2	0x0D	/** Lid Closure Status 2 */
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
 


 #endif	/* CAP1114_H */

