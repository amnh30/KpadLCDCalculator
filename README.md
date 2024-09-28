---

# 📟 AVR Calculator Project

Welcome to the **AVR Calculator Project**! This project implements a simple calculator using an AVR microcontroller. It features an LCD display for output and a keypad for input. 

## 🛠️ Features

- **Basic Operations**: Supports addition, subtraction, multiplication, and division.
- **User-Friendly Interface**: Utilizes a 16x2 LCD to display inputs and results.
- **Keypad Input**: Allows users to input numbers and operations easily.

## 💻 Code Overview

Here's a brief overview of the main components of the code:

### Includes
```c
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/delay.h>
#define C_CPU 8000000UL
```
- **Standard Libraries**: These headers provide basic type definitions and bit manipulation macros.
- **Delay**: Used for debouncing and creating delays in the application.

### MCAL and HAL Layers
```c
#include "MDIO/MDIO_Interface.h"
#include "HLCD/HLCD_interface.h"
#include "HKPD_interface.h"
#include <stdlib.h>
```
- **MDIO**: Microcontroller Digital Input/Output interface for pin management.
- **HLCD**: Functions to manage the LCD display.
- **HKPD**: Functions to handle the keypad input.

### Main Function
```c
int main(void) {
    u8 keyPressed = 0; // Store the pressed key
    // Other variable declarations...

    // Initialize the LCD and Keypad
    MDIO_IntialPins();
    HLCD_VoidLcdIint();
    HLCD_VoidLcdClear();

    while (1) {
        // Main loop for key processing
    }
}
```
- **Key Handling**: The main loop checks for key presses and processes user inputs.
- **Operands and Operators**: Handles the input of operands and operators, performing calculations based on the user’s input.

## 🖥️ How to Run

1. **Setup Environment**: Ensure you have an AVR development environment set up (e.g., Atmel Studio).
2. **Connect Hardware**: Connect your AVR microcontroller to an LCD and keypad.
3. **Compile and Upload**: Compile the code and upload it to your microcontroller.
4. **Start Calculating**: Use the keypad to enter numbers and operations, and view results on the LCD.

## 📦 Project Structure

```
/AVR_Calculator_Project
│
├── MDIO
│   ├── MDIO_Interface.h
│   └── MDIO_Implementation.c
│
├── HLCD
│   ├── HLCD_interface.h
│   └── HLCD_Implementation.c
│
├── HKPD_interface.h
└── main.c
```

## 📖 Dependencies

- **AVR GCC**: Compiler for AVR microcontrollers.
- **AVR Libc**: Standard library for AVR development.

## 🚀 Contribution

Feel free to contribute to this project! Create a pull request for any improvements or new features you'd like to add. 

## 📞 Contact

For questions or suggestions, please reach out via email at [amn951753@gmail.com](mailto:yamn951753@gmail.com).


Happy coding! 🎉✨

--- 
