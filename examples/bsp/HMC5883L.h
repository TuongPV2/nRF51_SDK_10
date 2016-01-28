/*  
 *	HMC5883L.h
 *	HMC5883L registers
 * 	
 *  Tuong Pham
 *  phamtuongbk999[at]gmail[dot]com
 *  
 */
#ifndef HMC5883_H
#define HMC5883_H

#define HMC5883_W	0x3C
#define HMC5883_R	0x3D

enum HMC5883L {
	HMC_CFG_REG_A = 0,	// 0,R/W
	HMC_CFG_REG_B,		// 1,R/W
	HMC_MODE,			// 2,R/W
	HMC_DATA_OUT_X_MSB,	// 3,Data Output X MSB Register | Read 
	HMC_DATA_OUT_X_LSB,	// 4,Data Output X LSB Register | Read 
	HMC_DATA_OUT_Z_MSB,	// 5,Data Output Z MSB Register | Read
	HMC_DATA_OUT_Z_LSB,	// 6,Data Output Z LSB Register | Read
	HMC_DATA_OUT_Y_MSB,	// 7,Data Output Y MSB Register | Read
	HMC_DATA_OUT_Y_LSB,	// 8,Data Output Y LSB Register | Read
	HMC_STATUS,			// 9,Status Register | Read
	IDENT_REG_A,		//10,Identification Register A  | Read
	IDENT_REG_B,		//11,Identification Register B  | Read
	IDENT_REG_C			//12,Identification Register C  | Read
};

/* Output rate */
#define OR_0075			0x00<<2
#define OR_0150			0x01<<2
#define OR_0300			0x02<<2
#define OR_0750			0x03<<2
#define OR_1500			0x04<<2
#define OR_3000			0x05<<2
#define OR_7500			0x06<<2
#define OR_RES 			0x07<<2

/* Measurement mode */
#define MM_NORMAL 		0x00
#define MM_POS    		0x01
#define MM_NEG    		0x02
#define MM_RES    		0x03

/* Gain */
#define GN_1370 		0x00<<5
#define GN_1090 		0x01<<5
#define GN_820  		0x02<<5
#define GN_660  		0x03<<5
#define GN_440  		0x04<<5
#define GN_390  		0x05<<5
#define GN_330  		0x06<<5
#define GN_230  		0x07<<5

/* Operation mode */
#define HIGH_SPEED      0x80
#define MD_CONTINOUS    0x00
#define MD_SINGLE       0x01
#define MD_IDLE         0x03


#endif
