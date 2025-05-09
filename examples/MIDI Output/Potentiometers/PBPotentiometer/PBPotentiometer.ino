/** 
 * This example demonstrates the use of MIDI Pitch Bend potentiometers that
 * can be used for changing effect parameters, volumes, pan and balance
 * controls, etc. It can control almost any knob in your DAW software.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * Connections
 * -----------
 * 
 * - A0: wiper of a potentiometer
 * - A1: wiper of a second potentiometer (imperfect component example)
 * 
 * Connect the left terminal of the potentiometer to ground, and the right one
 * to V<sub>CC</sub>.
 * 
 * Behavior
 * --------
 * 
 * - When you turn the potentiometer, you should receive MIDI Pitch Bend
 *   events on channel 1, with a value between -8192 and +8191.
 * - The analog input is filtered, so there shouldn't be any noise on the 
 *   position. If there is, check your wiring, and make sure that the resistance
 *   of the potentiometer isn't too high (10 kΩ is ideal).
 * - For imperfect components, you can set minimum and maximum thresholds to
 *   filter out noise at the extremes of the potentiometer's range.
 * 
 * Mapping
 * -------
 * 
 * Select the Arduino as a custom MIDI controller in your DAW, and use the 
 * MIDI learn option to assign the potentiometer to a function.
 * 
 * Written by PieterP, 2019-08-23  
 * https://github.com/tttapa/Control-Surface
 * 
 * Modified by Nuryn Sophea, 2025-03-10
 */

#include <midimap.h> // Include the midimap library

 // Instantiate a MIDI over USB interface.
 USBMIDI_Interface midi;
 
 // For perfect components (no thresholding needed)
 PBPotentiometer perfectPotentiometer {
   A0,        // Analog pin connected to potentiometer
   Channel_1, // MIDI Channel 1
    //100,        // Minimum threshold if the sensor is not perfect (0-1633)
    //900,       // Maximum threshold if the sensor is not perfect (0-1633)
 };
 

 
 void setup() {
   midimap.begin(); // Initialize midimap
 }
 
 void loop() {
   midimap.loop(); // Update the midimap
 }
 