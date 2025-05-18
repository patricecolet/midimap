#pragma once

#include <midimap/midimap_class.hpp>
#include <AH/Hardware/Ultrasonic.hpp>

BEGIN_CS_NAMESPACE

using AH::Ultrasonic;

/**
 * @brief   Class that sends MIDI control change messages based on ultrasonic sensor readings.
 * 
 * @ingroup MIDI_Senders
 */
class UltrasonicCCSender {
public:
    /**
     * @brief Constructor with default threshold values.
     * @param address MIDI address for sending control change.
     * @param PinList The pin list for the ultrasonic sensor.
     * @param sendInterval Fixed time between MIDI messages in milliseconds.
     */
    UltrasonicCCSender(MIDIAddress address, UltrasonicPinList PinList, uint16_t sendInterval = 50)
            : _address(address), 
              _ultrasonic(PinList.echo, PinList.trigger),
              _minThreshold(100),  // Default min threshold
              _maxThreshold(4000),  // Default max threshold
              _sendInterval(sendInterval),
              _lastSendTime(0)
    {}

    /**
     * @brief Constructor with custom threshold values.
     * @param address MIDI address for sending control change.
     * @param PinList The pin list for the ultrasonic sensor.
     * @param minThreshold The minimum distance threshold in mm.
     * @param maxThreshold The maximum distance threshold in mm.
     * @param sendInterval Fixed time between MIDI messages in milliseconds.
     */
    UltrasonicCCSender(MIDIAddress address, UltrasonicPinList PinList,
                      uint16_t minThreshold, uint16_t maxThreshold, uint16_t sendInterval = 50)
            : _address(address), 
              _ultrasonic(PinList.echo, PinList.trigger),
              _minThreshold(minThreshold),
              _maxThreshold(maxThreshold),
              _sendInterval(sendInterval),
              _lastSendTime(0)
    {}

    void begin() {
        _ultrasonic.begin();
    }

    void update() {
        unsigned long currentTime = millis();
        if (currentTime - _lastSendTime < _sendInterval) {
            return;
        }
        
        uint16_t distance = _ultrasonic.readDistanceMM();
        
        // Map using the threshold values
        int16_t value = map(distance, _minThreshold, _maxThreshold, 127, 0);
        value = constrain(value, 0, 127);

        static int16_t lastvalue = -1; // Invalid initial value to force first send
        if (value != lastvalue) {
            MIDIChannelCable channelCable = {_address.getChannel(), _address.getCableNumber()};
            midimap.sendControlChange(_address, value);
            lastvalue = value;
        }
        
        _lastSendTime = currentTime;
    }

private:
    MIDIAddress _address;   ///< MIDI address for sending key pressure.
    Ultrasonic _ultrasonic; ///< Ultrasonic sensor object.
    uint16_t _minThreshold; ///< Minimum distance threshold in mm.
    uint16_t _maxThreshold; ///< Maximum distance threshold in mm.
    const uint16_t _sendInterval; ///< Fixed time between MIDI messages in milliseconds.
    unsigned long _lastSendTime;  ///< Time of last MIDI message sent.
};

END_CS_NAMESPACE