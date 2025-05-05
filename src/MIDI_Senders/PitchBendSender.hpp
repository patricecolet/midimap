#pragma once

#include <AH/Math/IncreaseBitDepth.hpp>
#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

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
class PitchBendSender {
  public:
    // Default constructor with full range (no thresholding)
    PitchBendSender() 
        : _MinThreshold(0), _MaxThreshold((1 << INPUT_PRECISION_BITS) - 1), 
          _lastSentValue(0xFFFF), _thresholdingEnabled(false) {}
        
    // Constructor with thresholds
    PitchBendSender(uint16_t MinThreshold, uint16_t MaxThreshold)
        : _MinThreshold(MinThreshold), _MaxThreshold(MaxThreshold), 
          _lastSentValue(0xFFFF), _thresholdingEnabled(true) {}

    /// Send a MIDI pitch bend message with the given value and channel+cable.
    /// address.getAddress() is ignored.
    /// Value should be @p INPUT_PRECISION_BITS wide.
    void send(uint16_t value, MIDIAddress address) {
        uint16_t mappedValue;
        
        if (_thresholdingEnabled) {
            // Apply the threshold filter
            if (value < _MinThreshold) {
                value = _MinThreshold;
            } else if (value > _MaxThreshold) {
                value = _MaxThreshold;
            }
            
            // Map the filtered value to 0-16383 range (14-bit)
            mappedValue = map(value, _MinThreshold, _MaxThreshold, 0, 0x3FFF);
        } else {
            // For perfect components, just ensure the value is in the 14-bit range
            mappedValue = AH::increaseBitDepth<14, precision(), uint16_t>(value);
        }

        // Only send if the value has changed
        if (mappedValue != _lastSentValue) {
            // ignore address byte, just use channel and cable numbers
            MIDIChannelCable channelCN = address.getChannelCable();
            midimap.sendPitchBend(channelCN, mappedValue);
            
            // Update the last sent value
            _lastSentValue = mappedValue;
        }
    }

    /// Get this sender's precision.
    constexpr static uint8_t precision() {
        static_assert(INPUT_PRECISION_BITS <= 14,
                      "Maximum pitch bend resolution is 14 bits");
        return INPUT_PRECISION_BITS;
    }
    
  private:
    uint16_t _MinThreshold, _MaxThreshold;
    uint16_t _lastSentValue; // Store the last sent value
    bool _thresholdingEnabled; // Flag to indicate if thresholding is enabled
};

END_CS_NAMESPACE
