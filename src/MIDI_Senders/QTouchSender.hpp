#pragma once

#include <midimap/midimap_class.hpp>
#include <AH/Math/IncreaseBitDepth.hpp>
#ifdef ARDUINO_ARCH_SAMD
#include <Adafruit_FreeTouch.h>

BEGIN_CS_NAMESPACE

//using oversample_t = tag_oversample_level_t;
//using series_resistor_t = tag_series_resistor_t;
//using freq_mode_t = tag_freq_mode_t;

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
class QTouchSender {
    public:
        /**
         * @brief   Constructor for VelostatPolyNoteSender.
         * 
         * @param   TriggerValue
         *          The threshold for triggering aftertouch.
         * @param   MinNoteThreshold
         *          The minimum threshold for triggering a note.
         */
        QTouchSender(pin_t analogPin, MIDIAddress address, uint8_t TriggerValue, uint8_t MinNoteThreshold, oversample_t OVERSAMPLE, series_resistor_t RESISTOR, freq_mode_t FREQ_MODE)          
            : _QTouch(analogPin, OVERSAMPLE, RESISTOR, FREQ_MODE), _address(address), _pin(analogPin), _TriggerValue(TriggerValue), _MinNoteThreshold(MinNoteThreshold), _OVERSAMPLE(OVERSAMPLE), _RESISTOR(RESISTOR), _FREQMODE(FREQ_MODE) {}

        void begin(){
            _QTouch.begin();
        }

        void update(){
            static uint16_t min_val = 65535;  // Start with max possible value
            static uint16_t max_val = 0;      // Start with min possible value
            uint16_t raw_value = _QTouch.measure();

            // Update min/max
            if (raw_value < min_val) min_val = raw_value;
            if (raw_value > max_val) max_val = raw_value;

            // Map using dynamic range
            uint8_t value = map(raw_value, min_val, max_val, 0, 127);

            static bool isNoteOn = false; // Tracks if the note is currently on
            
            Serial.println(value);    
            if (value < _MinNoteThreshold) {
                // If the value is below MinNoteThreshold, stop the note (send Note Off)
                if (isNoteOn) {
                    midimap.sendNoteOff(_address, 0);  // 0 velocity for Note Off
                    isNoteOn = false;
                }
            } 
            else if (value >= _MinNoteThreshold && value < _TriggerValue) {
                // If value is between MinNoteThreshold and TriggerValue, play a normal note (Note On)
                if (!isNoteOn) {
                    midimap.sendNoteOn(_address, value);  // Note On with max velocity
                    isNoteOn = true;
                }
            } 
            else if (value >= _TriggerValue) {
                // If value exceeds TriggerValue, send Aftertouch along with Note On
                if (!isNoteOn) {
                    midimap.sendNoteOn(_address, value);  // Note On with max velocity
                    isNoteOn = true;
                }
                midimap.sendKeyPressure(_address, value);  // Send Polyphonic Aftertouch (Channel Pressure)
            }
            delay(200);
        }

        /** 
         * @brief   Returns the precision of the sensor readings, which is fixed to 7 bits for MIDI compatibility.
         * @return  The precision of the sensor readings (7-bit resolution).
         */
        constexpr static uint8_t precision() { return 7; }

    private:
        Adafruit_FreeTouch _QTouch;
        uint8_t _pin, _TriggerValue, _MinNoteThreshold;
        oversample_t _OVERSAMPLE;
        series_resistor_t _RESISTOR;
        freq_mode_t _FREQMODE;  
        MIDIAddress _address;
};

END_CS_NAMESPACE

#endif