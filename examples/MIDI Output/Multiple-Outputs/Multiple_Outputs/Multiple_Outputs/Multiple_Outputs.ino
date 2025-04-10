/**
 * This example demonstrates how to simulate Polyphonic Aftertouch using multiple potentiometer,
 * providing expressive control in your DAW software. The intensity of the object hitting each
 * potentiometer simulates aftertouch pressure for different notes.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 *
 * Cabling Details
 * ---------------
 * - 5V: Power supply for the photoresistors
 * - A0, A1: Photoresistors connected to these pins to simulate polyphonic aftertouch
 * - Pull-up resistors: 500kΩ between each analog pin and 5V to stabilize the signals
 *
 * MIDI Mapping
 * ------------
 * In your DAW, select the Arduino as a custom MIDI controller and use the MIDI learn feature
 * to map polyphonic aftertouch to your desired functions.
 *
 * Written by Nuryn Sophea, 2025-04-08
 */

#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate multiple PolyAftertouch objects for different notes
KPPotentiometer photoresistor{
    A8,                            // Analog pin connected to first photoresistor
    {MIDI_Notes::C[4], Channel_1}, // C4 on channel 1
    55,                            // Minimum threshold if the sensor is not perfect (0-127)
    127,                            // Maximum threshold if the sensor is not perfect (0-127)
};
 const uint8_t triggerValue = 10;  // Threshold at which note is triggered
 NotePotentiometer potentiometer{
   A8,                               // Analog pin connected to potentiometer
   { MIDI_Notes::C[4], Channel_1 },  // Note C4 on channel 1
   triggerValue,                     // Trigger threshold
   55,                               // Minimum threshold (0-127)
   127,                               // Maximum threshold (0-127)
 };



KPPotentiometer photoresistor2{
  A7,                            // Analog pin connected to first photoresistor
  {MIDI_Notes::D[4], Channel_1}, // C4 on channel 1
  90,                            // Minimum threshold if the sensor is not perfect (0-127)
  127,                            // Maximum threshold if the sensor is not perfect (0-127)
};
 const uint8_t triggerValue2 = 10;  // Threshold at which note is triggered
 NotePotentiometer potentiometer2{
   A7,                               // Analog pin connected to potentiometer
   { MIDI_Notes::D[4], Channel_1 },  // Note C4 on channel 1
   triggerValue2,                     // Trigger threshold
   90,                               // Minimum threshold (0-127)
   127,                               // Maximum threshold (0-127)
 };



 KPPotentiometer photoresistor3{
  A2,                            // Analog pin connected to first photoresistor
  {48, Channel_1}, // C4 on channel 1
  90,                            // Minimum threshold if the sensor is not perfect (0-127)
  127,                            // Maximum threshold if the sensor is not perfect (0-127)
};
 const uint8_t triggerValue3 = 10;  // Threshold at which note is triggered
 NotePotentiometer potentiometer3{
   A2,                               // Analog pin connected to potentiometer
   {48, Channel_1 },  // Note C4 on channel 1
   triggerValue3,                     // Trigger threshold
   90,                               // Minimum threshold (0-127)
   127,                               // Maximum threshold (0-127)
 };



 KPPotentiometer photoresistor4{
  A3,                            // Analog pin connected to first photoresistor
  {50, Channel_1}, // C4 on channel 1
  90,                            // Minimum threshold if the sensor is not perfect (0-127)
  127,                            // Maximum threshold if the sensor is not perfect (0-127)
};
 const uint8_t triggerValue4 = 10;  // Threshold at which note is triggered
 NotePotentiometer potentiometer4{
   A3,                               // Analog pin connected to potentiometer
   {50, Channel_1 },  // Note C4 on channel 1
   triggerValue4,                     // Trigger threshold
   90,                               // Minimum threshold (0-127)
   127,                               // Maximum threshold (0-127)
 };



 KPPotentiometer photoresistor5{
  A4,                            // Analog pin connected to first photoresistor
  {51, Channel_1}, // C4 on channel 1
  90,                            // Minimum threshold if the sensor is not perfect (0-127)
  127,                            // Maximum threshold if the sensor is not perfect (0-127)
};
 const uint8_t triggerValue5 = 10;  // Threshold at which note is triggered
 NotePotentiometer potentiometer5{
   A4,                               // Analog pin connected to potentiometer
   {51, Channel_1 },  // Note C4 on channel 1
   triggerValue5,                     // Trigger threshold
   90,                               // Minimum threshold (0-127)
   127,                               // Maximum threshold (0-127)
 };



 KPPotentiometer photoresistor6{
  A5,                            // Analog pin connected to first photoresistor
  {55, Channel_1}, // C4 on channel 1
  90,                            // Minimum threshold if the sensor is not perfect (0-127)
  127,                            // Maximum threshold if the sensor is not perfect (0-127)
};
 const uint8_t triggerValue6 = 10;  // Threshold at which note is triggered
 NotePotentiometer potentiometer6{
   A5,                               // Analog pin connected to potentiometer
   {55, Channel_1 },  // Note C4 on channel 1
   triggerValue6,                     // Trigger threshold
   90,                               // Minimum threshold (0-127)
   127,                               // Maximum threshold (0-127)
 };

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}


