#include "CCPotentiometer.h"

// Constructor
CCPotentiometer::CCPotentiometer(uint8_t pin, uint8_t ccNumber, uint8_t channel, int threshold) 
    : pin(pin), ccNumber(ccNumber), channel(channel), lastValue(-1), threshold(threshold) {}

// Initialize pin
void CCPotentiometer::begin() {
    pinMode(pin, INPUT);
}

// Read and send MIDI CC if value has changed
void CCPotentiometer::update() {
    int rawValue = analogRead(pin);
    int midiValue = map(rawValue, 0, 1023, 0, 127); // Map to MIDI range

    if (abs(midiValue - lastValue) > threshold) { // Send only if change is significant
        sendMIDI(ccNumber, midiValue);
        lastValue = midiValue;
    }
}

// Send a MIDI CC message using MIDIUSB
void CCPotentiometer::sendMIDI(uint8_t control, uint8_t value) {
    midiEventPacket_t event = {0x0B, 0xB0 | (channel - 1), control, value}; // MIDI Control Change
    MidiUSB.sendMIDI(event);
    MidiUSB.flush();
}
