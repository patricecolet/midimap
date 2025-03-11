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
 * The accelerometer can measure motion along three axes (X, Y, and Z), and these measurements are translated 
 * into MIDI messages to control things like volume, pitch, or other parameters. The X-axis will be mapped to one 
 * MIDI controller, the Y-axis to another, and the Z-axis to a third, providing dynamic and expressive control.
 *
 * The accelerometer communicates with the Arduino using the **SPI (Serial Peripheral Interface)** protocol,
 * enabling faster data transfer for real-time motion sensing.
 * 
 * This setup allows you to create more interactive performances or adjust parameters in real-time based on 
 * device orientation.
 * 
 * @boards  AVR, AVR USB, Nano Every, Due, Nano 33 IoT, Nano 33 BLE, UNO R4, Pi Pico, Teensy 3.x, ESP32, ESP8266
 * 
 * Cabling Details
 * ---------------
 * - 5V: Power supply for the accelerometer.
 * - GND: Ground connection for the accelerometer.
 * - SPI MOSI: Accelerometer’s MOSI (Master Out Slave In) pin connected to the SPI MOSI pin on the Arduino.
 * - SPI MISO: Accelerometer’s MISO (Master In Slave Out) pin connected to the SPI MISO pin on the Arduino.
 * - SPI SCK: Accelerometer’s SCK (Serial Clock) pin connected to the SPI clock pin on the Arduino.
 * - SPI CS (Chip Select): Accelerometer’s CS (Chip Select) pin connected to a digital pin on the Arduino (e.g., Pin 10).
 * 
 * The accelerometer readings are mapped to MIDI Controller values, with each axis controlling a different MIDI parameter. 
 * The values from the X, Y, and Z axes are read via SPI communication, scaled to an appropriate range for MIDI controllers, 
 * and then sent as MIDI messages.
 * 
 * You can use the **MIDI controller numbers** in your DAW to assign specific parameters to each controller 
 * for real-time control.
 * 
 * MIDI Mapping
 * ------------
 * In your DAW, select the Arduino as a custom MIDI controller and use the MIDI learn feature to map 
 * the three MIDI controllers (one for each axis) to the desired functions.
 * 
 * Code written by Hazri Haqimi, 2025-03-11
 */


#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a CCPotentiometer object
Accelerometer3AxisSensor accelerometer3axis {                                // Analog pin connected to potentiometer
  {MIDI_CC::Channel_Volume, CHANNEL_1}, // Channel volume of channel 1
  {MIDI_CC::Pan, CHANNEL_1}, // Channel Pan of channel 2
  {MIDI_CC::Modulation_Wheel, CHANNEL_1}, // Channel Modulation Wheel of channel 3
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
