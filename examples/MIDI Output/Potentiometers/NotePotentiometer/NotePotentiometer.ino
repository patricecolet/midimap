/**
 * @file NotePotentiometer.ino
 * @brief Simulating Velocity-Sensitive Notes using a Potentiometer and MIDI.
 *
 * This example demonstrates how to use a potentiometer to generate MIDI Note messages
 * with velocity sensitivity. This allows for expressive control over note dynamics
 * based on how quickly you turn the potentiometer.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * 
 * Connections
 * -----------
 * 
 * - A0: wiper of a potentiometer (perfect component)
 * 
 * Connect the left terminal of the potentiometer to ground, and the right one
 * to V<sub>CC</sub>.
 *
 * ## Behavior
 * - If the potentiometer value is below MinNoteThreshold: No note is played (Note Off).
 * - When the potentiometer value rises above MinNoteThreshold: Note On is triggered.
 * - The velocity of the Note On message is determined by how quickly you turn the potentiometer.
 * - When the potentiometer value falls below MinNoteThreshold: Note Off is triggered.
 *
 * ## MIDI Mapping
 * 1. Connect your Arduino to your computer.
 * 2. Select the Arduino as a **MIDI input device** in your DAW.
 * 3. Use the **MIDI Learn** feature to map the note.
 *
 * Written by Nuryn Sophea, 2025-04-03
 */

#include <midimap.h>  // Include the midimap library

USBMIDI_Interface midi;  // Instantiate a MIDI over USB interface.

const uint8_t MinNoteThreshold = 50;

// Velocity sensitivity parameters
float minPhysicalVelocity = 0.01;  // Slow press - lower values make slow presses more sensitive
float maxPhysicalVelocity = 1.0;   // Fast press - higher values require faster presses for max velocity

// For perfect components (no thresholding needed)
NotePotentiometer potentiometer{
  A0,                               // Analog pin connected to potentiometer
  { MIDI_Notes::C[4], Channel_1 },  // Note C4 on channel 1
  MinNoteThreshold,                 // Minimum note threshold
  minPhysicalVelocity,              // Minimum physical velocity
  maxPhysicalVelocity   ,            // Maximum physical velocity
  100,                               // Minimum threshold if the sensor is not perfect (0-127)
  120 ,                              // Maximum threshold if the sensor is not perfect (0-127)
};



void setup() {
  midimap.begin();  // Initialize midimap
}

void loop() {
  midimap.loop();  // Update the midimap
}
