/*
 *SPSV2_PROGRAM.c
 *
 *Created: 9/17/2024 8:49:37 PM
 *Author: Basel Mohamed Mostafa Sayed
 *Description: This file contains all the source code for the functions used in
 *the Smart Power Supply V2.0 system
 */
#define F_CPU 16000000UL

/*UTILS */
#include "UTILS/Bit_operation.h"
#include "UTILS/STD_TYPES.h"
#include "UTILS/VECTOR.h"

/*MCAL */
#include <util/delay.h>

#include "../../../MCAL/ADC_DRIVER/ADC_DRIVER/ADC_PROGRAM.h"
#include "../../../MCAL/ADC_DRIVER/ADC_DRIVER/ADC_REG.h"
#include "../../../MCAL/GIE_DRIVER/GIE_DRIVER/GIE_PROGRAM.h"
#include "../../../MCAL/GIE_DRIVER/GIE_DRIVER/GIE_REG.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_CONFIG.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_PROGRAM.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_REG.h"
#include "../../../MCAL/TIMER/TMR1_INTERRUPT/TMR1_INTERRUPT/TMR1_CONFIG.h"
#include "../../../MCAL/TIMER/TMR1_INTERRUPT/TMR1_INTERRUPT/TMR1_PROGRAM.h"
#include "../../../MCAL/TIMER/TMR1_INTERRUPT/TMR1_INTERRUPT/TMR1_REG.h"
#include "../../../MCAL/TIMER/TMR2_INTERRUPT/TMR2_INTERRUPT/TMR2_CONFIG.h"
#include "../../../MCAL/TIMER/TMR2_INTERRUPT/TMR2_INTERRUPT/TMR2_PROGRAM.h"
#include "../../../MCAL/TIMER/TMR2_INTERRUPT/TMR2_INTERRUPT/TMR2_REG.h"
#include "ATmega32_DIO/DIO_PROGRAM.h"
#include "ATmega32_DIO/DIO_REG.h"

/*HAL */
#include "../../../HAL/LCD_DRIVER/LCD_DRIVER/LCD_AMIT_KIT_CONFIG.h"
#include "../../../HAL/LCD_DRIVER/LCD_DRIVER/LCD_PRIVATE.h"
#include "../../../HAL/LCD_DRIVER/LCD_DRIVER/LCD_PROGRAM.h"
#include "../../../HAL/LM35 - Temp Sensor/LM35 - Temp Sensor/LM35_PROGRAM.h"
#include "../../../HAL/SWITCH_DRIVER/SWITCH_DRIVER/SWITCH_PROGRAM.h"
#include "SPSV2_PROGRAM.h"

u8 arrowCursor2[] = {0b01000, 0b01100, 0b01110, 0b11111,
                     0b11111, 0b01110, 0b01100, 0b01000};

