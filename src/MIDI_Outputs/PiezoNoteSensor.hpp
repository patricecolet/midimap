#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/PiezoNoteSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending Polyphonic Aftertouch messages based on an
 *          analog input, such as a sensor or fader.
 * 
 * This class reads an analog input, applies filtering, and sends MIDI
 * Polyphonic Aftertouch (Poly Pressure) messages.
 */
class PiezoNoteSensor : public MIDIFilteredAnalog<PiezoNoteSender> {
  public:
    /** 
     * @brief   Create a new PPAftertouchSensor object with the given analog pin, 
     *          note number, and MIDI channel.
     * 
     * @param   analogPin
     *          The analog input pin to read from.
     * @param   note
     *          The MIDI note number [0, 127] to apply the pressure to.
     * @param   address
     *          The MIDI address containing the channel [CHANNEL_1, CHANNEL_16].
     */
    PiezoNoteSensor(pin_t analogPin, MIDIAddress address , uint8_t threshold)
        : MIDIFilteredAnalog(analogPin, address, {threshold})  {}

};

END_CS_NAMESPACE