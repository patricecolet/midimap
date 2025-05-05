#pragma once

#include <OSC_Interfaces/OSC_Interface.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief Class for sending values as OSC messages
 */
class OSCValueSender {
  public:
    /**
     * @brief Constructor
     * 
     * @param address OSC address pattern to send to
     */
    OSCValueSender(const char* address)
        : _address(address) {}
    
    /**
     * @brief Send a value as an OSC message
     * 
     * @param value Value to send
     * @param interface OSC interface to send through
     * @return true if sent successfully, false otherwise
     */
    bool send(float value, OSCInterface& interface) const {
        return interface.sendOSC(_address, value);
    }
    
    /**
     * @brief Send multiple values as an OSC message
     * 
     * @param values Array of values to send
     * @param size Number of values
     * @param interface OSC interface to send through
     * @return true if sent successfully, false otherwise
     */
    bool send(const float* values, size_t size, OSCInterface& interface) const {
        return interface.sendOSC(_address, values, size);
    }
    
    /**
     * @brief Get the OSC address pattern
     * 
     * @return const char* OSC address pattern
     */
    const char* getAddress() const {
        return _address;
    }
    
  private:
    const char* _address;
};

END_CS_NAMESPACE
