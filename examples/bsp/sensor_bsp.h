/*  
 *	BSP for smartlock platform
 * 	Pham Van Tuong
 *  phamtuongbk999[at]gmail[dot]com
 *  7th Jan, 2016
 *	V1.0
 */

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Convert 7-bit device address to 8-bit addressing
 * @param[in] The 7-bit device address
 * @return The 8-bit address 
 */
uint8_t sensorBSP_addr(uint8_t addr_7bit);
/**
 * @brief Function for initializing Sensor and verifies it's on the bus.
 * @param[in] device_address Device TWI addess in bits [6:0].
 * @return 
 * @retval true if Sensor found on the bus and ready for operation.
 * @retval false if Sensor not found on the bus or communicatuon failure.
 */
bool sensorBSP_init(uint8_t device_address);

/**
 * @brief Function for writing a Sensor register contents over TWI.
 * @param[in] register_address Register address to start writing to. Find the alias 
 * 				in TMP75B.h, HMC5883L.h
 * @param[in] value Value to write to register
 * @retval true Register write succeeded
 * @retval false Register write failed
*/

bool sensorBSP_register_write(uint8_t device_addr, uint8_t reg_addr, const uint8_t value);
/**
 * @brief Function for reading Sensor register contents over TWI.
 * Reads one or more consecutive registers.
 * @param[in]  register_address Register address to start reading from. Find the alias 
 * 				in TMP75B.h, HMC5883L.h
 * @param[in]  number_of_bytes Number of bytes to read
 * @param[out] destination Pointer to a data buffer where read data will be stored
 * @retval true Register read succeeded
 * @retval false Register read failed
*/
bool sensorBSP_register_read(uint8_t register_address, uint8_t *destination, uint8_t number_of_bytes);

/**
  @brief Function for reading and verifying Sensor product ID.
  @retval true Product ID is what was expected
  @retval false Product ID was not what was expected
*/
bool sensorBSP_verify_product_id(void);