#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/ContinuousNoteSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Note messages based on an 
 *          analog input from a potentiometer with a simple threshold trigger.
 * 
 * @ingroup MIDIOutputElements
 */
class NoteTouch : public MIDIFilteredTouch<ContinuousNoteSender> {
  public:
    /** 
     * @brief   Create a new NoteTouch object with the given analog pin,
     *          note number, MIDI channel, and trigger value.
     * 
     * @param   touchPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   triggerValue
     *          The threshold value [0, 127] at which the note is triggered.
     */
    NoteTouch(int touchPin, MIDIAddress address, uint8_t triggerValue)
        : MIDIFilteredTouch(touchPin, address, ContinuousNoteSender(triggerValue)) {}
                                                 
    /** 
     * @brief   Create a new NoteTouch object with the given analog pin,
     *          note number, MIDI channel, trigger value, and thresholds for imperfect components.
     * 
     * @param   touchPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   triggerValue
     *          The threshold value [0, 127] at which the note is triggered.
     * @param   MinThreshold
     *          The minimum threshold value [0, 127].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 127].
     */
    NoteTouch(int touchPin, MIDIAddress address, uint8_t triggerValue,
                     uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredTouch(touchPin, address, 
                            ContinuousNoteSender(triggerValue, MinThreshold, MaxThreshold)) {}
};

END_CS_NAMESPACE