void SPSV2_init(void) {
   /*Initializing important pin directions */
   DIO_setPinDirection(MAIN_MENU_POT_PORT, MAIN_MENU_POT_PIN,
                       DIO_PIN_INPUT);  // Potentiometer Pin input ADC
   DIO_setPinDirection(VOLT_DIV_HIGH_PORT, VOLT_DIV_HIGH_PIN,
                       DIO_PIN_INPUT);  // High mode Voltage Divider pin
   DIO_setPinDirection(VOLT_DIV_LOW_PORT, VOLT_DIV_LOW_PIN, DIO_PIN_INPUT); // Low mode voltage Divider pin
   DIO_setPinDirection(
       ACS712_PORT, ACS712_PIN,
       DIO_PIN_OUTPUT);  // Current measurement module for Low/High outputs pin
   DIO_setPinDirection(PWM0_PORT, PWM0_PIN,
                       DIO_PIN_OUTPUT);               // PWM on Timer 0 pin
   SWITCH_init(ENTER_SWITCH_PORT, ENTER_SWITCH_PIN);  // Enter switch Pin
   SWITCH_init(HOME_SWITCH_PORT, HOME_SWITCH_PIN);    // Home switch Pin
   DIO_setPinDirection(
       RELAY_HIGH_OUT_PORT, RELAY_HIGH_OUT_PIN,
       DIO_PIN_OUTPUT);  // Relay control Pin for the High power output
   DIO_setPinDirection(
       RELAY_LOW_OUT_PORT, RELAY_LOW_OUT_PIN,
       DIO_PIN_OUTPUT);  // Relay control Pin for the low power output
   DIO_setPinDirection(LED_INDIC_HIGH_PORT, LED_INDIC_HIGH_PIN,
                       DIO_PIN_OUTPUT);  // LED indicator pin for High output
   DIO_setPinDirection(LED_INDIC_LOW_PORT, LED_INDIC_LOW_PIN,
                       DIO_PIN_OUTPUT);  // LED indicator pin for low output
   DIO_setPinDirection(CHARGE_MODE_SIG_PORT, CHARGE_MODE_SIG_PIN,
                       DIO_PIN_OUTPUT);  // Charging mode activate signal
   DIO_setPinDirection(LM35_PORT, LM35_PIN,
                       DIO_PIN_INPUT);  // Temperature sensor pin (LM35)
   DIO_setPinDirection(ACS712_MEASUREMENT_PORT, ACS712_MEASUREMENT_PIN,
                       DIO_PIN_OUTPUT);  // Current measurement relay signal
   DIO_setPinDirection(FAN_PORT, FAN_PIN, DIO_PIN_OUTPUT); // 12V Fan header pin
}

void SPSV2_startProg(void) {
   // Printing on the LCD details about the program
   LCD_displayString((u8 *)"SPS V2");
   LCD_moveCursor(1, 0);
   LCD_displayString((u8 *)"Initializing .");
   _delay_ms(500);
   LCD_displayString((u8 *)".");
   _delay_ms(500);
   LCD_displayString((u8 *)".");
}

void SPSV2_readTemp(void) {
   u8 local_u8Err = 0;
   f32 local_u16Temp = LM35_getVal(ADC_CHANNEL4);

   // if the temperature exceeds 35 degree Celsius, the program prompts the user
   // with a warning to turn off the SPSU
   if (local_u16Temp > 35.0) {
      LCD_clear();
      LCD_displayString((u8 *)"Warning");
      _delay_ms(250);
      LCD_displayChar('!');
      _delay_ms(250);
      LCD_displayChar('!');
      _delay_ms(250);
      LCD_clear();
      LCD_displayString((u8 *)"Temperature is");
      LCD_moveCursor(1, 0);
      LCD_displayString((u8 *)"Too hot!");
      _delay_ms(750);
      LCD_clear();
      LCD_displayString((u8 *)"Please turn off");
      LCD_moveCursor(1, 0);
      LCD_displayString((u8 *)"PSU for now...");
      _delay_ms(2000);
      LCD_clear();

      // Setting error to 1
      local_u8Err = 1;
   } else {
      // Setting error to 0
      local_u8Err = 0;
   }
}

void SPSV2_updateScreenPosition(u16 copy_u16PotAdcVal, u8 *copy_u8CursorPos,
                                u8 *copy_u8ScreenPos) {
   // Conditions to change the variables based on the ADC value.
   if (copy_u16PotAdcVal >= 0 && copy_u16PotAdcVal < 170) {
      *copy_u8ScreenPos = SCREEN_1;
      *copy_u8CursorPos =
          0;  // High Voltage output using the buck converter circuit.
   } else if (copy_u16PotAdcVal >= 170 && copy_u16PotAdcVal < 340) {
      *copy_u8ScreenPos = SCREEN_1;
      *copy_u8CursorPos = 1;  // Second function of traditional Voltage output.
   } else if (copy_u16PotAdcVal >= 340 && copy_u16PotAdcVal < 510) {
      *copy_u8ScreenPos = SCREEN_2;
      *copy_u8CursorPos =
          0;  // Third function to turn on lithium battery charging.
   } else if (copy_u16PotAdcVal >= 510 && copy_u16PotAdcVal < 680) {
      *copy_u8ScreenPos = SCREEN_2;
      *copy_u8CursorPos =
          1;  // Fourth function to Measure input signal frequency and duty cycle.
   } else if (copy_u16PotAdcVal >= 680 && copy_u16PotAdcVal < 850) {
      *copy_u8ScreenPos = SCREEN_3;
      *copy_u8CursorPos =
          0;  // Fifth function to Control Fan Speed.
   } else if (copy_u16PotAdcVal >= 850) {
   *copy_u8ScreenPos = SCREEN_3;
   *copy_u8CursorPos =
   1;  // Sixth function to turn off the fan completely.
   }
}

