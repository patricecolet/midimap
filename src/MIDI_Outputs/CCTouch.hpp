#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/ContinuousCCSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class of MIDIOutputElement that reads the touch input from an
 *          ESP32 capacitive touch sensor, and sends out 7-bit MIDI 
 *          Control Change events.
 * 
 * The touch input is filtered and adaptive baseline tracking is applied for maximum
 * stability. The class uses multi-stage smoothing to provide clean, responsive
 * control signals.
 *
 * @ingroup MIDIOutputElement
 */
class CCTouch : public MIDIFilteredTouch<ContinuousCCSender> {
  public:
    /** 
     * @brief   Create a new CCTouch object with the given touch pin, 
     *          controller number and channel.
     * 
     * @param   touchPin
     *          The ESP32 touch pin to read from.
     * @param   address
     *          The MIDI address containing the controller number [0, 119], 
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     */
    CCTouch(int touchPin, MIDIAddress address)
        : MIDIFilteredTouch(touchPin, address, {}) {}
        
    /** 
     * @brief   Create a new CCTouch object with the given touch pin, 
     *          controller number, channel, and threshold values.
     * 
     * @param   touchPin
     *          The ESP32 touch pin to read from.
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
