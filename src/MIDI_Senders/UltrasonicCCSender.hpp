#pragma once

#include <midimap/midimap_class.hpp>
#include <AH/Hardware/Ultrasonic.hpp>

BEGIN_CS_NAMESPACE

using AH::Ultrasonic;

/**
 * @brief Class that converts sensor data to MIDI key pressure messages.
 *
 * @ingroup MIDI_Senders
 */
class UltrasonicCCSender  {
    public:
        UltrasonicCCSender (MIDIAddress address, pin_t pin, uint8_t range)
            : _address(address), _ultrasonic(pin), _range(range) {}

        /// Initializes the sensor.
        void begin() {
            _ultrasonic.begin();
        }

        void update() {
            uint16_t distance = _ultrasonic.readDistanceMM();
            uint8_t value = map(distance, 0, 1000, 0, _range); // Convert mm to MIDI range
            value = constrain(value, 0, _range);

            static uint8_t last_value = 255; // Store last sent value
            if (value != last_value) {
                midimap.sendKeyPressure(_address, value);
                last_value = value;
            }
        }

    private:
        MIDIAddress _address;   ///< MIDI address for sending key pressure.
        Ultrasonic _ultrasonic; ///< Ultrasonic sensor object.
        uint8_t _range;
};

END_CS_NAMESPACE
