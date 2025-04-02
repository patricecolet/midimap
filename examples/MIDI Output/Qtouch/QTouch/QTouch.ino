#include <midimap.h> // Include the midimap library

USBMIDI_Interface midi; // Instantiate a MIDI over USB interface.

const uint8_t TriggerValue = 100; //range = MinNoteThreshold until 127
const uint8_t MinNoteThreshold = 40;

// Instantiate a QTouch object
#ifdef ARDUINO_ARCH_SAMD
QTouchNote QTouch{
    A0,                             // Pin connected to the QTouch sensor
    {MIDI_Notes::C[4], Channel_1},  // Note C4 on channel 1
    TriggerValue,                   // Starting of the aftertouch
    MinNoteThreshold,               // Minimum note threshold
    OVERSAMPLE_4,                   // Oversampling    -- ONLY FOR SAMD21 --
    RESISTOR_50K,                   // 50k resistor    -- ONLY FOR SAMD21 --
    FREQ_MODE_NONE                  // Frequency mode  -- ONLY FOR SAMD21 --
};
#elif defined(ESP32)
QTouchNote QTouch{
    A0,                             // Use a valid ESP32 touch pin)
    {MIDI_Notes::C[4], Channel_1},  // Note C4 on channel 1
    TriggerValue,                   // Starting of the aftertouch
    MinNoteThreshold                // Minimum note threshold
};
#endif

void setup()
{
  midimap.begin(); // Initialize midimap
}

void loop()
{
  midimap.loop(); // Update the midimap 
}




