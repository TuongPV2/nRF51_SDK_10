/*  Copyright (c) 2011 Jeff Rowberg
 *	HMC5883L registers
 *	BSP for smartlock platform
 * 	Pham Van Tuong
 *  phamtuongbk999[at]gmail[dot]com
 *  29th Jan, 2016
 *	V1.0
 */

#ifndef HMC5883L_H
#define HMC5883L_H

#define HMC5883L_ADDRESS      0x1E

/**
 *	HMC5883L register map
 */
#define HMC5883L_CFG_A        0x00
#define HMC5883L_CFG_B        0x01
#define HMC5883L_MODE         0x02
#define HMC5883L_DATA_X_H     0x03
#define HMC5883L_DATA_X_L     0x04
#define HMC5883L_DATA_Z_H     0x05
#define HMC5883L_DATA_Z_L     0x06
#define HMC5883L_DATA_Y_H     0x07
#define HMC5883L_DATA_Y_L     0x08
#define HMC5883L_STATUS       0x09
#define HMC5883L_ID_A         0x0A	/* These register is read only */
#define HMC5883L_ID_B         0x0B
#define HMC5883L_ID_C         0x0C

/**
 * @ Configuration Register A
 *	Default value: 0x10
 *	CRA7  CRA6  CRA5  CRA4  CRA3  CRA2  CRA1  CRA0
 *	CRA7  MA1	MA0	  DO2	DO1   DO0	MS1	  MS0
 *******************************************************************************
 *	MA1 to MA0 :Select number of samples averaged (1 to 8) per measurement output.
 *	00 = 1 (default)
 *	01 = 2
 *	10 = 4
 *	11 = 8
 *******************************************************************************
 *	DO2 to DO0: Data Output Rate Bits
 *	| DO2 | DO1 | DO0 | Typical Data Output Rate (Hz)
 *	| 0   |	0  	| 0   | 0.75
 *	| 0   |	0  	| 1   | 1.5
 *	| 0   |	1  	| 0   | 3
 *	| 0   |	1  	| 1   | 7.5
 *	| 1   |	0  	| 0   | 15 (default)
 *	| 1   |	0  	| 1   | 30
 *	| 1   |	1  	| 0   | 75
 *	| 1   |	1  	| 1   | Reserved
 *******************************************************************************
 *	MS1 to MS0: Measurement Mode
 *	00 - Normal measurement configuration (default)
 *	01 - Positive bias configuration for X, Y, and Z axes
 *	10 - Negative bias configuration for X, Y and Z axes
 *	11 - reserved.
 */
#define HMC5883L_CFG_A_AVERAGE_BIT    6
#define HMC5883L_CFG_A_AVERAGE_LENGTH 2
#define HMC5883L_CFG_A_RATE_BIT       4
#define HMC5883L_CFG_A_RATE_LENGTH    3
#define HMC5883L_CFG_A_BIAS_BIT       1
#define HMC5883L_CFG_A_BIAS_LENGTH    2

#define HMC5883L_CFG_A_AVERAGING_1    0x00
#define HMC5883L_CFG_A_AVERAGING_2    0x01
#define HMC5883L_CFG_A_AVERAGING_4    0x02
#define HMC5883L_CFG_A_AVERAGING_8    0x03


#define HMC5883L_CFG_A_RATE_0P75      0x00
#define HMC5883L_CFG_A_RATE_1P5       0x01
#define HMC5883L_CFG_A_RATE_3         0x02
#define HMC5883L_CFG_A_RATE_7P5       0x03
#define HMC5883L_CFG_A_RATE_15        0x04
#define HMC5883L_CFG_A_RATE_30        0x05
#define HMC5883L_CFG_A_RATE_75        0x06
 
#define HMC5883L_CFG_A_NORMAL         0x00
#define HMC5883L_CFG_A_POSITIVE       0x01
#define HMC5883L_CFG_A_NEGATIVE       0x02
 
/**
 * @ Configuration Register B
 *	Default value: 0x20
 *	CRB7  CRB6  CRB5  CRB4  CRB3  CRB2  CRB1  CRB0
 *	GN2   GN1	GN0	   0	  0		0	 0	  	0
 *******************************************************************************
 *	GN2 to GN0: Gain Configuration Bits
 *	CRB4 to CRB0  0  These bits must be cleared for correct operation
 *	For more detail, see p12 datasheet
 */
#define HMC5883L_CFG_BGAIN_BIT      7
#define HMC5883L_CFG_BGAIN_LENGTH   3

#define HMC5883L_CFG_B_GAIN_1370    0x00
#define HMC5883L_CFG_B_GAIN_1090    0x01
#define HMC5883L_CFG_B_GAIN_820     0x02
#define HMC5883L_CFG_B_GAIN_660     0x03
#define HMC5883L_CFG_B_GAIN_440     0x04
#define HMC5883L_CFG_B_GAIN_390     0x05
#define HMC5883L_CFG_B_GAIN_330     0x06
#define HMC5883L_CFG_B_GAIN_220     0x07

/**
 * @ Mode Register
 * Default value: 0x01
 * MR7	 MR6  MR5  MR4  MR3  MR2   MR1    MR0
 * HS(0) (0)  (0)  (0)  (0)  (0)  MD1(0)  MD0(1)
 *******************************************************************************
 * HS: Set this pin to enable High Speed I2C, 3400kHz.
 * MR1 to MR0 Mode select bits
 * | MD1 | MD0 | Operating mode
 * |  0  |  0  | Continuous-Measurement Mode
 * |  0  |  1  | Single-Measurement Mode (Default)
 * |  1  |  1  | Idle Mode. Device is placed in idle mode.
 * |  1  |  1  | Idle Mode. Device is placed in idle mode.
 *******************************************************************************
 * - Continuous-Measurement Mode: the device continuously performs measurements 
 * and places the result in the data register.
 * RDY goes high when new data is placed in all three registers.
 * - Single-Measurement Mode: device performs a single measurement, sets RDY 
 * high and returned to idle mode
 */
#define HMC5883L_MODEREG_BIT        1
#define HMC5883L_MODEREG_LENGTH     2

#define HMC5883L_MODE_CONTINUOUS    0x00
#define HMC5883L_MODE_SINGLE        0x01
#define HMC5883L_MODE_IDLE          0x02


/**
 * @ Status Register
 * Default value : 0
 * SR7  SR6  SR5  SR4  SR3   SR2  SR1      SR0
 * (0)  (0)  (0)  (0)  (0)   (0)  LOCK(0)  RDY(0
 *******************************************************************************
 * SR1 - LOCK: Data output register lock
 * SR0 - RDY : Ready Bit
 *				Set when data is written to all six data registers
 *				Cleared when device initiates a write to the data output...
 * For more detail, see p.16 datasheet
 */
#define HMC5883L_STATUS_LOCK_BIT    1
#define HMC5883L_STATUS_READY_BIT   0

/** 
 * @ Identification Register A
 * The identification register A is used to identify the device
 * Register values: 0x48 ('H')
 * @ Identification Register B
 * The identification register B is used to identify the device
 * Register values: 0x04
 * @ Identification Register C
 * The identification register C is used to identify the device
 * Register values: 0x03

 */

#endif /* HMC5883L_H */