#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/NotePotentiometerSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Note messages based on an 
 *          analog input from a potentiometer with velocity sensitivity.
 * 
 * @ingroup MIDIOutputElements
 */
class NotePotentiometer : public MIDIFilteredAnalog<NotePotentiometerSender> {
  public:
  /** 
     * @brief   Create a new NotePotentiometer object with the given analog pin,
     *          note number, MIDI channel, and custom velocity settings.
     * 
     * @param   analogPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   MinNoteThreshold
     *          The minimum value required for the note to activate.
     * @param   minPhysicalVelocity
     *          The minimum physical velocity value.
     * @param   maxPhysicalVelocity
     *          The maximum physical velocity value.
     */
    NotePotentiometer(pin_t analogPin, MIDIAddress address, uint8_t MinNoteThreshold,
                     float minPhysicalVelocity, float maxPhysicalVelocity)
        : MIDIFilteredAnalog(analogPin, address, {MinNoteThreshold, 10, 
                                                 minPhysicalVelocity, maxPhysicalVelocity}) {}
                                                 
    /** 
     * @brief   Create a new NotePotentiometer object with the given analog pin,
     *          note number, MIDI channel, custom velocity settings, and thresholds for imperfect components.
     * 
     * @param   analogPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   MinNoteThreshold
     *          The minimum value required for the note to activate.
     * @param   minPhysicalVelocity
     *          The minimum physical velocity value.
     * @param   maxPhysicalVelocity
     *          The maximum physical velocity value.
     * @param   MinThreshold
     *          The minimum threshold value [0, 127].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 127].
     */
    NotePotentiometer(pin_t analogPin, MIDIAddress address, uint8_t MinNoteThreshold,
                     float minPhysicalVelocity, float maxPhysicalVelocity,
                     uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredAnalog(analogPin, address, {MinNoteThreshold, 10, 
                                                 minPhysicalVelocity, maxPhysicalVelocity,
                                                 MinThreshold, MaxThreshold}) {}
};

END_CS_NAMESPACE
