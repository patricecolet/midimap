#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/ContinuousPCSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A Program Change event is sent when the potentiometer value rises above
 *          the trigger threshold.
 * 
 * @ingroup MIDIOutputElements
 */
class PCPotentiometer : public MIDIFilteredAnalog<ContinuousPCSender> {
  public:
    /**
     * @brief   Create a new PCPotentiometer object with the given analog pin, 
     *          program number, channel, and trigger threshold.
     * 
     * @param   pin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the program number [0, 127], 
     *          channel [Channel_1, Channel_16], and optional cable number 
     *          [Cable_1, Cable_16].
     * @param   triggerValue
     *          The threshold value [0, 127] at which to send the Program Change.
     */
    PCPotentiometer(pin_t pin, MIDIAddress address, uint8_t triggerValue)
        : MIDIFilteredAnalog(pin, address, ContinuousPCSender(triggerValue)) {}

    /**
     * @brief   Create a new PCPotentiometer object with the given analog pin, 
     *          program number, channel, trigger threshold, and input range.
     * 
     * @param   pin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the program number [0, 127], 
     *          channel [Channel_1, Channel_16], and optional cable number 
     *          [Cable_1, Cable_16].
     * @param   triggerValue
     *          The threshold value [0, 127] at which to send the Program Change.
     * @param   minThreshold
     *          The minimum value of the potentiometer [0, 127].
     * @param   maxThreshold
     *          The maximum value of the potentiometer [0, 127].
     */
    PCPotentiometer(pin_t pin, MIDIAddress address, uint8_t triggerValue, 
                    uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredAnalog(pin, address, 
                    ContinuousPCSender(triggerValue, MinThreshold, MaxThreshold)) {}
};

END_CS_NAMESPACE
