#pragma once
#include <Arduino.h>
#include <MIDIUSB.h>

class CCPotentiometer {
private:
    uint8_t pin;       // Analog input pin
    uint8_t ccNumber;  // MIDI CC number
    uint8_t channel;   // MIDI Channel (1-16)
    int lastValue;     // Last sent value
    int threshold;     // Threshold to reduce redundant messages

public:
    CCPotentiometer(uint8_t pin, uint8_t ccNumber, uint8_t channel, int threshold = 2);
    
    void begin();
    void update();
    void sendMIDI(uint8_t control, uint8_t value);
};

