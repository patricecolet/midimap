#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/PitchBendSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class of MIDIOutputElement that reads the touch input from an
 *          ESP32 capacitive touch sensor, and sends out 14-bit MIDI **Pitch Bend** 
 *          events.
 * 
 * The touch input is filtered and adaptive baseline tracking is applied for maximum
 * stability. This provides smooth, expressive pitch control suitable for
 * vibrato effects and continuous pitch modulation.
 *
 * The actual precision is "only" 10 bits, because this is the resolution of the
 * built-in ADC, and this is the default resolution used by the Mackie Control
 * Universal protocol.
 *
 * @ingroup MIDIOutputElements
 */
class PBTouch : public MIDIFilteredTouch<PitchBendSender<10>> {
  public:
    /** 
     * @brief   Create a new PBTouch object with the given touch pin
     *          and channel.
     * 
     * @param   touchPin
     *          The ESP32 touch pin to read from.
     * @param   address
     *          The MIDI channel [Channel_1, Channel_16] and optional Cable
     *          Number [Cable_1, Cable_16].
     */
    PBTouch(pin_t touchPin, MIDIChannelCable address)
        : MIDIFilteredTouch(touchPin, address, {}) {}
        
    /** 
     * @brief   Create a new PBTouch object with the given touch pin, 
     *          channel, and threshold values.
     * 
     * @param   touchPin
     *          The ESP32 touch pin to read from.
     * @param   address
     *          The MIDI channel [Channel_1, Channel_16] and optional Cable
     *          Number [Cable_1, Cable_16].
     * @param   MinThreshold
     *          The minimum threshold value [0, 1023].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 1023].
     */
    PBTouch(pin_t touchPin, MIDIChannelCable address, uint16_t MinThreshold, uint16_t MaxThreshold)
        : MIDIFilteredTouch(touchPin, address, {MinThreshold, MaxThreshold}) {}
};

END_CS_NAMESPACE
