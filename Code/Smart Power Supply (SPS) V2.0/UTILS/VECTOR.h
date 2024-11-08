/*
 * VECTOR.h
 *
 * Created: 9/10/2024 8:53:46 AM
 *  Author: Basel Mohamed Mostafa Sayed
 *  Description: This file contains all vectors related to interrupt peripherals for the ATmega32
 */

#ifndef VECTOR_H_
#define VECTOR_H_

/* Interrupt Service Routine (ISR) */
#define ISR(vector_num) void vector_num(void) __attribute__((signal, used, externally_visible)); \
                        void vector_num(void)

/* Vector Numbers */
#define INT_0 __vector_1
#define INT_1 __vector_2
#define INT_2 __vector_3
#define TMR1_CAPT_VECT __vector_6
#define TMR1_COMPA_VECT __vector_7
#define TMR1_COMPB_VECT __vector_8
#define TMR1_NORMAL_VECT __vector_9
#define TMR2_CTC_VECT __vector_4 
#define TMR2_NORMAL_VECT __vector_5
#define TMR0_CTC_VECT __vector_10
#define TMR0_NORMAL_VECT __vector_11

#endif /* VECTOR_H_ */
