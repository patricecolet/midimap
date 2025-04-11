/**
 * This example demonstrates how to simulate Polyphonic Aftertouch using a photoresistor,
 * providing expressive control in your DAW software. The intensity of light hitting the
 * photoresistor simulates aftertouch pressure, which can control various MIDI parameters.
 *
 * This setup allows for dynamic control of MIDI aftertouch, adding more expressiveness to
 * your performance or production.
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
 * The photoresistor's light exposure determines the polyphonic aftertouch pressure value,
 * allowing you to control aftertouch dynamically by adjusting the light levels.
 *
 * Mapping
 * -------
 * 
 * In your DAW, select the Arduino as a custom MIDI controller and use the MIDI learn feature
 * to map polyphonic aftertouch to your desired functions.
 *
 * Written by Hazri Haqimi, 2025-03-03
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a PolyAftertouch object
KPPotentiometer photoresistor{
    A5,                            // Analog pin connected to photoresistor
    {MIDI_Notes::C[4], Channel_1}, // Channel volume of channel 1
    //0,        // Minimum threshold if the sensor is not perfect (0-127)
    //127,       // Maximum threshold if the sensor is not perfect (0-127)
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}