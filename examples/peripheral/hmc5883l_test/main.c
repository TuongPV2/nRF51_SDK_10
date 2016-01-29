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

#define NUMBER_OF_SAMPLES 20    /** Max = 255 */
/**
 *  @ Global variables
 */
/**
 * @brief Structure for holding sum of samples from accelerometer.
 */
// typedef struct
// {
//     int16_t x;
//     int16_t y;
//     int16_t z;
// } sum_t;
// static sum_t m_sum = {0};

/**
 * @brief Union to keep raw and converted data from accelerometer samples at one memory space.
 */
// typedef union{
//     uint8_t raw;
//     int8_t  conv;
// } elem_t;

/**
 * @brief Enum for selecting accelerometer orientation.
 */
// typedef enum{
//     LEFT = 1,
//     RIGHT = 2,
//     DOWN = 5,
//     UP = 6
// } accelerometer_orientation_t;

/**
 * @brief Structure for holding samples from accelerometer.
 */
typedef struct
{
    uint8_t  x;
    uint8_t  y;
    uint8_t  z;
    //uint8_t tilt;
} sample_t;


/* Buffer for samples. */
//static sample_t m_sample_buffer[NUMBER_OF_SAMPLES] = {0};

/* Indicates if reading operation from accelerometer has ended. */
static volatile bool m_xfer_done = true;
/* Indicates if setting mode operation has ended. */
//static volatile bool m_set_mode_done;

static const nrf_drv_twi_t m_twi_hmc5883 = NRF_DRV_TWI_INSTANCE(0);

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
 * @brief Function for averaging samples from accelerometer.
 */
// void read_data(sample_t * p_new_sample)
// {
//     /* Variable to count samples. */
//     static uint8_t sample_idx;
//     static uint8_t prev_tilt;
    
//     sample_t * p_sample = &m_sample_buffer[sample_idx];
    
//     /* Subtracting oldest sample. */
//     m_sum.x    -= p_sample->x.conv;
//     m_sum.y    -= p_sample->y.conv;
//     m_sum.z    -= p_sample->z.conv;
    
//     p_sample->tilt = p_new_sample->tilt;    
    
//     int_to_uint(&p_sample->x.conv, p_new_sample->x.raw);
//     int_to_uint(&p_sample->y.conv, p_new_sample->y.raw);
//     int_to_uint(&p_sample->z.conv, p_new_sample->z.raw);
    
//     /* Adding new sample. This way we always have defined number of samples. */
//     m_sum.x    += p_sample->x.conv;
//     m_sum.y    += p_sample->y.conv;
//     m_sum.z    += p_sample->z.conv;

//     ++sample_idx;
//     if (sample_idx >= NUMBER_OF_SAMPLES)
//     {
//         sample_idx = 0;
//     }

//     if (sample_idx == 0 || (prev_tilt && (prev_tilt != p_sample->tilt)))
//     {
//         char const * orientation;
//         switch ((p_sample->tilt >> 2) & 0x07)
//         {
//             case LEFT: 
//                 orientation = "LEFT";
//                 break;
//             case RIGHT:
//                 orientation = "RIGHT"; 
//                 break;
//             case DOWN:             
//                 orientation = "DOWN";  
//                 break;
//             case UP:
//                 orientation = "UP";    
//                 break;
//             default: 
//                 orientation = "?";     
//                 break;
//         }
//         printf("X: %3d, Y: %3d, Z: %3d | %s%s%s\r\n",
//                 m_sum.x / NUMBER_OF_SAMPLES,
//                 m_sum.y / NUMBER_OF_SAMPLES,
//                 m_sum.z / NUMBER_OF_SAMPLES,
//                 orientation,
//                 (p_sample->tilt & TILT_TAP_MASK) ? " TAP"   : "",
//                 (p_sample->tilt & TILT_SHAKE_MASK) ? " SHAKE" : "");
//                 prev_tilt = p_sample->tilt;
//     }
// }

/**
 * @brief 
 */
// void hmc5883_set_mode(void)
// {
//     ret_code_t err_code;
//     /* Writing to MMA7660_REG_MODE "1" enables the accelerometer. */
//     uint8_t reg[2] = {MMA7660_REG_MODE, ACTIVE_MODE};

//     err_code = nrf_drv_twi_tx(&m_twi_mma_7660, MMA7660_ADDR, reg, sizeof(reg), false);  
//     APP_ERROR_CHECK(err_code);
    
//     while(m_set_mode_done == false);
// }

/**
 * @brief HMC5883L events handler.
 */
void hmc5883_events_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{   
    ret_code_t err_code;
    static sample_t m_sample;
    
    switch(p_event->type)
    {
        case NRF_DRV_TWI_RX_DONE:
            //read_data(&m_sample);
            printf("X:%d \n\r", m_sample.x);
            printf("Y:%d \n\r", m_sample.y);
            printf("Z:%d \n\r", m_sample.z);
            m_xfer_done = true;
            break;
        case NRF_DRV_TWI_TX_DONE:
            m_xfer_done = false;
            /* Read 4 bytes from the specified address. */
            err_code = nrf_drv_twi_rx(&m_twi_hmc5883, HMC5883L_ADDRESS, (uint8_t*)&m_sample, sizeof(m_sample), false);
            APP_ERROR_CHECK(err_code);
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
       .scl                = I2C0_CLK,
       .sda                = I2C0_DATA,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH
    };
    
    err_code = nrf_drv_twi_init(&m_twi_hmc5883, &hmc5883_config, hmc5883_events_handler, NULL);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_twi_enable(&m_twi_hmc5883);
}


/**
 * @brief Function for main application entry.
 */
int main(void)
{
    LEDS_CONFIGURE(LEDS_MASK);
    LEDS_OFF(LEDS_MASK);

    debug_console_init();

    printf("\n\rThis is DEBUG CONSOLE\n\r");
    
    hmc5883_twi_init();

    uint8_t reg = 0;
    ret_code_t err_code;

    while (true)
    {
        nrf_delay_ms(100);
        /* Start transaction with a slave with the specified address. */
        do
        {
            /* code */
            __WFE();
        } while (m_xfer_done == false);
        err_code = nrf_drv_twi_tx(&m_twi_hmc5883, HMC5883L_ADDRESS, &reg, sizeof(reg), true);
        APP_ERROR_CHECK(err_code);
        m_xfer_done = false;
    }

}


/** @} */
