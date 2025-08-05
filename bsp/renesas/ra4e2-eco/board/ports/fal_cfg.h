#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>

#define RA4E2_ONCHIP_FLASH_DEV_NAME    "onchip_flash"
/* Flash 设备表 */
extern const struct fal_flash_dev ra4e2_onchip_flash;

#define FAL_FLASH_DEV_TABLE                                          \
{                                                                   \
    &ra4e2_onchip_flash,                                            \
}

/* 分区表 (128KB 总容量) */
#define FAL_PART_TABLE                                                               \
{\
    {FAL_PART_MAGIC_WORD, "app",        RA4E2_ONCHIP_FLASH_DEV_NAME, 0, 128*1024, 0},  \
}

#endif /* _FAL_CFG_H_ */
