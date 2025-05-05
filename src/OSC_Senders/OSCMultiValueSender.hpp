#pragma once

#include <AH/Arduino-Wrapper.h>
#include "../OSC_Interfaces/OSCInterface.hpp"

BEGIN_CS_NAMESPACE

/**
 * @brief   Class for sending multi-value OSC messages
 */
class OSCMultiValueSender {
  public:
    /**
     * @brief Constructor
     * 
     * @param address OSC address pattern
     */
    OSCMultiValueSender(const char* address) : address(address) {}
    
    /**
     * @brief Send multiple values through the given OSC interface
     * 
     * @param values Array of values to send
     * @param size Number of values
     * @param oscInterface OSC interface to send through
     * @return true if sent successfully
     */
    bool send(const float* values, size_t size, OSCInterface& oscInterface) const {
        return oscInterface.sendOSC(address, values, size);
    }
    
    /**
     * @brief Get the OSC address
     * 
     * @return OSC address pattern
     */
    const char* getAddress() const {
        return address;
    }
    
  private:
    const char* address;
};

END_CS_NAMESPACE
