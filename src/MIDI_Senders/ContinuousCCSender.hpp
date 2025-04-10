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
  // Default constructor with full range (no thresholding)
  ContinuousCCSender() 
      : _MinThreshold(0), _MaxThreshold(127), _lastSentValue(255), _thresholdingEnabled(false) {}
      
  // Constructor with thresholds
  ContinuousCCSender(uint8_t MinThreshold, uint8_t MaxThreshold)
      : _MinThreshold(MinThreshold), _MaxThreshold(MaxThreshold), _lastSentValue(255), 
        _thresholdingEnabled(true) {}

  /// Send a 7-bit CC message to the given address.
  void send(uint8_t value, MIDIAddress address)
  {
    uint8_t mappedValue;
    
    if (_thresholdingEnabled) {
      // Apply the threshold filter
      if (value < _MinThreshold) {
        value = _MinThreshold;  // If value is below MinThreshold, use MinThreshold
      } else if (value > _MaxThreshold) {
        value = _MaxThreshold;  // If value is above MaxThreshold, use MaxThreshold
      }
      
      // Map the filtered value to 0-127 range
      mappedValue = map(value, _MinThreshold, _MaxThreshold, 0, 127);
    } else {
      // For perfect components, just ensure the value is in the 0-127 range
      mappedValue = value > 127 ? 127 : value;
    }

    // Only send if the value has changed
    if (mappedValue != _lastSentValue) {
      // Send the mapped value
      midimap.sendControlChange(address, mappedValue);

      // Update the last sent value
      _lastSentValue = mappedValue;
    }
  }

  /// Get the resolution of the sender in bits (always returns 7).
  constexpr static uint8_t precision() { return 7; }

private:
  uint8_t _MinThreshold, _MaxThreshold;
  uint8_t _lastSentValue; // Store the last sent value
  bool _thresholdingEnabled; // Flag to indicate if thresholding is enabled
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
  // Default constructor with full range (no thresholding)
  ContinuousCCSender14() 
      : _MinThreshold(0), _MaxThreshold((1 << INPUT_PRECISION_BITS) - 1), 
        _lastSentValue(0xFFFF), _thresholdingEnabled(false) {}
      
  // Constructor with thresholds
  ContinuousCCSender14(uint16_t MinThreshold, uint16_t MaxThreshold)
      : _MinThreshold(MinThreshold), _MaxThreshold(MaxThreshold), 
        _lastSentValue(0xFFFF), _thresholdingEnabled(true) {}

  /// Send a 14-bit CC message to the given address.
  /// Sends two 7-bit CC packets, one for @p address (MSB), and one for
  /// @p address + 0x20 (LSB).
  void send(uint16_t value, MIDIAddress address)
  {
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
      midimap.sendControlChange(address + 0x00, (mappedValue >> 7) & 0x7F);
      midimap.sendControlChange(address + 0x20, (mappedValue >> 0) & 0x7F);
      
      // Update the last sent value
      _lastSentValue = mappedValue;
    }
  }

  /// Get this sender's precision.
  constexpr static uint8_t precision()
  {
    static_assert(INPUT_PRECISION_BITS <= 14,
                  "Maximum resolution is 14 bits");
    return INPUT_PRECISION_BITS;
  }
  
private:
  uint16_t _MinThreshold, _MaxThreshold;
  uint16_t _lastSentValue; // Store the last sent value
  bool _thresholdingEnabled; // Flag to indicate if thresholding is enabled
};

END_CS_NAMESPACE
