#include <rtthread.h>
#include <rthw.h>
#include <stdint.h>
#include <string.h>

#define COREDUMP_MAGIC 0xDEADBEEF
#define MAX_STACK_DEPTH 128
#define COREDUMP_VERSION 1

/* 核心转储头部信息 */
typedef struct {
    uint32_t magic;          /* 魔术字，用于验证 */
    uint32_t version;        /* 版本号 */
    uint32_t exception_type; /* 异常类型 */
    uint32_t cpsr;           /* 当前程序状态寄存器 */
    uint32_t sp;             /* 栈指针 */
    uint32_t lr;             /* 链接寄存器 */
    uint32_t pc;             /* 程序计数器 */
    uint32_t regs[13];       /* R0-R12通用寄存器 */
    uint32_t stack_len;      /* 栈数据长度 */
    uint32_t stack_data[MAX_STACK_DEPTH]; /* 栈数据 */
} coredump_header_t;

static coredump_header_t coredump_header;

/* 异常处理钩子函数 */
static rt_err_t coredump_exception_hook(void* context)
{
    RT_UNUSED(context);
    // rt_kprintf("coredump: exception occur\n");
    // rt_base_t level;
    // uint32_t *stack_ptr;
    // int i;

    // struct exception_stack_frame* exception_frame = (struct exception_stack_frame*)context;

    // /* 关闭中断防止嵌套 */
    // level = rt_hw_interrupt_disable();

    // /* 初始化核心转储头部 */
    // memset(&coredump_header, 0, sizeof(coredump_header_t));
    // coredump_header.magic = COREDUMP_MAGIC;
    // coredump_header.version = COREDUMP_VERSION;
    // // coredump_header.exception_type = exception_type;

    // /* 保存寄存器信息 */
    // for (i = 0; i < 13; i++)
    // {
    //     coredump_header.regs[i] = regs[i];
    // }
    // coredump_header.sp = exception_frame.sp;
    // coredump_header.lr = regs[14];
    // coredump_header.pc = regs[15];
    // coredump_header.cpsr = rt_hw_get_cpsr();

    // /* 保存栈数据 */
    // stack_ptr = (uint32_t *)coredump_header.sp;
    // coredump_header.stack_len = MAX_STACK_DEPTH;
    // for (i = 0; i < MAX_STACK_DEPTH; i++)
    // {
    //     coredump_header.stack_data[i] = stack_ptr[i];
    // }

    // /* 恢复中断 */
    // rt_hw_interrupt_enable(level);

    // /* 输出核心转储信息 */
    // rt_kprintf("\n=== RT-Thread Coredump ===\n");
    // rt_kprintf("Magic: 0x%08x\n", coredump_header.magic);
    // rt_kprintf("Version: %d\n", coredump_header.version);
    // // rt_kprintf("Exception Type: 0x%08x\n", coredump_header.exception_type);
    // rt_kprintf("CPSR: 0x%08x\n", coredump_header.cpsr);
    // rt_kprintf("Registers:\n");
    // for (i = 0; i < 13; i++)
    // {
    //     rt_kprintf("R%-2d: 0x%08x\t", i, coredump_header.regs[i]);
    //     if ((i + 1) % 4 == 0) rt_kprintf("\n");
    // }
    // rt_kprintf("\nSP: 0x%08x\tLR: 0x%08x\tPC: 0x%08x\n",
    //           coredump_header.sp, coredump_header.lr, coredump_header.pc);
    // rt_kprintf("Stack Dump (0x%08x):\n", coredump_header.sp);
    // for (i = 0; i < MAX_STACK_DEPTH; i++)
    // {
    //     if (i % 4 == 0) rt_kprintf("0x%08x: ", (uint32_t)(stack_ptr + i));
    //     rt_kprintf("%08x ", coredump_header.stack_data[i]);
    //     if ((i + 1) % 4 == 0) rt_kprintf("\n");
    // }
    // rt_kprintf("=== End of Coredump ===\n");

    return RT_EOK;
}

/* 初始化函数 */
static int coredump_init(void)
{
    /* 注册异常处理钩子 */
    // rt_hw_exception_install(coredump_exception_hook);
    // rt_kprintf("Coredump initialized, version %d\n", COREDUMP_VERSION);
    return RT_EOK;
}

/* 导出为自动初始化函数 */
INIT_APP_EXPORT(coredump_init);
