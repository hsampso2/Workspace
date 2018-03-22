/*
 * main.c for ECE 266 Lab 6, rotary
 *
 *  Created on: Aug 23, 2016
 *  Last updated on: Sep 19, 2017
 *      Author: zzhang
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <driverlib/sysctl.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_i2c.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/i2c.h>
#include "launchpad.h"
#include "seg7.h"
#include "seg7digit.h"
#include "rotary.h"

// Switch type
typedef enum {
    Off, On
} switch_t;

//static switch_t rotaryState= Off;
static switch_t displayState = On;

int value = 0;



static uint8_t seg7Coding[10] = {
        0b00111111,         // digit 0
        0b00000110,         // digit 1
        0b01011011,         // digit 2
        0b01001111,         // digit 3
        0b01100110,         // digit 4
        0b01101101,         // digit 5
        0b01111101,         // digit 6
        0b00000111,         // digit 7
        0b01111111,         // digit 8
        0b01101111,         // digit 9
};
uint8_t code[4];

static uint8_t colon = 0b10000000;


void
checkRotary(uint32_t time){
    //uint32_t delay = 1;
    //motionInit();
    value = rotaryStart();
    //uprintf("%d", value);
   /* if(value != 0){
        rotaryState = On;
    }
    else{
        rotaryState = Off;
    }*/
    //schdCallback(checkMotion, time + delay);
}

