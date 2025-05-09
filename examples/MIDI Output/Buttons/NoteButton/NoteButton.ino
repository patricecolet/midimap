/**
 * This is an example that demonstrates the use of MIDI Note Buttons that can be
 * used for triggering samples, mute/solo/rec buttons, play/pause/stop buttons,
 * etc. It can control almost any push button control in your DAW software.
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
 * - When the button on pin 5 is pressed, a MIDI Note On message is sent for
 *   note C4.
 * - When the button on pin 5 is released, a MIDI Note Off message is sent for
 *   note C4.
 *
 * See @ref MIDI_Notes for a table of MIDI note numbers.
 *
 * Mapping
 * -------
 *
 * Select the Arduino as a custom MIDI controller in your DAW, and use the
 * MIDI learn option to assign the button to a function.
 *
 * Written by PieterP, 2019-08-07
 * https://github.com/tttapa/Control-Surface
 *
 * Modified by Hazri Haqimi, 2025-03-03
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a NoteButton object
NoteButton button{
    5,                             // Push button on pin 5
    {MIDI_Notes::C[4], Channel_1}, // Note C4 on MIDI channel 1
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}