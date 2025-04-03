#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>
#include <MIDI_Senders/NotePotentiometerSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Note messages based on an 
 *          analog input from a potentiometer with velocity sensitivity.
 */
class NotePotentiometer : public MIDIFilteredAnalog<NotePotentiometerSender> {
  public:
    /** 
     * @brief   Create a new NotePotentiometer object with the given analog pin,
     *          note number, and MIDI channel.
     * 
     * @param   analogPin
     *          The analog input pin connected to the potentiometer.
     * @param   address
     *          The MIDI address containing the note and channel.
     * @param   MinNoteThreshold
     *          The minimum value required for the note to activate.
     * @param   range
     *          The range of MIDI output values.
     * @param   velocity
     *          The default velocity value (default: 0x7F).
     * @param   minPhysicalVelocity
     *          The minimum physical velocity value (default: 0.01).
     * @param   maxPhysicalVelocity
     *          The maximum physical velocity value (default: 1.0).
     */
    NotePotentiometer(pin_t analogPin, MIDIAddress address, uint8_t MinNoteThreshold, uint8_t range, 
                     uint8_t velocity, float minPhysicalVelocity, float maxPhysicalVelocity)
        : MIDIFilteredAnalog(analogPin, address, {MinNoteThreshold, range, 10, velocity, 
                                                 minPhysicalVelocity, maxPhysicalVelocity}) {}

    void setVelocity(uint8_t velocity) { this->sender.setVelocity(velocity); }
    uint8_t getVelocity() const { return this->sender.getVelocity(); }
    
    void setThresholdOffset(uint8_t offset) { this->sender.setThresholdOffset(offset); }
    uint8_t getThresholdOffset() const { return this->sender.getThresholdOffset(); }
    
    void setMinPhysicalVelocity(float minVelocity) { this->sender.setMinPhysicalVelocity(minVelocity); }
    float getMinPhysicalVelocity() const { return this->sender.getMinPhysicalVelocity(); }
    
    void setMaxPhysicalVelocity(float maxVelocity) { this->sender.setMaxPhysicalVelocity(maxVelocity); }
    float getMaxPhysicalVelocity() const { return this->sender.getMaxPhysicalVelocity(); }
};

END_CS_NAMESPACE


