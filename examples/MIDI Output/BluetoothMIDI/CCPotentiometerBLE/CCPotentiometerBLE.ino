/**
 * This example demonstrates the use of a MIDI Control Change potentiometer
 * that can be used for changing effect parameters, volume, pan, and balance
 * controls, etc. It can control almost any knob in your DAW software.
 *
 * The ESP32 sends MIDI Control Change (CC) messages **wirelessly** via
 * **Bluetooth MIDI (BLE MIDI)**, allowing for cable-free control.
 *
 * @board  ESP32 (Required for Bluetooth MIDI support)
 *
 * Connections
 * -----------
 *
 * - **A0:** Wiper of a potentiometer
 *
 * Connect the **left terminal** of the potentiometer to **ground (GND)**,
 * and the **right terminal** to **VCC (3.3V)**.
 *
 * Behavior
 * --------
 *
 * - When you turn the potentiometer, you should receive MIDI Control Change
 *   events with values ranging from **0 to 127**.
 * - The analog input is filtered to reduce noise. If you experience jitter,
 *   check your wiring and ensure the potentiometer resistance is **10 kΩ**.
 *
 * Mapping
 * -------
 *
 * The ESP32 acts as a **Bluetooth MIDI controller**, so you need to pair it
 * with your DAW or music software that supports BLE MIDI.
 *
 * - **MIDI CC Number:** 7 (Channel Volume)
 * - **MIDI Channel:** 1
 *
 * **How to Connect via Bluetooth MIDI:**
 * - On **iOS/macOS**, use **GarageBand** or **MIDI BLE Connect** to pair the ESP32.
 * - On **Windows**, use **MIDI Berry** with a virtual loopback device.
 * - On **Android**, use **MIDI BLE Peripheral**.
 *
 * Once connected, use the **MIDI Learn** feature in your DAW to assign
 * the potentiometer to control any parameter.
 *
 * Written by PieterP, 2019-08-13
 * https://github.com/tttapa/Control-Surface
 *
 * Modified by Hazri Haqimi, 2025-03-03 (Added Bluetooth MIDI Support for ESP32)
 */

#include <midimap.h>

// Instantiate a MIDI over BLE interface.
BluetoothMIDI_Interface midi;

uint8_t range = 127; // range of the MIDI Outputs

CCPotentiometer potentiometer{
    // Create a new instance of the class `CCPotentiometer`, called `potentiometer`,
    A0,                                   // on pin A0
    {MIDI_CC::Channel_Volume, CHANNEL_1}, // that sends MIDI messages with controller 7 (channel volume) on channel 1.
    range,                                // range of the MIDI Outputs
};

void setup()
{
    // Initialize everything
    midimap.begin();
}

void loop()
{
    // Update the midimap (check whether the potentiometer's input has
    // changed since last time, if so, send the new value over BLE MIDI).
    midimap.loop();
}