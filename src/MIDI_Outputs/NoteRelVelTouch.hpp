#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/ContinuousNoteRelVelSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief A class for sending MIDI Note messages with Release Velocity based on an
 * ESP32 touch sensor input.
 *
 * The Release Velocity is calculated based on how quickly the touch sensor
 * is released between the trigger threshold and note-off threshold.
 * This provides expressive control over note endings, which is particularly
 * useful for realistic piano sounds and other instruments where release
 * characteristics are important.
 *
 * @ingroup MIDIOutputElements
 */
class NoteRelVelTouch : public MIDIFilteredTouch<ContinuousNoteRelVelSender> {
public:
    /**
     * @brief Create a new NoteRelVelTouch object with the given touch pin,
     * note number, MIDI channel, and velocity parameters.
     *
     * @param touchPin
     * The ESP32 touch pin to read from.
     * @param address
     * The MIDI address containing the note and channel.
     * @param MinNoteThreshold
     * The threshold value [0, 127] at which timing starts for velocity calculation.
     * @param minPhysicalVelocity
     * The minimum physical velocity that maps to MIDI velocity 1.
     * @param maxPhysicalVelocity
     * The maximum physical velocity that maps to MIDI velocity 127.
     */
    NoteRelVelTouch(int touchPin, MIDIAddress address,
                         uint8_t MinNoteThreshold, float minPhysicalVelocity, float maxPhysicalVelocity)
        : MIDIFilteredTouch(touchPin, address,
                             ContinuousNoteRelVelSender(MinNoteThreshold, minPhysicalVelocity, maxPhysicalVelocity)) {}
    /**
     * @brief Create a new NoteRelVelTouch object with the given touch pin,
     * note number, MIDI channel, velocity parameters, and thresholds.
     *
     * @param touchPin
     * The ESP32 touch pin to read from.
     * @param address
     * The MIDI address containing the note and channel.
     * @param MinNoteThreshold
     * The threshold value [0, 127] at which timing starts for velocity calculation.
     * @param minPhysicalVelocity
     * The minimum physical velocity that maps to MIDI velocity 1.
     * @param maxPhysicalVelocity
     * The maximum physical velocity that maps to MIDI velocity 127.
     * @param MinThreshold
     * The minimum threshold value [0, 127] for the touch sensor.
     * @param MaxThreshold
     * The maximum threshold value [0, 127] for the touch sensor.
     */
    NoteRelVelTouch(int touchPin, MIDIAddress address,
                         uint8_t MinNoteThreshold, float minPhysicalVelocity, float maxPhysicalVelocity,
                         uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredTouch(touchPin, address,
                             ContinuousNoteRelVelSender(MinNoteThreshold, minPhysicalVelocity, maxPhysicalVelocity,
                                                        MinThreshold, MaxThreshold)) {}
};

END_CS_NAMESPACE
