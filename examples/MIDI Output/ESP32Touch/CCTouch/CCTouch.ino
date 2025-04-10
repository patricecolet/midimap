/** 
 * This example demonstrates the use of ESP32 touch sensors with MIDI Control Change
 * output. The touch sensor can be used for controlling effect parameters, volumes,
 * pan controls, etc. in your DAW software.
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
 * - When you touch or approach the sensor, you should receive MIDI Control Change
 *   events, with a value between 0 and 127.
 * - The touch input is filtered using adaptive baseline tracking with
 *   multi-stage smoothing to provide stable values.
 * 
 * Mapping
 * -------
 * 
 * Select the ESP32 as a custom MIDI controller in your DAW, and use the 
 * MIDI learn option to assign the touch sensor to a function.  
 * It will send the MIDI Control Change Channel Volume parameter for channel 1.
 * 
 * 
 * Modified by Hazri Haqimi, 2023-03-03
 */

// Uncomment this line to enable debug output for touch sensor readings
//#define DEBUG_TOUCH

// Touch sensor configuration parameters
// Uncomment and modify these values to customize the touch sensor behavior

// Smoothing coefficient for raw readings (default: 0.95f)
// Higher = more responsive but noisier, Lower = smoother but slower
//#define TOUCH_SMOOTH_COEF 0.95f

// Baseline tracking speed (default: 0.01f)
// Higher = faster adaptation to environmental changes
//#define TOUCH_BASELINE_COEF 0.01f

// Threshold for freezing baseline updates (default: 400.0f)
//#define TOUCH_BASELINE_THRESHOLD 400.0f

// Output smoothing coefficient (default: 0.2f)
// Higher = more responsive output, Lower = smoother output
//#define TOUCH_MAPPED_SMOOTH_COEF 0.2f

// Maximum expected delta value (default: 4000.0f)
// Lower for long-range detection, higher for short-range/direct touch
// For long-range detection, try: 500.0f
// For short-range detetction, try (default)
#define TOUCH_DELTA_MAX 500.0f

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Create a touch sensor that sends MIDI CC messages
CCTouch touchSensor {
  T1,                                   // Touch pin connected to sensor
  {MIDI_CC::Channel_Volume, CHANNEL_1}, // Channel volume of channel 1
  //47
  //127
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
