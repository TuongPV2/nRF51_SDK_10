/*  Copyright (c) 
 *	TMP75B registers
 *	BSP for smartlock platform
 * 	Pham Van Tuong
 *  phamtuongbk999[at]gmail[dot]com
 *  29th Jan, 2016
 *	V1.0
 */

/** 	Convertion guide
*To convert positive temperatures to a digital data format:
*	1. Divide the temperature by the resolution
*	2. Then, convert the result to binary code with a 12-bit, left-justified 
*		format and MSB = 0 to denote a positive sign
*	Example: (+50°C) / (0.0625°C / LSB) = 800 = 320h = 0011 0010 0000
********************************************************************************
*To convert a positive digital data format to temperature:
*	1. Convert the 12-bit, left-justified binary temperature result, 
*		with the MSB = 0 to a decimal number
*	2. Then, multiply the decimal number by the resolution to obtain 
*		the positive temperature
*	Example: 0011 0010 0000 = 320h = 800 × (0.0625°C / LSB) = +50°C
********************************************************************************
*To convert negative temperatures to a digital data format:
*	1. Divide the absolute value of the temperature by the resolution
*	2. Convert the result to binary code with a 12-bit, left-justified format
*	3. Then, generate the 2's complement of the result 
*	Example: (|–25°C|) / (0.0625°C / LSB) = 400 = 190h = 0001 1001 0000
*	2's complement: 1110 0110 1111 + 1 = 1110 0111 0000
********************************************************************************
*To convert a negative digital data format to temperature:
*	1. Generate the twos compliment of the 12-bit, left-justified binary number 
*	of the temperature result by complementing the binary number and adding one
*	2. Convert to decimal number and multiply by the resolution 
*		to get the absolute temperature
*	3. then multiply by –1 for the negative sign
*	Example: 1110 0111 0000 has 2's compliment of 0001 1001 0000 = 0001 1000 1111 + 1
*	Convert to temperature: 0001 1001 0000 = 190h = 400;
*		400 × (0.0625°C / LSB) = 25°C = (|–25°C|);
*		(|–25°C|) × (–1) = –25°C
*
*/

/**	Serial Bus Address
*	| A2	| A1	| A0	| Address |
*	| GND	| GND	| GND	| 1001000 |	0x48
*	| GND	| GND	| Vss	| 1001001 | 0x49
*	| GND	| Vss	| GND	| 1001010 | 0x4A
*	| GND	| Vss	| Vss	| 1001011 | 0x4B
*	| Vss	| GND	| GND	| 1001100 |	0x4C
*	| Vss	| GND	| Vss	| 1001101 | 0x4D
*	| Vss	| Vss	| GND	| 1001110 |
*	| Vss	| Vss	| Vss	| 1001111 |
*/


#ifndef TMP75B_H
#define TMP75B_H

#define TMP75B_ADDRESS            0x4C // this device only has one address

/** TMP75B Register map */
#define TMP75B_TEMP				0
#define TMP75B_CFG				0x01
#define TMP75B_TEMP_L_LIMIT		0x02
#define TMP75B_TEMP_H_LIMIT		0x03

/** Configuration Register Description 
OS 		One-shot mode
		In shutdown (SD = 1), write 1 to start a conversion. OS always reads back 0.
		CR 		Conversion rate control
		CR = 0h: 37-Hz conversion rate (typ) (default)
		CR = 1h: 18-Hz conversion rate (typ)
		CR = 2h: 9-Hz conversion rate (typ)
		CR = 3h: 4-Hz conversion rate (typ)
FQ 		Fault queue to trigger the ALERT pin
		FQ = 0h: 1 fault (default)
		FQ = 1h: 2 faults
		FQ = 2h: 4 faults
		FQ = 3h: 6 faults
POL 		ALERT polarity control
		POL = 0: ALERT is active low (default)
		POL = 1: ALERT is active high
TM 		ALERT thermostat mode control
		TM = 0: ALERT is in comparator mode (default)
		TM = 1: ALERT is in interrupt mode
SD 		Shutdown control bit
		SD = 0: Device is in continuous conversion mode (default)
		SD = 1: Device is in shutdown mode
*/
#define TMP75B_CFG_OS			15		
#define TMP75B_CFG_CR_H			14
#define TMP75B_CFG_CR_L			13
#define TMP75B_CFG_FQ_H			12
#define TMP75B_CFG_FQ_L			11
#define TMP75B_CFG_POL			10
#define TMP75B_CFG_TM			9
#define TMP75B_CFG_SD			8

#endif /* TMP75B_H */