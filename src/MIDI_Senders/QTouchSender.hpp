#pragma once

#include <midimap/midimap_class.hpp>
#include <AH/Hardware/Touch.hpp>

BEGIN_CS_NAMESPACE

using AH::Touch;

/**
 * @brief A class that sends MIDI Note On, Note Off, and Polyphonic Aftertouch messages 
 *        based on touch sensor input.
 *
 * This class reads values from a touch sensor, applies thresholds for triggering MIDI events,
 * and sends MIDI messages. The values are compared against two thresholds:
 * - MinNoteThreshold: Below this value, the note is turned off.
 * - TriggerValue: When the value exceeds this threshold, Polyphonic Aftertouch is triggered.
 *
 * @ingroup MIDI_Senders
 */
class QTouchSender {
public:
    /**
     * @brief Constructor for QTouchSender on SAMD architecture.
     *
     * @param address MIDI address for the note and aftertouch messages.
     * @param pin The touch pin to read from.
     * @param triggerValue The threshold for triggering aftertouch.
     * @param minNoteThreshold The minimum threshold for triggering a note.
     * @param oversample Oversampling setting for the touch sensor.
     * @param resistor Series resistor setting for the touch sensor.
     * @param freqMode Frequency mode setting for the touch sensor.
     */
    #ifdef ARDUINO_ARCH_SAMD
    QTouchSender(MIDIAddress address, pin_t pin, uint8_t triggerValue, uint8_t minNoteThreshold,
                 oversample_t oversample, series_resistor_t resistor, freq_mode_t freqMode)
        : _touch(pin, oversample, resistor, freqMode), 
          _address(address), 
          _triggerValue(triggerValue), 
          _minNoteThreshold(minNoteThreshold),
          _isNoteOn(false) {}
    #elif defined(ESP32)
    /**
     * @brief Constructor for QTouchSender on ESP32 architecture.
     *
     * @param address MIDI address for the note and aftertouch messages.
     * @param pin The touch pin to read from.
     * @param triggerValue The threshold for triggering aftertouch.
     * @param minNoteThreshold The minimum threshold for triggering a note.
     */
    QTouchSender(MIDIAddress address, pin_t pin, uint8_t triggerValue, uint8_t minNoteThreshold)
        : _touch(pin), 
          _address(address), 
          _triggerValue(triggerValue), 
          _minNoteThreshold(minNoteThreshold),
          _isNoteOn(false) {}
    #endif

    /**
     * @brief Initialize the touch sensor.
     */
    void begin() {
        _touch.begin();
    }

    /**
     * @brief Update the touch reading and send MIDI messages based on thresholds.
     */
    void update() {
        uint8_t value = _touch.read();
        
        if (value < _minNoteThreshold) {
            // If the value is below MinNoteThreshold, stop the note (send Note Off)
            if (_isNoteOn) {
                midimap.sendNoteOff(_address, 0); // 0 velocity for Note Off
                _isNoteOn = false;
            }
        }
        else if (value >= _minNoteThreshold && value < _triggerValue) {
            // If value is between MinNoteThreshold and TriggerValue, play a normal note (Note On)
            if (!_isNoteOn) {
                midimap.sendNoteOn(_address, value);
                _isNoteOn = true;
            }
        }
        else if (value >= _triggerValue) {
            // If value exceeds TriggerValue, send Aftertouch along with Note On
            if (!_isNoteOn) {
                midimap.sendNoteOn(_address, value);
                _isNoteOn = true;
            }
            midimap.sendKeyPressure(_address, value); // Send Polyphonic Aftertouch
        }
    }

private:
    Touch _touch;                ///< Touch sensor object.
    MIDIAddress _address;        ///< MIDI address for sending messages.
    uint8_t _triggerValue;       ///< Threshold for triggering aftertouch.
    uint8_t _minNoteThreshold;   ///< Minimum threshold for triggering a note.
    bool _isNoteOn;              ///< Tracks if the note is currently on.
};

END_CS_NAMESPACE
