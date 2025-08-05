/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_uart_rxi_isr, /* SCI9 RXI (Receive data full) */
            [1] = sci_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [2] = sci_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [3] = sci_uart_eri_isr, /* SCI9 ERI (Receive error) */
            [4] = r_icu_isr, /* ICU IRQ1 (External pin interrupt 1) */
            [5] = r_icu_isr, /* ICU IRQ5 (External pin interrupt 5) */
            [6] = r_icu_isr, /* ICU IRQ3 (External pin interrupt 3) */
            [7] = sci_i2c_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [8] = sci_i2c_tei_isr, /* SCI0 TEI (Transmit end) */
            [9] = fcu_frdyi_isr, /* FCU FRDYI (Flash ready interrupt) */
            [10] = fcu_fiferr_isr, /* FCU FIFERR (Flash access error interrupt) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI9_RXI,GROUP0), /* SCI9 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TXI,GROUP1), /* SCI9 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TEI,GROUP2), /* SCI9 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI9_ERI,GROUP3), /* SCI9 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ1,GROUP4), /* ICU IRQ1 (External pin interrupt 1) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ5,GROUP5), /* ICU IRQ5 (External pin interrupt 5) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ3,GROUP6), /* ICU IRQ3 (External pin interrupt 3) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TXI,GROUP7), /* SCI0 TXI (Transmit data empty) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TEI,GROUP0), /* SCI0 TEI (Transmit end) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_FCU_FRDYI,GROUP1), /* FCU FRDYI (Flash ready interrupt) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_FCU_FIFERR,GROUP2), /* FCU FIFERR (Flash access error interrupt) */
        };
        #endif
        #endif