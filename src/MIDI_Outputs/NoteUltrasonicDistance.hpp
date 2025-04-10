#pragma once

#include <MIDI_Senders/NoteUltrasonicDistanceSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief A class for sending MIDI Note messages based on an
 * ultrasonic distance sensor with a threshold trigger.
 *
 * @ingroup MIDIOutputElements
 */
class NoteUltrasonicDistance : public NoteUltrasonicDistanceSender, public Updatable<>
{
public:
    /**
     * @brief Create a new NoteUltrasonicDistance object with the given digital pin,
     * note number, MIDI channel, and trigger value.
     *
     * @param digitalPin
     * The digital pin connected to the ultrasonic sensor.
     * @param address
     * The MIDI address containing the note and channel.
     * @param triggerValue
     * The threshold value [0, 127] at which the note is triggered.
     */
    NoteUltrasonicDistance(pin_t digitalPin, MIDIAddress address, uint8_t triggerValue)
        : NoteUltrasonicDistanceSender(address, digitalPin, triggerValue) {}
    /**
     * @brief Create a new NoteUltrasonicDistance object with the given analog pin,
     * note number, MIDI channel, trigger value, and thresholds for imperfect components.
     *
     * @param analogPin
     * The analog input pin connected to the potentiometer.
     * @param address
     * The MIDI address containing the note and channel.
     * @param triggerValue
     * The threshold value [0, 127] at which the note is triggered.
     * @param MinThreshold
     * The minimum threshold value [0, 127].
     * @param MaxThreshold
     * The maximum threshold value [0, 127].
     */
    NoteUltrasonicDistance(pin_t digitalPin, MIDIAddress address, uint8_t triggerValue,
                           uint8_t MinThreshold, uint8_t MaxThreshold)
        : NoteUltrasonicDistanceSender(address, digitalPin, triggerValue, MinThreshold, MaxThreshold) {}

    // Initialize pin for sensor
    void begin() { NoteUltrasonicDistanceSender::begin(); }
    // Update aftertouch value based on sensor
    void update() { NoteUltrasonicDistanceSender::update(); }
};

END_CS_NAMESPACE