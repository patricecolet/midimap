#pragma once

#include <AH/Containers/Updatable.hpp>
#include "../OSC_Interfaces/OSCWifi_Interface.hpp"
#include <MIDI_Interfaces/MIDI_Interface.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief Class for sending MIDI SysEx messages as OSC
 */
class OSCSysEx_send : public AH::Updatable<> {
  public:
    /**
     * @brief Constructor for OSCSysEx_send
     * 
     * @param interface Reference to OSCWifi_Interface to send through
     */
    OSCSysEx_send(OSCWifi_Interface &interface)
        : _interface(interface), _changed(false) {}
    
    /**
     * @brief Initialize the OSC SysEx sender
     */
    void begin() override {}
    
    /**
     * @brief Update and send the OSC SysEx message if changed
     */
    void update() override {
        if (_changed) {
            // Convert SysEx to OSC
            // This is a simplified implementation
            char address[32];
            
            // Check if we have enough data to extract manufacturer ID
            if (_message.length > 1) {
                // The first byte after F0 is typically the manufacturer ID
                sprintf(address, "/midi/sysex/%d", _message.data[1]);
            } else {
                // Fallback if message is too short
                sprintf(address, "/midi/sysex");
            }
            
            // In a real implementation, you would convert the SysEx data
            // to appropriate OSC arguments
            _interface.sendOSC(address, 1.0f);
            _changed = false;
        }
    }
    
    /**
     * @brief Set the MIDI SysEx message to send
     * 
     * @param message SysExMessage to send
     */
    void setMessage(SysExMessage message) {
        _message = message;
        _changed = true;
    }
    
  private:
    OSCWifi_Interface& _interface;
    SysExMessage _message;
    bool _changed;
};

END_CS_NAMESPACE
