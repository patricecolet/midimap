#pragma once

#include <midimap/midimap_class.hpp> // Include MIDI library
#include <AH/Math/IncreaseBitDepth.hpp>
#include <AH/Filters/Hysteresis.hpp> // Include the hysteresis filter

BEGIN_CS_NAMESPACE

/**
 * @brief   Class that sends MIDI Note messages with velocity based on potentiometer input
 *          with hysteresis filtering and debouncing.
 *
 * @ingroup MIDI_Senders
 */
class NoteVelPotentiometerSender {
public:
    // Constructor with velocity parameters but no thresholding
    NoteVelPotentiometerSender(uint8_t MinNoteThreshold,
                           float minPhysicalVelocity, float maxPhysicalVelocity)
        : _MinNoteThreshold(MinNoteThreshold), _MaxThreshold(127), _thresholdOffset(12),
          _minPhysicalVelocity(minPhysicalVelocity), _maxPhysicalVelocity(maxPhysicalVelocity), 
          _thresholdingEnabled(false), _isNoteOn(false), _lastStateChangeTime(0), 
          _debounceTime(2), _startTime(0), _startValue(0) {
        _TriggerValue = _MinNoteThreshold + _thresholdOffset;
    }

    // Constructor with full parameters including thresholding
    NoteVelPotentiometerSender(uint8_t MinNoteThreshold,
                           float minPhysicalVelocity, float maxPhysicalVelocity,
                           uint8_t MinThreshold, uint8_t MaxThreshold)
        : _MinNoteThreshold(MinNoteThreshold), _MaxThreshold(MaxThreshold), _thresholdOffset(12),
          _minPhysicalVelocity(minPhysicalVelocity), _maxPhysicalVelocity(maxPhysicalVelocity), 
          _thresholdingEnabled(true), _MinThreshold(MinThreshold), _isNoteOn(false), 
          _lastStateChangeTime(0), _debounceTime(2), _startTime(0), _startValue(0) {
        _TriggerValue = _MinNoteThreshold + _thresholdOffset;
    }

    void send(uint8_t value, MIDIAddress address) {
        // Apply thresholding if enabled
        uint8_t mappedValue;
        if (_thresholdingEnabled) {
            // Apply the threshold filter
            if (value < _MinThreshold) {
                value = _MinThreshold;
            }
            else if (value > _MaxThreshold) {
                value = _MaxThreshold;
            }

            // Map the filtered value to 0-127 range
            mappedValue = map(value, _MinThreshold, _MaxThreshold, 0, 127);
        }
        else {
            // For perfect components, just ensure the value is in the 0-127 range
            mappedValue = value > 127 ? 127 : value;
        }

        // Apply hysteresis filter to reduce noise and prevent false triggers
        if (!hysteresis.update(mappedValue)) {
            return; // Skip processing if the value hasn't changed significantly
        }

        // Get the filtered value after hysteresis
        mappedValue = hysteresis.getValue();

        // Get current time for debouncing and velocity calculation
        unsigned long currentTime = millis();

        // Note On logic with velocity calculation
        if (!_isNoteOn) {
            // First threshold crossing (velocity measurement start)
            if (mappedValue >= _MinNoteThreshold && _startTime == 0) {
                _startTime = currentTime;
                _startValue = mappedValue;
            }
            
            // Second threshold crossing (note trigger and velocity calculation)
            if (_startTime > 0 && mappedValue >= _TriggerValue) {
                if (currentTime - _lastStateChangeTime >= _debounceTime) {
                    // Calculate time difference in milliseconds
                    unsigned long timeDiff = currentTime - _startTime;
                    
                    // Ensure we don't divide by zero
                    if (timeDiff == 0) {
                        timeDiff = 1;
                    }
                    
                    // Calculate distance traveled
                    uint8_t distance = _TriggerValue - _MinNoteThreshold;
                    
                    // Calculate physical velocity (distance/time)
                    float physicalVelocity = (float)distance * 1000.0 / timeDiff; // Units: threshold units per second
                    
                    // Calculate MIDI velocity based on physical velocity
                    uint8_t velocity = calculateMIDIVelocity(physicalVelocity);
                    
                    // Send Note On with calculated velocity
                    midimap.sendNoteOn(address, velocity);
                    _isNoteOn = true;
                    _lastStateChangeTime = currentTime;
                    _startTime = 0; // Reset for next time
                }
            }
        }
        
        // Note Off logic
        if (_isNoteOn && mappedValue <= _MinNoteThreshold) {
            // Check if enough time has passed since the last state change
            if (currentTime - _lastStateChangeTime >= _debounceTime) {
                // Value has decreased below the lower threshold - Note Off with zero velocity
                midimap.sendNoteOff(address, 0);
                _isNoteOn = false;
                _lastStateChangeTime = currentTime;
                _startTime = 0; // Reset timing
            }
        }
    }
    
    // Helper method to calculate MIDI velocity from physical velocity
    uint8_t calculateMIDIVelocity(float physicalVelocity) {
        if (physicalVelocity >= _maxPhysicalVelocity) {
            return 127;
        } else if (physicalVelocity <= _minPhysicalVelocity) {
            return 1;
        } else {
            // Map the physical velocity to MIDI velocity range (1-127)
            // We multiply by 1000 to avoid floating point precision issues
            return map(physicalVelocity * 1000, 
                      _minPhysicalVelocity * 1000, 
                      _maxPhysicalVelocity * 1000, 
                      1, 127);
        }
    }
    
    /**
     * @brief   Returns the precision of the sensor readings, which is fixed to 7 bits for MIDI compatibility.
     * @return  The precision of the sensor readings (7-bit resolution).
     */
    constexpr static uint8_t precision() { return 7; }

private:
    uint8_t _TriggerValue, _MinNoteThreshold, _MinThreshold, _MaxThreshold, _thresholdOffset;
    float _minPhysicalVelocity, _maxPhysicalVelocity;
    bool _thresholdingEnabled;
    bool _isNoteOn;                   // Tracks if the note is currently on
    unsigned long _lastStateChangeTime; // Time of the last state change
    unsigned long _debounceTime;      // Debounce time in milliseconds
    
    // Velocity calculation variables
    unsigned long _startTime;         // Time when first threshold was crossed
    uint8_t _startValue;              // Value when first threshold was crossed

    // Hysteresis filter with 3-bit reduction, higher hysteresis for less sensitivity
    Hysteresis<1, uint8_t, uint8_t> hysteresis;
};

END_CS_NAMESPACE
