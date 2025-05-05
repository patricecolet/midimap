#pragma once

#if defined(ESP32) || defined(ESP8266)

#include <AH/Containers/Updatable.hpp>
#include <MIDI_Interfaces/MIDI_Interface.hpp>
#include <MIDI_Interfaces/MIDI_Callbacks.hpp>
#include <OSC_Interfaces/OSCWifi_Interface.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Simple class for converting MIDI messages to OSC
 */
class MIDItoOSC_Converter : public AH::Updatable<>, public MIDI_Callbacks {
  public:
    /**
     * @brief Constructor
     * 
     * @param midiInterface MIDI interface to read from
     * @param oscInterface OSC interface to send through
     */
    MIDItoOSC_Converter(MIDI_Interface &midiInterface, OSCWifi_Interface &oscInterface)
        : _midiInterface(midiInterface), _oscInterface(oscInterface) {
        
        // Register this object as the callback handler for the MIDI interface
        _midiInterface.setCallbacks(this);
        
        // Set default address patterns
        _noteOnAddress = "/midi/noteon/%d";
        _noteOffAddress = "/midi/noteoff/%d";
        _ccAddress = "/midi/cc/%d/%d";
        _pitchBendAddress = "/midi/pitchbend/%d";
        _pressureAddress = "/midi/pressure/%d";
        _programAddress = "/midi/program/%d";
    }
    
    /**
     * @brief Initialize the converter
     */
    void begin() override {
        // Nothing to do here
    }
    
    /**
     * @brief Update and process MIDI messages
     */
    void update() override {
        // Process any pending MIDI messages
        _midiInterface.update();
    }
    
    /**
     * @brief Set the OSC address pattern for Note On messages
     * 
     * @param address OSC address pattern (must include %d for channel)
     */
    void setNoteOnAddress(const char* address) {
        _noteOnAddress = address;
    }
    
    /**
     * @brief Set the OSC address pattern for Note Off messages
     * 
     * @param address OSC address pattern (must include %d for channel)
     */
    void setNoteOffAddress(const char* address) {
        _noteOffAddress = address;
    }
    
    /**
     * @brief Set the OSC address pattern for Control Change messages
     * 
     * @param address OSC address pattern (must include %d for channel and %d for controller)
     */
    void setCCAddress(const char* address) {
        _ccAddress = address;
    }
    
    /**
     * @brief Set the OSC address pattern for Pitch Bend messages
     * 
     * @param address OSC address pattern (must include %d for channel)
     */
    void setPitchBendAddress(const char* address) {
        _pitchBendAddress = address;
    }
    
    /**
     * @brief Set the OSC address pattern for Channel Pressure messages
     * 
     * @param address OSC address pattern (must include %d for channel)
     */
    void setPressureAddress(const char* address) {
        _pressureAddress = address;
    }
    
    /**
     * @brief Set the OSC address pattern for Program Change messages
     * 
     * @param address OSC address pattern (must include %d for channel)
     */
    void setProgramAddress(const char* address) {
        _programAddress = address;
    }
    
    // MIDI_Callbacks implementation
    void onChannelMessage(MIDI_Interface &, ChannelMessage message) override {
        uint8_t channel = message.getChannel().getOneBased();
        auto messageType = message.getMessageType();
        
        char address[64];
        
        switch (messageType) {
            case MIDIMessageType::NOTE_ON:
                sprintf(address, _noteOnAddress, channel);
                {
                    float values[2] = {
                        static_cast<float>(message.getData1()),
                        static_cast<float>(message.getData2()) / 127.0f
                    };
                    _oscInterface.sendOSC(address, values, 2);
                }
                break;
                
            case MIDIMessageType::NOTE_OFF:
                sprintf(address, _noteOffAddress, channel);
                {
                    float values[2] = {
                        static_cast<float>(message.getData1()),
                        0.0f  // Velocity 0 for note off
                    };
                    _oscInterface.sendOSC(address, values, 2);
                }
                break;
                
            case MIDIMessageType::CONTROL_CHANGE:
                sprintf(address, _ccAddress, channel, message.getData1());
                _oscInterface.sendOSC(address, static_cast<float>(message.getData2()) / 127.0f);
                break;
                
            case MIDIMessageType::PITCH_BEND:
                sprintf(address, _pitchBendAddress, channel);
                {
                    // Combine the two 7-bit values into one 14-bit value
                    uint16_t bendValue = (message.getData2() << 7) | message.getData1();
                    float normalizedBend = static_cast<float>(bendValue) / 8192.0f - 1.0f; // Range -1.0 to +1.0
                    
                    _oscInterface.sendOSC(address, normalizedBend);
                }
                break;
                
            case MIDIMessageType::CHANNEL_PRESSURE:
                sprintf(address, _pressureAddress, channel);
                _oscInterface.sendOSC(address, static_cast<float>(message.getData1()) / 127.0f);
                break;
                
            case MIDIMessageType::PROGRAM_CHANGE:
                sprintf(address, _programAddress, channel);
                _oscInterface.sendOSC(address, static_cast<float>(message.getData1()));
                break;
                
            default:
                // Other message types not handled
                break;
        }
    }
    
    void onSysExMessage(MIDI_Interface &, SysExMessage message) override {
        // SysEx messages not handled in this simple converter
    }
    
    void onSysCommonMessage(MIDI_Interface &, SysCommonMessage message) override {
        // System Common messages not handled in this simple converter
    }
    
    void onRealTimeMessage(MIDI_Interface &, RealTimeMessage message) override {
        // Real-Time messages not handled in this simple converter
    }
    
  private:
    MIDI_Interface& _midiInterface;
    OSCWifi_Interface& _oscInterface;
    
    // OSC address patterns
    const char* _noteOnAddress;
    const char* _noteOffAddress;
    const char* _ccAddress;
    const char* _pitchBendAddress;
    const char* _pressureAddress;
    const char* _programAddress;
};

END_CS_NAMESPACE

#endif // defined(ESP32) || defined(ESP8266)
