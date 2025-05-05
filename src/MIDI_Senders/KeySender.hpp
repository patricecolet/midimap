#pragma once

#include <midimap/midimap_class.hpp>
#include <Arduino.h>

BEGIN_CS_NAMESPACE

class KeySender 
{
public:
    KeySender(MIDIAddress address, pin_t pin)
        : _address(address), _pin(pin) {}

    void begin() 
    {
        pinMode(_pin, OUTPUT); // Set pin mode to input
    }

    void update()  
    {
        digitalWrite(_pin, LOW);
        delayMicroseconds(2);
        digitalWrite(_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(_pin, LOW);

        //pinMode(_pin, INPUT);

        long duration = pulseIn(_pin, HIGH, 30000); // Measure pulse duration
         // Debugging line to print the duration

        if (duration == 0)
        {
            return; // If there's no valid duration, don't send any message
        }

        float distance = (duration / 2) * 0.0343; // Convert to distance in cm
        uint8_t value = map(distance, 0, 100, 0, 127);
        value = constrain(value, 0, 127);

        Serial.print("value: ");
        Serial.println(value);

        midimap.sendKeyPressure(_address, value); // Send MIDI message
        //pinMode(_pin, OUTPUT);                    // Set pin mode to input
    }

private:
    MIDIAddress _address;
    pin_t _pin;
};

END_CS_NAMESPACE