void
checkSeg(uint32_t time){
    int k=1;
    int i;
    int calculation = value;
    double mean = (double) calculation;
    mean = (mean/4096) * 100;

    for(i = 1; i <= mean*2; i++){
        if(k==1){
                code[0] = seg7Coding[0] + colon;
                code[1] = seg7Coding[0] + colon;
                code[2] = seg7Coding[0] + colon;
                code[3] = seg7Coding[0] + colon;
                k=0;
            }

            if(code[0]==(seg7Coding[0] + colon)){
                code[0]=seg7Coding[1] + colon;
            }
            else if(code[0]==(seg7Coding[1] + colon)){
                code[0]=seg7Coding[2] + colon;
            }
            else if(code[0]==(seg7Coding[2] + colon)){
                code[0]=seg7Coding[3] + colon;
            }
            else if(code[0]==(seg7Coding[3] + colon)){
                code[0]=seg7Coding[4] + colon;
            }
            else if(code[0]==(seg7Coding[4] + colon)){
                code[0]=seg7Coding[5] + colon;
            }
            else if(code[0]==(seg7Coding[5] + colon)){
                code[0]=seg7Coding[6] + colon;
            }
            else if(code[0]==(seg7Coding[6] + colon)){
                code[0]=seg7Coding[7] + colon;
            }
            else if(code[0]==(seg7Coding[7] + colon)){
                code[0]=seg7Coding[8] + colon;
            }
            else if(code[0]==(seg7Coding[8] + colon)){
                code[0]=seg7Coding[9] + colon;
            }
            else if(code[0]==(seg7Coding[9] + colon)){
                code[0]=seg7Coding[0] + colon;
                if(code[1]==(seg7Coding[0] + colon)){
                    code[1]=seg7Coding[1] + colon;
                }
                else if(code[1]==(seg7Coding[1] + colon)){
                    code[1]=seg7Coding[2] + colon;
                }
                else if(code[1]==(seg7Coding[2] + colon)){
                    code[1]=seg7Coding[3] + colon;
                }
                else if(code[1]==(seg7Coding[3] + colon)){
                    code[1]=seg7Coding[4] + colon;
                }
                else if(code[1]==(seg7Coding[4] + colon)){
                    code[1]=seg7Coding[5] + colon;
                }
                else if(code[1]==(seg7Coding[5] + colon)){
                    code[1]=seg7Coding[6] + colon;
                }
                else if(code[1]==(seg7Coding[6] + colon)){
                    code[1]=seg7Coding[7] + colon;
                }
                else if(code[1]==(seg7Coding[7] + colon)){
                    code[1]=seg7Coding[8] + colon;
                }
                else if(code[1]==(seg7Coding[8] + colon)){
                    code[1]=seg7Coding[9] + colon;
                }
                else if(code[1]==(seg7Coding[9] + colon)){
                    code[1]=seg7Coding[0] + colon;
                    if(code[2]==(seg7Coding[0] + colon)){
                        code[2]=seg7Coding[1] + colon;
                    }
                    else if(code[2]==(seg7Coding[1] + colon)){
                        code[2]=seg7Coding[2] + colon;
                    }
                    else if(code[2]==(seg7Coding[2] + colon)){
                        code[2]=seg7Coding[3] + colon;
                    }
                    else if(code[2]==(seg7Coding[3] + colon)){
                        code[2]=seg7Coding[4] + colon;
                    }
                    else if(code[2]==(seg7Coding[4] + colon)){
                        code[2]=seg7Coding[5] + colon;
                    }
                    else if(code[2]==(seg7Coding[5] + colon)){
                         code[2]=seg7Coding[6] + colon;
                    }
                    else if(code[2]==(seg7Coding[6] + colon)){
                         code[2]=seg7Coding[7] + colon;
                    }
                    else if(code[2]==(seg7Coding[7] + colon)){
                         code[2]=seg7Coding[8] + colon;
                    }
                    else if(code[2]==(seg7Coding[8] + colon)){
                         code[2]=seg7Coding[9] + colon;
                    }
                    else if(code[2]==(seg7Coding[9] + colon)){
                         code[2]=seg7Coding[0] + colon;
                         if(code[3]==(seg7Coding[0] + colon)){
                             code[3]=seg7Coding[1] + colon;
                         }
                         else if(code[3]==(seg7Coding[1] + colon)){
                             code[3]=seg7Coding[2] + colon;
                         }
                         else if(code[3]==(seg7Coding[2] + colon)){
                             code[3]=seg7Coding[3] + colon;
                         }
                         else if(code[3]==(seg7Coding[3] + colon)){
                             code[3]=seg7Coding[4] + colon;
                         }
                         else if(code[3]==(seg7Coding[4] + colon)){
                             code[3]=seg7Coding[5] + colon;
                         }
                         else if(code[3]==(seg7Coding[5] + colon)){
                             code[3]=seg7Coding[6] + colon;
                         }
                         else if(code[3]==(seg7Coding[6] + colon)){
                             code[3]=seg7Coding[7] + colon;
                         }
                         else if(code[3]==(seg7Coding[7] + colon)){
                              code[3]=seg7Coding[8] + colon;
                         }
                         else if(code[3]==(seg7Coding[8] + colon)){
                              code[3]=seg7Coding[9] + colon;
                         }
                         else if(code[3]==(seg7Coding[9] + colon)){ //wrap around
                              code[0] = seg7Coding[0] + colon;
                              code[1] = seg7Coding[0] + colon;
                              code[2] = seg7Coding[0] + colon;
                              code[3] = seg7Coding[0] + colon;
                         }

                    }
                }
            }
            if(colon == 0b00000000){
                code[0] = code[0] & 0b01111111;
                code[1] = code[1] & 0b01111111;
                code[2] = code[2] & 0b01111111;
                code[3] = code[3] & 0b01111111;

            }
            /*if(colon == 0b10000000){
                    code[0] = code[0] + 0b10000000;
                    code[1] = code[1] + 0b10000000;
                    code[2] = code[2] + 0b10000000;
                    code[3] = code[3] + 0b10000000;
                }*/
            //seg7Update(code);

            // Calculate the display digits and colon setting for the next update
            if (colon == 0b00000000) {
                colon = 0b10000000;
                code[0] = code[0] + 0b10000000;
                code[1] = code[1] + 0b10000000;
                code[2] = code[2] + 0b10000000;
                code[3] = code[3] + 0b10000000;
            }
            else {
                colon = 0b00000000;

        }
    }
    if(i==1){
        code[0] = seg7Coding[0] & 0b01111111;
        code[1] = seg7Coding[0] & 0b00000000;
        code[2] = seg7Coding[0] & 0b00000000;
        code[3] = seg7Coding[0] & 0b00000000;

    }
    else{
        code[0] = code[0] & 0b01111111;
        code[1] = code[1] & 0b01111111;
        code[2] = code[2] & 0b01111111;
        code[3] = code[3] & 0b01111111;
    }
    if(mean * 2 < 1999){
        code[0] = code[0] & 0b01111111;
        code[1] = code[1] & 0b01111111;
        code[2] = code[2] & 0b01111111;
        code[3] = code[3] & 0b00000000;
    }

    if(mean * 2 < 199){
        code[0] = code[0] & 0b01111111;
        code[1] = code[1] & 0b01111111;
        code[2] = code[2] & 0b00000000;
        code[3] = code[3] & 0b00000000;
    }
    if(mean * 2 < 19){
        code[0] = code[0] & 0b01111111;
        code[1] = code[1] & 0b00000000;
        code[2] = code[2] & 0b00000000;
        code[3] = code[3] & 0b00000000;
    }


    seg7Update(code);
    uprintf("%d\n", mean);
}

