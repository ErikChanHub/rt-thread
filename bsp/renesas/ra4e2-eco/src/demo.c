#include <rtthread.h>

static void test_coredump(void)
{
    rt_kprintf("Triggering division by zero to generate coredump...\n");
    int zero = 0;
    int result = 1 / zero; /* 触发除零异常 */
    rt_kprintf("%d\n", result);
    RT_UNUSED(result);
}
MSH_CMD_EXPORT(test_coredump, Trigger coredump for testing);


void test_null_pointer(void)
{
    volatile int *null_ptr = RT_NULL;
    *null_ptr = 0; // 触发空指针解引用异常
}
MSH_CMD_EXPORT(test_null_pointer, Trigger null pointer dereference exception);

void test_array_out_of_bounds(void)
{
    int arr[10];
    arr[100] = 0; // 触发数组越界异常
}
MSH_CMD_EXPORT(test_array_out_of_bounds, Trigger array out-of-bounds exception);

void stack_overflow_recursive(int depth)
{
    char large_buffer[1024];
    large_buffer[0] = depth; // 防止编译器优化
    stack_overflow_recursive(depth + 1);
}
void test_stack_overflow(void)
{
    stack_overflow_recursive(0); // 触发栈溢出异常
}
MSH_CMD_EXPORT(test_stack_overflow, Trigger stack overflow exception);

void test_invalid_instruction(void)
{
    asm volatile (
        ".word 0xe7f000f0" // ARM架构未定义指令
    );
}
MSH_CMD_EXPORT(test_invalid_instruction, Trigger invalid instruction exception);

void test_assert_failure(void)
{
    RT_ASSERT(0); // 触发断言失败
}
MSH_CMD_EXPORT(test_assert_failure, Trigger assertion failure exception);