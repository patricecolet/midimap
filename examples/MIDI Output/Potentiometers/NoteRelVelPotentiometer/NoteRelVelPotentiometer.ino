/**
 * This example demonstrates how to use a potentiometer to generate MIDI Note messages
 * with velocity sensitivity. This allows for expressive control over note dynamics
 * based on how quickly you turn the potentiometer.
 *
 * @boards AVR, AVR USB, ESP32, SAM, SAMD
 *
 * Connections
 * -----------
 *
 * - A0: wiper of a potentiometer (perfect component)
 *
 * Connect the left terminal of the potentiometer to ground, and the right one
 * to V<sub>CC</sub>.
 *
 * Behavior
 * --------
 *
 * - If the potentiometer value is below MinNoteThreshold: No note is played (Note Off).
 * - When the potentiometer value rises above MinNoteThreshold: Note On is triggered.
 * - The velocity of the Note On message is determined by how quickly you turn the potentiometer.
 * - When the potentiometer value falls below MinNoteThreshold: Note Off is triggered following how quickly you release the potentiometer.
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

#include <midimap.h> // Include the midimap library

USBMIDI_Interface midi; // Instantiate a MIDI over USB interface.
// Note velocity parameters
const uint8_t minNoteThreshold = 10;    // Threshold at which timing starts
const float minPhysicalVelocity = 0.5;  // Minimum physical velocity (units/second)
const float maxPhysicalVelocity = 50.0; // Maximum physical velocity (units/second)

NoteRelVelPotentiometer potentiometer{
    A0,                            // Analog pin connected to potentiometer
    {MIDI_Notes::C[4], Channel_1}, // Note C4 on channel 1
    minNoteThreshold,              // Minimum note threshold
    minPhysicalVelocity,           // Minimum physical velocity
    maxPhysicalVelocity,           // Maximum physical velocity
    40,                            // Minimum threshold (0-127)
    127,                           // Maximum threshold (0-127)
};
void setup() {
    midimap.begin(); // Initialize midimap
}
void loop() {
    midimap.loop(); // Update the midimap
}