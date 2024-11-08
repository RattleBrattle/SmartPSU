# SmartPSU

Welcome to the Smart Power Supply project! This repository contains the code and design files for a versatile power supply unit currently under development. The smart power supply is designed to provide reliable and adjustable power output for various applications, featuring multiple modes to cater to different power requirements.

![This Picture is a final representation of the Smart Power Supply circuit and is simulation for Proteus](https://github.com/RattleBrattle/SmartPSU/blob/main/Proteus%20Schematic%20Simulation.png?raw=true)

## Features

The Smart Power Supply has 5 main features:
- The voltage is sensed using a voltage divider of Power Resistors.
- The Current is measured using the current sensor module board ACS712.

## Components:
* ACS712 Current sensor module board 20A.
* Linear Transformer 24V @ 5A.
* 4x 18650 battery holder.
* TP4056 Lithium battery charger.
* 120mm Fan.
* L7812, L7805 Regulators and their dependencies.
* LM317T and LM337T for Low power circuit and it's dependencies.
* LM338T for High Power circuit and it's dependencies.
* L293D for PWM fan control.
* LM35DZ Temperature sensor.
* LCD 16x2 display.
* 10kohm potentiometer, two buttons for the Menu controls.
* 2 USB type A female outputs for charging circuits output.
* 8 Banana Plugs for outputs of Power circuits and input of Frequency counter.

### High Power Mode:
- The mode's output is maximum at 5A, and at around 34V that means the output is around ~170W!
- Provides a high power output suitable for demanding applications and High Powered electronics.
- Ensures stable and efficient power delivery for high-performance devices using the effective but simple LM338T voltage regulator.

### Low Power Mode:
- This mode's output is maximum at 1.5, which is suitable for everyday electronics and logic circuits or weak motors.
- Offers a low power output for energy-efficient operation.
- Ideal for applications that require minimal power consumption.
- both positive and negative output using the LM317T and LM337T voltage regulators respectively.
- 
### Charging Circuits:
- 5W circuit and a 40W circuit for both USB output ports.
- Includes dedicated charging circuits for various battery types and Charging mobile phones.
- Supports charging for 18650 and Lithium-ion batteries.
- Ensures safe and efficient battery charging with built-in protection features.

40W Charging Circuit schematic:
![40W Charging Circuit](https://github.com/RattleBrattle/SmartPSU/blob/main/Images/Charging%20Circuits/40W%20Charging.png?raw=true)

30W Charging Circuit schematic:
![30W Charging Circuit](https://github.com/RattleBrattle/SmartPSU/blob/main/Images/Charging%20Circuits/5W%20Circuit.png?raw=true)

### Frequency Counter:
- Using Precise calculations and the Timer 1 Peripheral on the ATmega32A, i managed to code a very useful feature
like that in the Smart Power Supply, simply put the frequency counter gives the user option to choose between the diverse
type of Prescalers in the ATmega32A Timer 1 peripheral depending on the frequency of the signal being tested.
The user Changes the Prescaler just like the main menu using the potentiometer and buttons.

- Example of the Menu:
![Prescaler-Menu](https://github.com/user-attachments/assets/dd1ecc1b-d4cb-4cae-935f-4f38db478654)

### PWM Fan Control and Temperature sensor:
- The user can control the FAN speed by choosing the option in the Main Menu, using the L293D
as PWM controller and the Input power is 12V using the L7812 Regulator.
- The Power supply also has a critical function, a function that calculates the current temperature.
Where if the current temperature exceeds 35 degrees, Their is a warning message that is prompted to the user
on the LCD screen warning them!

![The Temperature sensor and 12V fan Control:](https://github.com/user-attachments/assets/5c2bda85-9acb-49a0-b5f9-0f2d4087508a)

### Usage
When the user first powers on the device, the LCD screen prints out a menu with a cursor.
- The user controls the cursor position by moving the Main Menu potentiometer next to the LCD screen.
- When the user wants the function chosen, Press the "ENTR" button.
- When the user wants to exit the current function, Press the "HOME" button.

## Contributing

Contributions are welcome! If you have any suggestions, bug reports, or feature requests, Please email me at baselmohamed802@gmail.com or [message me on my LinkedIn page](www.linkedin.com/in/basel-sayed-b11534243)! 

## License

This project is licensed under the [GNU] - see the [LICENSE](LICENSE) file for details.
