#pragma once

#include <AH/Math/IncreaseBitDepth.hpp>
#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class that sends continuous MIDI control change messages with a
 *          resolution of 7 bits.
 *
 * @ingroup MIDI_Senders
 */
class ContinuousCCSender
{
public:
  ContinuousCCSender(uint8_t range)
      : _range(range) {}
      
  /// Send a 7-bit CC message to the given address.
  void send(uint8_t value, MIDIAddress address)
  {
    uint8_t mappedValue = map(value, 0, 127, 0, _range);
    midimap.sendControlChange(address, mappedValue);
  }

  /// Get the resolution of the sender in bits (always returns 7).
  constexpr static uint8_t precision() { return 7; }

private:
  uint8_t _range;
};

/**
 * @brief   Class that sends continuous MIDI control change messages with a
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
class ContinuousCCSender14
{
public:
  /// Send a 14-bit CC message to the given address.
  /// Sends two 7-bit CC packets, one for @p address (MSB), and one for
  /// @p address + 0x20 (LSB).
  void send(uint16_t value, MIDIAddress address)
  {
    value = AH::increaseBitDepth<14, precision(), uint16_t>(value);
    midimap.sendControlChange(address + 0x00, (value >> 7) & 0x7F);
    midimap.sendControlChange(address + 0x20, (value >> 0) & 0x7F);
  }

  /// Get this sender's precision.
  constexpr static uint8_t precision()
  {
    static_assert(INPUT_PRECISION_BITS <= 14,
                  "Maximum resolution is 14 bits");
    return INPUT_PRECISION_BITS;
  }
};

END_CS_NAMESPACE