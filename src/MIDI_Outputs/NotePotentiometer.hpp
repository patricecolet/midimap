#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/NotePotentiometerSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Note messages based on an 
 *          analog input from a potentiometer with a simple threshold trigger.
 * 
 * @ingroup MIDIOutputElements
 */
class NotePotentiometer : public MIDIFilteredAnalog<NotePotentiometerSender> {
  public:
<<<<<<< HEAD
    /** 
     * @brief   Create a new NotePotentiometer object with the given analog pin,
     *          note number, MIDI channel, and trigger value.
=======
  /** 
     * @brief   Create a new NotePotentiometer object with the given analog pin,
     *          note number, MIDI channel, and custom velocity settings.
>>>>>>> 7a74c1554e19f4efb7b40d1f0c36367fceca554b
     * 
     * @param   analogPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
<<<<<<< HEAD
     * @param   triggerValue
     *          The threshold value [0, 127] at which the note is triggered.
     */
    NotePotentiometer(pin_t analogPin, MIDIAddress address, uint8_t triggerValue)
        : MIDIFilteredAnalog(analogPin, address, NotePotentiometerSender(triggerValue)) {}
=======
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
>>>>>>> 7a74c1554e19f4efb7b40d1f0c36367fceca554b
                                                 
    /** 
     * @brief   Create a new NotePotentiometer object with the given analog pin,
     *          note number, MIDI channel, trigger value, and thresholds for imperfect components.
     * 
     * @param   analogPin
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
    NotePotentiometer(pin_t analogPin, MIDIAddress address, uint8_t triggerValue,
                     uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredAnalog(analogPin, address, 
                            NotePotentiometerSender(triggerValue, MinThreshold, MaxThreshold)) {}
};

END_CS_NAMESPACE
