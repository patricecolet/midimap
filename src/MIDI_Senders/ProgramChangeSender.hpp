#pragma once

#include <midimap/midimap_class.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class that sends MIDI program change messages.
 * 
 * @ingroup MIDI_Senders
 */
class ProgramChangeSender {
  public:
    /// Sends a MIDI program change message for the given program.
    void sendOn(MIDIAddress address) {
        midimap.sendProgramChange(address);
    }
    /// Doesn't do anything (you cannot "un-select" a program).
    void sendOff(MIDIAddress address) { (void)address; }
};

END_CS_NAMESPACE