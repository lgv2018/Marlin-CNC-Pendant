/****************************************
 * configurations.h - define variables and configure hardware
 * This file is part of the Marlin-CNC-Pendant. For more information including usage and licensing please refer to: https://github.com/DeeEmm/Marlin-CNC-Pendant
 * 
 * 
 * NOTE
 * output pins (*_OUT_PIN) connected to control boards as follows:
 * physical > logical pin reference  https://www.arduino.cc/en/Hacking/PinMapping2560 
 * 
 * 
 * RAMPS physical pins
 * JOY_X_PIN   - AUX2 pin A5  (logical Pin 59)
 * JOY_Y_PIN   - AUX2 pin A10 (logical Pin 60)
 * JOY_Z_PIN   - AUX2 pin A12 (logical Pin 63)
 * JOY_EN_PIN  - AUX2 pin D44 (logical Pin 64)
 * 
 * 
 * MCP4151 VCR (VOLTAGE CONTROLLED RESISTOR) (10kohm)
 * This chip works over SPI comms, which means you need to connect MOSI (serial data) and 
 * SCK (serial clock) lines between the arduino and MCP4151. In addition to this you also 
 * need to enable each chip individually to identify which chip you are writing to. 
 * This is done by holding the CS (Chip Select) line low. 
 * The MCP4151 chip will revert to mid-scale when powered up, other variants may not.
 * 
 * Pin connections for MCP4151.
 * Three devices are required - one for each axis, connected as follows:
 * 
 * 1 -CS (Chip Select) - Nano Pin 14/15/16 for X/Y/Z axis respectively
 * 2 - SCK (Clock) - Nano Pin 13 (SCK) for all devices
 * 3 - SDI/SDO (Serial) - Nano Pin 11 (MOSI) for all devices
 * 4 - GND (0V)
 * 5 - GND (0v)
 * 6 - Wiper out - Connect to the X/Y/Z axis input on your RAMPs/3D printer controller
 * 7 - VCC (5v)
 * 8 - VCC (5v)
 * 
 * You also need to debounce the encoder by using 10000pF capacitors between the A pin and GND and B pin GND
 * 
 * MARLIN CONFIGURATION
 * The following values can be found in Configuration_adv.h in Marlin 
 * 
 * Uncomment the following line...
 * #define JOYSTICK
 * 
 * Next we need to tune the joystick values by using the M118 command in your printer host program (eg repetier)
 * For the Gcode command to work you will need to add the following line
 * #define JOYSTICK_DEBUG
 * 
 * Then issue the M119 command a number of times and average out the reading. This is the centre value (the 8175 value below).
 * This value should be half of the full 14 bit range (16384/2 = 8192) but may differ depending on the resistance of the circuit.
 * If the value differs a little then adjust the values in Marlin.
 * 
 * Next you want to addjust the deadband limits (the +/-100 value below). This value has to be larger than any of the readings you 
 * got from the M119 command. There should not really be any reason to change this
 * 
 * #define JOY_X_LIMITS { 5600, 8175-100, 8175-100, 10800 } // min, deadzone start, deadzone end, max
 * #define JOY_Y_LIMITS { 5600, 8175-100, 8175-100, 11000 }
 * #define JOY_Z_LIMITS { 4800, 8175-100, 8175-100, 11550 }
 * 
 * 
 * Notes:
 * 
 ***/

 #pragma once

 /****************************************
 * SELECT BOARD TYPE 
 ***/

#define ARDUINO_NANO //Default



/****************************************
 * GENERAL SETTINGS
 ***/

//#define SERIAL_DEBUG                      // Enable Serial debug mode

#define VCR_POT_RES 256                   // 128 or 256 depeonding on VCR chip resolution and settings
#define BYTE_ADDRESS 0x00                 // 0x00 is pot wiper address

#define JOY_X_CENTER_VALUE (float) 8192   // 14 BIT ADC resolution = 2^14 = 16384 
#define JOY_Y_CENTER_VALUE (float) 8192   // Mid range (center position) = 16384 / 2 = 8192
#define JOY_Z_CENTER_VALUE (float) 8192   // Should be same as returned by M119 but may differ slightly depending on resistance of VCR / circuits

#define CLICK_PULSE_WIDTH 100              // Jog pulse duration in ms for single click moves (used for X1 speed and adaptive speeds < 1 click per sec)
#define JOG_PULSE_WIDTH 10                 // Jog pulse duration in ms

#define JOG_SPEED_X1 5                    // NOTE: Speed range is between 0 ~ 64 (0 ~ 100%)      
#define JOG_SPEED_X10 10                  // Choose values to suit your setup
#define JOG_SPEED_X100 20                 // e.g. 16 = 25% 

#define ADAPTIVE_SPEED_RANGE 150          // Adaptive speed range
#define MAX_CLICK_SPEED 200               // Maximum click speed in adaptive mode (speed range)
#define MIN_CLICK_SPEED 20               // Maximum click speed in adaptive mode (speed range)

#define MIN_ADAPTIVE_SPEED 5              // Minimum speed in adaptive mode
#define MAX_ADAPTIVE_SPEED 20             // Maximum speed in adaptive mode

#define SPEED_SWITCH_ENABLE true          // Disable system if speed selector switch is open: [0] - X1 - X10 - X100
                                          // Otherwise enable signal should be mnaged externally with a physical switch



/****************************************
 * CONFIGURE PINS 
 * Default configuration is for a nano
 * Add additional boards / configurations as required
 ***/

// ARDUINO NANO
#ifdef ARDUINO_NANO

    // Define interrupts: 
    // Jogwheel pins and interrupts need to be set for each board variant
    // Default interrupts 0 & 1 are on pins 2 & 3 on a nano. This may differ for other boards.
    #define INTERRUPT_A 0               // Default 0 = pin 2 on nano (JOGWHEEL_PIN_A)
    #define INTERRUPT_B 1               // Default 1 = pin 3 on nano (JOGWHEEL_PIN_B)


    // Define Physical Pins: 
    // (colour codes for generic MPG handwheel pendant included)
    
    // Inputs
    #define JOGWHEEL_PIN_A 2            // MPG - green
    #define JOGWHEEL_PIN_B 3            // MPG - white

    #define JOG_SPEED_X1_PIN 4          // MPG - orange
    #define JOG_SPEED_X10_PIN 5         // MPG - grey/black
    #define JOG_SPEED_X100_PIN 6        // MPG - grey
    
    #define X_AXIS_SELECT_PIN 7         // MPG - yellow
    #define Y_AXIS_SELECT_PIN 8         // MPG - yellow/black
    #define Z_AXIS_SELECT_PIN 9         // MPG - brown

    #define ADAPTIVE_SPEED_PIN 10       // Adaptive speed enable pin


    // Define outputs

    #define MOSI 11                     // pin 3 on all MCP4151s (SDI/SDO)
    #define SCK 13                      // pin 2 on all MCP4151s (SCK)
    #define X_AXIS_CS_PIN 14            // pin 1 on X Axis MCP4151 (CS)
    #define Y_AXIS_CS_PIN 15            // pin 1 on Y Axis MCP4151 (CS)
    #define Z_AXIS_CS_PIN 16            // pin 1 on Z Axis MCP4151 (CS)

    #define ENABLE_OUT_PIN 17           // JOY_EN_PIN 

#endif
