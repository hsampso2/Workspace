/*
 * motion.h: Basic driver functions for the buzzer.
 * This code is designed for Lab 4 Motion Detection Alarm
 *
 *  Created on: Sep 20, 2016
 *      Author: zzhang
 */

#ifndef RANGER_H_
#define RANGER_H_

// Initialize the motion
void rangerInit();

// Turn on the motion
uint32_t rangerDetect();

static void sendStartPulse();

#endif /* MOTION_H_ */