void SPSV2_printMenu(u8 copy_u8CursorPos, u8 copy_u8ScreenPos) {
   // Displaying the cursor on the screen
   LCD_clear();

   switch (copy_u8ScreenPos) {
      case SCREEN_1:
         LCD_displayString((u8 *)" High Power mode");
         LCD_moveCursor(1, 0);
         LCD_displayString((u8 *)" Low Power mode");
         break;
      case SCREEN_2:
         LCD_displayString((u8 *)" Charging mode");
         LCD_moveCursor(1, 0);
         LCD_displayString((u8 *)" Frequency Count");
         break;
      case SCREEN_3:
         LCD_displayString((u8 *)" Fan Speed");
		 LCD_moveCursor(1, 0);
		 LCD_displayString(" Turn Off Fan");
         break;
      default:  // Displaying error code 0, relating to the menu function not
                // working correctly.
         LCD_displayString((u8 *)"Error Code:");
         LCD_displayNumber(ERR_MENU, 0);
         break;
   }
}

void SPSV2_updateCursorPrescaler(u16 copy_u16PotAdcVal,
                                 u8 *copy_u8CursorPosFreq,
                                 u8 *copy_u8ScreenPosFreq) {
   // Conditions to change the variables based on the ADC value.
   if (copy_u16PotAdcVal < 204) {
      *copy_u8ScreenPosFreq = SCREEN_1;
      *copy_u8CursorPosFreq = 0;  // Prescaler 1
   } else if (copy_u16PotAdcVal < 408) {
      *copy_u8ScreenPosFreq = SCREEN_1;
      *copy_u8CursorPosFreq = 2;  // Prescaler 8
   } else if (copy_u16PotAdcVal < 612) {
      *copy_u8ScreenPosFreq = SCREEN_1;
      *copy_u8CursorPosFreq = 4;  // Prescaler 64
   } else if (copy_u16PotAdcVal < 816) {
      *copy_u8ScreenPosFreq = SCREEN_1;
      *copy_u8CursorPosFreq = 7;  // Prescaler 256
   } else {
      *copy_u8ScreenPosFreq = SCREEN_1;
      *copy_u8CursorPosFreq = 11;  // Prescaler 1024
   }
}

void SPSV2_printMenuPrescaler(u8 copy_u8CursorPosFreq,
                              u8 copy_u8ScreenPosFreq) {
   // Displaying the cursor on the screen
   LCD_clear();

   switch (copy_u8ScreenPosFreq) {
      case SCREEN_1:
         LCD_displayString((u8 *)"Select Prescaler:");
         LCD_moveCursor(1, 0);
         LCD_displayString((u8 *)" 1 8 64 256 1024");
         break;
      default:  // Displaying error code 2, relating to the selection of
                // Prescaler not functioning correctly.
         LCD_displayString((u8 *)"Error Code: ");
         LCD_displayNumber(ERR_MENU_FREQ, 0);
         break;
   }
}

