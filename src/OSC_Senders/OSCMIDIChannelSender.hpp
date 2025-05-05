#pragma once

#include <AH/Arduino-Wrapper.h>
#include "../OSC_Interfaces/OSCInterface.hpp"
#include <MIDI_Interfaces/MIDI_Interface.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class for sending MIDI Channel messages as OSC
 */
class OSCMIDIChannelSender {
  public:
    /**
     * @brief Constructor
     * 
     * @param addressPrefix Prefix for OSC address (default: "/midi/channel")
     */
    OSCMIDIChannelSender(const char* addressPrefix = "/midi/channel") 
        : addressPrefix(addressPrefix) {}
    
    /**
     * @brief Send a MIDI Channel message through the given OSC interface
     * 
     * @param message MIDI Channel message to send
     * @param oscInterface OSC interface to send through
     * @return true if sent successfully
     */
    bool send(ChannelMessage message, OSCInterface& oscInterface) const {
        char address[64];
        sprintf(address, "%s/%d/%d", addressPrefix, message.getChannel(), message.getMessageType());
        
        float values[2] = {
            static_cast<float>(message.getData1()),
            static_cast<float>(message.getData2())
        };
        
        return oscInterface.sendOSC(address, values, 2);
    }
    
  private:
    const char* addressPrefix;
};

END_CS_NAMESPACE
