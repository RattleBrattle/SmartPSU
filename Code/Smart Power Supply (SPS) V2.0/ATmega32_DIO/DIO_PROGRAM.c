/*
 * DIO_PROGRAM.c
 *
 *  Created on: Aug 13, 2024
 *      Author: Basel Mohamed Mostafa Sayed
 *      Description: DIO code for the Atmega32 AVR microcontroller.
 */

/* UTILS Libraries */
#include "../UTILS/STD_TYPES.h"
#include "../UTILS/Bit_operation.h"

/* MCAL Layer */
#include "DIO_PROGRAM.h"
#include "DIO_REG.h"

void DIO_setPinDirection(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8dir) {
   switch (copy_u8port) {
   case DIO_PORTA:
      switch (copy_u8dir) {
      case DIO_PIN_INPUT:
         CLR_BIT(DDRA_REG, copy_u8pin);
         break;
      case DIO_PIN_OUTPUT:
         SET_BIT(DDRA_REG, copy_u8pin);
         break;
      }
      break;
   case DIO_PORTB:
      switch (copy_u8dir) {
      case DIO_PIN_INPUT:
         CLR_BIT(DDRB_REG, copy_u8pin);
         break;
      case DIO_PIN_OUTPUT:
         SET_BIT(DDRB_REG, copy_u8pin);
         break;
      }
      break;
   case DIO_PORTC:
      switch (copy_u8dir) {
      case DIO_PIN_INPUT:
         CLR_BIT(DDRC_REG, copy_u8pin);
         break;
      case DIO_PIN_OUTPUT:
         SET_BIT(DDRC_REG, copy_u8pin);
         break;
      }
      break;
   case DIO_PORTD:
      switch (copy_u8dir) {
      case DIO_PIN_INPUT:
         CLR_BIT(DDRD_REG, copy_u8pin);
         break;
      case DIO_PIN_OUTPUT:
         SET_BIT(DDRD_REG, copy_u8pin);
         break;
      }
      break;
   default: // Add an Error Prompt or interrupt here later******
      break;
   }
}

void DIO_setPinVal(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8val) {
   switch (copy_u8port) {
   case DIO_PORTA:
      switch (copy_u8val) {
      case DIO_PIN_OUTPUT_LOW:
         CLR_BIT(PORTA_REG, copy_u8pin);
         break;
      case DIO_PIN_OUTPUT_HIGH:
         SET_BIT(PORTA_REG, copy_u8pin);
         break;
      }
      break;
   case DIO_PORTB:
      switch (copy_u8val) {
      case DIO_PIN_OUTPUT_LOW:
         CLR_BIT(PORTB_REG, copy_u8pin);
         break;
      case DIO_PIN_OUTPUT_HIGH:
         SET_BIT(PORTB_REG, copy_u8pin);
         break;
      }
      break;
   case DIO_PORTC:
      switch (copy_u8val) {
      case DIO_PIN_OUTPUT_LOW:
         CLR_BIT(PORTC_REG, copy_u8pin);
         break;
      case DIO_PIN_OUTPUT_HIGH:
         SET_BIT(PORTC_REG, copy_u8pin);
         break;
      }
      break;
   case DIO_PORTD:
      switch (copy_u8val) {
      case DIO_PIN_OUTPUT_LOW:
         CLR_BIT(PORTD_REG, copy_u8pin);
         break;
      case DIO_PIN_OUTPUT_HIGH:
         SET_BIT(PORTD_REG, copy_u8pin);
         break;
      }
      break;
   default: // Add an Error Prompt or interrupt here later******
      break;
   }
}

void DIO_togglePinVal(u8 copy_u8port, u8 copy_u8pin) {
   switch (copy_u8port) {
   case DIO_PORTA:
      TOGG_BIT(PORTA_REG, copy_u8pin);
      break;
   case DIO_PORTB:
      TOGG_BIT(PORTB_REG, copy_u8pin);
      break;
      break;
   case DIO_PORTC:
      TOGG_BIT(PORTC_REG, copy_u8pin);
      break;
   case DIO_PORTD:
      TOGG_BIT(PORTD_REG, copy_u8pin);
      break;
   default: // Add an Error Prompt or interrupt here later******
      break;
   }
}

u8 DIO_readPinVal(u8 copy_u8port, u8 copy_u8pin) {
   u8 local_u8State;

   switch (copy_u8port) {
   case DIO_PORTA:
      local_u8State = GET_BIT(PINA_REG, copy_u8pin);
      break;
   case DIO_PORTB:
      local_u8State = GET_BIT(PINB_REG, copy_u8pin);
      break;
   case DIO_PORTC:
      local_u8State = GET_BIT(PINC_REG, copy_u8pin);
      break;
   case DIO_PORTD:
      local_u8State = GET_BIT(PINC_REG, copy_u8pin);
      break;
   default: // Add an Error Prompt or interrupt here later******
      break;
   }

   return local_u8State;
}

