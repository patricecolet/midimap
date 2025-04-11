/** 
 * This example demonstrates the use of ESP32 touch sensors to send MIDI Program Change
 * messages. The touch sensor acts as a trigger to switch between different instrument
 * sounds, patches, or presets in your synthesizer or DAW.
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
 * - When you touch the sensor and exceed the trigger threshold, a Program Change
 *   message is sent to select the "Steel Drums" instrument (MIDI program 114)
 * - The touch input is filtered using adaptive baseline tracking with
 *   multi-stage smoothing to provide stable triggering
 * 
 * Mapping
 * -------
 * 
 * Select the ESP32 as a custom MIDI controller in your DAW or connect it to a
 * MIDI synthesizer. When you touch the sensor, it will send a MIDI Program Change
 * message on channel 1 to select the Steel Drums instrument.
 * 
 * This can be used to switch between different instrument sounds, effects presets,
 * or any other function in your DAW that responds to Program Change messages.
 * 
 * Modified by Hazri Haqimi, 2023-04-10
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

// Instantiate a MIDI over USB interface
USBMIDI_Interface midi;

const uint8_t triggerValue = 10;  // Threshold at which note is triggered

// Instantiate a PCButton that reads the input from a push button and sends out
// a MIDI Program Change message when it's pressed.
PCTouch touch {
  T1,                                 // pin
  {MIDI_PC::Steel_Drums, Channel_1}, // address
  triggerValue,                     // Trigger threshold
  //90,                               // Minimum threshold (0-127)
  //125,                              // Maximum threshold (0-127)
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}