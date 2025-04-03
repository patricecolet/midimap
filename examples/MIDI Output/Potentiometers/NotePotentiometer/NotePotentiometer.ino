/**
 * @file VelostatPolyNote.ino
 * @brief Simulating Polyphonic Aftertouch using Velostat and MIDI.
 *
 * This example demonstrates how to use **Velostat** (a pressure-sensitive material) in a
 * **voltage divider circuit** to generate MIDI **Polyphonic Aftertouch**.
 * This allows for **independent pressure control per note**, adding expressiveness to your performance.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * ## Electrical Setup: Voltage Divider (Pont Diviseur de Tension)
 * The circuit uses a **voltage divider** to convert the pressure-sensitive resistance of Velostat
 * into a readable voltage signal:
 *
 * ```
 *        +5V
 *         │
 *         │
 *         Velostat (Pressure-sensitive material)
 *         │
 *         ├───► A0 (Analog Input - Reads voltage)
 *         │
 *         R1 (Fixed Resistor, 10kΩ)  <-- Pull-down resistor
 *         │
 *        GND
 * ```
 *
 * - **Velostat:** Changes resistance based on applied pressure.
 * - **R1 (10kΩ Pull-down Resistor):** Ensures stability by pulling A0 to GND when no pressure is applied.
 * - **A0 (Analog Pin):** Reads voltage between Velostat and R1, mapping it to a MIDI pressure.
 *
 * ## Behavior
 * - If **no pressure is applied**, the Velostat has **high resistance**, causing a **high voltage** at A0.
 * - If **light pressure is applied**, the resistance decreases, lowering voltage at A0, triggering **Note On**.
 * - If **strong pressure is applied**, the voltage is low enough to trigger **Polyphonic Aftertouch**.
 *
 * ## MIDI Mapping
 * - **If pressure < MinNoteThreshold:** No note is played (Note Off).
 * - **If MinNoteThreshold ≤ pressure < TriggerValue:** Normal note (Note On).
 * - **If pressure ≥ TriggerValue:** Note plays with **Polyphonic Aftertouch**.
 *
 * ## Usage
 * 1. Connect your Arduino to your computer.
 * 2. Select the Arduino as a **MIDI input device** in your DAW.
 * 3. Use the **MIDI Learn** feature to map Polyphonic Aftertouch.
 *
 * Written by Nuryn Sophea, 2025-04-03
 */

#include <midimap.h> // Include the midimap library

 USBMIDI_Interface midi; // Instantiate a MIDI over USB interface.
 
 const uint8_t MinNoteThreshold = 50;
 uint8_t range = 127; // range of MIDI Output
 
 // Velocity sensitivity parameters
 float minPhysicalVelocity = 0.01; // Slow press - lower values make slow presses more sensitive
 float maxPhysicalVelocity = 1.0;  // Fast press - higher values require faster presses for max velocity
 
 // Instantiate a NotePotentiometer object
 NotePotentiometer potentiometer{
     A0,                            // Analog pin connected to potentiometer
     {MIDI_Notes::C[4], Channel_1}, // Note C4 on channel 1
     MinNoteThreshold,              // Minimum note threshold
     range,                         // Range of MIDI Output
     0x7F,                          // Default velocity (127)
     minPhysicalVelocity,           // Minimum physical velocity
     maxPhysicalVelocity            // Maximum physical velocity
 };
 
 void setup()
 {
   midimap.begin(); // Initialize midimap
 }
 
 void loop()
 {
   midimap.loop(); // Update the midimap
 }