/** 
 * This example demonstrates the use of ESP32 touch sensors to send MIDI Pitch Bend
 * messages. The touch sensor can be used for expressive pitch control, vibrato effects,
 * and other continuous pitch modulations in your DAW or synthesizer.
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
 * - When you touch or approach the sensor, you should receive MIDI Pitch Bend
 *   events, with values ranging from -8192 to +8191 (centered at 0).
 * - The touch input is filtered using adaptive baseline tracking with
 *   multi-stage smoothing to provide stable, expressive control.
 * 
 * Mapping
 * -------
 * 
 * Select the ESP32 as a custom MIDI controller in your DAW, and use the 
 * MIDI learn option to assign the touch sensor to pitch bend control.
 * It will send MIDI Pitch Bend messages on channel 1, which can be
 * used to bend notes up or down, create vibrato effects, or control
 * any parameter that responds to pitch bend data.
 * 
 * The pitch bend range (how much the pitch changes) is determined by
 * your synthesizer or DAW settings, typically ±2 semitones by default.
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

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Create a touch sensor that sends MIDI CC messages
PBTouch touchSensor {
  T1,                                   // Touch pin connected to sensor
  CHANNEL_1, // Channel volume of channel 1
  //47
  //127
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
