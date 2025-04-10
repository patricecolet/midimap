/**
 * This example demonstrates how to use an ultrasonic distance sensor to generate MIDI Note messages.
 * This allows for expressive control over note dynamics based on the distance detected by the sensor.
 *
 * @boards  AVR, AVR USB, ESP32, SAM, SAMD
 * 
 * Connections
 * -----------
 * 
 * - D7: Signal pin of the ultrasonic sensor (Trig/Echo combined)
 * 
 * Note: This example uses a single-pin ultrasonic sensor. If your sensor has separate
 * Trig and Echo pins, you'll need to modify the code accordingly.
 *
 * Behavior
 * --------
 * 
 * - If the distance is greater than MaxDistanceThreshold: No note is played (Note Off).
 * - When the distance becomes less than MaxDistanceThreshold: Note On is triggered.
 * - When the distance becomes greater than MaxDistanceThreshold: Note Off is triggered.
 *
 * Mapping
 * -------
 * 
 * Select the Arduino as a custom MIDI controller in your DAW, and use the 
 * MIDI learn option to assign the sensor to a function. 
 * Select the Arduino as a **MIDI input device** in your DAW. Use the **MIDI Learn** feature to map the note.
 * 
 * Written by Nuryn Sophea, 2025-04-08
 */

 #include <midimap.h>  // Include the midimap library

 USBMIDI_Interface midi;  // Instantiate a MIDI over USB interface.
 
 const uint8_t triggerValue = 10;  // Threshold at which note is triggered

 NoteUltrasonicDistance noteultrasonicdistance{
   D7,                               // Analog pin connected to potentiometer
   { MIDI_Notes::C[4], Channel_1 },  // Note C4 on channel 1
   triggerValue,                     // Trigger threshold
   40,                               // Minimum threshold (0-127)
   127,                              // Maximum threshold (0-127)
 };
 
 void setup() {
   midimap.begin();  // Initialize midimap
 }
 
 void loop() {
   midimap.loop();  // Update the midimap
 }