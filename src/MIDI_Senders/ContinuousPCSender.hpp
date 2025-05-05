#pragma once

#include <midimap/midimap_class.hpp> // Include MIDI library
#include <AH/Math/IncreaseBitDepth.hpp>
#include <AH/Filters/Hysteresis.hpp> // Include the hysteresis filter

BEGIN_CS_NAMESPACE

/**
 * @brief Class that sends MIDI Program Change messages based on potentiometer input
 * with hysteresis filtering and debouncing.
 *
 * @ingroup MIDI_Senders
 */
class ContinuousPCSender {
public:
    ContinuousPCSender(uint8_t triggerValue)
        : _TriggerValue(triggerValue), _thresholdOffset(12), _MinThreshold(0), _MaxThreshold(127), _thresholdingEnabled(false),
          _isNoteOn(false), _lastStateChangeTime(0), _debounceTime(2) {
        _PCTrigger = triggerValue + _thresholdOffset > 127 ? 127 : triggerValue + _thresholdOffset;
    }

    ContinuousPCSender(uint8_t triggerValue, uint8_t MinThreshold, uint8_t MaxThreshold)
        : _TriggerValue(triggerValue), _thresholdOffset(12), _MinThreshold(MinThreshold), _MaxThreshold(MaxThreshold), _thresholdingEnabled(true),
          _isNoteOn(false), _lastStateChangeTime(0), _debounceTime(2) {
        _PCTrigger = triggerValue + _thresholdOffset > 127 ? 127 : triggerValue + _thresholdOffset;
    }
          

    void send(uint8_t value, MIDIAddress address)
    {
        // Apply thresholding if enabled
        uint8_t mappedValue;
        if (_thresholdingEnabled)
        {
            // Apply the threshold filter
            if (value < _MinThreshold)
            {
                value = _MinThreshold;
            }
            else if (value > _MaxThreshold)
            {
                value = _MaxThreshold;
            }

            // Map the filtered value to 0-127 range
            mappedValue = map(value, _MinThreshold, _MaxThreshold, 0, 127);
        }
        else
        {
            // For perfect components, just ensure the value is in the 0-127 range
            mappedValue = value > 127 ? 127 : value;
        }

        // Apply hysteresis filter to reduce noise and prevent false triggers
        if (!hysteresis.update(mappedValue))
        {
            return; // Skip processing if the value hasn't changed significantly
        }

        // Get the filtered value after hysteresis
        mappedValue = hysteresis.getValue();

        // Get current time for debouncing
        unsigned long currentTime = millis();

        // Check if we should trigger a note on
        if (!_isNoteOn && mappedValue >= _TriggerValue)
        {
            // Check if enough time has passed since the last state change
            if (currentTime - _lastStateChangeTime >= _debounceTime)
            {
                // Value has increased past the trigger threshold - Send Program Change
                midimap.sendProgramChange(address);
                _isNoteOn = true;
                _lastStateChangeTime = currentTime;
            }
        }
        // Check if we should reset the state (value dropped below trigger threshold)
        else if (_isNoteOn && mappedValue < _TriggerValue)
        {
            // Check if enough time has passed since the last state change
            if (currentTime - _lastStateChangeTime >= _debounceTime)
            {
                _isNoteOn = false;
                _lastStateChangeTime = currentTime;
            }
        }
    }

    /// Doesn't do anything (you cannot "un-select" a program).
    void sendOff(MIDIAddress address) { (void)address; }

    /**
     * @brief Returns the precision of the sensor readings, which is fixed to 7 bits for MIDI compatibility.
     * @return The precision of the sensor readings (7-bit resolution).
     */
    constexpr static uint8_t precision() { return 7; }

private:
    uint8_t _PCTrigger, _TriggerValue, _MinThreshold, _MaxThreshold, _thresholdOffset;
    bool _thresholdingEnabled;
    bool _isNoteOn;                     // Tracks if the note is currently on
    unsigned long _lastStateChangeTime; // Time of the last state change
    unsigned long _debounceTime;        // Debounce time in milliseconds

    // Hysteresis filter with 3-bit reduction, higher hysteresis for less sensitivity
    Hysteresis<1, uint8_t, uint8_t> hysteresis;
};

END_CS_NAMESPACE
