#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/ContinuousNoteSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Note On/Off messages based on an 
 *          ESP32 capacitive touch sensor input with a simple threshold trigger.
 * 
 * When the touch sensor value exceeds the threshold, a Note On message is sent.
 * When the value falls below the threshold, a Note Off message is sent.
 * The touch input is filtered using adaptive baseline tracking with multi-stage
 * smoothing to provide stable triggering.
 * 
 * @ingroup MIDIOutputElements
 */
class NoteTouch : public MIDIFilteredTouch<ContinuousNoteSender> {
  public:
    /** 
     * @brief   Create a new NoteTouch object with the given touch pin,
     *          note number, MIDI channel, and trigger value.
     * 
     * @param   touchPin
     *          The ESP32 touch pin to read from.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   triggerValue
     *          The threshold value [0, 127] at which the note is triggered.
     */
    NoteTouch(int touchPin, MIDIAddress address, uint8_t triggerValue)
        : MIDIFilteredTouch(touchPin, address, ContinuousNoteSender(triggerValue)) {}
                                                 
    /** 
     * @brief   Create a new NoteTouch object with the given touch pin,
     *          note number, MIDI channel, trigger value, and thresholds.
     * 
     * @param   touchPin
     *          The ESP32 touch pin to read from.
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
