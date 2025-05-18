#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/ContinuousCCSender.hpp>

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
class CCPotentiometer14 : public MIDIFilteredAnalog<ContinuousCCSender14<10>> {
  public:
    /** 
     * @brief   Create a new CCPotentiometer14 object with the given analog pin, 
     *          controller number and channel.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the controller number [0, 119], 
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     */
    CCPotentiometer14(pin_t analogPin, MIDIAddress address)
        : MIDIFilteredAnalog(analogPin, address, ContinuousCCSender14<10>{}) {}
        
    /** 
     * @brief   Create a new CCPotentiometer14 object with the given analog pin, 
     *          controller number, channel, and threshold values.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the controller number [0, 119], 
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     * @param   MinThreshold
     *          The minimum threshold value.
     * @param   MaxThreshold
     *          The maximum threshold value.
     */
    CCPotentiometer14(pin_t analogPin, MIDIAddress address, uint16_t MinThreshold, uint16_t MaxThreshold)
        : MIDIFilteredAnalog(analogPin, address, ContinuousCCSender14<10>{MinThreshold, MaxThreshold}) {}
        
    /** 
     * @brief   Create a new CCPotentiometer14 object with the given analog pin, 
     *          controller number, channel, threshold values, and send interval.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the controller number [0, 119], 
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     * @param   MinThreshold
     *          The minimum threshold value.
     * @param   MaxThreshold
     *          The maximum threshold value.
     * @param   sendInterval
     *          Fixed time between MIDI messages in milliseconds.
     */
    CCPotentiometer14(pin_t analogPin, MIDIAddress address, uint16_t MinThreshold, uint16_t MaxThreshold, uint16_t sendInterval)
        : MIDIFilteredAnalog(analogPin, address, ContinuousCCSender14<10>{MinThreshold, MaxThreshold, sendInterval}) {}
};

END_CS_NAMESPACE