void
checkSeg2(uint32_t time){
    int k=1;
        int i;
        int calculation = value;
        for(i = 1; i <= calculation*2; i++){
            if(k==1){
                    code[0] = seg7Coding[0] + colon;
                    code[1] = seg7Coding[0] + colon;
                    code[2] = seg7Coding[0] + colon;
                    code[3] = seg7Coding[0] + colon;
                    k=0;
                }

                if(code[0]==(seg7Coding[0] + colon)){
                    code[0]=seg7Coding[1] + colon;
                }
                else if(code[0]==(seg7Coding[1] + colon)){
                    code[0]=seg7Coding[2] + colon;
                }
                else if(code[0]==(seg7Coding[2] + colon)){
                    code[0]=seg7Coding[3] + colon;
                }
                else if(code[0]==(seg7Coding[3] + colon)){
                    code[0]=seg7Coding[4] + colon;
                }
                else if(code[0]==(seg7Coding[4] + colon)){
                    code[0]=seg7Coding[5] + colon;
                }
                else if(code[0]==(seg7Coding[5] + colon)){
                    code[0]=seg7Coding[6] + colon;
                }
                else if(code[0]==(seg7Coding[6] + colon)){
                    code[0]=seg7Coding[7] + colon;
                }
                else if(code[0]==(seg7Coding[7] + colon)){
                    code[0]=seg7Coding[8] + colon;
                }
                else if(code[0]==(seg7Coding[8] + colon)){
                    code[0]=seg7Coding[9] + colon;
                }
                else if(code[0]==(seg7Coding[9] + colon)){
                    code[0]=seg7Coding[0] + colon;
                    if(code[1]==(seg7Coding[0] + colon)){
                        code[1]=seg7Coding[1] + colon;
                    }
                    else if(code[1]==(seg7Coding[1] + colon)){
                        code[1]=seg7Coding[2] + colon;
                    }
                    else if(code[1]==(seg7Coding[2] + colon)){
                        code[1]=seg7Coding[3] + colon;
                    }
                    else if(code[1]==(seg7Coding[3] + colon)){
                        code[1]=seg7Coding[4] + colon;
                    }
                    else if(code[1]==(seg7Coding[4] + colon)){
                        code[1]=seg7Coding[5] + colon;
                    }
                    else if(code[1]==(seg7Coding[5] + colon)){
                        code[1]=seg7Coding[6] + colon;
                    }
                    else if(code[1]==(seg7Coding[6] + colon)){
                        code[1]=seg7Coding[7] + colon;
                    }
                    else if(code[1]==(seg7Coding[7] + colon)){
                        code[1]=seg7Coding[8] + colon;
                    }
                    else if(code[1]==(seg7Coding[8] + colon)){
                        code[1]=seg7Coding[9] + colon;
                    }
                    else if(code[1]==(seg7Coding[9] + colon)){
                        code[1]=seg7Coding[0] + colon;
                        if(code[2]==(seg7Coding[0] + colon)){
                            code[2]=seg7Coding[1] + colon;
                        }
                        else if(code[2]==(seg7Coding[1] + colon)){
                            code[2]=seg7Coding[2] + colon;
                        }
                        else if(code[2]==(seg7Coding[2] + colon)){
                            code[2]=seg7Coding[3] + colon;
                        }
                        else if(code[2]==(seg7Coding[3] + colon)){
                            code[2]=seg7Coding[4] + colon;
                        }
                        else if(code[2]==(seg7Coding[4] + colon)){
                            code[2]=seg7Coding[5] + colon;
                        }
                        else if(code[2]==(seg7Coding[5] + colon)){
                             code[2]=seg7Coding[6] + colon;
                        }
                        else if(code[2]==(seg7Coding[6] + colon)){
                             code[2]=seg7Coding[7] + colon;
                        }
                        else if(code[2]==(seg7Coding[7] + colon)){
                             code[2]=seg7Coding[8] + colon;
                        }
                        else if(code[2]==(seg7Coding[8] + colon)){
                             code[2]=seg7Coding[9] + colon;
                        }
                        else if(code[2]==(seg7Coding[9] + colon)){
                             code[2]=seg7Coding[0] + colon;
                             if(code[3]==(seg7Coding[0] + colon)){
                                 code[3]=seg7Coding[1] + colon;
                             }
                             else if(code[3]==(seg7Coding[1] + colon)){
                                 code[3]=seg7Coding[2] + colon;
                             }
                             else if(code[3]==(seg7Coding[2] + colon)){
                                 code[3]=seg7Coding[3] + colon;
                             }
                             else if(code[3]==(seg7Coding[3] + colon)){
                                 code[3]=seg7Coding[4] + colon;
                             }
                             else if(code[3]==(seg7Coding[4] + colon)){
                                 code[3]=seg7Coding[5] + colon;
                             }
                             else if(code[3]==(seg7Coding[5] + colon)){
                                 code[3]=seg7Coding[6] + colon;
                             }
                             else if(code[3]==(seg7Coding[6] + colon)){
                                 code[3]=seg7Coding[7] + colon;
                             }
                             else if(code[3]==(seg7Coding[7] + colon)){
                                  code[3]=seg7Coding[8] + colon;
                             }
                             else if(code[3]==(seg7Coding[8] + colon)){
                                  code[3]=seg7Coding[9] + colon;
                             }
                             else if(code[3]==(seg7Coding[9] + colon)){ //wrap around
                                  code[0] = seg7Coding[0] + colon;
                                  code[1] = seg7Coding[0] + colon;
                                  code[2] = seg7Coding[0] + colon;
                                  code[3] = seg7Coding[0] + colon;
                             }

                        }
                    }
                }
                if(colon == 0b00000000){
                    code[0] = code[0] & 0b01111111;
                    code[1] = code[1] & 0b01111111;
                    code[2] = code[2] & 0b01111111;
                    code[3] = code[3] & 0b01111111;

                }
                /*if(colon == 0b10000000){
                        code[0] = code[0] + 0b10000000;
                        code[1] = code[1] + 0b10000000;
                        code[2] = code[2] + 0b10000000;
                        code[3] = code[3] + 0b10000000;
                    }*/
                //seg7Update(code);

                // Calculate the display digits and colon setting for the next update
                if (colon == 0b00000000) {
                    colon = 0b10000000;
                    code[0] = code[0] + 0b10000000;
                    code[1] = code[1] + 0b10000000;
                    code[2] = code[2] + 0b10000000;
                    code[3] = code[3] + 0b10000000;
                }
                else {
                    colon = 0b00000000;

            }
        }
        if(i==1){
            code[0] = seg7Coding[0] & 0b01111111;
            code[1] = seg7Coding[0] & 0b00000000;
            code[2] = seg7Coding[0] & 0b00000000;
            code[3] = seg7Coding[0] & 0b00000000;

        }
        else{
            code[0] = code[0] & 0b01111111;
            code[1] = code[1] & 0b01111111;
            code[2] = code[2] & 0b01111111;
            code[3] = code[3] & 0b01111111;
        }
        if(calculation * 2 < 1999){
            code[0] = code[0] & 0b01111111;
            code[1] = code[1] & 0b01111111;
            code[2] = code[2] & 0b01111111;
            code[3] = code[3] & 0b00000000;
        }

        if(calculation * 2 < 199){
            code[0] = code[0] & 0b01111111;
            code[1] = code[1] & 0b01111111;
            code[2] = code[2] & 0b00000000;
            code[3] = code[3] & 0b00000000;
        }
        if(calculation * 2 < 19){
            code[0] = code[0] & 0b01111111;
            code[1] = code[1] & 0b00000000;
            code[2] = code[2] & 0b00000000;
            code[3] = code[3] & 0b00000000;
        }

        uprintf("%d\n", calculation);
        seg7Update(code);
}

