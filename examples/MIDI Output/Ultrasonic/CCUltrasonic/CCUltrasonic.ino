/**
 * This example demonstrates the use of the Ultrasonic Distance Sensor that
 * can be used for changing effect parameters, volumes, pan and balance
 * controls, etc. It can control almost any knob in your DAW software.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 *
 * Connections
 * -----------
 *
 * - D7 : Yellow, SIG
 * - GND : GND
 * - VCC : 5V
 *
 * Behavior
 * --------
 *
 * When the input value changes, the Ultrasonic Distance Sensor will send a
 * MIDI Control Change event with a value between 0 and 127.
 *
 * Mapping
 * -------
 *
 * Select the Arduino as a custom MIDI controller in your DAW, and use the
 * MIDI learn option to assign the ultrasonic distance sensor to a function.
 * It will send the MIDI Control Change Channel Volume parameter for channel 1.
 *
 * Written by Nuryn Sophea, 2025-04-11
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// For perfect components (no thresholding needed)
CCUltrasonic Ultrasonic {
  A5,                              // Analog pin connected to potentiometer
  {MIDI_CC::Channel_Volume, Channel_1 }, // Channel volume of channel 1
   //5,                            // Minimum threshold if the sensor is not perfect (0-127)
   //125,                          // Maximum threshold if the sensor is not perfect (0-127)
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}