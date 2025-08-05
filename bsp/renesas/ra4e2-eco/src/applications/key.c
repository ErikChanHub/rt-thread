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

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

#define LED2_PIN    BSP_IO_PORT_01_PIN_13 /* Onboard LED pins */
#define BTN1_PIN    BSP_IO_PORT_00_PIN_05
void key_thread_entry(void *param)
{
    while (1)
    {
        rt_pin_write(LED2_PIN, !rt_pin_read(BTN1_PIN));
    }
}

static rt_thread_t tid1 = RT_NULL;
void key_sample(void)
{
    tid1 = rt_thread_create("key_thread",
                            key_thread_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
}

MSH_CMD_EXPORT(key_sample, key sample);
