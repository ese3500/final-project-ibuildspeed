/*
 * i2c.h
 *
 * Created: 4/25/2024 10:33:54 PM
 *  Author: Ahmed
 */
#ifndef I2C_H
#define I2C_H

#include <stdint.h>

// Macro definitions
#define F_CPU          16000000UL                             // Clock Speed
#define BAUD_RATE      9600                                   // Baud rate for UART
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)   // Baud rate prescaler

// Function prototypes for GAS sensor
void startCondition_gas(void);
void startI2C_gas(void);
void stop_gas(void);
void setAddress_gas(uint8_t write_enable);
uint8_t readByte_gas(uint8_t ack);
uint16_t readGas(void);

// Function prototypes for BRAKE sensor
void startCondition_brake(void);
void startI2C_brake(void);
void stop_brake(void);
void setAddress_brake(uint8_t write_enable);
uint8_t readByte_brake(uint8_t ack);
uint16_t readBrake(void);

#endif   // I2C_H
