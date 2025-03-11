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
template <uint8_t INPUT_PRECISION_BITS>
class PitchBendUltrasonicSender {
    static const uint16_t THRESHOLD = 5; // Define threshold for value changes
public:
    PitchBendUltrasonicSender (MIDIAddress address, pin_t pin)
            : _address(address), _ultrasonic(pin) {}
    /// Value should be @p INPUT_PRECISION_BITS wide.

    void begin() {
            _ultrasonic.begin();
    }

    void update() {
        uint16_t distance = _ultrasonic.readDistanceMM();

        // Map distance (0-1000mm) to pitch bend range (0 to 16383)
        int16_t pitchBendValue = map(distance, 100, 800, 16383, 0);
        pitchBendValue = constrain(pitchBendValue, 0, 16383);
        //Serial.print("hello");

        static int16_t lastPitchBendValue = 0; // Invalid initial value to force first send
        if (pitchBendValue != lastPitchBendValue) {
            MIDIChannelCable channelCable = {_address.getChannel(), _address.getCableNumber()};
            //Serial.println(pitchBendValue);
            //Serial.print("hello");
            midimap.sendPitchBend(channelCable, pitchBendValue);
            lastPitchBendValue = pitchBendValue;
        }
    }

    /// Get this sender's precision.
    constexpr static uint8_t precision() {
        static_assert(INPUT_PRECISION_BITS <= 14,
                      "Maximum pitch bend resolution is 14 bits");
        return INPUT_PRECISION_BITS;
    }
private:
    MIDIAddress _address;   ///< MIDI address for sending key pressure.
    Ultrasonic _ultrasonic; ///< Ultrasonic sensor object.
};

END_CS_NAMESPACE