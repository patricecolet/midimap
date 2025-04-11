/**
 * This example demonstrates the use of the Ultrasonic Distance Sensor that
 * can be used for changing effect of Aftertouch.
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
 * When the input value changes (e.g. from a sensor or potentiometer),
 * this sketch sends a Channel Pressure (Aftertouch) MIDI message on the specified channel. 
 * The pressure value typically represents how hard a key is being pressed after it’s already held down,
 * and it can be used to control effects like vibrato, volume, or modulation in a DAW or synth.
 *
 * Mapping
 * -------
 *
 * Select the Arduino as a custom MIDI controller in your DAW, and use the
 * MIDI learn option to assign the ultrasonic distance sensor to a function.
 * It will send the MIDI Control Change Channel Volume parameter for channel 1.
 *
 * Written by Nuryn Sophea, 2025-03-03
 */

#include <midimap.h> // Include the midimap library for handling MIDI messages

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a CPPotentiometer object
CPUltrasonic potentiometer{
    A0,        // Analog pin connected to potentiometer
    CHANNEL_1, // Channel volume of channel 1
    //48,        // Minimum threshold if the sensor is not perfect (0-127)
    //127,       // Maximum threshold if the sensor is not perfect(0-127)
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}