/*
 * SPSV2.h
 *
 * Created: 9/17/2024 8:49:47 PM
 *  Author: Basel Mohamed Mostafa Sayed
 *  Description: This file contains the MACROS and function headers for the SPS
 * V2.0
 */

#ifndef SPSV2_PROGRAM_H_
#define SPSV2_PROGRAM_H_

/* Smart Power Supply V2.0 MACROS */

#define SCREEN_1 0
#define SCREEN_2 1
#define SCREEN_3 2

// Error Codes for debugging
#define ERR_MENU 0
#define ERR_FUNCTIONS 1
#define ERR_MENU_FREQ 2
#define ERR_SELECT_PRESCALER 3

// Potentiometer
#define MAIN_MENU_POT_PORT DIO_PORTA
#define MAIN_MENU_POT_PIN DIO_PIN0

// Main Menu switches
#define ENTER_SWITCH_PORT DIO_PORTC
#define ENTER_SWITCH_PIN DIO_PIN6
#define HOME_SWITCH_PORT DIO_PORTC
#define HOME_SWITCH_PIN DIO_PIN7

// PWM0 output
#define PWM0_PORT DIO_PORTB
#define PWM0_PIN DIO_PIN3

// HIGH output relay
#define RELAY_HIGH_OUT_PORT DIO_PORTC
#define RELAY_HIGH_OUT_PIN DIO_PIN3

// LOW output relay
#define RELAY_LOW_OUT_PORT DIO_PORTC
#define RELAY_LOW_OUT_PIN DIO_PIN4

// ACS712 - 20A module current sense
#define ACS712_PORT DIO_PORTA
#define ACS712_PIN DIO_PIN2

// HIGH power mode Voltage Divider
#define VOLT_DIV_HIGH_PORT DIO_PORTA
#define VOLT_DIV_HIGH_PIN DIO_PIN0
#define R1 6800
#define R2 1000

// Low power mode voltage Divider
#define VOLT_DIV_LOW_PORT DIO_PORTA
#define VOLT_DIV_LOW_PIN DIO_PIN3
#define R1L 6800
#define R2L 1000

// LED indicators
#define LED_INDIC_HIGH_PORT DIO_PORTB
#define LED_INDIC_HIGH_PIN DIO_PIN1
#define LED_INDIC_LOW_PORT DIO_PORTB
#define LED_INDIC_LOW_PIN DIO_PIN0

// Charging mode signal
#define CHARGE_MODE_SIG_PORT DIO_PORTD
#define CHARGE_MODE_SIG_PIN DIO_PIN2

// LM35 Pin
#define LM35_PORT DIO_PORTA
#define LM35_PIN DIO_PIN4

// Current Measurement selection Pin for ACS712 current sensor module
#define ACS712_MEASUREMENT_PORT DIO_PORTB
#define ACS712_MEASUREMENT_PIN DIO_PIN2

// Input capture unit (ICP1 PD6) Pin for reading input frequency
#define ICP_PORT DIO_PORTD
#define ICP_PIN DIO_PIN6

// Fan Header pin
#define FAN_PORT DIO_PORTD
#define FAN_PIN DIO_PIN7

/* Smart Power Supply V2.0 Function Prototypes */

// This function initializes the Program (Start up)
void SPSV2_init(void);

// This function also has another purpose, which is to wait slightly until all
// the components are stable
void SPSV2_startProg(void);

// Main function (1), this function takes the potentiometer value and
// accordingly updates the cursor placement on the screen and the screen itself.
void SPSV2_updateScreenPosition(u16 copy_u16PotAdcVal, u8 *copy_u8CursorPos,
                                u8 *copy_u8ScreenPos);

// Main function (2), this function prints the main menu on the LCD screen
// depending on the current value of current screen position
void SPSV2_printMenu(u8 copy_u8CursorPos, u8 copy_u8ScreenPos);

// Main function (3), this function simply takes the Cursor position and current
// screen value and executes the function the user has the cursor on
void SPSV2_chooseFun(u8 copy_u8CursorPos, u8 copy_u8ScreenPos);

// Main function (4), Function to map the main potentiometer ADC value to PWM
// duty cycle as a means to vary the control signal
u8 SPSV2_mapAdcToPwm(u16 adcValue);

// Main function(5), Function to read the input voltage and print it on the
// screen
f32 SPSV2_convertADCToVoltage(u16 copy_u16AdcValue);

// Main function(6), Function to read the input voltage and print it on the
// screen
f32 SPSV2_convertADCToVoltage_LOWMODE(void);

// Main function(6), Function to calculate the current moving through the output
// voltages
f32 SPSV2_readCurrent(void);

// Function to read the temperature and print a warning if the temperature is
// too hot
void SPSV2_readTemp(void);

// Function to use the High power output
void SPSV2_highPowerOut(void);

// Function to use the Low power output
void SPSV2_lowPowerOut(void);

// Function to turn the Smart Power Supply to charging mode (unable to use the
// voltage outputs in charging mode)
void SPSV2_chargingMode(void);

// Function to read cursor position and print the cursor on the Prescaler menu
// selection
void SPSV2_updateCursorPrescaler(u16 copy_u16PotAdcVal,
                                 u8 *copy_u8CursorPosFreq,
                                 u8 *copy_u8ScreenPosFreq);

// Menu to select the Prescaler for the Input capture unit peripheral inside the
// frequency counter mode
void SPSV2_printMenuPrescaler(u8 copy_u8CursorPosFreq, u8 copy_u8ScreenPosFreq);

// Setting the Prescaler to a value the user chose in the menu
void SPSV2_choosePrescaler(u8 copy_u8CursorPos, u8 copy_u8ScreenPos,
                           u8 *copy_u8PrescalerVal);

// Function to use the frequency counter and read input frequency and calculate
// the Duty cycle of the input signal (0-5V)
void SPSV2_freqCounterIcp(void);

// Control Fan Speed
void SPSV2_controlFanSpeed(void);

// Function to completely turn off the fan.
void SPSV2_turnOffFan();

#endif /* SPSV2_PROGRAM_H_ */