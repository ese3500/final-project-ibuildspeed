#ifndef SPEEDCONTROLLERS_H
#define SPEEDCONTROLLERS_H
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

void Initialize_throttle();
double set_throttle(uint16_t acc_value);
double set_brake(uint16_t brake_value);
void e_brake();
void brake_lights();

void neutral();
#endif