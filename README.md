# 🛡️ Password-Protected Motor Control System

Welcome to the **Password-Protected Motor Control System** project! This system allows users to perform basic arithmetic operations using a keypad interface and display the results on an LCD.

## 📋 Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [How It Works](#how-it-works)
- [Code Structure](#code-structure)
- [Configuration](#configuration)
- [Future Enhancements](#future-enhancements)
- [Author](#author)
- [License](#license)

## 🎯 Introduction
This project utilizes an AVR microcontroller to create a password-protected system where users can perform basic mathematical operations. The input is taken from a keypad, and the output is displayed on an LCD.

## 🌟 Features
- Input of two operands and an operator using a keypad.
- Display results on an LCD.
- Handle basic arithmetic operations: addition, subtraction, multiplication, and division.
- Error handling for division by zero.
- Clear the input with a dedicated key.

## ⚙️ How It Works
1. The system initializes the keypad and LCD.
2. Users enter the first operand, followed by an operator, and then the second operand.
3. The result is calculated and displayed on the LCD.
4. Users can clear the input using the designated key.

## 📂 Code Structure
The code consists of the following components:

- **Includes**: Standard and custom libraries for functionality.
- **Variables**: Definitions for operands, operator, and result storage.
- **Main Loop**: Handles keypress events and performs calculations.

Here’s a brief overview of the main code:

```c
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/delay.h>
#define C_CPU 8000000UL

/* MCAL Layer Include */
#include "MDIO/MDIO_Interface.h"

/* HAL Layer Include */
#include "HLCD/HLCD_interface.h"
#include "HKPD_interface.h"
#include <stdlib.h>

int main(void) {
    u8 keyPressed = 0; // Store the pressed key
    char operand1[9] = {0}; // Store the first operand (max 8 digits + null terminator)
    char operand2[9] = {0}; // Store the second operand (max 8 digits + null terminator)
    char operator = 0; // Store the operator (+, -, *, /)
    u32 operand1Idx = 0; // Index to track operand1
    u32 operand2Idx = 0; // Index to track operand2
    u8 currentState = 1; // 1 - first operand, 2 - operator, 3 - second operand
    float result = 0; // Store the result
    u8 calculationComplete = 0; // Flag to check if calculation is done

    // Initialize the LCD and Keypad
    MDIO_IntialPins();
    HLCD_VoidLcdIint();
    HLCD_VoidLcdClear();

    while (1) {
        // Check if a key is pressed
        if (HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK) {
            _delay_ms(200); // Debounce delay
            if (keyPressed != HKPD_NO_KEY_PRESSED) {
                // Handle numeric input (0-9)
                if (keyPressed >= '0' && keyPressed <= '9') {
                    if (currentState == 1 && operand1Idx < 8) { // First operand
                        operand1[operand1Idx++] = keyPressed;
                        HLCD_VoidLcdWriteChar(keyPressed);
                    } else if (currentState == 3 && operand2Idx < 8) { // Second operand
                        operand2[operand2Idx++] = keyPressed;
                        HLCD_VoidLcdWriteChar(keyPressed);
                    }
                }
                // Handle operator input (+, -, *, /)
                else if ((keyPressed == '+' || keyPressed == '-' || keyPressed == '*' || keyPressed == '/') && currentState == 1) {
                    operator = keyPressed;
                    currentState = 3; // Move to second operand
                    HLCD_VoidLcdWriteChar(keyPressed);
                }
                // Handle equal key (=)
                else if (keyPressed == '=' && currentState == 3) {
                    operand1[operand1Idx] = '\0'; // Null-terminate strings
                    operand2[operand2Idx] = '\0';

                    int num1 = atoi(operand1); // Convert to int
                    int num2 = atoi(operand2);

                    // Perform the operation
                    switch (operator) {
                        case '+':
                            result = num1 + num2;
                            break;
                        case '-':
                            result = num1 - num2;
                            break;
                        case '*':
                            result = num1 * num2;
                            break;
                        case '/':
                            if (num2 != 0) {
                                result = (float)num1 / (float)num2; // Cast to float for proper division
                            } else {
                                HLCD_VoidLcdClear();
                                HLCD_u8WriteStr("Err: Div by 0");
                                calculationComplete = 1; // Set flag for division by zero
                                continue; // Skip to the next iteration
                            }
                            break;
                        default:
                            break;
                    }

                    HLCD_VoidLcdClear();
                    if (operator == '/' && num2 != 0) {
                        HLCD_VoidLcdWriteFloat(result); // Display result as float
                    } else {
                        HLCD_VoidLcdWriteInt((int)result); // Display result as integer
                    }

                    calculationComplete = 1; // Set flag to indicate calculation is done
                }
                // Handle clear key ('C')
                else if (keyPressed == '%') { // Clear
                    HLCD_VoidLcdClear();
                    operand1Idx = operand2Idx = 0; // Reset operands
                    currentState = 1; // Back to first operand
                    operand1[0] = operand2[0] = '\0'; // Reset operands
                }

                _delay_ms(10); // Small delay for debouncing
                keyPressed = 0;
            }
        }
    }
}
⚙️ Configuration
Trial Limit:
You can modify the number of allowed password attempts by changing the following line:

c
Copy code
#define MAX_TRIALS 3
Stepper Motor Settings:
The angle, direction, and speed input for the stepper motor can be customized within the RunStepperMotor function.

🔮 Future Enhancements
Here are some ideas for improving the system:

Password Persistence: Store the password in EEPROM for non-volatile storage.
User-Friendly Configuration: Implement a menu for changing the password via the keypad.
Advanced Motor Control: Add speed control features for the DC motor.
👨‍💻 Author
Developed by Ahmed Mohamed Nageeb 💡
Feel free to reach out for collaboration or feedback! 😄

🛡️ License
All rights reserved. © 2024

arduino
Copy code

Feel free to customize any sections as needed, especially the author information and future en
