#pragma once

#include <midimap/midimap_class.hpp>
#include <AH/Hardware/Ultrasonic.hpp>

BEGIN_CS_NAMESPACE

using AH::Ultrasonic;

/**
 * @brief Class that converts sensor data to MIDI key pressure messages.
 *
 * @ingroup MIDI_Senders
 */
class UltrasonicKPSender {
    public:
        UltrasonicKPSender(MIDIAddress address, pin_t pin)
            : _address(address), _ultrasonic(pin), _MinThreshold(0), _MaxThreshold(127), 
              _lastSentValue(255), _thresholdingEnabled(false) {}
        
        UltrasonicKPSender(MIDIAddress address, pin_t pin, uint8_t MinThreshold, uint8_t MaxThreshold)
            : _address(address), _ultrasonic(pin), _MinThreshold(MinThreshold), _MaxThreshold(MaxThreshold), 
              _lastSentValue(255), _thresholdingEnabled(true) {}

        /// Initializes the sensor.
        void begin() {
            _ultrasonic.begin();
        }

        void update() {
            uint8_t mappedValue;
            uint16_t distance = _ultrasonic.readDistanceMM();
            //Serial.println(distance);
            if (_thresholdingEnabled) {
                // Apply the threshold filter
                if (distance < _MinThreshold) {
                    distance = _MinThreshold;  // If value is below MinThreshold, use MinThreshold
                } else if (distance > _MaxThreshold) {
                    distance = _MaxThreshold;  // If value is above MaxThreshold, use MaxThreshold
                }
                Serial.println(_MaxThreshold);
                // Map the filtered value to 0-127 range
                mappedValue = map(distance, _MinThreshold, _MaxThreshold, 0, 127);
            } else {
                // For perfect components, just ensure the value is in the 0-127 range
                mappedValue = distance > 127 ? 127 : distance;
            }
            
            if (mappedValue != _lastSentValue) {
                // Send the mapped value
                midimap.sendKeyPressure(_address, mappedValue);
    
                // Update the last sent value
                _lastSentValue = mappedValue;
            }
            
        }

    private:
        MIDIAddress _address;   ///< MIDI address for sending key pressure.
        Ultrasonic _ultrasonic; ///< Ultrasonic sensor object.
        bool _thresholdingEnabled; // Flag to indicate if thresholding is enabled
        uint8_t _lastSentValue; // Store the last sent value
        uint8_t _MinThreshold, _MaxThreshold;
};

END_CS_NAMESPACE
