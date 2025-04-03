#include <midimap.h> // Include the midimap library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

const uint8_t TriggerValue1 = 127; //range = MinNoteThreshold until range1
const uint8_t MinNoteThreshold1 = 100;

uint8_t range1 = 127; // Range of the MIDI Output
// Instantiate Velostat objects
NotePotentiometer Velostat1{
    A2,                            // Analog pin connected to velostat
    {MIDI_Notes::C[4], Channel_1}, // Note G4 on channel 1
    TriggerValue1,                      // Starting of the aftertouch
    MinNoteThreshold1,                 // Minimum note threshold
    range1,                       // Range of the MIDI Output
};

//////////////////////////////////////////////////////////////////////////

const uint8_t TriggerValue2 = 127; //range = MinNoteThreshold until range2
const uint8_t MinNoteThreshold2 = 100;

// Instantiate Velostat objects
NotePotentiometer Velostat2{
    A3,                            // Analog pin connected to velostat
    {MIDI_Notes::D[4], Channel_1}, // Note A4 on channel 1
    TriggerValue2,                      // Starting of the aftertouch
    MinNoteThreshold2,                 // Minimum note threshold
    range1,                       // Range of the MIDI Output
};

//////////////////////////////////////////////////////////////////////////

const uint8_t TriggerValue3 = 127; //range = MinNoteThreshold until range1
const uint8_t MinNoteThreshold3 = 100;

// Instantiate Velostat objects
NotePotentiometer Velostat3{
    A4,                            // Analog pin connected to velostat
    {MIDI_Notes::E[4], Channel_1}, // Note G4 on channel 1
    TriggerValue3,                      // Starting of the aftertouch
    MinNoteThreshold3,                 // Minimum note threshold
    range1,                       // Range of the MIDI Output
};

//////////////////////////////////////////////////////////////////////////

const uint8_t TriggerValue4 = 127; //range = MinNoteThreshold until range2
const uint8_t MinNoteThreshold4 = 100;

// Instantiate Velostat objects
NotePotentiometer Velostat4{
    A5,                            // Analog pin connected to velostat
    {MIDI_Notes::F[4], Channel_1}, // Note A4 on channel 1
    TriggerValue4,                      // Starting of the aftertouch
    MinNoteThreshold4,                 // Minimum note threshold
    range1,                       // Range of the MIDI Output
};

//////////////////////////////////////////////////////////////////////////

const uint8_t TriggerValue5 = 127; //range = MinNoteThreshold until range1
const uint8_t MinNoteThreshold5 = 100;

// Instantiate Velostat objects
NotePotentiometer Velostat5{
    A7,                            // Analog pin connected to velostat
    {MIDI_Notes::G[4], Channel_1}, // Note G4 on channel 1
    TriggerValue5,                      // Starting of the aftertouch
    MinNoteThreshold5,                 // Minimum note threshold
    range1,                       // Range of the MIDI Output
};

//////////////////////////////////////////////////////////////////////////

const uint8_t TriggerValue6 = 127; //range = MinNoteThreshold until range2
const uint8_t MinNoteThreshold6 = 100;

// Instantiate Velostat objects
NotePotentiometer Velostat6{
    A8,                            // Analog pin connected to velostat
    {MIDI_Notes::A[4], Channel_1}, // Note A4 on channel 1
    TriggerValue6,                      // Starting of the aftertouch
    MinNoteThreshold6,                 // Minimum note threshold
    range1,                       // Range of the MIDI Output
};

void setup() {
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}