#pragma once

#include <MIDI_Outputs/Abstract/MIDIFilteredTouch.hpp>
#include <MIDI_Senders/ContinuousPCSender.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI Program Change messages based on an
 *          ESP32 capacitive touch sensor input with a threshold trigger.
 * 
 * A Program Change event is sent when the touch sensor value rises above
 * the trigger threshold, allowing you to switch between different instrument
 * sounds, patches, or presets in your synthesizer or DAW.
 * 
 * @ingroup MIDIOutputElements
 */
class PCTouch : public MIDIFilteredTouch<ContinuousPCSender> {
  public:
    /**
     * @brief   Create a new PCTouch object with the given touch pin, 
     *          program number, channel, and trigger threshold.
     * 
     * @param   pin
     *          The ESP32 touch pin to read from.
     * @param   address
     *          The MIDI address containing the program number [0, 127], 
     *          channel [Channel_1, Channel_16], and optional cable number 
     *          [Cable_1, Cable_16].
     * @param   triggerValue
     *          The threshold value [0, 127] at which to send the Program Change.
     */
    PCTouch(pin_t pin, MIDIAddress address, uint8_t triggerValue)
        : MIDIFilteredTouch(pin, address, ContinuousPCSender(triggerValue)) {}

    /**
     * @brief   Create a new PCTouch object with the given touch pin, 
     *          program number, channel, trigger threshold, and input range.
     * 
     * @param   pin
     *          The ESP32 touch pin to read from.
     * @param   address
     *          The MIDI address containing the program number [0, 127], 
     *          channel [Channel_1, Channel_16], and optional cable number 
     *          [Cable_1, Cable_16].
     * @param   triggerValue
     *          The threshold value [0, 127] at which to send the Program Change.
     * @param   minThreshold
     *          The minimum value of the touch sensor [0, 127].
     * @param   maxThreshold
     *          The maximum value of the touch sensor [0, 127].
     */
    PCTouch(pin_t pin, MIDIAddress address, uint8_t triggerValue, 
                    uint8_t MinThreshold, uint8_t MaxThreshold)
        : MIDIFilteredTouch(pin, address, 
                    ContinuousPCSender(triggerValue, MinThreshold, MaxThreshold)) {}
};

END_CS_NAMESPACE