void
checkPushButton(uint32_t time)
{
    int code = pbRead();

    switch (code) {
    case 1:                                     // SW1: Start the buzzer
        if (displayState == Off) {
            uprintf("PercentileMode\n\r");
            displayState = On;

        }
        break;

    case 2:                                     // SW2: Stop the buzzer
        if (displayState == On) {
            uprintf("RawMode\n\r");
            displayState = Off;

        }
        break;


    }
}

void
checkRotation(uint32_t time)
{
    uint32_t delay;

   /* if(rotaryState == On){
        //uprintf("turning: %d\r\n", value);
        delay = 250;                // software debouncing
    }
    else if(rotaryState == Off){
        //uprintf("not turning \r\n");
        delay = 250;                // software debouncing
    }*/

    delay = 50;
    schdCallback(checkRotary, time + delay);
    schdCallback(checkPushButton, time + delay);
    if(displayState == On){
        schdCallback(checkSeg, time + delay);
        //uprintf("test1");
    }
    else if(displayState == Off){
        schdCallback(checkSeg2, time + delay);
        //uprintf("test2");
    }
    schdCallback(checkRotation, time + delay);
}

int main(void)
{
    lpInit();
    seg7Init();
    rotaryInit();

    uprintf("%s\n\r", "Lab 6: Rotary");



    // Schedule the first callback events for LED flashing and push button checking.
    // Those trigger callback chains. The time unit is millisecond.
    schdCallback(checkRotation, 1005);
    // Run the event scheduler to process callback events
    while (true) {
        schdExecute();
    }

}
