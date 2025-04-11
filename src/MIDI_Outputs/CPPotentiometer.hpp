#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/ContinuousCPSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class of MIDIOutputElement%s that read the analog input from a
 *          **potentiometer or fader**, and send out 7-bit MIDI 
 *          **Control Change** events.
 * 
 * The analog input is filtered and hysteresis is applied for maximum
 * stability.  
 * This version cannot be banked.
 *
 * @ingroup MIDIOutputElements
 */
class CPPotentiometer : public MIDIFilteredAnalog<ContinuousCPSender> {
  public:
    /** 
     * @brief   Create a new CPPotentiometer object with the given analog pin and channel.
     *          For perfect components that don't need thresholding.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the channel [CHANNEL_1, CHANNEL_16], 
     *          and optional cable number [CABLE_1, CABLE_16].
     */
    CPPotentiometer(pin_t analogPin, MIDIChannelCable address)
        : MIDIFilteredAnalog(analogPin, address, {}) {}
        
    /** 
     * @brief   Create a new CPPotentiometer object with the given analog pin, 
     *          channel, and threshold values for imperfect components.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the channel [CHANNEL_1, CHANNEL_16], 
     *          and optional cable number [CABLE_1, CABLE_16].
     * @param   MinThreshold
     *          The minimum threshold value [0, 127].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 127].
     */
    CPPotentiometer(pin_t analogPin, MIDIChannelCable address, uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredAnalog(analogPin, address, {MinThreshold, MaxThreshold}) {}
};

END_CS_NAMESPACE