void SPSV2_choosePrescaler(u8 copy_u8CursorPos, u8 copy_u8ScreenPos,
                           u8 *copy_u8PrescalerVal) {
   u8 local_u8EnterSwitch = SWITCH_getState(ENTER_SWITCH_PORT, ENTER_SWITCH_PIN,
                                            SWITCH_INPUT_PULLDOWN);

   if (local_u8EnterSwitch) {
      switch (copy_u8ScreenPos) {
         case SCREEN_1:
            switch (copy_u8CursorPos) {
               case 0:
                  *copy_u8PrescalerVal = TMR1_PRESCALER_1;
                  break;
               case 2:
                  *copy_u8PrescalerVal = TMR1_PRESCALER_8;
                  break;
               case 4:
                  *copy_u8PrescalerVal = TMR1_PRESCALER_64;
                  break;
               case 7:
                  *copy_u8PrescalerVal = TMR1_PRESCALER_256;
                  break;
               case 11:
                  *copy_u8PrescalerVal = TMR1_PRESCALER_1024;
                  break;
               default:
                  // Displaying error code 3, relating to selection of Prescaler
                  // malfunctioned.
                  LCD_displayString((u8 *)"Error Code:");
                  LCD_displayNumber(ERR_SELECT_PRESCALER, 0);
                  break;
            }

            break;
         default:
            // Displaying error code 3, relating to selection of Prescaler
            // malfunctioned.
            LCD_displayString((u8 *)"Error Code:");
            LCD_displayNumber(ERR_SELECT_PRESCALER, 0);
            break;
      }
   }
}

void SPSV2_chooseFun(u8 copy_u8CursorPos, u8 copy_u8ScreenPos) {
   u8 local_u8EnterSwitch = SWITCH_getState(ENTER_SWITCH_PORT, ENTER_SWITCH_PIN,
                                            SWITCH_INPUT_PULLDOWN);

   if (local_u8EnterSwitch) {
      switch (copy_u8ScreenPos) {
         case SCREEN_1:
            switch (copy_u8CursorPos) {
               case 0:
                  SPSV2_highPowerOut();
                  break;
               case 1:
                  SPSV2_lowPowerOut();
                  break;
            }

            break;
         case SCREEN_2:
            switch (copy_u8CursorPos) {
               case 0:
                  SPSV2_chargingMode();
                  break;
               case 1:
                  SPSV2_freqCounterIcp();
                  break;
            }

            break;
         case SCREEN_3:
            switch (copy_u8CursorPos) {
               case 0:
			      SPSV2_controlFanSpeed();
                  break;
               case 1:
			      SPSV2_turnOffFan();
                  break;
            }

            break;
         default:  // Displaying error code 0, relating to the menu function not
                   // working correctly.
            LCD_displayString((u8 *)"Error Code:");
            LCD_displayNumber(ERR_FUNCTIONS, 0);
            break;
      }
   }
}

u8 SPSV2_mapAdcToPwm(u16 copy_u16AdcValue) {
   // Example piecewise function (you may need to adjust these values based on
   // your observations)
   if (copy_u16AdcValue < 512) {
      return (u8)((copy_u16AdcValue * 50) / 511);  // Scale 0-511 to 0-50
   } else {
      return (u8)(50 + ((copy_u16AdcValue - 512) * 50) /
                           511);  // Scale 512-1023 to 50-100
   }
}

f32 SPSV2_convertADCToVoltage(u16 copy_u16AdcValue) {
   const f32 ADC_REF_VOLTAGE = 5.0;

   // Read ADC value from channel 0
   u16 adcValue = ADC_getValue(ADC_CHANNEL0);

   // Calculate the output voltage from ADC value
   f32 copy_f32Vout = (adcValue / 1023.0) * ADC_REF_VOLTAGE;

   // Calculate the input voltage using the voltage divider formula
   f32 copy_f32Vin = copy_f32Vout * ((R1 + R2) / (f32)R2);

   return copy_f32Vin;
}

f32 SPSV2_convertADCToVoltage_LOWMODE(void) {
	const f32 ADC_REF_VOLTAGE = 5.0;

	// Read ADC value from channel 0
	u16 adcValue = ADC_getValue(ADC_CHANNEL3);

	// Calculate the output voltage from ADC value
	f32 copy_f32Vout = (adcValue / 1023.0) * ADC_REF_VOLTAGE;

	// Calculate the input voltage using the voltage divider formula
	f32 copy_f32Vin = copy_f32Vout * ((R1L + R2L) / (f32)R2L);

	return copy_f32Vin;
}

