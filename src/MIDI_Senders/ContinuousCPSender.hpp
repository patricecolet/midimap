#pragma once

#include <AH/Math/IncreaseBitDepth.hpp>
#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief Class for sending MIDI Channel Pressure messages with continuous values.
 * 
 * This class handles the sending of MIDI Channel Pressure messages with optional
 * thresholding to filter input values. It only sends messages when the value has
 * changed from the previous sent value to reduce MIDI traffic.
 */
class ContinuousCPSender
{
  public:
  /**
   * @brief Default constructor with full range (no thresholding).
   * 
   * Creates a sender that uses the full MIDI range (0-127) without any thresholding.
   */
  ContinuousCPSender() 
      : _MinThreshold(0), _MaxThreshold(127), _lastSentValue(255), _thresholdingEnabled(false) {}
      
  /**
   * @brief Constructor with thresholds.
   * 
   * Creates a sender with specified minimum and maximum thresholds.
   * Input values will be constrained to this range before mapping to MIDI values.
   * 
   * @param MinThreshold The minimum threshold value (input values below this will be set to this value)
   * @param MaxThreshold The maximum threshold value (input values above this will be set to this value)
   */
  ContinuousCPSender(uint8_t MinThreshold, uint8_t MaxThreshold)
      : _MinThreshold(MinThreshold), _MaxThreshold(MaxThreshold), _lastSentValue(255), 
        _thresholdingEnabled(true) {}

  /**
   * @brief Send a 7-bit Channel Pressure message to the given address.
   * 
   * Sends a MIDI Channel Pressure message with the given value to the specified address.
   * The value is thresholded if thresholding is enabled, and mapped to the 0-127 range.
   * Messages are only sent if the value has changed from the last sent value.
   * 
   * @param value The input value to send (0-127)
   * @param address The MIDI address to send to
   */
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
      MIDIChannelCable channelCN = address.getChannelCable();
      midimap.sendChannelPressure(channelCN, mappedValue);

      // Update the last sent value
      _lastSentValue = mappedValue;
    }
  }

  /**
   * @brief Get the resolution of the sender in bits.
   * 
   * @return Always returns 7 (bits), as MIDI Channel Pressure messages use 7-bit values.
   */
  constexpr static uint8_t precision() { return 7; }

private:
  uint8_t _MinThreshold;       ///< Minimum threshold for input values
  uint8_t _MaxThreshold;       ///< Maximum threshold for input values
  uint8_t _lastSentValue;      ///< Stores the last sent value to avoid sending duplicates
  bool _thresholdingEnabled;   ///< Flag indicating if thresholding is enabled
};

END_CS_NAMESPACE
