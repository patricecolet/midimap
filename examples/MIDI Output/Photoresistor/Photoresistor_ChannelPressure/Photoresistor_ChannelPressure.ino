/** 
 * This example demonstrates how to simulate Channel Pressure using a photoresistor,
 * providing expressive control in your DAW software. The intensity of light hitting the 
 * photoresistor simulates the pressure applied to a key after it is initially pressed, 
 * which can control various MIDI parameters.
 *
 * This setup allows for dynamic control of Channel Pressure, adding expressiveness to your 
 * performance or production.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * Connections
 * -----------
 * - 5V: Power supply for the photoresistor
 * - A0: Photoresistor connected to this pin to simulate Channel Pressure based on light intensity.
 * - Pull-up resistor: 500kΩ between the A0 pin and 5V to stabilize the signal.
 * 
 * Behavior
 * --------
 * 
 * The photoresistor's light exposure determines the Channel Pressure value, allowing you to 
 * simulate the pressure applied to a key after it is initially pressed by adjusting the light levels.
 * 
 * You can refer to the **MIDI note numbers** to map specific notes to your MIDI controller.
 * 
 * Mapping
 * --------
 * In your DAW, select the Arduino as a custom MIDI controller and use the MIDI learn feature 
 * to map Channel Pressure to your desired functions.
 * 
 * Written by Hazri Haqimi, 2025-03-03
 */

 #include <midimap.h> // Include the midimap library for handling MIDI messages

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a ChannelPressureSensor object
ChannelPressureSensor photoresistor {
  A0,                                   // Analog pin connected to photoresistor
   CHANNEL_1, // Channel volume of channel 1
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
 