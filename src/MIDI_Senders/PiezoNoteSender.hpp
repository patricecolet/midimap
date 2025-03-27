#pragma once

#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class that sends a MIDI note on and off message based on piezo input value,
 *          ensuring that notes are sent only once when crossing the threshold.
 * 
 * @ingroup MIDI_Senders
 */
class PiezoNoteSender {
public:
    /**
     * @brief Constructor
     * @param threshold The value threshold to trigger the note on/off
     */
    PiezoNoteSender(uint8_t threshold) 
        : _threshold(threshold), _isNoteOn(false) {}

    /**
     * @brief Sends a MIDI note on/off message based on the input value.
     * 
     * @param value The sensor input value
     * @param address The MIDI note address
     */
    void send(uint8_t value, MIDIAddress address) {
        if (value > _threshold && !_isNoteOn) {
            sendOn(address);
            _isNoteOn = true;
        } 
        else if (value < _threshold && _isNoteOn) {
            sendOff(address);
            _isNoteOn = false;
        }
    }

    /// Send a note on message to the given address with fixed velocity
    void sendOn(MIDIAddress address) {
        midimap.sendNoteOn(address, 0x7F);
    }
    
    /// Send a note off message to the given address
    void sendOff(MIDIAddress address) {
        midimap.sendNoteOff(address, 0);
    }

    /// Get the resolution (precision) of the sender in bits
    constexpr static uint8_t precision() { return 7; }

private:
    uint8_t _threshold;
    bool _isNoteOn;  ///< Tracks whether the note is currently on
};

END_CS_NAMESPACE