void DIO_setInputInternalPullup(u8 copy_u8port, u8 copy_u8pin) {
   switch (copy_u8port) {
   case DIO_PORTA:
      DIO_setPinVal(DIO_PORTA, copy_u8pin, DIO_PIN_OUTPUT_HIGH);
      break;
   case DIO_PORTB:
      DIO_setPinVal(DIO_PORTB, copy_u8pin, DIO_PIN_OUTPUT_HIGH);
      break;
   case DIO_PORTC:
      DIO_setPinVal(DIO_PORTC, copy_u8pin, DIO_PIN_OUTPUT_HIGH);
      break;
   case DIO_PORTD:
      DIO_setPinVal(DIO_PORTD, copy_u8pin, DIO_PIN_OUTPUT_HIGH);
      break;
   }
}

void DIO_setPortDir(u8 copy_u8port, u8 copy_u8dir) {
   switch (copy_u8port) {
   case DIO_PORTA:
      switch (copy_u8dir) {
      case DIO_PORT_INPUT:
         CLR_BIT(DDRA_REG, 0);
         CLR_BIT(DDRA_REG, 1);
         CLR_BIT(DDRA_REG, 2);
         CLR_BIT(DDRA_REG, 3);
         CLR_BIT(DDRA_REG, 4);
         CLR_BIT(DDRA_REG, 5);
         CLR_BIT(DDRA_REG, 6);
         CLR_BIT(DDRA_REG, 7);
         break;
      case DIO_PORT_OUTPUT:
         SET_BIT(DDRA_REG, 0);
         SET_BIT(DDRA_REG, 1);
         SET_BIT(DDRA_REG, 2);
         SET_BIT(DDRA_REG, 3);
         SET_BIT(DDRA_REG, 4);
         SET_BIT(DDRA_REG, 5);
         SET_BIT(DDRA_REG, 6);
         SET_BIT(DDRA_REG, 7);
         break;
      }
      break;
   case DIO_PORTB:
      switch (copy_u8dir) {
      case DIO_PORT_INPUT:
         CLR_BIT(DDRB_REG, 0);
         CLR_BIT(DDRB_REG, 1);
         CLR_BIT(DDRB_REG, 2);
         CLR_BIT(DDRB_REG, 3);
         CLR_BIT(DDRB_REG, 4);
         CLR_BIT(DDRB_REG, 5);
         CLR_BIT(DDRB_REG, 6);
         CLR_BIT(DDRB_REG, 7);
         break;
      case DIO_PORT_OUTPUT:
         SET_BIT(DDRB_REG, 0);
         SET_BIT(DDRB_REG, 1);
         SET_BIT(DDRB_REG, 2);
         SET_BIT(DDRB_REG, 3);
         SET_BIT(DDRB_REG, 4);
         SET_BIT(DDRB_REG, 5);
         SET_BIT(DDRB_REG, 6);
         SET_BIT(DDRB_REG, 7);
         break;
      }
      break;
   case DIO_PORTC:
      switch (copy_u8dir) {
      case DIO_PORT_INPUT:
         CLR_BIT(DDRC_REG, 0);
         CLR_BIT(DDRC_REG, 1);
         CLR_BIT(DDRC_REG, 2);
         CLR_BIT(DDRC_REG, 3);
         CLR_BIT(DDRC_REG, 4);
         CLR_BIT(DDRC_REG, 5);
         CLR_BIT(DDRC_REG, 6);
         CLR_BIT(DDRC_REG, 7);
         break;
      case DIO_PORT_OUTPUT:
         SET_BIT(DDRC_REG, 0);
         SET_BIT(DDRC_REG, 1);
         SET_BIT(DDRC_REG, 2);
         SET_BIT(DDRC_REG, 3);
         SET_BIT(DDRC_REG, 4);
         SET_BIT(DDRC_REG, 5);
         SET_BIT(DDRC_REG, 6);
         SET_BIT(DDRC_REG, 7);
         break;
      }
      break;
   case DIO_PORTD:
      switch (copy_u8dir) {
      case DIO_PORT_INPUT:
         CLR_BIT(DDRD_REG, 0);
         CLR_BIT(DDRD_REG, 1);
         CLR_BIT(DDRD_REG, 2);
         CLR_BIT(DDRD_REG, 3);
         CLR_BIT(DDRD_REG, 4);
         CLR_BIT(DDRD_REG, 5);
         CLR_BIT(DDRD_REG, 6);
         CLR_BIT(DDRD_REG, 7);
         break;
      case DIO_PORT_OUTPUT:
         SET_BIT(DDRD_REG, 0);
         SET_BIT(DDRD_REG, 1);
         SET_BIT(DDRD_REG, 2);
         SET_BIT(DDRD_REG, 3);
         SET_BIT(DDRD_REG, 4);
         SET_BIT(DDRD_REG, 5);
         SET_BIT(DDRD_REG, 6);
         SET_BIT(DDRD_REG, 7);
         break;
      }
      break;
   default: // Add an Error Prompt or interrupt here later******
      break;
   }
}

