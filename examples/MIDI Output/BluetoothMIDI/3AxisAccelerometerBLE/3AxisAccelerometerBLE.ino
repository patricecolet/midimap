/*****************************************************************************/
//	Function:    Get the accelemeter of the x/y/z axis.
//  Hardware:    Grove - 3-Axis Digital Accelerometer(±1.5g)
//	Arduino IDE: Arduino-1.0
//	Author:	 Frankie.Chu
//	Date: 	 Jan 10,2013
//	Version: v0.9b
//	by www.seeedstudio.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
/*******************************************************************************/

/**
 * This example demonstrates how to use an accelerometer with an SPI connection to control
 * three different MIDI Controllers based on the X, Y, and Z axes of movement. The ESP32
 * sends MIDI Control Change (CC) messages **wirelessly** via **Bluetooth MIDI (BLE MIDI)**.
 *
 * @boards  ESP32 (Required for Bluetooth MIDI support)
 *
 * Connections
 * -----------
 *
 * - **3.3V:** Power supply for the accelerometer
 * - **GND:** Ground connection for the accelerometer
 * - **MOSI:** Accelerometer's MOSI pin connected to ESP32 SPI MOSI pin
 * - **MISO:** Accelerometer's MISO pin connected to ESP32 SPI MISO pin
 * - **SCK:** Accelerometer's SCK pin connected to ESP32 SPI clock pin
 * - **CS:** Accelerometer's Chip Select pin connected to ESP32 digital pin (e.g., Pin 10)
 *
 * Behavior
 * --------
 *
 * - When you move the accelerometer, you should receive MIDI Control Change
 *   events with values ranging from **0 to 127** for each axis.
 * - The accelerometer readings are filtered to reduce noise and provide smooth control.
 *
 * Mapping
 * -------
 *
 * The ESP32 acts as a **Bluetooth MIDI controller**, sending data from the accelerometer's
 * three axes:
 *
 * - **X-axis** → MIDI CC 1 (e.g., Modulation)
 * - **Y-axis** → MIDI CC 7 (e.g., Volume)
 * - **Z-axis** → MIDI CC 74 (e.g., Filter Cutoff)
 *
 * **How to Connect via Bluetooth MIDI:**
 * - On **iOS/macOS**, use **GarageBand** or **MIDI BLE Connect** to pair the ESP32.
 * - On **Windows**, use **MIDI Berry** with a virtual loopback device.
 * - On **Android**, use **MIDI BLE Peripheral**.
 *
 * Once connected, use the **MIDI Learn** feature in your DAW to assign
 * the accelerometer axes to control any parameters.
 *
 * Code written by Hazri Haqimi, 2025-03-11
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
BluetoothMIDI_Interface midi;

// Instantiate a Accelerometer3AxisSensor object
Accelerometer3AxisSensor accelerometer3axis{
    {MIDI_CC::Channel_Volume, CHANNEL_1},   // Channel volume of channel 1
    {MIDI_CC::Pan, CHANNEL_1},              // Channel Pan of channel 1
    {MIDI_CC::Modulation_Wheel, CHANNEL_1}, // Channel Modulation Wheel of channel 1

};

void setup()
{
  midimap.begin(); // Initialize midimap
}

void loop()
{
  midimap.loop(); // Update the midimap
}