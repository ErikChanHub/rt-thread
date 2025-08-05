// #include <rtthread.h>
// #include <rtdevice.h>

// #define MPU_ADDR            0x68    /* AD0 拉低 */
// #define REG_WHO_AM_I        0x75
// #define REG_PWR_MGMT_1      0x6B
// #define REG_ACCEL_XOUT_H    0x3B

// static struct rt_i2c_bus_device *i2c_bus;

// /* I2C 写 1 字节 */
// static rt_err_t mpu_write_reg(rt_uint8_t reg, rt_uint8_t val)
// {
//     rt_uint8_t buf[2] = {reg, val};
//     struct rt_i2c_msg msg =
//     {
//         .addr  = MPU_ADDR,
//         .flags = RT_I2C_WR,
//         .buf   = buf,
//         .len   = 2,
//     };
//     return rt_i2c_transfer(i2c_bus, &msg, 1) == 1 ? RT_EOK : -RT_ERROR;
// }

// /* I2C 连续读 len 字节 */
// static rt_err_t mpu_read_bytes(rt_uint8_t reg, rt_uint8_t *data, rt_size_t len)
// {
//     struct rt_i2c_msg msgs[2] =
//     {
//         { .addr = MPU_ADDR, .flags = RT_I2C_WR, .buf = &reg, .len = 1 },
//         { .addr = MPU_ADDR, .flags = RT_I2C_RD, .buf =  data, .len = len},
//     };
//     return rt_i2c_transfer(i2c_bus, msgs, 2) == 2 ? RT_EOK : -RT_ERROR;
// }

// #include "sensor_inven_mpu6xxx.h"

// int mpu_demo(void)
// {
//     // i2c_bus = (struct rt_i2c_bus_device *)rt_device_find("i2c1");
//     // if (!i2c_bus)
//     // {
//     //     rt_kprintf("not find i2c1!\n");
//     //     return -RT_ERROR;
//     // }

//     // /* 唤醒 MPU6050 */
//     // mpu_write_reg(REG_PWR_MGMT_1, 0x00);
//     // rt_thread_mdelay(10);

//     // /* 读取芯片 ID */
//     // rt_uint8_t id = 0;
//     // mpu_read_bytes(REG_WHO_AM_I, &id, 1);
//     // rt_kprintf("WHO_AM_I = 0x%02X\n", id); /* 正常应为 0x68 */

//     // /* 连续读取加速度 */
//     // while (1)
//     // {
//     //     rt_uint8_t buf[6];
//     //     mpu_read_bytes(REG_ACCEL_XOUT_H, buf, 6);
//     //     rt_int16_t ax = (buf[0]<<8) | buf[1];
//     //     rt_int16_t ay = (buf[2]<<8) | buf[3];
//     //     rt_int16_t az = (buf[4]<<8) | buf[5];
//     //     rt_kprintf("AX:%6d  AY:%6d  AZ:%6d\n", ax, ay, az);
//     //     rt_thread_mdelay(500);
//     // }

//     struct rt_sensor_config cfg;

//     rt_kprintf("111\n");
    
//     cfg.intf.dev_name = "i2c1";
//     cfg.intf.user_data = (void *)MPU6XXX_ADDR_DEFAULT;
//     cfg.irq_pin.pin = RT_PIN_NONE;

//     rt_hw_mpu6xxx_init("mpu", &cfg);

//     return 0;
// }
// // INIT_APP_EXPORT(mpu_demo);
// MSH_CMD_EXPORT(mpu_demo, mpu_demo);
