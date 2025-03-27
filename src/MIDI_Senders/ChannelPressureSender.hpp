#pragma once

#include <AH/Math/IncreaseBitDepth.hpp>
#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class that sends MIDI Channel Pressure (Aftertouch) messages.
 *
 * @tparam  INPUT_PRECISION_BITS
 *          The resolution of the input values. For example, if
 *          @p INPUT_PRECISION_BITS == 12, the send function expects a @p value
 *          between 0 and 4095.
 *
 * @ingroup MIDI_Senders
 */
template <uint8_t INPUT_PRECISION_BITS>
class ChannelPressureSender
{
public:
    ChannelPressureSender(uint8_t range)
        : _range(range) {}

    /// Send a MIDI Channel Pressure message with the given value.
    /// The address.getAddress() is ignored (only channel+cable are used).
    /// Value should be @p INPUT_PRECISION_BITS wide.
    void send(uint16_t value, MIDIAddress address)
    {
        // Ensure the precision is correct for 12-bit input
        static_assert(INPUT_PRECISION_BITS <= 12,
                      "Aftertouch resolution is 7 bits (max input: 12-bit)");

        // Convert the input to range (0–range)
        value = map(value, 0, (1 << precision()) - 1, 0, _range);

        // Get MIDI channel and cable number
        MIDIChannelCable channelCN = address.getChannelCable();
        midimap.sendChannelPressure(channelCN, value);
    }

    /// Get this sender's precision.
    constexpr static uint8_t precision()
    {
        return INPUT_PRECISION_BITS;
    }

private:
    uint8_t _range;
};

END_CS_NAMESPACE
