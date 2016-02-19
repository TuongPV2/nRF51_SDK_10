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
#include "HMC5883L.h"

#define UART_TX_BUF_SIZE 256    /** UART TX buffer size. */
#define UART_RX_BUF_SIZE 1      /** UART RX buffer size. */

/**
 *  @ Global variables
 */
/** Data structure: [0] Register, [1] Data */
uint8_t cfg_a[2] = {HMC5883L_CFG_A, 0x70}; /* 8-average, 15 Hz default, normal measurement */
uint8_t cfg_b[2] = {HMC5883L_CFG_B, 0xA0}; /* Gain=5, or any other desired gain */


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

void set_mode(void)
{
	ret_code_t err_code;
    uint8_t cfg_mode[2] = {HMC5883L_MODE, 0x00}; /* Continuous-measurement mode */

    err_code = nrf_drv_twi_tx(&m_twi_hmc5883, HMC5883L_ADDRESS, cfg_mode, sizeof(cfg_mode), true);
	APP_ERROR_CHECK(err_code);
    //while(mode_status == false);
}


uint32_t who_am_i()
{
    ret_code_t err_code;
    uint8_t value;
    uint8_t addr8 = HMC5883L_ID_A;

    err_code = nrf_drv_twi_tx(&m_twi_hmc5883, HMC5883L_ADDRESS, &addr8, 1, true);

    if (NRF_SUCCESS == err_code)
        err_code = nrf_drv_twi_rx(&m_twi_hmc5883, HMC5883L_ADDRESS, &value, 1, true);
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
    
    hmc5883_twi_init();
    nrf_delay_ms(10);

	i_am = who_am_i();

    nrf_delay_ms(10);
    
    while(true)
    {
        nrf_delay_ms(100);
        
        __WFE();
    }

}


/** @} */
