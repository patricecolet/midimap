#pragma once

#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class that sends MIDI Polyphonic Pressure (Aftertouch) messages with Note On/Off.
 *
 * @tparam  INPUT_PRECISION_BITS
 *          The resolution of the input values. For example, if
 *          @p INPUT_PRECISION_BITS == 10, the send function expects a @p value
 *          between 0 and 1024.
 *
 * @ingroup MIDI_Senders
 */
template <uint8_t INPUT_PRECISION_BITS>
class PolyphonicPressureSender
{
public:
static void send(uint16_t value, MIDIAddress address) {
    static_assert(INPUT_PRECISION_BITS <= 10,
                  "Aftertouch resolution is 7 bits (max input: 10-bit)");
        // Map value to 7-bit range (0-127)
        value = map(value, 0, (1 << precision()) - 1, 0, 127);
          
        // Send Polyphonic Aftertouch (Key Pressure) message
        midimap.sendKeyPressure(address, value);

    }

    /// Get the resolution (precision) of the sender in bits
    constexpr static uint8_t precision() { return INPUT_PRECISION_BITS; }
};

END_CS_NAMESPACE

