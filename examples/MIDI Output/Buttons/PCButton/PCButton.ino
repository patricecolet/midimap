/** 
 * This is an example that demonstrates the use of MIDI Program Change buttons.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD, Teensy 3.x
 * 
 * Connections
 * -----------
 * 
 * - 2: momentary push button (to ground)
 * 
 * The internal pull-up resistor for the button will be enabled automatically.
 * 
 * Behavior
 * --------
 * 
 * - When the button on pin 2 is pressed, the MIDI Program for 
 *   "Steel Drums" is selected.
 * 
 * Written by PieterP, 2019-08-07  
 * https://github.com/tttapa/Control-Surface
 * 
 * Modified by Nuryn Sophea, 2025-04-03
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface
USBMIDI_Interface midi;

// Instantiate a PCButton that reads the input from a push button and sends out
// a MIDI Program Change message when it's pressed.
PCButton pcBtn {
  2,                                 // pin
  {MIDI_PC::Steel_Drums, Channel_1}, // address
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
