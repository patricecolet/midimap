#pragma once

#include <MIDI_Senders/UltrasonicCCSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Sends MIDI aftertouch based on ultrasonic sensor readings.
 *
 * This class extends UltrasonicCCSender and uses an ultrasonic sensor to send MIDI aftertouch messages.
 *
 * @ingroup MIDIOutputElements
 */

class CCUltrasonic : public UltrasonicCCSender, public Updatable<> {
  public:
    /**
     * @brief   Create a new CCUltrasonic object with the given pin, note number
     *          and channel.
     * 
     * @param   pin
     *          The SIG pin to read from.  
     * @param   address
     *          The MIDI address containing the note number [0, 127], 
     *          channel [Channel_1, Channel_16], and optional cable number 
     *          [Cable_1, Cable_16].
     */
    CCUltrasonic(pin_t pin, MIDIAddress address, uint8_t range)
        : UltrasonicCCSender(address, pin , range) {}

    // Initialize pin for sensor
    void begin() { UltrasonicCCSender::begin();}
    // Update aftertouch value based on sensor
    void update() { UltrasonicCCSender::update();}
};

END_CS_NAMESPACE


