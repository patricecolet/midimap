#ifndef NoteButton_h
#define NoteButton_h

#include <Arduino.h>
#include <MIDIUSB.h>  // Include the MIDIUSB library for sending MIDI messages

class NoteButton {
  public:
    NoteButton(int pin, byte note, byte channel = 1);  // Constructor with pin, note, and optional channel
    void begin();                                       // Initialize the button
    void update();                                      // Update the button state
    void setNote(byte note);                            // Change the MIDI note
    void setChannel(byte channel);                      // Change the MIDI channel

  private:
    int _pin;              // Pin number for the button
    byte _note;            // MIDI note to send when button is pressed
    byte _channel;         // MIDI channel to send the note on
    bool _lastButtonState; // Last button state
    bool _currentButtonState; // Current button state
};

#endif