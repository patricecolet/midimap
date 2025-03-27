/**
 * @file PiezoNote.ino
 * @brief Example demonstrating the use of a Piezo Sensor as a MIDI Note Trigger.
 *
 * This example shows how to use a Piezo Sensor to trigger MIDI Note On/Off
 * messages, allowing it to function as a drum pad, percussive trigger, or
 * similar input for your DAW.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 *
 * @section connections Connections
 *
 * - A Piezo Sensor is connected to an **analog input pin** (e.g., A0).
 * - A **1MΩ resistor** is wired in **parallel** with the Piezo Sensor.
 *
 * @section impact Why Use a 1MΩ Resistor in Parallel?
 *
 * The Piezo Sensor generates a high-voltage spike when struck, which can
 * potentially damage the microcontroller or result in inconsistent readings.
 * Using a **1MΩ resistor in parallel** helps to:
 *
 * - **Prevent excessive voltage spikes** by providing a discharge path.
 * - **Stabilize the signal**, preventing it from floating after the impact.
 * - **Improve sensitivity** by ensuring consistent note triggering.
 *
 * @section behavior Behavior
 *
 * - When the Piezo Sensor is struck hard enough (above a set threshold),
 *   a **MIDI Note On** message is sent for **note C4**.
 * - When the vibration decays below the threshold, a **MIDI Note Off** message
 *   is sent for **note C4**.
 *
 * @section mapping Mapping
 *
 * Select the Arduino as a custom MIDI controller in your DAW, and use the
 * MIDI learn option to assign the Piezo trigger to a function.
 *
 * @note Adjust the threshold in the code to fine-tune sensitivity.
 *
 * Written by Hazri Haqimi, 2025-03-27
 */

#include <midimap.h>

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

uint8_t threshold = 100; // note threshold (0-127)

PiezoNoteSensor piezo{
    A0,                            // Analog pin connected to piezo
    {MIDI_Notes::C[4], Channel_1}, // Channel volume of channel 1
    threshold,                     // note threshold
};

void setup()
{
    midimap.begin();
}

void loop()
{
    midimap.loop();
}
