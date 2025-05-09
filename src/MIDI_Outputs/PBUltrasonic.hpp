#pragma once

#include <MIDI_Senders/UltrasonicPBSender.hpp>

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
class PBUltrasonic : public UltrasonicPBSender<10>, public Updatable<> {
  public:
    /** 
     * @brief   Create a new PBUltrasonic object with the given analog pin
     *          and channel.
     * 
     * @param   pin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI channel [Channel_1, Channel_16] and optional Cable
     *          Number [Cable_1, Cable_16].
     */
    PBUltrasonic(pin_t pin, MIDIAddress address)
        : UltrasonicPBSender(address, pin) {}

    // Initialize pin for sensor
    void begin() { UltrasonicPBSender::begin();}
    // Update aftertouch value based on sensor
    void update() { UltrasonicPBSender::update();}
};

END_CS_NAMESPACE
