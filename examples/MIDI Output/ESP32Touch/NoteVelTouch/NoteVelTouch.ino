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
 * Modified by Hazri Haqimi, 2023-04-10
 */

// Uncomment this line to enable debug output for touch sensor readings
#define DEBUG_TOUCH

// For long-range detection, try TOUCH_DELTA_MAX = 150, TOUCH_BASELINE_THRESHOLD = 50;
// For short-range detetction, try TOUCH_DELTA_MAX = 4000, TOUCH_BASELINE_THRESHOLD = 3500;
// For direct touch detection, try TOUCH_DELTA_MAX = 200000, TOUCH_BASELINE_THRESHOLD = 400;

// Maximum expected delta value (default: 4000.0f)
//#define TOUCH_DELTA_MAX 200000.0f

// Threshold for freezing baseline updates (default: 100.0f)
//#define TOUCH_BASELINE_THRESHOLD 400.0f


 #include <midimap.h>  // Include the midimap library

 USBMIDI_Interface midi;  // Instantiate a MIDI over USB interface.
  
 // Note velocity parameters
 const uint8_t minNoteThreshold = 10;  // Threshold at which timing starts
 const float minPhysicalVelocity = 0.5; // Minimum physical velocity (units/second)
 const float maxPhysicalVelocity = 50.0; // Maximum physical velocity (units/second)
 
 NoteVelTouch potentiometer{
   A0,                               // Analog pin connected to potentiometer
   { MIDI_Notes::C[4], Channel_1 },  // Note C4 on channel 1
   minNoteThreshold,                 // Minimum note threshold
   minPhysicalVelocity,              // Minimum physical velocity
   maxPhysicalVelocity,              // Maximum physical velocity
   //40,                               // Minimum threshold (0-127)
   //127,                              // Maximum threshold (0-127)
 };
  
 void setup() {
   midimap.begin();  // Initialize midimap
 }
  
 void loop() {
   midimap.loop();  // Update the midimap
 }
