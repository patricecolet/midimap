#pragma once

#include <Network/WiFiConnection.hpp>
#include "OSC_Interface.hpp"
#include <MIDI_Interfaces/MIDI_Interface.hpp>
#include <WiFiUdp.h>
#include <OSCMessage.h>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending MIDI messages over OSC via WiFi
 * 
 * @ingroup MIDIInterfaces
 */
class OSCWifi_Interface : public MIDI_Interface, public WiFiConnection, public OSCInterface {
  public:
    /**
     * @brief Constructor for OSCWifi_Interface
     * 
     * @param host Target IP address
     * @param port Target UDP port
     * @param ssid WiFi network name (optional)
     * @param pwd WiFi password (optional)
     */
    OSCWifi_Interface(const char *host, uint16_t port, 
                      const char *ssid = nullptr, const char *pwd = nullptr)
        : WiFiConnection(ssid, pwd), _host(host), _port(port) {}

    /**
     * @brief Initialize the WiFi and OSC connections
     */
    void begin() override {
        WiFiConnection::begin();
        if (isConnected()) {
            _udp.begin(_port);
        }
    }

    /**
     * @brief Update function to check WiFi connection and process OSC messages
     */
    void update() override {
        WiFiConnection::update();
        if (isConnected()) {
            // Process incoming OSC messages if needed
            int packetSize = _udp.parsePacket();
            if (packetSize > 0) {
                // Handle incoming OSC messages
                // This could be expanded to parse OSC messages
            }
        }
    }
    
    /**
     * @brief Send an OSC message with a single float value
     * 
     * @param address OSC address pattern
     * @param value Float value to send
     * @return true if sent successfully, false otherwise
     */
    bool sendOSC(const char* address, float value) override {
        if (!isConnected()) return false;
        
        OSCMessage msg(address);
        msg.add(value);
        
        _udp.beginPacket(_host, _port);
        msg.send(_udp);
        return _udp.endPacket() > 0;
    }
    
    /**
     * @brief Send an OSC message with multiple float values
     * 
     * @param address OSC address pattern
     * @param values Array of float values
     * @param size Number of values
     * @return true if sent successfully, false otherwise
     */
    bool sendOSC(const char* address, const float* values, size_t size) override {
        if (!isConnected()) return false;
        
        OSCMessage msg(address);
        for (size_t i = 0; i < size; i++) {
            msg.add(values[i]);
        }
        
        _udp.beginPacket(_host, _port);
        msg.send(_udp);
        return _udp.endPacket() > 0;
    }

  protected:
    // Implementation of MIDI_Interface virtual methods
    void sendChannelMessageImpl(ChannelMessage msg) override {
        // Convert MIDI Channel Message to OSC and send
        char address[32];
        sprintf(address, "/midi/channel/%d/%d", msg.getChannel().getOneBased(), static_cast<int>(msg.getMessageType()));
        
        float values[2] = {
            static_cast<float>(msg.getData1()),
            static_cast<float>(msg.getData2())
        };
        
        sendOSC(address, values, 2);
    }
    
    void sendSysCommonImpl(SysCommonMessage msg) override {
        // Convert MIDI SysCommon Message to OSC and send
        char address[32];
        sprintf(address, "/midi/syscommon/%d", static_cast<int>(msg.getMessageType()));
        
        float values[2] = {
            static_cast<float>(msg.getData1()),
            static_cast<float>(msg.getData2())
        };
        
        sendOSC(address, values, 2);
    }
    
    void sendSysExImpl(SysExMessage message) override {
        // Convert MIDI SysEx Message to OSC and send
        char address[32];
        if (message.length > 1) {
            sprintf(address, "/midi/sysex/%d", message.data[1]); // Le premier octet après F0 est l'ID du fabricant
        } else {
            sprintf(address, "/midi/sysex");
        }
        sendOSC(address, 1.0f);
    }
    
    void sendRealTimeImpl(RealTimeMessage msg) override {
        // Convert MIDI RealTime Message to OSC and send
        char address[32];
        sprintf(address, "/midi/realtime/%d", static_cast<int>(msg.getMessageType()));
        
        sendOSC(address, 1.0f); // Just send a trigger
    }
    
    void sendNowImpl() override {
        // No buffering in this implementation
    }
    
    // Implementation of MIDIStaller virtual method
    void handleStall() override {
        // Handle stall condition - this could be a no-op or log a message
        Serial.println("MIDI stall detected in OSCWifi_Interface");
    }

  private:
    const char* _host;
    uint16_t _port;
    WiFiUDP _udp;
};

END_CS_NAMESPACE
