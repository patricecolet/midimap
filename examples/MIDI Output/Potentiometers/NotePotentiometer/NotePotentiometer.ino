/**
 * This example demonstrates how to use a potentiometer to generate MIDI Note messages. This allows for expressive control over note dynamics
 * based on how quickly you turn the potentiometer.
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
 * - If the potentiometer value is below MinNoteThreshold: No note is played (Note Off).
 * - When the potentiometer value rises above MinNoteThreshold: Note On is triggered.
 * - When the potentiometer value falls below MinNoteThreshold: Note Off is triggered.
 *
 * Mapping
 * -------
 * 
 * Select the Arduino as a custom MIDI controller in your DAW, and use the 
 * MIDI learn option to assign the potentiometer to a function. 
 * Select the Arduino as a **MIDI input device** in your DAW. Use the **MIDI Learn** feature to map the note.
 * 
 * Written by Nuryn Sophea, 2025-04-03
 */

 #include <midimap.h>  // Include the midimap library

 USBMIDI_Interface midi;  // Instantiate a MIDI over USB interface.
 
 const uint8_t triggerValue = 10;  // Threshold at which note is triggered

 NotePotentiometer potentiometer{
  A5,                               // Analog pin connected to potentiometer
  { MIDI_Notes::D[3], Channel_1 },  // Note C4 on channel 1
  triggerValue,                     // Trigger threshold
  5,                               // Minimum threshold (0-127)
  125,                              // Maximum threshold (0-127)
};
 
 void setup() {
   midimap.begin();  // Initialize midimap
 }
 
 void loop() {
   midimap.loop();  // Update the midimap
 }