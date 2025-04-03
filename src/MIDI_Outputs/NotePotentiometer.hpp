#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/NotePotentiometerSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending **Polyphonic Aftertouch** messages based on an 
 *          analog input from a **Velostat sensor**.
 * 
 * This class reads analog input, applies filtering, and sends MIDI 
 * **Polyphonic Aftertouch** (Poly Pressure) messages, making it ideal 
 * for expressive MIDI controllers.
 */
class NotePotentiometer : public MIDIFilteredAnalog<NotePotentiometerSender> {
  public:
    /** 
     * @brief   Create a new **VelostatPolyNote** object with the given analog pin,
     *          note number, and MIDI channel.
     * 
     * @param   analogPin
     *          The analog input pin connected to Velostat.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   TriggerValue
     *          The threshold where **Polyphonic Aftertouch** begins.
     * @param   MinNoteThreshold
     *          The minimum value required for the note to activate.
     */
    NotePotentiometer(pin_t analogPin, MIDIAddress address, uint8_t TriggerValue, uint8_t MinNoteThreshold,uint8_t range,uint8_t velocity = 0x7F)
        : MIDIFilteredAnalog(analogPin, address, {TriggerValue, MinNoteThreshold, range, velocity}) {}

        void setVelocity(uint8_t velocity) { this->sender.setVelocity(velocity); }
        /// Get the velocity of the MIDI Note events.
        uint8_t getVelocity() const { return this->sender.getVelocity(); }
};

END_CS_NAMESPACE
