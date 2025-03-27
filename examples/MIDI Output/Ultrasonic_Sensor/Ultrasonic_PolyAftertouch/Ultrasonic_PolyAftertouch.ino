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
 * - When you put an obstacle near the sensor, the note you hear will have an aftertouch effect depending on the distance you put your obstacle.
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

#include <midimap.h>

// Instantiate a MIDI over USB interface
USBMIDI_Interface midi;

uint8_t range = 127; // range of MIDI Output

// Ultrasonic sensor on pin 7, sending aftertouch for Note C4 (60) on Channel 1
CCUltrasonic ultrasonic{
    7,
    {MIDI_Notes::C[4], Channel_1},
    range, // range of MIDI Output
};

void setup()
{
  midimap.begin(); // Initialize midimap
}

void loop()
{
  midimap.loop(); // Update the midimap
}