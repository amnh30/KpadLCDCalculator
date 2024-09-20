#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/delay.h>
#define C_CPU 8000000UL

/*MCAL Layer Include*/
#include "MDIO/MDIO_Interface.h"

/* HAL Layer Include*/
#include "HLCD/HLCD_interface.h"
#include "HKPD_interface.h"

int main(void)
{
    u8 keyPressed = 0;          // Store the pressed key
    u8 operand1[8] = {0};       // Store the first operand (max 8 digits)
    u8 operand2[8] = {0};       // Store the second operand (max 8 digits)
    u8 operator= 0;             // Store the operator (+, -, *, /)
    u8 operand1Idx = 0;         // Index to track operand1
    u8 operand2Idx = 0;         // Index to track operand2
    u8 currentState = 1;        // 1 - first operand, 2 - operator, 3 - second operand
    int result = 0;             // Store the result
    u8 calculationComplete = 0; // Flag to check if calculation is done

    // Initialize the LCD and Keypad
    MDIO_IntialPins();
    HLCD_VoidLcdIint();
    HLCD_VoidLcdClear();

    while (1)
    {
        // Check if a key is pressed
        HKPD_u8GetPressedKey(&keyPressed) == STD_TYPE_OK;
        _delay_ms(200);
        if (keyPressed != HKPD_NO_KEY_PRESSED)
        {

            // Handle numeric input (0-9)
            if (keyPressed >= '0' && keyPressed <= '9') // If it's a number
            {
                if (currentState == 1) // First operand
                {
                    if (operand1Idx < 5) // Limit to 8 digits
                    {
                        operand1[operand1Idx++] = keyPressed;
                        HLCD_VoidLcdWriteChar(keyPressed); // Display on LCD
                    }
                }
                else if (currentState == 3) // Second operand
                {
                    if (operand2Idx < 8) // Limit to 8 digits
                    {
                        operand2[operand2Idx++] = keyPressed;
                        HLCD_VoidLcdWriteChar(keyPressed); // Display on LCD
                    }
                }
            }
            // Handle operator input (+, -, *, /)
            else if ((keyPressed == '+' || keyPressed == '-' || keyPressed == '*' || keyPressed == '/') && currentState == 1)
            {
                operator= keyPressed;
                currentState = 3;                  // Move to second operand
                HLCD_VoidLcdWriteChar(keyPressed); // Display on LCD
            }
            // Handle equal key (=)
            else if (keyPressed == '=' && currentState == 3) // Equals, perform the calculation
            {
                operand1[operand1Idx] = '\0'; // Null-terminate strings
                operand2[operand2Idx] = '\0';

                int num1 = atoi((const char *)operand1); // Convert to int
                int num2 = atoi((const char *)operand2);

                // Perform the operation
                switch (operator)
                {
                case '+':
                    result = num1 + num2;
                    // Display the result
                    HLCD_VoidLcdClear();
                    HLCD_VoidLcdWriteInt(result);
                    break;
                case '-':
                    result = num1 - num2;
                    // Display the result
                    HLCD_VoidLcdClear();
                    HLCD_VoidLcdWriteInt(result);
                    break;
                case '*':
                    result = num1 * num2;
                    // Display the result
                    HLCD_VoidLcdClear();
                    HLCD_VoidLcdWriteInt(result);
                    break;
                case '/':
                    if (num2 != 0)
                    {
                        HLCD_VoidLcdClear();
                        float result = (float)num1 / (float)num2; // Cast to float for proper division
                        HLCD_VoidLcdWriteFloat(result);
                    }
                    else
                    {
                        HLCD_VoidLcdClear();
                        HLCD_u8WriteStr("Err: Div by 0");
                        calculationComplete = 1;
                        continue;
                    }
                    break;
                default:
                    break;
                }

                calculationComplete = 1; // Set flag to indicate calculation is done
            }
            // Handle clear key ('C')
            else if (keyPressed == '%') // Clear
            {
                HLCD_VoidLcdClear();
                operand1Idx = operand2Idx = 0; // Reset operands
                currentState = 1;              // Back to first operand
            }

            _delay_ms(100); // Small delay for debouncing
            keyPressed = 0;
        }
    }
}
