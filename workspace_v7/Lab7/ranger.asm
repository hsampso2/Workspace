; Motion driver functions built on top of Tivaware
; Lab 4, ECE 266, spring 2018
; Created by Zhao Zhang

; To include names declared in C
 .cdecls "stdint.h", "stdbool.h", "stdio.h", "inc/hw_memmap.h", "driverlib/pin_map.h", "driverlib/gpio.h", "driverlib/sysctl.h", "launchpad.h", "driverlib/timer.h", "ranger.h"

					.text
;					.global motionOn
;					.global motionOff

; GPIO peripheral, port base and pin mask value for the buzzer
; The motion is assumed to be connected to J17, and then the buzzer's
; signal pin is connected to PC5.
RANGER_PERIPH   .field  SYSCTL_PERIPH_GPIOC
RANGER_PORT     .field 	GPIO_PORTC_BASE
RANGER_PIN      .equ	GPIO_PIN_5

TIMER_PERIPH    .field  SYSCTL_PERIPH_WTIMER0
TIMER_BASE      .field  WTIMER0_BASE


;
; void motionInit(): Initialze the buzz peripheral, port, and pin direction
;
rangerInit      PUSH 	{LR}

                ; Initialize the GPIO peripheral for the port that the motion uses:
                ;   Call SysCtlPeripheralEnable(MOTION_PERIPH)
                LDR   r0, TIMER_PERIPH
                BL    SysCtlPeripheralEnable

                LDR   r0, RANGER_PORT
                BL    SysCtlPeripheralEnable

				LDR   r0, RANGER_PORT
				MOV   r1, #RANGER_PIN
                BL    GPIOPinTypeTimer

                LDR   r0, TIMER_BASE
                MOV   r1, #(TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP)
                BL    TimerConfigure

                LDR   r0, TIMER_BASE
                MOV   r1, #TIMER_A
                MOV   r2, #TIMER_EVENT_BOTH_EDGES

                MOV   r0, #RANGER_PIN
                BL    GPIOPinConfigure

                LDR   r0, TIMER_BASE
                MOV   r1, #1
                BL    TimerIntClear

                POP   {PC}

;
; void motionOn(): Turn on the motion. It calls GPIOPinWrite() to write 1 to the signal pin.
;
rangerDetect        PUSH  {LR}

                ; Write 1 to the GPIO pin that the motion uses:
		;   Call GPIOPinWrite(MOTION_PORT, MOTION_PIN, MOTION_PIN)
                BL sendStartPulse
                SUB   r0, r0, r1
                MOV   r1, #340
                MUL   r0, r0, r1


                POP   {PC}




sendStartPulse	    PUSH {LR}

				LDR   r0, TIMER_BASE
				MOV   r1, #TIMER_A
				BL    TimerValueGet
				PUSH  {r0} ;push rising time

				LDR   r0, TIMER_BASE
                MOV   r1, #1
                BL    TimerIntClear
				;call other function(s)

				LDR   r0, TIMER_BASE
				MOV   r1, #TIMER_A
				BL    TimerValueGet
				PUSH  {r0} ;push falling time

				LDR   r0, TIMER_BASE
                MOV   r1, #1
                BL    TimerIntClear
				;call other function(s)

				POP   {r1, r0} ;rising time and falling time returned




