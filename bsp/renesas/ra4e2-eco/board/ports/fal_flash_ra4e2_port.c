/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 */

#include <fal.h>
#include <hal_data.h> 

/* base address of the flash sectors */
#define ADDR_FLASH_BASE          ((uint32_t)0x00000000)  // RA4E2 Flash起始地址
#define FLASH_SECTOR_SIZE        (16 * 1024)             // 扇区大小：16KB
#define FLASH_TOTAL_SIZE         (128 * 1024)            // 总容量：128KB


void g_flash_callback(flash_callback_args_t * p_args)
{
    return;
}

static int init(void)
{
    // fsp_err_t err;
    // /* 初始化RA4E2 Flash驱动 */
    // err = R_FLASH_HP_Open(&g_flash0_ctrl, &g_flash0_cfg);
    // if (err != FSP_SUCCESS)
    // {
    //     return -1;
    // }
    return _flash_init();
}

static int read(long offset, uint8_t *buf, size_t size)
{
    uint32_t addr = ADDR_FLASH_BASE + offset;
    // /* 检查地址范围 */
    // if (offset + size > FLASH_TOTAL_SIZE)
    // {
    //     return -1;
    // }
    // memcpy(buf, (void *)addr, size);
    return _flash_read(offset, buf, size);
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    // fsp_err_t err;
    uint32_t addr = ADDR_FLASH_BASE + offset;
    // /* 检查地址范围和对齐 */
    // if (offset + size > FLASH_TOTAL_SIZE || (offset % 4) != 0)
    // {
    //     return -1;
    // }
    // /* 解锁Flash写入 */
    // err = R_FLASH_HP_Write(&g_flash_ctrl, addr, (uint32_t )(*buf), size / 4);
    // if (err != FSP_SUCCESS)
    //     return -1;
    
    // /* 等待写入完成 */
    // while (R_FACI_HP->FSTATR_b.FRDY == 0U);

    size = _flash_write(addr, buf, size);
    
    return size;
}

static int erase(long offset, size_t size)
{
    // fsp_err_t err;
    uint32_t addr = ADDR_FLASH_BASE + offset;
    // // uint32_t sector = addr / FLASH_SECTOR_SIZE;
    // /* 检查地址范围 */
    // if (offset + size > FLASH_TOTAL_SIZE)
    // {
    //     return -1;
    // }
    // /* 擦除扇区 */
    // err = R_FLASH_HP_Erase(&g_flash0_ctrl, addr, size / FLASH_SECTOR_SIZE);
    // if (err != FSP_SUCCESS)
    //     return -1;
    
    // /* 等待擦除完成 */
    // while (R_FACI_HP->FSTATR_b.FRDY == 0U);
    
    return _flash_hp0_erase(addr, size);
}

const struct fal_flash_dev ra4e2_onchip_flash =
{
    .name       = RA4E2_ONCHIP_FLASH_DEV_NAME,
    .addr       = ADDR_FLASH_BASE,
    .len        = FLASH_TOTAL_SIZE,
    .blk_size   = FLASH_SECTOR_SIZE,  // 块大小=扇区大小：16KB
    .ops        = {init, read, write, erase},
    .write_gran = 2 * 8                   // 写入粒度：8位
};
