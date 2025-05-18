#pragma once

#include <MIDI_Senders/UltrasonicKPSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Sends MIDI aftertouch based on ultrasonic sensor readings.
 *
 * This class extends UltrasonicKPSender and uses an ultrasonic sensor to send MIDI aftertouch messages.
 *
 * @ingroup MIDIOutputElements
 */

class KPUltrasonic : public UltrasonicKPSender, public Updatable<> {
  public:
    /**
     * @brief   Create a new KPUltrasonic object with the given pin, note number
     *          and channel.
     * 
     * @param   PinList
     *          The Trigger and Echo pin from HC-SR04. 
     * @param   address
     *          The MIDI address containing the note number [0, 127], 
     *          channel [Channel_1, Channel_16], and optional cable number 
     *          [Cable_1, Cable_16].
     */
    KPUltrasonic(UltrasonicPinList PinList, MIDIAddress address)
        : UltrasonicKPSender(address, PinList) {}

    /** 
     * @brief   Create a new KPUltrasonic object with the given analog pin, 
     *          note number, MIDI channel, and threshold values for imperfect components.
     * 
     * @param   PinList
     *          The Trigger and Echo pin from HC-SR04.
     * @param   address
     *          The MIDI address containing the note number [0, 127],
     *          channel [CHANNEL_1, CHANNEL_16], and optional cable number 
     *          [CABLE_1, CABLE_16].
     * @param   MinThreshold
     *          The minimum threshold value [0, 255].
     * @param   MaxThreshold
     *          The maximum threshold value [0, 255].
     */

     KPUltrasonic(UltrasonicPinList PinList, MIDIAddress address, uint8_t MinThreshold, uint8_t MaxThreshold)
        : UltrasonicKPSender(address, PinList, MinThreshold, MaxThreshold) {}

    // Initialize pin for sensor
    void begin() { UltrasonicKPSender::begin();}
    // Update aftertouch value based on sensor
    void update() { UltrasonicKPSender::update();}
};

END_CS_NAMESPACE


