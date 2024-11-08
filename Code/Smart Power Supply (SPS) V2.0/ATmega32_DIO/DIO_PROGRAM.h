/*
 * DIO_PROGRAM.h
 *
 *  Created on: Aug 12, 2024
 *      Author: Basel Mohamed Mostafa Sayed
 */

#ifndef DIO_PROGRAM_H_
#define DIO_PROGRAM_H_

/* DIO Ports */
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

/* DIO PIN and PORT Output/Input */
#define DIO_PIN_INPUT 0
#define DIO_PIN_OUTPUT 1
#define DIO_PIN_OUTPUT_HIGH 1
#define DIO_PIN_OUTPUT_LOW 0
#define DIO_PORT_INPUT 0
#define DIO_PORT_OUTPUT 1
#define DIO_PORT_OUTPUT_LOW 0
#define DIO_PORT_OUTPUT_HIGH 1

/* DIO pins */
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

/***** DIO PIN APIS *****/

// Function to set the pin direction to desired "input or output" state
void DIO_setPinDirection(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8dir);

// Function to set the desired output pin to "HIGH" or "LOW" state
void DIO_setPinVal(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8val);

// Function to toggle the pin
void DIO_togglePinVal(u8 copy_u8port, u8 copy_u8pin);

// Function to get the current value of the PIN, wither it's currently "HIGH" or "LOW"
u8 DIO_readPinVal(u8 copy_u8port, u8 copy_u8pin);

// Function that sets up the internal pull up resistor of the MC
void DIO_setInputInternalPullup(u8 copy_u8port, u8 copy_u8pin);

/***** DIO PORT APIS *****/
// Function to set an entire port direction memory to either be input or output
void DIO_setPortDir(u8 copy_u8port, u8 copy_u8dir);

// Function to set an entire port value to be either output HIGH or output LOW
void DIO_setPortVal(u8 copy_u8port, u8 copy_u8val);

#endif /* DIO_PROGRAM_H_ */
