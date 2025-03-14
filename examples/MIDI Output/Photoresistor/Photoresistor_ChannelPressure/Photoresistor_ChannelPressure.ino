/** 
 * This example demonstrates how to simulate Channel Pressure using a photoresistor,
 * providing expressive control in your DAW software. The intensity of light hitting the 
 * photoresistor simulates the pressure applied to a key after it is initially pressed, 
 * which can control various MIDI parameters.
 *
 * This setup allows for dynamic control of Channel Pressure, adding expressiveness to your 
 * performance or production.
 *
 * @boards  AVR, AVR USB, Nano Every, Due, Nano 33 IoT, Nano 33 BLE, UNO R4, Pi Pico, Teensy 3.x, ESP32, ESP8266
 * 
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

 // Instantiate a MIDI over USB interface
 USBMIDI_Interface midi; 
 
 // Define threshold values for note triggering
 const uint8_t TriggerValue = 60;        // Value at which aftertouch begins
 const uint8_t MinNoteThreshold = 10;    // Minimum value required to trigger a note
 
 // Instantiate a VelostatPolyNote object to handle MIDI note and aftertouch behavior
 VelostatPolyNote Velostat{
     A0,                            // Analog pin connected to Velostat sensor
     {MIDI_Notes::C[4], Channel_1}, // MIDI Note C4 on channel 1
     TriggerValue,                  // Threshold for triggering aftertouch
     MinNoteThreshold               // Minimum threshold to activate a note
 };
 
 void setup()
 {
   midimap.begin(); // Initialize the midimap library for MIDI communication
 }
 
 void loop()
 {
   midimap.loop(); // Continuously process MIDI events in the main loop
 }
 