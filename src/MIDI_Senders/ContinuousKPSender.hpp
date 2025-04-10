#pragma once

#include <AH/Math/IncreaseBitDepth.hpp>
#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class that sends MIDI Polyphonic Pressure (Aftertouch) messages with a 
 *          resolution of 7 bits.
 *
 * @ingroup MIDI_Senders
 */
class ContinuousKPSender {
public:
    // Default constructor with full range (no thresholding)
    ContinuousKPSender() 
        : _MinThreshold(0), _MaxThreshold(127), _lastSentValue(255), _thresholdingEnabled(false) {}
        
    // Constructor with thresholds
    ContinuousKPSender(uint8_t MinThreshold, uint8_t MaxThreshold)
        : _MinThreshold(MinThreshold), _MaxThreshold(MaxThreshold), _lastSentValue(255), 
          _thresholdingEnabled(true) {}

    /// Send a 7-bit Polyphonic Pressure message to the given address.
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
            midimap.sendKeyPressure(address, mappedValue);

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

END_CS_NAMESPACE
