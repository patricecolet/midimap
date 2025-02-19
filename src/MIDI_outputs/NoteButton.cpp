#include "NoteButton.hpp"  // Ensure this matches the header file name exactly

// Constructor to initialize the button parameters
NoteButton::NoteButton(int pin, byte note, byte channel) {
  _pin = pin;
  _note = note;
  _channel = channel;
  _lastButtonState = HIGH;  // Assume the button starts as unpressed (with internal pull-up)
  _currentButtonState = HIGH;
}

void NoteButton::begin() {
  pinMode(_pin, INPUT_PULLUP);  // Set the pin as an input with pull-up resistor
}

void NoteButton::update() {
  _currentButtonState = digitalRead(_pin);  // Read the current state of the button

  // If the button is pressed (transition from HIGH to LOW)
  if (_lastButtonState == HIGH && _currentButtonState == LOW) {
    // Send MIDI Note On message with full velocity (127)
    midiEventPacket_t noteOn = {0x09, 0x90 | (_channel - 1), _note, 127};
    MidiUSB.sendMIDI(noteOn);
    MidiUSB.flush();  // Ensure the message is sent
  }
  
  // If the button is released (transition from LOW to HIGH)
  if (_lastButtonState == LOW && _currentButtonState == HIGH) {
    // Send MIDI Note Off message
    midiEventPacket_t noteOff = {0x08, 0x80 | (_channel - 1), _note, 0};
    MidiUSB.sendMIDI(noteOff);
    MidiUSB.flush();  // Ensure the message is sent
  }

  _lastButtonState = _currentButtonState;  // Update the last button state
}

void NoteButton::setNote(byte note) {
  _note = note;  // Set a new MIDI note
}

void NoteButton::setChannel(byte channel) {
  _channel = channel;  // Set a new MIDI channel
}