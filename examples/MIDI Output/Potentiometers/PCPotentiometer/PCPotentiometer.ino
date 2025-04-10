/**
 * This example demonstrates how to use a potentiometer to change MIDI Programs.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * 
 * Connections
 * -----------
 * 
 * - A0: wiper of a potentiometer 
 * - Connect the left terminal of the potentiometer to ground, and the right one
 *   to V<sub>CC</sub>.
 * - 47nF capacitor between A0 and GND, to prevent noise.
 *
 * Behavior
 * --------
 * 
 * - When the potentiometer value rises above MinNoteThreshold: The MIDI Program for 
 *   "Steel Drums" is selected.
 * 
 * Written by Nuryn Sophea, 2025-04-10
 */

 #include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface
USBMIDI_Interface midi;

const uint8_t triggerValue = 10;  // Threshold at which note is triggered

// Instantiate a PCButton that reads the input from a push button and sends out
// a MIDI Program Change message when it's pressed.
PCPotentiometer pcpotentiometer {
  2,                                 // pin
  {MIDI_PC::Steel_Drums, Channel_1}, // address
  triggerValue,                     // Trigger threshold
  90,                               // Minimum threshold (0-127)
  125,                              // Maximum threshold (0-127)
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}