/* @Eng. Mohamed Elsayed */
/* startup_stm32f103c6.s */

.section .Vector_Table

.word 0x20001000        /* Initial Stack Pointer (sp) */
.word Vector_Handler    /* Reset Handler: Entry point after reset, calls main */
.word Vector_Handler    /* Non-Maskable Interrupt (NMI) Handler */
.word Vector_Handler    /* Hard Fault Handler */
.word Vector_Handler    /* Memory Management Fault Handler */
.word Vector_Handler    /* Bus Fault Handler */
.word Vector_Handler    /* Usage Fault Handler */
.word 0                 /* Reserved */
.word 0                 /* Reserved */
.word 0                 /* Reserved */
.word 0                 /* Reserved */
.word Vector_Handler    /* Supervisor Call (SVC) Handler */
.word Vector_Handler    /* Debug Monitor Handler */
.word 0                 /* Reserved */
.word Vector_Handler    /* Pendable request for system service (PendSV) Handler */
.word Vector_Handler    /* System Tick Timer (SysTick) Handler */


.section .text

Reset_Handler:
    bl main
    b .
.thumb_func
Vector_Handler:
    b Reset_Handler