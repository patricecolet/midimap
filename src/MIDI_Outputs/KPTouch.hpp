#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
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
class KPTouch : public MIDIFilteredTouch<ContinuousPASender>
{
public:
    /**
     * @brief   Create a new KPTouch object with the given analog pin,
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
    KPTouch(pin_t analogPin, MIDIAddress address)
        : MIDIFilteredTouch(analogPin, address, {}) {}

    /**
     * @brief   Create a new KPTouch object with the given analog pin,
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
    KPTouch(pin_t analogPin, MIDIAddress address, uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredTouch(analogPin, address, {MinThreshold, MaxThreshold}) {}
};

END_CS_NAMESPACE
