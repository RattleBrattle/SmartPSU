# SmartPSU

Welcome to the Smart Power Supply project! This repository contains the code and design files for a versatile power supply unit currently under development. The smart power supply is designed to provide reliable and adjustable power output for various applications, featuring multiple modes to cater to different power requirements.

![This Picture is a final representation of the Smart Power Supply circuit and is simulation for Proteus](https://github.com/RattleBrattle/SmartPSU/blob/main/Proteus%20Schematic%20Simulation.png?raw=true)

## Features

The Smart Power Supply currently supports the following 3 functions, with more ideas that I want to implement coming along the way:

### High Power Mode
- The mode's output is maximum at 5A, and at around 34V that means the output is around ~170W!
- Provides a high power output suitable for demanding applications and High Powered electronics.
- Ensures stable and efficient power delivery for high-performance devices using the effective but simple LM338T voltage regulator.

### Low Power Mode
- This mode's output is maximum at 1.5, which is suitable for everyday electronics and logic circuits or weak motors.
- Offers a low power output for energy-efficient operation.
- Ideal for applications that require minimal power consumption.
- both positive and negative output using the LM317T and LM337T voltage regulators respectively.
- 
### Charging Circuit Outputs
- 5W circuit and a 40W circuit for both USB output ports.
- Includes dedicated charging circuits for various battery types and Charging mobile phones.
- Supports charging for 18650 and Lithium-ion batteries.
- Ensures safe and efficient battery charging with built-in protection features.

40W Charging Circuit schematic:
![40W Charging Circuit](https://github.com/RattleBrattle/SmartPSU/blob/main/Images/Charging%20Circuits/40W%20Charging.png?raw=true)

30W Charging Circuit schematic:
![30W Charging Circuit](https://github.com/RattleBrattle/SmartPSU/blob/main/Images/Charging%20Circuits/5W%20Circuit.png?raw=true)

### Frequency Counter input:
- Using Precise calculations and the Timer 1 Peripheral on the ATmega32A, i managed to code a very useful feature
like that in the Smart Power Supply, simply put the frequency counter gives the user option to choose between the diverse
type of Prescalers in the ATmega32A Timer 1 peripheral depending on the frequency of the signal being tested.
The user Changes the Prescaler just like the main menu using the potentiometer and buttons.

- Example of the Menu:
![Prescaler-Menu](https://github.com/user-attachments/assets/dd1ecc1b-d4cb-4cae-935f-4f38db478654)


## Getting Started

WIP!

### Installation

WIP!

### Usage
When the user first powers on the device, the LCD screen prints out a menu with a cursor.
- The user controls the cursor position by moving the Main Menu potentiometer next to the LCD screen.
- When the user wants the function chosen, Press the "ENTR" button.
- When the user wants to exit the current function, Press the "HOME" button.

## Contributing

Contributions are welcome! If you have any suggestions, bug reports, or feature requests, Please email me at baselmohamed802@gmail.com or [message me on my LinkedIn page](www.linkedin.com/in/basel-sayed-b11534243)! 

## License

This project is licensed under the [Your License] - see the [LICENSE](LICENSE) file for details.
