
#include "midimap.h"

// Create a potentiometer on A0, sending MIDI CC #7 on channel 1
CCPotentiometer midimap(A0, 7, 2); //potentiometer

void setup() {
    midimap.begin();
}

void loop() {
    midimap.update();
}
