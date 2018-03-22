; Motion driver functions built on top of Tivaware
; Lab 4, ECE 266, spring 2018
; Created by Zhao Zhang

; To include names declared in C
 .cdecls "stdint.h", "stdbool.h", "stdio.h", "inc/hw_memmap.h", "driverlib/pin_map.h", "driverlib/adc.h", "driverlib/sysctl.h", "launchpad.h", "rotary.h"

					.text
;					.global rotaryOn
;					.global rotaryOff

; GPIO peripheral, port base and pin mask value for the buzzer
; The motion is assumed to be connected to J17, and then the buzzer's
; signal pin is connected to PC5.
ROTARY_PERIPH   .field  SYSCTL_PERIPH_ADC0
ROTARY_PORT     .field 	ADC0_BASE



;
; void rotaryInit(): Initialze the buzz peripheral, port, and pin direction
;
rotaryInit      PUSH 	{LR}

                ; Initialize the GPIO peripheral for the port that the rotary uses:
                ;   Call SysCtlPeripheralEnable(ROTARY_PERIPH)
                LDR   r0, ROTARY_PERIPH
                BL    SysCtlPeripheralEnable


                LDR   r0, ROTARY_PORT
                MOV   r1, #0
                MOV   r2, #ADC_TRIGGER_PROCESSOR
                MOV   r3, #0
                BL    ADCSequenceConfigure

			    LDR   r0, ROTARY_PORT
				MOV   r1, #0
				MOV   r2, #0
				MOV   r3, #(ADC_CTL_IE |ADC_CTL_END | ADC_CTL_CH2)
				BL    ADCSequenceStepConfigure

				LDR   r0, ROTARY_PORT
				MOV   r1, #0
				BL    ADCSequenceEnable

                POP   {PC}

;
; void motionOn(): Turn on the motion. It calls GPIOPinWrite() to write 1 to the signal pin.
;
rotaryStart        PUSH  {LR}
				SUB sp, #4
                ; Write 1 to the GPIO pin that the motion uses:
		;   Call GPIOPinWrite(ROTARY_PIN, ROTARY_PIN)
                LDR   r0, ROTARY_PORT
                MOV   r1, #0
                BL    ADCProcessorTrigger

loop			LDR   r0, ROTARY_PORT
				MOV   r1, #0
				MOV   r2, #false
				BL    ADCIntStatus
				CMP   r0, #0
				BEQ   loop

				LDR   r0, ROTARY_PORT
				MOV   r1, #0
				MOV   r2, sp
				BL    ADCSequenceDataGet

                POP   {r0, PC}

