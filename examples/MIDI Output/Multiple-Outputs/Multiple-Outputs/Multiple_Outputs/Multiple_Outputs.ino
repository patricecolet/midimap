#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

// Instantiate NoteButtonInverse objects
NoteButtonInverse capa1 {
  0,                             // Push button on pin 0
  {MIDI_Notes::C[4], Channel_1}, // Note C4 on MIDI channel 1
};

NoteButtonInverse capa2 {
  1,                             // Push button on pin 1
  {MIDI_Notes::D[4], Channel_1}, // Note D4 on MIDI channel 1
};

NoteButtonInverse capa3 {
  2,                             // Push button on pin 2
  {MIDI_Notes::E[4], Channel_1}, // Note E4 on MIDI channel 1
};

NoteButtonInverse capa4 {
  3,                             // Push button on pin 3
  {MIDI_Notes::F[4], Channel_1}, // Note F4 on MIDI channel 1
};

const uint8_t TriggerValue1 = 60; //range = MinNoteThreshold until 127
const uint8_t MinNoteThreshold1 = 20;

// Instantiate Velostat objects
VelostatNote Velostat1{
    A8,                            // Analog pin connected to velostat
    {MIDI_Notes::G[4], Channel_1}, // Note G4 on channel 1
    TriggerValue1,                      // Starting of the aftertouch
    MinNoteThreshold1,                 // Minimum note threshold
};

const uint8_t TriggerValue2 = 60; //range = MinNoteThreshold until 127
const uint8_t MinNoteThreshold2 = 20;

// Instantiate Velostat objects
VelostatNote Velostat2{
    A9,                            // Analog pin connected to velostat
    {MIDI_Notes::A[4], Channel_1}, // Note A4 on channel 1
    TriggerValue2,                      // Starting of the aftertouch
    MinNoteThreshold2,                 // Minimum note threshold
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}