# IoT Motor Control with LCD Display

## Overview

This project integrates an MSP430 microcontroller with an ESP8266 Wi-Fi module to create a remote-controlled system for managing a DC motor and displaying information on an LCD. Users can set the motor speed via a web interface, and the system provides real-time feedback on an I2C-connected LCD.
![image](https://github.com/user-attachments/assets/13beddea-73f8-476a-a71e-e3b1584126c6)


## Components

### MSP430 Microcontroller

- **I2C LCD Control**: 
  - The MSP430 communicates with an LCD using the I2C protocol. Functions in `lcd_i2c.c` and `lcd_I2C.h` handle initialization, data sending, and display control.
  - Key functions include:
    - `I2C_Init(int addr)`: Initializes I2C communication with the LCD.
    - `LCD_Setup()`: Sets up the LCD for operation.
    - `LCD_Write(char *text)`: Writes text to the LCD.

- **ADC Reading**:
  - The ADC (Analog-to-Digital Converter) reads an analog input, potentially from a sensor or potentiometer.
  - Configuration:
    - `ADCMCTL0 = 0x0002;` selects the ADC channel.
    - `ADCMEM0` stores the conversion result, representing the analog voltage as a digital value.
  - Purpose: The ADC value is scaled and displayed on the LCD as a percentage, indicating the motor's duty cycle or another relevant metric.

### ESP8266 Wi-Fi Module

- **Web Server**:
  - Hosts a web server to accept HTTP GET requests from a browser. Users submit motor speed values via an HTML form.
  - Configuration:
    - `WiFiServer server(80)`: Sets up the server on port 80.
    - The `loop()` function processes client requests and serves a simple HTML page.

- **PWM Control**:
  - The ESP8266 uses PWM to control motor speed based on user input.
  - Process:
    - Extracts motor speed value from the HTTP request.
    - Maps the speed (0-100) to PWM range (0-255) using `map()`.
    - `analogWrite(output2, dutyValue)`: Sets the PWM signal to control motor speed.

## Communication

- **Interfacing**: While the MSP430 and ESP8266 operate independently, they could be integrated via I2C or UART for enhanced control and feedback.

## Project Workflow

1. **Setup**: 
   - Initialize the MSP430 for LCD and ADC operations.
   - Connect the ESP8266 to Wi-Fi and start the web server.

2. **User Interaction**: 
   - Users access the web server and input a desired motor speed.
   - The server processes this input and adjusts the motor speed via PWM.

3. **Display**: 
   - The MSP430 reads the ADC input and displays the corresponding duty cycle on the LCD.

4. **Feedback**: 
   - Future enhancements could include sending ADC values or other data from the MSP430 to the ESP8266 for display on the web interface.

## Future Enhancements

- **Security**: Implement authentication for the web server to secure access.
- **Feedback Loop**: Integrate sensor feedback to dynamically adjust motor speed.
- **Direct Communication**: Establish a protocol between MSP430 and ESP8266 for integrated control.

## Conclusion

This project demonstrates the integration of microcontrollers and Wi-Fi modules in IoT applications, allowing remote control and monitoring of hardware components. The modular design facilitates future enhancements and scalability.
