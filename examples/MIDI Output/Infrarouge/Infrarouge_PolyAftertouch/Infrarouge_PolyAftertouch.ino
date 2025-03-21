/** 
 * This example demonstrates how to simulate Channel Pressure using a 2Y0A21 infrared (IR) sensor, 
 * providing expressive control in your DAW software. The intensity of the infrared light detected 
 * by the IR sensor simulates the pressure applied to a key after it is initially pressed, which 
 * can control various MIDI parameters.
 *
 * The **2Y0A21** IR sensor has a sensing range of **10cm to 80cm** and measures the distance to 
 * the object in front of it, which in turn adjusts the Channel Pressure value. As the object moves 
 * closer or farther, the light intensity detected by the sensor changes, simulating pressure applied 
 * to a key after it is initially pressed.
 *
 * This setup allows for dynamic control of Channel Pressure, adding expressiveness to your 
 * performance or production.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * 
 * Cabling Details
 * ---------------
 * - 5V: Power supply for the IR sensor.
 * - A0: IR sensor connected to this pin to simulate Channel Pressure based on infrared light intensity.
 * - Pull-up resistor: 500kΩ between the A0 pin and 5V to stabilize the signal.
 * 
 * The **2Y0A21** infrared sensor's light exposure determines the Channel Pressure value, allowing you to 
 * simulate the pressure applied to a key after it is initially pressed by adjusting the light levels 
 * based on the distance to the sensor (between 10cm and 80cm).
 * 
 * You can refer to the **MIDI note numbers** to map specific notes to your MIDI controller.
 * 
 * MIDI Mapping
 * ------------
 * In your DAW, select the Arduino as a custom MIDI controller and use the MIDI learn feature 
 * to map Channel Pressure to your desired functions.
 * 
 * Code written by Hazri Haqimi, 2025-03-03
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate a PolyAftertouch object
PolyAftertouchSensor Infrarouge {
  A0,                                   // Analog pin connected to photoresistor
  {MIDI_Notes::C[4], Channel_1}, // Channel volume of channel 1
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}