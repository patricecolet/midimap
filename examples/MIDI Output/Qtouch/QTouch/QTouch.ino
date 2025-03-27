#include <midimap.h> // Include the midimap library

USBMIDI_Interface midi; // Instantiate a MIDI over USB interface.

const uint8_t TriggerValue = 60; //range = MinNoteThreshold until 127
const uint8_t MinNoteThreshold = 10;

// Instantiate a QTouch object
QTouchNote QTouch{
    A0,                            // Analog pin connected to potentiometer
    {MIDI_Notes::C[4], Channel_1}, // Note C4 on channel 1
    TriggerValue,                      // Starting of the aftertouch
    MinNoteThreshold,                 // Minimum note threshold
    OVERSAMPLE_4,                   // Oversampling
    RESISTOR_50K,                   // 50k resistor
    FREQ_MODE_NONE                   // Frequency mode
};

void setup()
{
  midimap.begin(); // Initialize midimap
}

void loop()
{
  midimap.loop(); // Update the midimap
}




