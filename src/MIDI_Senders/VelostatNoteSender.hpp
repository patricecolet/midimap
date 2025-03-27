#pragma once

#include <midimap/midimap_class.hpp> // Include MIDI library
#include <AH/Math/IncreaseBitDepth.hpp>


BEGIN_CS_NAMESPACE

/**
 * @brief   A class that sends **MIDI Note On**, **Note Off**, and **Polyphonic Aftertouch** messages based on an analog input, such as a **Velostat sensor**.
 * 
 * This class reads the analog value from the Velostat sensor, applies thresholds for triggering MIDI events, and sends MIDI messages. The values are compared against two thresholds:
 * - **MinNoteThreshold**: Below this value, the note is turned off.
 * - **TriggerValue**: When the value exceeds this threshold, Polyphonic Aftertouch is triggered alongside the Note On message.
 *
 * The sensor's input value controls the note and aftertouch, allowing for dynamic, expressive control over the MIDI message outputs.
 * 
 * @note The `TriggerValue` allows you to define the point at which aftertouch starts, while the `MinNoteThreshold` ensures that the note is only played when the input value is sufficiently high.
 * 
 * @param   TriggerValue
 *          The threshold where **Polyphonic Aftertouch** begins (above this, the aftertouch is applied).
 * @param   MinNoteThreshold
 *          The minimum input value required to trigger a **Note On** message (below this, the note is turned off).
 * 
 * @note This class is designed to provide smooth, continuous control of **Polyphonic Aftertouch**, making it suitable for use in expressive MIDI controllers, such as those with pressure-sensitive sensors.
 */
class VelostatNoteSender {
    public:
        /**
         * @brief   Constructor for VelostatPolyNoteSender.
         * 
         * @param   TriggerValue
         *          The threshold for triggering aftertouch.
         * @param   MinNoteThreshold
         *          The minimum threshold for triggering a note.
         */
        VelostatNoteSender(uint8_t TriggerValue, uint8_t MinNoteThreshold ,uint8_t range , uint8_t velocity = 0x7F)
        : _TriggerValue(TriggerValue), _MinNoteThreshold(MinNoteThreshold) , _range (range), _velocity(velocity) {}

        /**
         * @brief   Reads the analog input and sends appropriate MIDI Note On, Note Off, and Polyphonic Aftertouch (Channel Pressure) messages.
         * 
         * The method checks the input value against the **MinNoteThreshold** and **TriggerValue** to decide whether to send a Note On, 
         * Note Off, or Aftertouch message.
         * 
         * - **Note Off** is sent if the value is below the **MinNoteThreshold**.
         * - **Note On** is sent if the value is above the **MinNoteThreshold** but below the **TriggerValue**.
         * - **Note On + Aftertouch** is sent if the value exceeds the **TriggerValue**.
         * 
         * @param   value
         *          The analog input value from the Velostat sensor.
         * @param   address
         *          The MIDI address for the note to send the messages to.
         */
        void send(uint8_t value, MIDIAddress address) {
            static bool isNoteOn = false; // Tracks if the note is currently on

            //Serial.println(value);  // Print the value for debugging
            value = map (value, 0, 127, 0, _range);
            
            if (value < _MinNoteThreshold) {
                // If the value is below MinNoteThreshold, stop the note (send Note Off)
                if (isNoteOn) {
                    midimap.sendNoteOff(address, 0);  // 0 velocity for Note Off
                    isNoteOn = false;
                }
            } 
            else if (value >= _MinNoteThreshold && value < _TriggerValue) {
                // If value is between MinNoteThreshold and TriggerValue, play a normal note (Note On)
                if (!isNoteOn) {
                    midimap.sendNoteOn(address, getVelocity());  // Note On with max velocity
                    isNoteOn = true;
                }
            } 
            else if (value >= _TriggerValue) {
                // If value exceeds TriggerValue, send Aftertouch along with Note On
                if (!isNoteOn) {
                    midimap.sendNoteOn(address, getVelocity());  // Note On with max velocity
                    isNoteOn = true;
                }
                midimap.sendKeyPressure(address, value);  // Send Polyphonic Aftertouch (Channel Pressure)
            }
        }

        void setVelocity(uint8_t velocity) { this->_velocity = velocity; }
        uint8_t getVelocity() const { return this->_velocity; }

        /** 
         * @brief   Returns the precision of the sensor readings, which is fixed to 7 bits for MIDI compatibility.
         * @return  The precision of the sensor readings (7-bit resolution).
         */
        constexpr static uint8_t precision() { return 7; }

    private:
        uint8_t _TriggerValue, _MinNoteThreshold, _velocity, _range;  ///< Thresholds for triggering Note On and Aftertouch
};

END_CS_NAMESPACE
