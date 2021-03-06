  /*
 * main.c: For Lab 5, Sleeping LaunchPad
 *
 * Created by Zhao Zhang.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inc/hw_memmap.h>
#include <inc/hw_ints.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/interrupt.h>
#include <driverlib/systick.h>
#include "launchpad.h"
#include "motion.h"
#include "buzzer.h"

// Color defines
#define     RED         0
#define     BLUE        1
#define     GREEN       2

// Color display setting
static volatile int colorSetting = RED;
static bool colorTable[3][3] = {
    {true, false, false},       // Red
    {false, true, false},       // Blue
    {false, false, true}        // Green
};

int code=0;
/*
 * LED flashing function. Note that this function must run in a thread, e.g. not be callback-based,
 * because the frequency of buzzer on/off is too high for the callback scheduling module.
 */
void
ledFlash()
{
    int i;

    while (true) {
            IntMasterDisable();     // disable all interrupts so that the color stays the same

            for (i = 0; i < 3; i++) {
                ledTurnOnOff(colorTable[colorSetting][0], colorTable[colorSetting][1],
                             colorTable[colorSetting][2]);
            waitMs(300);
            ledTurnOnOff(false, false, false);
            waitMs(300);
        }

            IntMasterEnable();      // enable interrupt signal from interrupt controller to CPU

            // The following is in-line assembly, i.e. inserting assembly instructions into C code
            // Execute an WFI instruction to put the processor into the sleep mode
            __asm("    wfi");
    }
}

/*
 * Interrupt handler for both push buttons (pins PF0 and PF4)
 */
void
pbIntrHandler()
{
    // Clear interrupt. This is necessary, otherwise the interrupt handler will be executed forever.
    code = pbRead();
    if(code==1){
        colorSetting = GREEN;
        uprintf("sw1\r\n");
    }
    else if(code==2){
        colorSetting = BLUE;
        uprintf("sw2\r\n");
    }
    else{
        colorSetting = RED;
        uprintf("motion\r\n");
    }
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);


}

void
pbIntrHandler3()
{
    // Clear interrupt. This is necessary, otherwise the interrupt handler will be executed forever.
    code = pbRead();
    if(code==1){
        colorSetting = GREEN;
        uprintf("sw1\r\n");
    }
    else if(code==2){
        colorSetting = BLUE;
        uprintf("sw2\r\n");
    }
    else{
        colorSetting = RED;
        uprintf("motion\r\n");
    }
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_5);


}




/*
 * Select a set of interrupts that can wake up the LaunchPad
 */
void
setInterrupts()
{
    // Disable the system tick interrupt, which has been enabled in lpInit();
    // otherwise, it will wake up Tiva C.
    SysTickIntDisable();
    // Set interrupt on Port F, pin 0 (SW1) and pin 4 (SW2)
    GPIOIntRegister(GPIO_PORTF_BASE, pbIntrHandler);            // register the interrupt handler
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4 );    // enable interrupts on SW1 and SW2 input
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4 ,    // interrupt on falling edge, note that SW1 and SW2 are active low
            GPIO_FALLING_EDGE);
    IntPrioritySet(INT_GPIOF, 0);                           // raise interrupt level to 0 (highest) to make sure MCU wakes up
}

void
setInterrupts2()
{
    // Disable the system tick interrupt, which has been enabled in lpInit();
    // otherwise, it will wake up Tiva C.
    SysTickIntDisable();
    // Set interrupt on Port F, pin 0 (SW1) and pin 4 (SW2)
    GPIOIntRegister(GPIO_PORTF_BASE, pbIntrHandler);            // register the interrupt handler
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0 );    // enable interrupts on SW1 and SW2 input
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0 ,    // interrupt on falling edge, note that SW1 and SW2 are active low
            GPIO_FALLING_EDGE);
    IntPrioritySet(INT_GPIOF, 0);                           // raise interrupt level to 0 (highest) to make sure MCU wakes up
}

void
setInterrupts3()
{
    // Disable the system tick interrupt, which has been enabled in lpInit();
    // otherwise, it will wake up Tiva C.
    SysTickIntDisable();
    // Set interrupt on Port F, pin 0 (SW1) and pin 4 (SW2)
    GPIOIntRegister(GPIO_PORTC_BASE, pbIntrHandler3);            // register the interrupt handler
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_5 );    // enable interrupts on SW1 and SW2 input
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_5 ,    // interrupt on falling edge, note that SW1 and SW2 are active low
            GPIO_FALLING_EDGE);
    IntPrioritySet(INT_GPIOF, 0);                           // raise interrupt level to 0 (highest) to make sure MCU wakes up
}


int
main(void)
{
    // Initialize the launchpad, buzzer
    lpInit();
    motionInit();
    // IN YOUR SOLUTION CODE, call the function that initializes the PIR montion sensor,
    //    which you wrote in Lab 4, e.g.
    // pirInit();

    // NOTE: In this lab, you should NOT use the callback scheduler because it will wake up the CPU
    // from sleeping.
    uprintf("%s\n\r", "Lab 5: Sleeping LaunchPad");
    setInterrupts();
    setInterrupts2();
    setInterrupts3();
    ledFlash();




}
