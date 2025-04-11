/** 
 * This example demonstrates the use of ESP32 touch sensors with MIDI Key Pressure
 * (Polyphonic Aftertouch) output. The touch sensor can be used for adding expressive
 * control to individual notes in synthesizers and virtual instruments.
 *
 * @boards ESP32
 * 
 * Connections
 * -----------
 * 
 * - T1: Connect to a conductive surface or wire for touch sensing
 * 
 * Behavior
 * --------
 * 
 * - When you touch or approach the sensor, you should receive MIDI Key Pressure
 *   events for the specified note, with a value between 0 and 127.
 * - The touch input is filtered using adaptive baseline tracking with
 *   multi-stage smoothing to provide stable values.
 * 
 * Mapping
 * -------
 * 
 * Select the ESP32 as a custom MIDI controller in your DAW, and use the 
 * MIDI learn option to assign the touch sensor to a function.  
 * It will send MIDI Key Pressure messages for note C4 on channel 1, which can be
 * used to add expressive control to individual notes in synthesizers that
 * support polyphonic aftertouch.
 * 
 * 
 * Modified by Hazri Haqimi, 2023-04-11
 */

// Uncomment this line to enable debug output for touch sensor readings
//#define DEBUG_TOUCH

// For long-range detection, try TOUCH_DELTA_MAX = 150, TOUCH_BASELINE_THRESHOLD = 50;
// For short-range detetction, try TOUCH_DELTA_MAX = 4000, TOUCH_BASELINE_THRESHOLD = 3500;
// For direct touch detection, try TOUCH_DELTA_MAX = 200000, TOUCH_BASELINE_THRESHOLD = 400;

// Maximum expected delta value (default: 4000.0f)
//#define TOUCH_DELTA_MAX 200000.0f

// Threshold for freezing baseline updates (default: 100.0f)
//#define TOUCH_BASELINE_THRESHOLD 400.0f

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Create a touch sensor that sends MIDI CC messages
KPTouch touchSensor {
  T1,                                   // Touch pin connected to sensor
  {MIDI_Notes::C[4], Channel_1}, // Channel volume of channel 1
  //47
  //127
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
