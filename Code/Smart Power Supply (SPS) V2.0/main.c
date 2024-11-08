/*
 * Smart Power Supply (SPS) V2.0.c
 * Created: 9/17/2024 8:43:58 PM
 *
 * Author: Basel Mohamed Mostafa Sayed
 * Email: baselmohamed802@gmail.com
 * LinkedIn: www.linkedin.com/in/basel-sayed-b11534243
 * Phone: 01033453452
 *
 * Description:
 * This main.c file contains the code for the Smart power supply V2.0.
 * The Smart Power Supply is a 120W power supply with many functionalities like
 * High Volt/Amp output, and Low Volt/Amp output. It also has Automatic overheat
 * shutdown detection using the LM35 temperature sensor. The main future of the
 * Power Supply is that everything is controlled via a menu using the LCD 16x2
 * and a simple potentiometer.
 */

#define F_CPU 16000000UL

/* UTILS */
#include "UTILS/Bit_operation.h"
#include "UTILS/STD_TYPES.h"
#include "UTILS/VECTOR.h"

/* MCAL */
#include <util/delay.h>

#include "../../../MCAL/ADC_DRIVER/ADC_DRIVER/ADC_PROGRAM.c"
#include "../../../MCAL/ADC_DRIVER/ADC_DRIVER/ADC_PROGRAM.h"
#include "../../../MCAL/ADC_DRIVER/ADC_DRIVER/ADC_REG.h"
#include "../../../MCAL/GIE_DRIVER/GIE_DRIVER/GIE_PROGRAM.c"
#include "../../../MCAL/GIE_DRIVER/GIE_DRIVER/GIE_PROGRAM.h"
#include "../../../MCAL/GIE_DRIVER/GIE_DRIVER/GIE_REG.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_CONFIG.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_PRIVATE.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_PROGRAM.c"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_PROGRAM.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_REG.h"
#include "../../../MCAL/TIMER/TMR1_INTERRUPT/TMR1_INTERRUPT/TMR1_CONFIG.h"
#include "../../../MCAL/TIMER/TMR1_INTERRUPT/TMR1_INTERRUPT/TMR1_PROGRAM.c"
#include "../../../MCAL/TIMER/TMR1_INTERRUPT/TMR1_INTERRUPT/TMR1_PROGRAM.h"
#include "../../../MCAL/TIMER/TMR1_INTERRUPT/TMR1_INTERRUPT/TMR1_REG.h"
#include "../../../MCAL/TIMER/TMR2_INTERRUPT/TMR2_INTERRUPT/TMR2_CONFIG.h"
#include "../../../MCAL/TIMER/TMR2_INTERRUPT/TMR2_INTERRUPT/TMR2_PROGRAM.h"
#include "../../../MCAL/TIMER/TMR2_INTERRUPT/TMR2_INTERRUPT/TMR2_PROGRAM.c"
#include "../../../MCAL/TIMER/TMR2_INTERRUPT/TMR2_INTERRUPT/TMR2_REG.h"
#include "ATmega32_DIO/DIO_PROGRAM.h"
#include "ATmega32_DIO/DIO_REG.h"

/* HAL */
#include "../../../HAL/LCD_DRIVER/LCD_DRIVER/LCD_AMIT_KIT_CONFIG.h"
#include "../../../HAL/LCD_DRIVER/LCD_DRIVER/LCD_PROGRAM.c"
#include "../../../HAL/LCD_DRIVER/LCD_DRIVER/LCD_PROGRAM.h"
#include "../../../HAL/LM35 - Temp Sensor/LM35 - Temp Sensor/LM35_PROGRAM.c"
#include "../../../HAL/LM35 - Temp Sensor/LM35 - Temp Sensor/LM35_PROGRAM.h"
#include "../../../HAL/SWITCH_DRIVER/SWITCH_DRIVER/SWITCH_PROGRAM.c"
#include "../../../HAL/SWITCH_DRIVER/SWITCH_DRIVER/SWITCH_PROGRAM.h"
#include "SPSV2_PROGRAM.h"

// Custom character for the cursor to display on screen
u8 arrowCursor[] = {0b01000, 0b01100, 0b01110, 0b11111,
                    0b11111, 0b01110, 0b01100, 0b01000};

int main(void) {
   // function to initialize all pins connected
   SPSV2_init();

   // Initializing All the HAL/MCAL components connected
   GIE_enable();
   LCD_init();
   ADC_init(ADC_REFERENCE_AVCC);
   TMR0_init(TMR0_FASTPWM_MODE, TMR0_PRELOAD_CLR, TMR0_PWM_NON_INVERT);

   // Calling the Start up function once
   SPSV2_startProg();

   // Defining variables
   u8 local_u8CurrentCursorPos = 0, local_u8CurrentScreenPos = 0;

   while (1) {
      // Read ADC value from channel 1
      u16 local_u16AdcValue = ADC_getValue(ADC_CHANNEL1);

      // Read Temperature
      SPSV2_readTemp();

      // Calling the function to update the screen and cursor position
      SPSV2_updateScreenPosition(local_u16AdcValue, &local_u8CurrentCursorPos,
                                 &local_u8CurrentScreenPos);

      // Calling the Print menu function
      SPSV2_printMenu(local_u8CurrentCursorPos, local_u8CurrentScreenPos);
      LCD_createAndDisplayChar(0, arrowCursor, local_u8CurrentCursorPos, 0);

      // Calling the function to choose which operation to initiate
      SPSV2_chooseFun(local_u8CurrentCursorPos, local_u8CurrentScreenPos);

      _delay_ms(200);
   }

   return 0;
}