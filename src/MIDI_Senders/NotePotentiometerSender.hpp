#pragma once

#include <midimap/midimap_class.hpp> // Include MIDI library
#include <AH/Math/IncreaseBitDepth.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class that sends MIDI Note messages based on potentiometer input
 *          with velocity sensitivity.
 *
 * @ingroup MIDI_Senders
 */
class NotePotentiometerSender {
    public:

        // Constructor with velocity parameters but no thresholding
        NotePotentiometerSender(uint8_t MinNoteThreshold, uint8_t thresholdOffset, 
                               float minPhysicalVelocity, float maxPhysicalVelocity)
            : _MinNoteThreshold(MinNoteThreshold), _MaxThreshold(127), _range(127), _thresholdOffset(thresholdOffset),
              _minPhysicalVelocity(minPhysicalVelocity), _maxPhysicalVelocity(maxPhysicalVelocity), _thresholdingEnabled(false) {
            _TriggerValue = _MinNoteThreshold + _thresholdOffset;
        }

        // Constructor with full parameters including thresholding
        NotePotentiometerSender(uint8_t MinNoteThreshold, uint8_t thresholdOffset, 
                               float minPhysicalVelocity, float maxPhysicalVelocity,
                               uint8_t MinThreshold, uint8_t MaxThreshold)
            : _MinNoteThreshold(MinNoteThreshold), _MaxThreshold(MaxThreshold), _range(127), _thresholdOffset(thresholdOffset),
              _minPhysicalVelocity(minPhysicalVelocity), _maxPhysicalVelocity(maxPhysicalVelocity), _thresholdingEnabled(true) {
            _TriggerValue = _MinNoteThreshold + _thresholdOffset;
        }

        void send(uint8_t value, MIDIAddress address) {
            static bool isNoteOn = false; // Tracks if the note is currently on
            static bool isPassing = false; // Tracks if we're in the threshold passing phase
            static unsigned long timerStart = 0; // To store when the timer started
            
            // Apply thresholding if enabled
            uint8_t mappedValue;
            if (_thresholdingEnabled) {
                // Apply the threshold filter
                if (value < _MinThreshold) {
                    value = _MinThreshold;
                } else if (value > _MaxThreshold) {
                    value = _MaxThreshold;
                }
                
                // Map the filtered value to 0-127 range
                mappedValue = map(value, _MinThreshold, _MaxThreshold, 0, 127);
            } else {
                // For perfect components, just ensure the value is in the 0-127 range
                mappedValue = value > 127 ? 127 : value;
            }
            
            // Map the input value to the specified range
            mappedValue = map(mappedValue, 0, 127, 0, _range);
            
            // Note On logic - measure time between thresholds
            if (!isNoteOn) {
                // Start timing when we cross the first threshold
                if (mappedValue >= _MinNoteThreshold && !isPassing) {
                    timerStart = millis();
                    isPassing = true;
                }
                // When we reach the second threshold, calculate velocity and send Note On
                else if (mappedValue >= _TriggerValue && isPassing) {
                    unsigned long pressDuration = millis() - timerStart;
                    
                    // Prevent division by zero
                    if (pressDuration == 0) {
                        pressDuration = 1;
                    }
                    
                    // Calculate velocity based on physical velocity formula: distance/time
                    uint8_t distance = _TriggerValue - _MinNoteThreshold;
                    float physicalVelocity = (float)distance / pressDuration; // Units: threshold units per millisecond
                    
                    // Scale the physical velocity to MIDI velocity range (1-127)
                    uint8_t calculatedVelocity = calculateMIDIVelocity(physicalVelocity);
                    
                    // Send the note with calculated velocity
                    midimap.sendNoteOn(address, calculatedVelocity);
                    isNoteOn = true;
                    isPassing = false;
                }
            }
            // Note Off logic - similar but in reverse
            else {
                // Start timing for note off when value drops below trigger threshold
                if (mappedValue < _TriggerValue && !isPassing) {
                    timerStart = millis();
                    isPassing = true;
                }
                // Complete note off when value drops below minimum threshold
                else if (mappedValue < _MinNoteThreshold && isPassing) {
                    unsigned long releaseDuration = millis() - timerStart;
                    
                    // Prevent division by zero
                    if (releaseDuration == 0) {
                        releaseDuration = 1;
                    }
                    
                    // Calculate release velocity based on physical velocity formula: distance/time
                    uint8_t distance = _TriggerValue - _MinNoteThreshold;
                    float physicalReleaseVelocity = (float)distance / releaseDuration;
                    
                    // Scale the physical release velocity to MIDI velocity range (1-127)
                    uint8_t releaseVelocity = calculateMIDIVelocity(physicalReleaseVelocity);
                    
                    // Send Note Off with calculated release velocity
                    midimap.sendNoteOff(address, releaseVelocity);
                    isNoteOn = false;
                    isPassing = false;
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
                return map(physicalVelocity * 100, 
                          _minPhysicalVelocity * 100, 
                          _maxPhysicalVelocity * 100, 
                          1, 127);
            }
        }

        /** 
         * @brief   Returns the precision of the sensor readings, which is fixed to 7 bits for MIDI compatibility.
         * @return  The precision of the sensor readings (7-bit resolution).
         */
        constexpr static uint8_t precision() { return 7; }

    private:
        uint8_t _TriggerValue, _MinNoteThreshold, _MinThreshold, _MaxThreshold, _range, _thresholdOffset;
        float _minPhysicalVelocity, _maxPhysicalVelocity;
        bool _thresholdingEnabled;
};

END_CS_NAMESPACE
