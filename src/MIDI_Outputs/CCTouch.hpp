#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/ContinuousCCSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class of MIDIOutputElement%s that read the touch input from an
 *          **ESP32 touch sensor**, and send out 7-bit MIDI 
 *          **Control Change** events.
 * 
 * The touch input is filtered and hysteresis is applied for maximum
 * stability.  
 * This version cannot be banked.
 *
 * @ingroup MIDIOutputElements
 */
class CCTouch : public MIDIFilteredTouch<ContinuousCCSender> {
  public:
    /** 
     * @brief   Create a new CCESP32Potentiometer object with the given touch pin, 
     *          controller number and channel. For perfect components that don't need thresholding.
     * 
     * @param   touchPin
     *          The touch pin to read from.
     * @param   address
     *          The MIDI address containing the controller number [0, 119], 
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     */
    CCTouch(int touchPin, MIDIAddress address)
        : MIDIFilteredTouch(touchPin, address, {}) {}
        
    /** 
     * @brief   Create a new CCESP32Potentiometer object with the given touch pin, 
     *          controller number, channel, and threshold values for imperfect components.
     * 
     * @param   touchPin
     *          The touch pin to read from.
     * @param   address
     *          The MIDI address containing the controller number [0, 119], 
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     * @param   MinThreshold
     *          The minimum threshold value [0, 127].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 127].
     */
    CCTouch(int touchPin, MIDIAddress address, int MinThreshold, int MaxThreshold)
        : MIDIFilteredTouch(touchPin, address, {MinThreshold, MaxThreshold}) {}
};

END_CS_NAMESPACE
