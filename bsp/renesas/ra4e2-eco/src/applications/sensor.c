/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-10     Sherman       first version
 */

#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>
#include <rtthread.h>
#include "hal_data.h"

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

#define LED2_PIN    BSP_IO_PORT_01_PIN_13 /* Onboard LED pins */
#define INT1_PIN    BSP_IO_PORT_02_PIN_12

void g_external_irq3_callback(external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    rt_pin_write(LED2_PIN, !rt_pin_read(INT1_PIN));
}

void sensor_sample(void)
{
    R_ICU_ExternalIrqOpen(&g_external_irq3_ctrl, &g_external_irq3_cfg);
    R_ICU_ExternalIrqEnable(&g_external_irq3_ctrl);
}

MSH_CMD_EXPORT(sensor_sample, sensor sample);
