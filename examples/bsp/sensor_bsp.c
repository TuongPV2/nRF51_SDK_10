/*  
 *	BSP for smartlock platform
 * 	Pham Van Tuong
 *  phamtuongbk999[at]gmail[dot]com
 *  7th Feb, 2016
 *	V1.0
 */

#include <stdbool.h>
#include <stdint.h>
#include "HMC5883L.h"
#include "TMP75B.h"
#include "devboard.h"
#include "twi_master.h"
#include "sensor_bsp.h"
#include "app_error.h"
 
uint8_t sensorBSP_addr(uint8_t addr_7bit)
{
	return (uint8_t)(addr_7bit << 1);
}

bool sensorBSP_init(void)
{
    ret_code_t err_code;
    
    const nrf_drv_twi_config_t hmc5883_config = {
       .scl                = I2C0_CLK,
       .sda                = I2C0_DATA,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH
    };
    
    err_code = nrf_drv_twi_init(&m_twi_hmc5883, &hmc5883_config, hmc5883_events_handler, NULL);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_twi_enable(&m_twi_hmc5883);
}



bool sensorBSP_register_write(uint8_t device_addr, uint8_t reg_addr, const uint8_t value)
{
    uint8_t w2_data[2];

    w2_data[0] = register_address;
    w2_data[1] = value;
    return nrf_drv_twi_tx(sensorBSP_addr(device_addr), w2_data, 2, TWI_ISSUE_STOP);
}

bool sensorBSP_register_read(uint8_t register_address, uint8_t *destination, uint8_t number_of_bytes);

bool sensorBSP_verify_product_id(void);