#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/ContinuousCPSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class of MIDIOutputElement that reads the touch input from an
 *          ESP32 capacitive touch sensor, and sends out 7-bit MIDI 
 *          Channel Pressure (Aftertouch) events.
 * 
 * The touch input is filtered and adaptive baseline tracking is applied for maximum
 * stability. The class uses multi-stage smoothing to provide clean, responsive
 * control signals suitable for expressive performance control.
 *
 * @ingroup MIDIOutputElements
 */
class CPTouch : public MIDIFilteredTouch<ContinuousCPSender> {
  public:
    /** 
     * @brief   Create a new CPTouch object with the given touch pin and channel.
     * 
     * @param   touchPin
     *          The ESP32 touch pin to read from.
     * @param   address
     *          The MIDI address containing the channel [CHANNEL_1, CHANNEL_16], 
     *          and optional cable number [CABLE_1, CABLE_16].
     */
    CPTouch(pin_t touchPin, MIDIChannelCable address)
        : MIDIFilteredTouch(touchPin, address, {}) {}
        
    /** 
     * @brief   Create a new CPTouch object with the given touch pin, 
     *          channel, and threshold values.
     * 
     * @param   touchPin
     *          The ESP32 touch pin to read from.
     * @param   address
     *          The MIDI address containing the channel [CHANNEL_1, CHANNEL_16], 
     *          and optional cable number [CABLE_1, CABLE_16].
     * @param   MinThreshold
     *          The minimum threshold value [0, 127].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 127].
     */
    CPTouch(pin_t touchPin, MIDIChannelCable address, uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredTouch(touchPin, address, {MinThreshold, MaxThreshold}) {}
};

END_CS_NAMESPACE
