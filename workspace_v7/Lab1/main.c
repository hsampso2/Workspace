/*
 * main.c
 *
 * ECE 266 Lab 1, Spring 2018
 *
 * Created by Zhao Zhang
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "launchpad.h"
int i = 0;

// Event-drive code for flashing LED
void
flashLED(uint32_t time)							// the scheduled time
{
	static enum {OFF, ON} state = OFF;			// LED ON/OFF state
	int delay = 1000;							// next LED event time

	// Flip LED and record state change
	switch (state) {
	case OFF:
		ledTurnOnOff(true, true, true);
		state = ON;
		break;

	case ON:
		ledTurnOnOff(false, false, false);
		state = OFF;
		break;
	}

	// Schedule the next callback
	schdCallback(flashLED, time + delay);
}

// Event driven code for checking push button
void
checkPushButton(uint32_t time)
{
	int code = pbRead();
	uint32_t delay;

	switch (code) {
	case 1:
		uprintf("%s\n\r", "SW1 is pushed.");
		ledTurnOnOff(false, false, false);
		delay = 250;							// Use an inertia for soft debouncing
		break;

	case 2:
		uprintf("%s\n\r", "SW2 is pushed");
		if(i==0){
		    ledTurnOnOff(true, true, true);
		    i++;
		}
		else if(i==1){
		    ledTurnOnOff(true, false, false);
		    i++;
		}
		else if(i==2){
		    ledTurnOnOff(false, false, true);
		    i++;
		}
		else if(i==3){
		    ledTurnOnOff(false, true, false);
		    i = 0;
		}
		delay = 250;							// Use an inertia for soft debouncing
		break;

	default:
		delay = 10;
	}

	schdCallback(checkPushButton, time + delay);
}

int main(void)
{
	lpInit();

	uprintf("%s\n\r", "Hello, world!");

	// Schedule the first callback events for LED flashing and push button checking.
	// Those trigger callback chains. The time unit is millisecond.
	//schdCallback(flashLED, 1000);
	schdCallback(checkPushButton, 1005);

	// Loop forever
	while (true) {
		schdExecute();
	}
}