f32 SPSV2_readCurrent(void) {
   const f32 ADC_REF_VOLTAGE = 5.0;
   const f32 CURRENT_SENSITIVITY =
       0.100;  // Sensitivity for ACS712-20B: 100mV/A
   const u16 ZERO_CURRENT_OFFSET =
       512;  // ADC value at zero current (approx. 2.5V for 5V supply)

   // Read ADC value from channel 2
   u16 adcValue = ADC_getValue(ADC_CHANNEL2);

   // Convert ADC value to voltage
   f32 voltage = (adcValue / 1023.0) * ADC_REF_VOLTAGE;

   // Calculate the current
   f32 current = (voltage - (ADC_REF_VOLTAGE / 2)) / CURRENT_SENSITIVITY;

   return current;
}

void SPSV2_highPowerOut(void) {
   // Clearing the screen before displaying the contents of the function and
   // enabling the Relay
   LCD_clear();
   DIO_setPinVal(RELAY_HIGH_OUT_PORT, RELAY_HIGH_OUT_PIN, DIO_PIN_OUTPUT_HIGH);
   // Turning on LED indicator
   DIO_setPinVal(LED_INDIC_HIGH_PORT, LED_INDIC_HIGH_PIN, DIO_PIN_OUTPUT_HIGH);
   // Current sensor read HIGH mode output
   DIO_setPinVal(ACS712_MEASUREMENT_PORT, ACS712_MEASUREMENT_PIN,
                 DIO_PIN_OUTPUT_LOW);

   while (1) {
      // Reading the home switch state
      u8 local_u8HomeSwitch = SWITCH_getState(HOME_SWITCH_PORT, HOME_SWITCH_PIN,
                                              SWITCH_INPUT_PULLDOWN);
      // Reading the ADC Value
      u16 local_u16AdcValue = ADC_getValue(ADC_CHANNEL1);
      f32 local_f32VoltVal = SPSV2_convertADCToVoltage(local_u16AdcValue);
      f32 local_f32CurrentVal = SPSV2_readCurrent();

      // Map the ADC value to PWM duty cycle using a piecewise function
      u8 pwmDutyCycle = SPSV2_mapAdcToPwm(local_u16AdcValue);

      // Generating a variable PWM signal based off the values of the main
      // potentiometer
      TMR0_generatePWM(pwmDutyCycle, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_64);

      // Displaying the voltage and current values being read
      LCD_displayString((u8 *)"Voltage: ");
      LCD_displayNumber(local_f32VoltVal, 2);
      LCD_displayChar('V');
      LCD_moveCursor(1, 0);
      LCD_displayString((u8 *)"Current: ");
      LCD_displayNumber(local_f32CurrentVal, 2);
      _delay_ms(350);
	  LCD_clear();

      if (local_u8HomeSwitch) {
         break;
      }
   }

   // Disabling TMR0 PWM output and clearing the LCD screen
   DIO_setPinVal(RELAY_HIGH_OUT_PORT, RELAY_HIGH_OUT_PIN, DIO_PIN_OUTPUT_LOW);
   DIO_setPinVal(LED_INDIC_HIGH_PORT, LED_INDIC_HIGH_PIN, DIO_PIN_OUTPUT_LOW);
   DIO_setPinVal(ACS712_MEASUREMENT_PORT, ACS712_MEASUREMENT_PIN,
                 DIO_PIN_OUTPUT_LOW);
   GIE_disable();
   TMR0_stop();
   LCD_clear();
}

