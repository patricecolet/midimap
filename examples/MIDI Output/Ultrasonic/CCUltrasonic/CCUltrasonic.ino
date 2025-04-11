#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// For perfect components (no thresholding needed)
CCUltrasonic Ultrasonic {
  A5,                              // Analog pin connected to potentiometer
  {MIDI_CC::Channel_Volume, Channel_1 }, // Channel volume of channel 1
   //5,                            // Minimum threshold if the sensor is not perfect (0-127)
   //125,                          // Maximum threshold if the sensor is not perfect (0-127)
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}