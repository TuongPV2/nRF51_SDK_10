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

/** @file
 * @defgroup uart_example_main main.c
 * @{
 * @ingroup uart_example
 * @brief UART Example Application main file.
 *
 * This file contains the source code for a sample application using UART.
 * 
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "boards.h"
#include "nrf.h"
#include "nrf_drv_config.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "app_uart.h"
#include "app_twi.h"
#include "app_error.h"
#include "bsp.h"
#include "CAP1114.h"

#define UART_TX_BUF_SIZE 256    /** UART TX buffer size. */
#define UART_RX_BUF_SIZE 1      /** UART RX buffer size. */

/**
 *  @ Global variables
 */
/** Data structure: [0] Register, [1] Data */


uint32_t i_am = 0;

static volatile bool mode_status;

/* Indicates if reading operation from accelerometer has ended. */
static volatile bool m_xfer_done = true;
/* Indicates if setting mode operation has ended. */
//static volatile bool m_set_mode_done;

static const nrf_drv_twi_t m_twi_hmc5883 = NRF_DRV_TWI_INSTANCE(I2C_ID);

void debugconsole_events_handler(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

/**
 * @brief Debug console initialization.
 */
void debug_console_init(void)
{
    uint32_t err_code;
    const app_uart_comm_params_t comm_params =
    {
        RX_PIN_NUMBER,
        TX_PIN_NUMBER,
        NULL,
        NULL,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        UART_BAUDRATE_BAUDRATE_Baud115200
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       debugconsole_events_handler,
                       APP_IRQ_PRIORITY_LOW,
                       err_code);

    APP_ERROR_CHECK(err_code);    
}

/**
 * @brief HMC5883L events handler.
 */
void hmc5883_events_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{   
    //static sample_t m_sample;
    
    switch(p_event->type)
    {
        case NRF_DRV_TWI_RX_DONE:
            m_xfer_done = true;
            break;

        case NRF_DRV_TWI_TX_DONE:
            mode_status = true;
            break;
        default:
            break;        
    }   
}


/**
 *  @ hmc5883_twi handler
 */
void hmc5883_twi_init(void)
{
    ret_code_t err_code;
    
    const nrf_drv_twi_config_t hmc5883_config = {
       .scl                = I2C_CLK,
       .sda                = I2C_DATA,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH
    };
    
    err_code = nrf_drv_twi_init(&m_twi_hmc5883, &hmc5883_config, hmc5883_events_handler, NULL);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_twi_enable(&m_twi_hmc5883);
}

/**
 * @brief Function for writing data to a sensor.
 *
 * Transmission will be stopped when error or time-out occurs.
 *
 * @param[in] sensor_Addr     Address of a specific slave device (only 7 LSB).
 * @param[in] p_Data          Pointer to a receive buffer.
 * @param[in] length          Number of bytes to be received.
 * @param[in] flag            After a specified number of bytes, transmission will 
 *                            be suspended (if flag is set) or stopped (if not).
 * @retval 
 */
uint32_t sensorBSP_write(uint8_t sensor_Addr, uint8_t* p_Data, uint32_t length, bool flag)
{
    ret_code_t err_code;
    
    err_code = nrf_drv_twi_tx(&m_twi_hmc5883, sensor_Addr, p_Data, length, flag);
    APP_ERROR_CHECK(err_code);

    return err_code;
}

/**
 * @brief Function for reading data from a sensor.
 *
 * Transmission will be stopped when error or time-out occurs.
 *
 * @param[in] sensor_Addr     Address of a specific slave device (only 7 LSB).
 * @param[in] p_Data          Pointer to a receive buffer.
 * @param[in] length          Number of bytes to be received.
 * @param[in] flag            After a specified number of bytes, transmission will 
 *                            be suspended (if flag is set) or stopped (if not).
 */
uint32_t sensorBSP_read(uint8_t sensor_Addr, uint8_t sensor_Reg, 
                        uint8_t* p_Data, uint32_t length, bool flag)
{
    ret_code_t err_code;
    //uint32_t length = 1;
    err_code = sensorBSP_write(sensor_Addr, &sensor_Reg, 1U, flag);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_twi_rx(&m_twi_hmc5883, sensor_Addr, p_Data, length, flag);
    APP_ERROR_CHECK(err_code);

    return err_code;
}

/**
 * @brief   Test TWI communication and Slave
 * @param[in] reg : slave's register adrress
 *
 * Note because of nrf_drv_twi_tx and nrf_drv_twi_rx @param[*pdata]'s type is uint8_t
 * so only read the register form 0 to 127
 */
uint32_t who_am_i(uint8_t reg)
{
    ret_code_t err_code;
    uint8_t value;
    uint8_t addr8 =  reg;  // = HMC5883L_ID_A;
    //addr8 = reg;

    err_code = nrf_drv_twi_tx(&m_twi_hmc5883, CAP1114_ADDR, &addr8, 1, true);

    if (NRF_SUCCESS == err_code)
        err_code = nrf_drv_twi_rx(&m_twi_hmc5883, CAP1114_ADDR, &value, 1, true);
    APP_ERROR_CHECK(err_code);
	return value;
}

/**
 * @brief Function for main application entry.
 */
int main(void)
{

    debug_console_init();

    printf("\n\rThis is DEBUG CONSOLE\n\r");
	nrf_gpio_cfg_output(I2C_RST);
    nrf_gpio_pin_set(I2C_RST);
	
    hmc5883_twi_init();
    nrf_delay_ms(10);
	
    nrf_gpio_pin_clear(I2C_RST);
    nrf_delay_ms(1);

	i_am = who_am_i(CAP1114_ID);
    
    while(true)
    {
        nrf_delay_ms(100);
        
        __WFE();
    }

}


/** @} */
