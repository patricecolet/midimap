/** 
 * This example demonstrates the use of MIDI Control Change potentiometers that
 * can be used for changing effect parameters, volumes, pan and balance
 * controls, etc. It can control almost any knob in your DAW software.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * 
 * Connections
 * -----------
 * 
<<<<<<< HEAD
<<<<<<<< HEAD:examples/MIDI Output/Potentiometers/CCPotentiometer/CCPotentiometer.ino
=======
>>>>>>> 8ad4b19 (merging branch latest 11-04-2025)
 * - A0: wiper of a potentiometer 
 * - Connect the left terminal of the potentiometer to ground, and the right one
 *   to V<sub>CC</sub>.
 * - 47nF capacitor between A0 and GND, to prevent noise.
<<<<<<< HEAD
========
 * - A0: wiper of a potentiometer (perfect component)
 * - A1: wiper of a second potentiometer (imperfect component)
 * 
 * Connect the left terminal of the potentiometer to ground, and the right one
 * to V<sub>CC</sub>.
>>>>>>>> 8ad4b19 (merging branch latest 11-04-2025):examples/MIDI Output/ESP32Touch/CCESP32Touch/CCESP32Touch.ino
=======
>>>>>>> 8ad4b19 (merging branch latest 11-04-2025)
 * 
 * Behavior
 * --------
 * 
 * - When you turn the potentiometer, you should receive MIDI Control Change
 *   events, with a value between 0 and 127.
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
 * It will send the MIDI Control Change Channel Volume parameter for channel 1.
 * 
 * Written by PieterP, 2019-08-13  
 * https://github.com/tttapa/Control-Surface
 * 
 * Modified by Hazri Haqimi, 2025-03-03
 */

 #include <midimap.h> // Include the midimap library

 // Instantiate a MIDI over USB interface.
 USBMIDI_Interface midi;
 
 // For perfect components (no thresholding needed)
 CCPotentiometer Potentiometer {
   A5,                              // Analog pin connected to potentiometer
   { MIDI_Notes::D[3], Channel_1 }, // Channel volume of channel 1
    //5,                            // Minimum threshold if the sensor is not perfect (0-127)
    //125,                          // Maximum threshold if the sensor is not perfect (0-127)
 };

 void setup() {
   midimap.begin(); // Initialize midimap
 }
 
 void loop() {
   midimap.loop(); // Update the midimap
 }
 