void DIO_setPortVal(u8 copy_u8port, u8 copy_u8val) {
   switch (copy_u8port) {
   case DIO_PORTA:
      switch (copy_u8val) {
      case DIO_PORT_OUTPUT_LOW:
         CLR_BIT(PORTA_REG, 0);
         CLR_BIT(PORTA_REG, 1);
         CLR_BIT(PORTA_REG, 2);
         CLR_BIT(PORTA_REG, 3);
         CLR_BIT(PORTA_REG, 4);
         CLR_BIT(PORTA_REG, 5);
         CLR_BIT(PORTA_REG, 6);
         CLR_BIT(PORTA_REG, 7);
         break;
      case DIO_PORT_OUTPUT_HIGH:
         SET_BIT(PORTA_REG, 0);
         SET_BIT(PORTA_REG, 1);
         SET_BIT(PORTA_REG, 2);
         SET_BIT(PORTA_REG, 3);
         SET_BIT(PORTA_REG, 4);
         SET_BIT(PORTA_REG, 5);
         SET_BIT(PORTA_REG, 6);
         SET_BIT(PORTA_REG, 7);
         break;
      }
      break;
   case DIO_PORTB:
      switch (copy_u8val) {
      case DIO_PORT_OUTPUT_LOW:
         CLR_BIT(PORTB_REG, 0);
         CLR_BIT(PORTB_REG, 1);
         CLR_BIT(PORTB_REG, 2);
         CLR_BIT(PORTB_REG, 3);
         CLR_BIT(PORTB_REG, 4);
         CLR_BIT(PORTB_REG, 5);
         CLR_BIT(PORTB_REG, 6);
         CLR_BIT(PORTB_REG, 7);
         break;
      case DIO_PORT_OUTPUT_HIGH:
         SET_BIT(PORTB_REG, 0);
         SET_BIT(PORTB_REG, 1);
         SET_BIT(PORTB_REG, 2);
         SET_BIT(PORTB_REG, 3);
         SET_BIT(PORTB_REG, 4);
         SET_BIT(PORTB_REG, 5);
         SET_BIT(PORTB_REG, 6);
         SET_BIT(PORTB_REG, 7);
         break;
      }
      break;
   case DIO_PORTC:
      switch (copy_u8val) {
      case DIO_PORT_OUTPUT_LOW:
         CLR_BIT(PORTC_REG, 0);
         CLR_BIT(PORTC_REG, 1);
         CLR_BIT(PORTC_REG, 2);
         CLR_BIT(PORTC_REG, 3);
         CLR_BIT(PORTC_REG, 4);
         CLR_BIT(PORTC_REG, 5);
         CLR_BIT(PORTC_REG, 6);
         CLR_BIT(PORTC_REG, 7);
         break;
      case DIO_PORT_OUTPUT_HIGH:
         SET_BIT(PORTC_REG, 0);
         SET_BIT(PORTC_REG, 1);
         SET_BIT(PORTC_REG, 2);
         SET_BIT(PORTC_REG, 3);
         SET_BIT(PORTC_REG, 4);
         SET_BIT(PORTC_REG, 5);
         SET_BIT(PORTC_REG, 6);
         SET_BIT(PORTC_REG, 7);
         break;
      }
      break;
   case DIO_PORTD:
      switch (copy_u8val) {
      case DIO_PORT_OUTPUT_LOW:
         CLR_BIT(PORTD_REG, 0);
         CLR_BIT(PORTD_REG, 1);
         CLR_BIT(PORTD_REG, 2);
         CLR_BIT(PORTD_REG, 3);
         CLR_BIT(PORTD_REG, 4);
         CLR_BIT(PORTD_REG, 5);
         CLR_BIT(PORTD_REG, 6);
         CLR_BIT(PORTD_REG, 7);
         break;
      case DIO_PORT_OUTPUT_HIGH:
         SET_BIT(PORTD_REG, 0);
         SET_BIT(PORTD_REG, 1);
         SET_BIT(PORTD_REG, 2);
         SET_BIT(PORTD_REG, 3);
         SET_BIT(PORTD_REG, 4);
         SET_BIT(PORTD_REG, 5);
         SET_BIT(PORTD_REG, 6);
         SET_BIT(PORTD_REG, 7);
         break;
      }
      break;
   default: // Add an Error Prompt or interrupt here later******
      break;
   }
}