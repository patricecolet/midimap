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
 * Cabling Details
 * ---------------
 * - 5V: Power supply for the photoresistor
 * - A0: Photoresistor connected to this pin to simulate polyphonic aftertouch based on light intensity.
 * - Pull-up resistor: 500kΩ between the A0 pin and 5V to stabilize the signal.
 *
 * The photoresistor's light exposure determines the polyphonic aftertouch pressure value,
 * allowing you to control aftertouch dynamically by adjusting the light levels.
 *
 * See @ref MIDI_Notes for a table of MIDI note numbers.
 *
 * MIDI Mapping
 * ------------
 * In your DAW, select the Arduino as a custom MIDI controller and use the MIDI learn feature
 * to map polyphonic aftertouch to your desired functions.
 *
 * Code written by Hazri Haqimi, 2025-03-03
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a PolyAftertouch object
PAPotentiometer photoresistor{
    A0,                            // Analog pin connected to photoresistor
    {MIDI_Notes::C[4], Channel_1}, // Channel volume of channel 1
    //48,        // Minimum threshold if the sensor is not perfect (0-127)
    //100,       // Maximum threshold if the sensor is not perfect (0-127)
};

void setup()
{
  midimap.begin(); // Initialize midimap
}

void loop()
{
  midimap.loop(); // Update the midimap
}