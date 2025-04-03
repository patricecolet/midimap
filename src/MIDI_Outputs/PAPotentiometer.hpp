#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/ContinuousPASender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending Polyphonic Aftertouch messages based on an
 *          analog input, such as a sensor or fader.
 * 
 * This class reads an analog input, applies filtering, and sends MIDI
 * Polyphonic Aftertouch (Poly Pressure) messages.
 * The analog input is filtered and hysteresis is applied for maximum stability.
 */
class PAPotentiometer : public MIDIFilteredAnalog<ContinuousPASender> {
  public:
    /** 
     * @brief   Create a new PAPotentiometer object with the given analog pin, 
     *          note number, and MIDI channel.
     *          For perfect components that don't need thresholding.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the note number [0, 127],
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     */
    PAPotentiometer(pin_t analogPin, MIDIAddress address)
        : MIDIFilteredAnalog(analogPin, address, {}) {}

    /** 
     * @brief   Create a new PAPotentiometer object with the given analog pin, 
     *          note number, MIDI channel, and threshold values for imperfect components.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI address containing the note number [0, 127],
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     * @param   MinThreshold
     *          The minimum threshold value [0, 255].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 255].
     */
    PAPotentiometer(pin_t analogPin, MIDIAddress address, uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredAnalog(analogPin, address, {MinThreshold, MaxThreshold}) {}
};

END_CS_NAMESPACE
