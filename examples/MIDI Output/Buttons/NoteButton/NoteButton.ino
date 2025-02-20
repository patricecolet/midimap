#include "midimap.h"

NoteButton midimap(5, 69); // Initialize the NoteButton with pin 5 and MIDI note 65 (F4)

void setup() {
  midimap.begin(); // Initialize the button
  
}

void loop() {
  midimap.update(); // Update the button state
}