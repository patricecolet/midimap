/** 
 * This example demonstrates the use of MIDI Pitch Bend that
 * can be used for changing effect parameters, volumes, pan and balance
 * controls, etc. It can control almost any knob in your DAW software.
 *
 * @boards  AVR, AVR USB, Nano Every, Due, Nano 33 IoT, Nano 33 BLE, UNO R4, Pi Pico, Teensy 3.x, ESP32, ESP8266
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
 * - When you move an object nearer or further from the ultrasonic sensor, you should receive MIDI Pitch Bend
 *   events on channel 1, with a value between -8192 and +8191.
 * - It uses 14 bits so there shouldn't be any noise on the 
 *   position. The resolution is 14 bits, so the precision is 16384.
 * 
 * Mapping
 * -------
 * 
 * Select the Arduino as a custom MIDI controller in your DAW, and use the 
 * MIDI learn option to assign the potentiometer to a function.
 * 
 * Written by Nuryn Sophea, 2025-03-11
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a PBPotentiometer object
PBUltrasonic ultrasonicpitchbend {
  D7,        // SIG pin connected to any Digital Pin
  Channel_1, // MIDI Channel 1
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
