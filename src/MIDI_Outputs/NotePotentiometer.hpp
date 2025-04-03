#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/NotePotentiometerSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Note messages based on an 
 *          analog input from a potentiometer with velocity sensitivity.
 */
class NotePotentiometer : public MIDIFilteredAnalog<NotePotentiometerSender> {
  public:
    /** 
     * @brief   Create a new NotePotentiometer object with the given analog pin,
     *          note number, and MIDI channel.
     * 
     * @param   analogPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   MinNoteThreshold
     *          The minimum value required for the note to activate.
     * @param   range
     *          The range of MIDI output values.
     * @param   minPhysicalVelocity
     *          The minimum physical velocity value.
     * @param   maxPhysicalVelocity
     *          The maximum physical velocity value.
     */
    NotePotentiometer(pin_t analogPin, MIDIAddress address, uint8_t MinNoteThreshold, uint8_t range, 
                     float minPhysicalVelocity, float maxPhysicalVelocity)
        : MIDIFilteredAnalog(analogPin, address, {MinNoteThreshold, range, 10, 
                                                 minPhysicalVelocity, maxPhysicalVelocity}) {}
};

END_CS_NAMESPACE


