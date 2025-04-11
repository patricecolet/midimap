#pragma once

#include <midimap/midimap_class.hpp>
#include <AH/Hardware/Ultrasonic.hpp>

BEGIN_CS_NAMESPACE

using AH::Ultrasonic;

/**
 * @brief   Class that sends continuous MIDI pitch bend messages with a 
 *          resolution of 14 bits.
 * 
 * @tparam  INPUT_PRECISION_BITS
 *          The resolution of the input values. For example, if 
 *          @p INPUT_PRECISION_BITS == 10, the send function expects a @p value
 *          between 0 and 1023.
 * 
 * @ingroup MIDI_Senders
 */
class UltrasonicCCSender {
public:
    UltrasonicCCSender (MIDIAddress address, pin_t pin)
            : _address(address), _ultrasonic(pin) {}

    void begin() {
            _ultrasonic.begin();
    }

    void update() {
        uint16_t distance = _ultrasonic.readDistanceMM();
        int16_t value = map(distance, 100, 800, 127, 0);
        value = constrain(value, 0, 127);

        static int16_t lastvalue = 0; // Invalid initial value to force first send
        if (value != lastvalue) {
            MIDIChannelCable channelCable = {_address.getChannel(), _address.getCableNumber()};
            midimap.sendControlChange(_address, value);
            lastvalue = value;
        }
    }
private:
    MIDIAddress _address;   ///< MIDI address for sending key pressure.
    Ultrasonic _ultrasonic; ///< Ultrasonic sensor object.
};

END_CS_NAMESPACE