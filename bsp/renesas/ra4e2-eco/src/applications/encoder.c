#include "hal_data.h"
#include <stdint.h>
#include <rtthread.h>

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

// 编码器状态变量
volatile int32_t encoder_count = 0;
volatile int32_t encoder_count_old = 0;
volatile uint8_t last_encoder_state = 0;

// A 相中断回调函数
void encoder_a_callback(external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

    //  rt_kprintf("last_encoder_state: %d\n", last_encoder_state);
    
    // 读取当前 A/B 相状态
    bsp_io_level_t level_a;
    bsp_io_level_t level_b;
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, &level_a);
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_02, &level_b);
    uint8_t current_state = (level_a << 1) | level_b;

    // rt_kprintf("current_state: %d\n", current_state);
    
    // 根据状态变化判断旋转方向
    if ((last_encoder_state == 0b00 && current_state == 0b01) ||
        (last_encoder_state == 0b01 && current_state == 0b11) ||
        (last_encoder_state == 0b11 && current_state == 0b10) ||
        (last_encoder_state == 0b10 && current_state == 0b00)) {
        encoder_count++;  // 顺时针
    } else {
        encoder_count--;  // 逆时针
    }
    
    last_encoder_state = current_state;
}

// B 相中断回调函数
void encoder_b_callback(external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    
    // 读取当前 A/B 相状态
    bsp_io_level_t level_a;
    bsp_io_level_t level_b;

    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, &level_a);
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_02, &level_b);
    uint8_t current_state = (level_a << 1) | level_b;
    
    // 根据状态变化判断旋转方向
    if ((last_encoder_state == 0b00 && current_state == 0b10) ||
        (last_encoder_state == 0b10 && current_state == 0b11) ||
        (last_encoder_state == 0b11 && current_state == 0b01) ||
        (last_encoder_state == 0b01 && current_state == 0b00)) {
        encoder_count--;  // 逆时针
    } else {
        encoder_count++;  // 顺时针
    }
    
    last_encoder_state = current_state;
}

// 主函数中初始化编码器
void encoder_init(void)
{
    /* 初始化 A/B 相外部中断 */
    R_ICU_ExternalIrqOpen(&g_external_irq1_ctrl, &g_external_irq1_cfg);
    R_ICU_ExternalIrqEnable(&g_external_irq1_ctrl);
    R_ICU_ExternalIrqOpen(&g_external_irq5_ctrl, &g_external_irq5_cfg);
    R_ICU_ExternalIrqEnable(&g_external_irq5_ctrl);
    // R_ICU_ExternalIrqOpen(&g_external_irq3_ctrl, &g_external_irq3_cfg);
    // R_ICU_ExternalIrqEnable(&g_external_irq3_ctrl);

    /* 初始化 GPIO（包括中断管脚方向和属性） */
    R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);

    // 读取初始状态
    bsp_io_level_t level_a;
    bsp_io_level_t level_b;
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, &level_a);
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_02, &level_b);
    last_encoder_state = (level_a << 1) | level_b;
}

// 读取编码器按键状态
bool encoder_button_pressed(void)
{
    bsp_io_level_t level;
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_12, &level);
    return (level == BSP_IO_LEVEL_HIGH);  // 低电平表示按键按下
}

static void thread1_entry(void *param)
{
    
    /* 初始化编码器 */
    encoder_init();

    /* 主循环 */
    while (1)
        {
        /* 处理编码器计数 */
        if (encoder_count != encoder_count_old)
        {
            // 处理旋转事件
            rt_kprintf("Encoder count: %ld\n", encoder_count);
            encoder_count_old = encoder_count;
        }
        
        // /* 检测按键 */
        if (encoder_button_pressed())
        {
            // 处理按键按下事件
            rt_kprintf("Encoder button pressed!\n");
            
            // 消抖处理
            // R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);
            // while (encoder_button_pressed());
            // R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);
        }
        
        /* 低功耗延时 */
        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

static rt_thread_t tid1 = RT_NULL;
void encoder_sample(void)
{
    tid1 = rt_thread_create("thread1",
                            thread1_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
}


MSH_CMD_EXPORT(encoder_sample, encoder sample);