void SPSV2_lowPowerOut(void) {
   // Clearing the screen before displaying the contents of the function and
   // enabling the Relay
   LCD_clear();
   DIO_setPinVal(RELAY_LOW_OUT_PORT, RELAY_LOW_OUT_PIN, DIO_PIN_OUTPUT_HIGH);
   // Turning on LED
   DIO_setPinVal(LED_INDIC_LOW_PORT, LED_INDIC_LOW_PIN, DIO_PIN_OUTPUT_HIGH);
   // Current sensor read LOW mode
   DIO_setPinVal(ACS712_MEASUREMENT_PORT, ACS712_MEASUREMENT_PIN,
                 DIO_PIN_OUTPUT_HIGH);

   // Printing information for the user on the current mode
   LCD_displayString((u8 *)"This mode is ");
   LCD_moveCursor(1, 0);
   LCD_displayString((u8 *)"Controlled by..");
   _delay_ms(350);
   LCD_clear();
   LCD_displayString((u8 *)"Potentiometers");
   LCD_moveCursor(1, 0);
   LCD_displayString((u8 *)"By the output");
   _delay_ms(350);
   LCD_clear();

   while (1) {
      // Reading the home switch state
      u8 local_u8HomeSwitch = SWITCH_getState(HOME_SWITCH_PORT, HOME_SWITCH_PIN,
                                              SWITCH_INPUT_PULLDOWN);
      f32 local_f32VoltVal = SPSV2_convertADCToVoltage_LOWMODE();
      f32 local_f32CurrentVal = SPSV2_readCurrent();

      // Display Voltage
      LCD_displayString((u8 *)"Voltage: ");
      LCD_displayNumber(local_f32VoltVal, 2);
      LCD_moveCursor(1, 0);
      LCD_displayString((u8 *)"Current: ");
      LCD_displayNumber(local_f32CurrentVal, 2);
      _delay_ms(250);
      LCD_clear();

      if (local_u8HomeSwitch) {
         break;
      }
   }

   // Disabling TMR0 PWM output and clearing the LCD screen
   DIO_setPinVal(RELAY_LOW_OUT_PORT, RELAY_LOW_OUT_PIN, DIO_PIN_OUTPUT_LOW);
   DIO_setPinVal(LED_INDIC_LOW_PORT, LED_INDIC_LOW_PIN, DIO_PIN_OUTPUT_LOW);
   DIO_setPinVal(ACS712_MEASUREMENT_PORT, ACS712_MEASUREMENT_PIN,
                 DIO_PIN_OUTPUT_LOW);
   LCD_clear();
}

void SPSV2_chargingMode(void) {
   // Sending the activate signal
   LCD_clear();
   DIO_setPinVal(CHARGE_MODE_SIG_PORT, CHARGE_MODE_SIG_PIN,
                 DIO_PIN_OUTPUT_HIGH);

   // Printing information for the user on the current mode
   LCD_displayString((u8 *)"Please wait");
   LCD_moveCursor(1, 0);
   LCD_displayString((u8 *)"while batteries");
   _delay_ms(750);
   LCD_clear();
   LCD_displayString((u8 *)"Finish");
   LCD_moveCursor(1, 0);
   LCD_displayString((u8 *)"Charging!!!");
   _delay_ms(750);
   LCD_clear();

   while (1) {
      // Reading the home switch state
      u8 local_u8HomeSwitch = SWITCH_getState(HOME_SWITCH_PORT, HOME_SWITCH_PIN,
                                              SWITCH_INPUT_PULLDOWN);
      u16 local_u16AdcValue = ADC_getValue(ADC_CHANNEL3);

      // Printing a loading screen to the user on the LCD
      LCD_displayString((u8 *)"Charging");
      LCD_displayChar('.');
      _delay_ms(250);
      LCD_displayChar('.');
      _delay_ms(250);
      LCD_displayChar('.');
      _delay_ms(250);
      LCD_displayChar('!');
      _delay_ms(250);
      LCD_clear();

      if (local_u8HomeSwitch) {
         break;
      }
   }

   // Turning off the signal
   LCD_clear();
   DIO_setPinVal(CHARGE_MODE_SIG_PORT, CHARGE_MODE_SIG_PIN, DIO_PIN_OUTPUT_LOW);
}

