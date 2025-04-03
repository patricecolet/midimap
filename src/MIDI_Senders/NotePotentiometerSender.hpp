#pragma once

#include <midimap/midimap_class.hpp> // Include MIDI library
#include <AH/Math/IncreaseBitDepth.hpp>


BEGIN_CS_NAMESPACE

/**
 * @brief   Constructor for NotePotentiometerSender.
 * 
 * @param   MinNoteThreshold
 *          The minimum threshold for triggering a note.
 * @param   range
 *          The range of MIDI output values.
 * @param   thresholdOffset
 *          The offset to add to MinNoteThreshold to calculate TriggerValue (default: 10).
 * @param   velocity
 *          The default velocity value (default: 0x7F).
 * @param   minPhysicalVelocity
 *          The minimum physical velocity value (default: 0.01).
 * @param   maxPhysicalVelocity
 *          The maximum physical velocity value (default: 1.0).
 */
class NotePotentiometerSender {
    public:
        /**
         * @brief   Constructor for NotePotentiometerSender.
         * 
         * @param   MinNoteThreshold
         *          The minimum threshold for triggering a note.
         * @param   range
         *          The range of MIDI output values.
         * @param   thresholdOffset
         *          The offset to add to MinNoteThreshold to calculate TriggerValue (default: 10).
         * @param   velocity
         *          The default velocity value (default: 0x7F).
         * @param   minPhysicalVelocity
         *          The minimum physical velocity value (default: 0.01).
         * @param   maxPhysicalVelocity
         *          The maximum physical velocity value (default: 1.0).
         */
        NotePotentiometerSender(uint8_t MinNoteThreshold, uint8_t range, uint8_t thresholdOffset = 10, 
                               uint8_t velocity, float minPhysicalVelocity, float maxPhysicalVelocity)
        : _MinNoteThreshold(MinNoteThreshold), _range(range), _thresholdOffset(thresholdOffset), _velocity(velocity),
          _minPhysicalVelocity(minPhysicalVelocity), _maxPhysicalVelocity(maxPhysicalVelocity) {
            _TriggerValue = _MinNoteThreshold + _thresholdOffset;
        }

        void send(uint8_t value, MIDIAddress address) {
            static bool isNoteOn = false; // Tracks if the note is currently on
            static bool isPassing = false; // Tracks if we're in the threshold passing phase
            static unsigned long timerStart = 0; // To store when the timer started
            
            // Map the input value to the specified range
            value = map(value, 0, 127, 0, _range);
            
            // Note On logic - measure time between thresholds
            if (!isNoteOn) {
                // Start timing when we cross the first threshold
                if (value >= _MinNoteThreshold && !isPassing) {
                    timerStart = millis();
                    isPassing = true;
                }
                // When we reach the second threshold, calculate velocity and send Note On
                else if (value >= _TriggerValue && isPassing) {
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
                if (value < _TriggerValue && !isPassing) {
                    timerStart = millis();
                    isPassing = true;
                }
                // Complete note off when value drops below minimum threshold
                else if (value < _MinNoteThreshold && isPassing) {
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

        void setVelocity(uint8_t velocity) { this->_velocity = velocity; }
        uint8_t getVelocity() const { return this->_velocity; }
        
        void setThresholdOffset(uint8_t offset) { 
            this->_thresholdOffset = offset; 
            _TriggerValue = _MinNoteThreshold + _thresholdOffset;
        }
        uint8_t getThresholdOffset() const { return this->_thresholdOffset; }
        
        void setMinPhysicalVelocity(float minVelocity) { this->_minPhysicalVelocity = minVelocity; }
        float getMinPhysicalVelocity() const { return this->_minPhysicalVelocity; }
        
        void setMaxPhysicalVelocity(float maxVelocity) { this->_maxPhysicalVelocity = maxVelocity; }
        float getMaxPhysicalVelocity() const { return this->_maxPhysicalVelocity; }

        /** 
         * @brief   Returns the precision of the sensor readings, which is fixed to 7 bits for MIDI compatibility.
         * @return  The precision of the sensor readings (7-bit resolution).
         */
        constexpr static uint8_t precision() { return 7; }

    private:
        uint8_t _TriggerValue, _MinNoteThreshold, _velocity, _range, _thresholdOffset;
        float _minPhysicalVelocity, _maxPhysicalVelocity;
};

END_CS_NAMESPACE
