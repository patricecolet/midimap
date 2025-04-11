#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/ContinuousNoteVelSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Note messages with velocity based on an 
 *          analog input from a potentiometer with a simple threshold trigger.
 *          The velocity is calculated based on how quickly the potentiometer
 *          is turned between the trigger threshold and note-on threshold.
 * 
 * @ingroup MIDIOutputElements
 */
class NoteVelTouch : public MIDIFilteredTouch<ContinuousNoteVelSender> {
  public:
    /** 
     * @brief   Create a new NoteVelTouch object with the given analog pin,
     *          note number, MIDI channel, and velocity parameters.
     * 
     * @param   touchPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   MinNoteThreshold
     *          The threshold value [0, 127] at which timing starts for velocity calculation.
     * @param   minPhysicalVelocity
     *          The minimum physical velocity that maps to MIDI velocity 1.
     * @param   maxPhysicalVelocity
     *          The maximum physical velocity that maps to MIDI velocity 127.
     */
    NoteVelTouch(int touchPin, MIDIAddress address, 
                      uint8_t MinNoteThreshold,
                      float minPhysicalVelocity, float maxPhysicalVelocity)
        : MIDIFilteredTouch(touchPin, address, 
                            ContinuousNoteVelSender(MinNoteThreshold,
                                                   minPhysicalVelocity, maxPhysicalVelocity)) {}
                                                 
    /** 
     * @brief   Create a new NoteVelTouch object with the given analog pin,
     *          note number, MIDI channel, velocity parameters, and thresholds for imperfect components.
     * 
     * @param   touchPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   MinNoteThreshold
     *          The threshold value [0, 127] at which timing starts for velocity calculation.
     * @param   minPhysicalVelocity
     *          The minimum physical velocity that maps to MIDI velocity 1.
     * @param   maxPhysicalVelocity
     *          The maximum physical velocity that maps to MIDI velocity 127.
     * @param   MinThreshold
     *          The minimum threshold value [0, 127] for the potentiometer.
     * @param   MaxThreshold
     *          The maximum threshold value [0, 127] for the potentiometer.
     */
    NoteVelTouch(int touchPin, MIDIAddress address, 
                      uint8_t MinNoteThreshold, float minPhysicalVelocity, float maxPhysicalVelocity,
                      uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredTouch(touchPin, address, 
                            ContinuousNoteVelSender(MinNoteThreshold, minPhysicalVelocity, maxPhysicalVelocity,
                                                   MinThreshold, MaxThreshold)) {}
};

END_CS_NAMESPACE
