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
 * This example demonstrates how to use an accelerometer with an SPI connection to control three different
 * MIDI Controllers based on the X, Y, and Z axes of movement. The accelerometer’s readings are mapped to MIDI
 * Controller values, allowing you to control various parameters in your DAW software with the device’s orientation.
 *
 * The accelerometer communicates with the ESP32 using **SPI (Serial Peripheral Interface)** protocol.
 * The obtained motion data is then sent as MIDI messages over **Bluetooth Low Energy (BLE)**, enabling
 * wireless MIDI control.
 *
 * The ESP32 acts as a **Bluetooth MIDI device**, sending MIDI CC messages based on real-time accelerometer
 * data, allowing for dynamic and expressive control of software instruments or effects in a DAW.
 *
 * **Supported Board:**
 * - **ESP32** (Required for Bluetooth MIDI support)
 *
 * **Cabling Details**
 * -------------------
 * - 3.3V: Power supply for the accelerometer.
 * - GND: Ground connection for the accelerometer.
 * - SPI MOSI: Accelerometer’s MOSI (Master Out Slave In) pin connected to the SPI MOSI pin on the ESP32.
 * - SPI MISO: Accelerometer’s MISO (Master In Slave Out) pin connected to the SPI MISO pin on the ESP32.
 * - SPI SCK: Accelerometer’s SCK (Serial Clock) pin connected to the SPI clock pin on the ESP32.
 * - SPI CS (Chip Select): Accelerometer’s CS (Chip Select) pin connected to a digital pin on the ESP32 (e.g., Pin 10).
 *
 * **MIDI Mapping**
 * ---------------
 * The values from the X, Y, and Z axes are read via SPI, scaled to an appropriate range for MIDI controllers,
 * and then transmitted over Bluetooth MIDI.
 *
 * - **X-axis** → MIDI CC 1 (e.g., Modulation)
 * - **Y-axis** → MIDI CC 7 (e.g., Volume)
 * - **Z-axis** → MIDI CC 74 (e.g., Filter Cutoff)
 *
 * In your DAW, pair the ESP32 via Bluetooth MIDI and use the **MIDI learn** feature to assign the
 * controllers to desired functions.
 *
 * **How to Connect via Bluetooth MIDI:**
 * - On **iOS/macOS**, use **GarageBand** or **MIDI BLE Connect** to pair the ESP32.
 * - On **Windows**, use **MIDI Berry** with a virtual loopback device.
 * - On **Android**, use **MIDI BLE Peripheral**.
 *
 * This setup enables wireless MIDI control via Bluetooth, eliminating the need for USB cables.
 *
 * Code written by Hazri Haqimi, 2025-03-11
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
BluetoothMIDI_Interface midi;

uint8_t range = 127; // range of the MIDI Outputs

// Instantiate a Accelerometer3AxisSensor object
Accelerometer3AxisSensor accelerometer3axis{
    {MIDI_CC::Channel_Volume, CHANNEL_1},   // Channel volume of channel 1
    {MIDI_CC::Pan, CHANNEL_1},              // Channel Pan of channel 1
    {MIDI_CC::Modulation_Wheel, CHANNEL_1}, // Channel Modulation Wheel of channel 1
    range,                                  // Range of MIDI Outputs
};

void setup()
{
  midimap.begin(); // Initialize midimap
}

void loop()
{
  midimap.loop(); // Update the midimap
}