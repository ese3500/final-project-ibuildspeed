#ifndef LIGHTS_H
#define LIGHTS_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

void Initialize_light_PWM();
uint16_t lights();
#endif