void SPSV2_freqCounterIcp(void) {
   // Sending the activate signal and Activating the Global interrupts
   LCD_clear();
   DIO_setPinDirection(ICP_PORT, ICP_PIN, DIO_PIN_INPUT);
   GIE_enable();

   // Defining necessary variables
   u8 local_u8CursorPosFreq = 0, local_u8ScreenPosFreq = 0;
   u8 local_u8Prescaler = 0;
   extern volatile u8 edge;
   extern volatile u16 period, high_time;

   // This loop runs until the user selects a Prescaler
   while (local_u8Prescaler == 0) {
      // Reading the home switch state
      u8 local_u8HomeSwitch = SWITCH_getState(HOME_SWITCH_PORT, HOME_SWITCH_PIN,
                                              SWITCH_INPUT_PULLDOWN);
      // Reading potentiometer ADC position for movement of cursor and selection
      // on Menu
      u16 local_u16AdcValue = ADC_getValue(ADC_CHANNEL1);

      // Updating Cursor position for the user to select the required Prescaler
      SPSV2_updateCursorPrescaler(local_u16AdcValue, &local_u8CursorPosFreq,
                                  &local_u8ScreenPosFreq);

      // Printing the Prescaler Menu for the user to choose the Prescaler
      SPSV2_printMenuPrescaler(local_u8CursorPosFreq, local_u8ScreenPosFreq);
      LCD_createAndDisplayChar(1, arrowCursor2, 1, local_u8CursorPosFreq);
      _delay_ms(150);

      // Selecting the Prescaler
      SPSV2_choosePrescaler(local_u8CursorPosFreq, local_u8ScreenPosFreq,
                            &local_u8Prescaler);

      if (local_u8HomeSwitch) {
         break;
      }
   }

   // Initialize Timer 1 in Input Capture Mode with the selected Prescaler
   TMR1_initModeICP(local_u8Prescaler);
   
   // This loop will keep reading the input signal and printing the frequency and duty cycle Until the user presses the home button
   while (1) {
      // Reading the home switch state
      u8 local_u8HomeSwitch = SWITCH_getState(HOME_SWITCH_PORT, HOME_SWITCH_PIN,
                                              SWITCH_INPUT_PULLDOWN);

      // Calculate frequency and duty cycle
      if (period != 0) {
		 LCD_clear();
         u32 frequency = F_CPU / (period * local_u8Prescaler);
         u8 duty_cycle = (high_time * 100) / period;
         LCD_displayString((u8 *)"Freq: ");
         LCD_displayNumber(frequency, 4);
         LCD_moveCursor(1, 0);
         LCD_displayString((u8 *)"Duty: ");
         LCD_displayNumber(duty_cycle, 4);
		 _delay_ms(150);
      }

      if (local_u8HomeSwitch) {
         break;
      }
   }

   // Clearing the LCD screen and stopping the Timer 1 peripheral
   GIE_disable();
   LCD_clear();
   TMR1_stop();
}

void SPSV2_controlFanSpeed(void) {
	// Clearing LCD, turning on Global interrupts.
	LCD_clear();
	GIE_enable();
	TMR2_init(TMR2_FASTPWM_MODE, TMR2_PRELOAD_CLR, TMR2_PWM_NON_INVERT);
	
   while (1) {
	   // Reading the home switch state and Potentiometer for fan speed
	   u8 local_u8HomeSwitch = SWITCH_getState(HOME_SWITCH_PORT, HOME_SWITCH_PIN,
	   SWITCH_INPUT_PULLDOWN);
	   u16 local_u16AdcValue = ADC_getValue(ADC_CHANNEL1);
	   
      // Map the ADC value to PWM duty cycle using a piecewise function
      u8 pwmDutyCycle = SPSV2_mapAdcToPwm(local_u16AdcValue);

      // Generating a variable PWM signal based off the values of the main
      // potentiometer
      TMR2_generatePWM(pwmDutyCycle, TMR2_PWM_NON_INVERT, TMR2_PRESCALER_64);

	   // Printing The speed on the LCD screen
	   LCD_displayString((u8 *)"Fan Speed: ");
	   LCD_moveCursor(1, 0);
	   LCD_displayNumber(pwmDutyCycle, 0);
	   LCD_displayChar('%');
	   _delay_ms(250);
	   LCD_clear();
	   
	   if (local_u8HomeSwitch) {
		   break;
	   }
   }
}

void SPSV2_turnOffFan() {
	// Turning off Timer 2 peripheral
	TMR2_stop();
	GIE_disable();
	LCD_clear();
	
	// Displaying info on the screen
	LCD_displayString((u8*)"Turning Off...");
	LCD_moveCursor(1, 0);
	LCD_displayString((u8*)"Fan");
	LCD_displayChar('.');
	_delay_ms(100);
	LCD_displayChar('.');
	_delay_ms(100);
	LCD_displayChar('.');
	LCD_displayChar('!');
	_delay_ms(200);
}