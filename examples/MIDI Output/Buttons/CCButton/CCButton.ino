/** 
 * This is an example that demonstrates the use of MIDI Control Change Buttons.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD, Teensy 3.x
 * 
 * Connections
 * -----------
 * 
 * - 5: momentary push button (to ground)
 * 
 * The internal pull-up resistor for the button will be enabled automatically.
 * 
 * Behavior
 * --------
 * 
 * - When the button on pin 5 is pressed, a MIDI Control Change message with a 
 *   value of 0x7F (127) is sent for General Purpose Controller #1.
 * - When the button on pin 5 is released, a MIDI Control Change message with a 
 *   value of 0x00 (0) is sent for General Purpose Controller #1
 * 
 * Mapping
 * -------
 * 
 * Select the Arduino as a custom MIDI controller in your DAW, and use the 
 * MIDI learn option to assign the button to a function.
 * 
 * Written by PieterP, 2019-09-29  
 * https://github.com/tttapa/Control-Surface
 * 
 * Modified by Nuryn Sophea, 2025-04-03
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a CCButton object
CCButton button {
  // Push button on pin 5:
  5,
  // General Purpose Controller #1 on MIDI channel 1:
  {MIDI_CC::General_Purpose_Controller_1, Channel_1},
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}