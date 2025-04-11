#pragma once

#include <AH/Math/IncreaseBitDepth.hpp>
#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Channel Pressure (Aftertouch) messages
 *          with optional input value thresholding.
 * 
 * This class takes an input value, applies optional thresholding and mapping,
 * and sends MIDI Channel Pressure messages. Channel Pressure affects all notes
 * on a channel simultaneously, providing expressive control over sounds.
 * 
 * @ingroup MIDISenders
 */
class ContinuousCPSender
{
  public:
    /**
     * @brief   Default constructor with full range (no thresholding).
     * 
     * Creates a sender that uses the full input range (0-127) without
     * any thresholding or remapping.
     */
    ContinuousCPSender() 
        : _MinThreshold(0), _MaxThreshold(127), _lastSentValue(255), _thresholdingEnabled(false) {}
      
    /**
     * @brief   Constructor with thresholds for input value range.
     * 
     * Creates a sender that maps input values from the specified range
     * to the full MIDI range (0-127).
     * 
     * @param   MinThreshold
     *          The minimum threshold value [0, 127].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 127].
     */
    ContinuousCPSender(uint8_t MinThreshold, uint8_t MaxThreshold)
        : _MinThreshold(MinThreshold), _MaxThreshold(MaxThreshold), _lastSentValue(255), 
          _thresholdingEnabled(true) {}

    /**
     * @brief   Send a Channel Pressure message to the given address.
     * 
     * The input value is thresholded (if enabled) and mapped to the
     * appropriate MIDI range. Messages are only sent when the value changes.
     * 
     * @param   value
     *          The input value [0, 127].
     * @param   address
     *          The MIDI address containing the channel and optional cable number.
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
     * @brief   Get the resolution of the sender in bits.
     * 
     * @return  The precision in bits (7 for Channel Pressure).
     */
    constexpr static uint8_t precision() { return 7; }

  private:
    uint8_t _MinThreshold;       ///< Minimum input threshold value
    uint8_t _MaxThreshold;       ///< Maximum input threshold value
    uint8_t _lastSentValue;      ///< Last sent MIDI value (for change detection)
    bool _thresholdingEnabled;   ///< Flag indicating if thresholding is enabled
};

END_CS_NAMESPACE
