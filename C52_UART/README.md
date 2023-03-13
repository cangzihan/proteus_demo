# C52 UART Communication Demo
This demo shows how to establish UART communication between two C52 microcontrollers using TTL logic levels. 
The demo circuit includes two C52 chips, each with 4 pushbuttons that can be used to send different messages to the other chip. 
The received messages are displayed on a 4x16 LCD screen attached to each C52.

## Getting Started
To open the demo circuit in Proteus, open the `c52_uart.pdsprj` file. 
Note that you will need to set the program file for each C52 chip to the appropriate `.hex` file in the `Code` folder.

## Usage
1. Open the `c52_uart.pdsprj` file in Proteus 8.9.
2. Set the program file for each C52 chip to the appropriate `.hex` file in the `Code` folder.
3. Simulate the circuit and press the pushbuttons on each chip to send messages to the other chip.
4. Check the LCD screens on each chip to see the received messages.

## Circuit Diagram
The circuit diagram can be found in the project `.pdsprj` file. 
The circuit consists of two C52 microcontrollers, each with its own set of 4 push buttons and a 4x16 LCD display. 
The microcontrollers communicate with each other via direct connection between their respective TXD and RXD pins.

## Credits
This demo was created by [cangzihan](https://github.com/cangzihan) and modified by [ChatGPT](https://github.com/ChatGPT).
