#pragma once

#include <MIDI_Senders/UltrasonicCCSender.hpp>

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
class CCUltrasonic : public UltrasonicCCSender, public Updatable<> {
  public:
    /** 
     * @brief   Create a new CCUltrasonic object with the given analog pin
     *          and channel.
     * 
     * @param   pin
     *          The analog input pin to read from.
     * @param   address
     *          The MIDI channel [Channel_1, Channel_16] and optional Cable
     *          Number [Cable_1, Cable_16].
     */
    CCUltrasonic(UltrasonicPinList PinList, MIDIAddress address)
        : UltrasonicCCSender(address, PinList) {}
    /** 
     * @brief   Create a new CCUltrasonic object with the given analog pin
     *          and channel.
     * 
     * @param   PinList
     *          The Trigger and Echo pin from HC-SR04.
     * @param   address
     *          The MIDI channel [Channel_1, Channel_16] and optional Cable
     *          Number [Cable_1, Cable_16].
     * @param   MinThreshold
     *          The minimum threshold value [0, 2000].
     * @param   MaxThreshold
     *          The maximum threshold value [MinThreshold, 4000].
     */
    CCUltrasonic(UltrasonicPinList PinList, MIDIAddress address, uint16_t MinThreshold, uint16_t MaxThreshold,const uint16_t sendInterval)
        : UltrasonicCCSender(address, PinList, MinThreshold, MaxThreshold, sendInterval) {}    

    // Initialize pin for sensor
    void begin() { UltrasonicCCSender::begin();}
    // Update aftertouch value based on sensor
    void update() { UltrasonicCCSender::update();}
};

END_CS_NAMESPACE