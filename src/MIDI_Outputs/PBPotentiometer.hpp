#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/PitchBendSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class of MIDIOutputElement%s that read the analog input from a
 *          **potentiometer or fader**, and send out 14-bit MIDI **Pitch Bend** 
 *          events.
 * 
 * The analog input is filtered and hysteresis is applied for maximum
 * stability.  
 * The actual precision is "only" 10 bits, because this is the resolution of the
 * built-in ADC, and this is the default resolution used by the Mackie Control
 * Universal protocol.  
 * This version cannot be banked.
 *
 * @ingroup MIDIOutputElements
 */
class PBPotentiometer : public MIDIFilteredAnalog<PitchBendSender<10>> {
  public:
    /** 
     * @brief   Create a new PBPotentiometer object with the given analog pin
     *          and channel. For perfect components that don't need thresholding.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI channel [Channel_1, Channel_16] and optional Cable
     *          Number [Cable_1, Cable_16].
     */
    PBPotentiometer(pin_t analogPin, MIDIChannelCable address)
        : MIDIFilteredAnalog(analogPin, address, {}) {}
        
    /** 
     * @brief   Create a new PBPotentiometer object with the given analog pin, 
     *          channel, and threshold values for imperfect components.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI channel [Channel_1, Channel_16] and optional Cable
     *          Number [Cable_1, Cable_16].
     * @param   MinThreshold
     *          The minimum threshold value [0, 1023].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 1023].
     */
    PBPotentiometer(pin_t analogPin, MIDIChannelCable address, uint16_t MinThreshold, uint16_t MaxThreshold)
        : MIDIFilteredAnalog(analogPin, address, {MinThreshold, MaxThreshold}) {}
};

END_CS_NAMESPACE
