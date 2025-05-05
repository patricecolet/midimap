/**
 * This example demonstrates how to simulate Channel Pressure using a photoresistor,
 * providing expressive control in your DAW software. The intensity of light hitting the
 * photoresistor simulates the pressure applied to a key after it is initially pressed,
 * which can control various MIDI parameters.
 *
 * This setup allows for dynamic control of Channel Pressure, adding expressiveness to your
 * performance or production.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * 
 * Connections
 * -----------
 * 
 * - A0: wiper of a potentiometer 
 * - Connect the left terminal of the potentiometer to ground, and the right one
 *   to V<sub>CC</sub>.
 * - 47nF capacitor between A0 and GND, to prevent noise.
 *
 * Behavior
 * --------
 *
 * The photoresistor's light exposure determines the Channel Pressure value, allowing you to
 * simulate the pressure applied to a key after it is initially pressed by adjusting the light levels.
 *
 * Mapping
 * --------
 * In your DAW, select the Arduino as a custom MIDI controller and use the MIDI learn feature
 * to map Channel Pressure to your desired functions.
 *
 * Written by Hazri Haqimi, 2025-03-03
 */

#include <midimap.h> // Include the midimap library for handling MIDI messages

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a CPPotentiometer object
CPPotentiometer potentiometer{
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
