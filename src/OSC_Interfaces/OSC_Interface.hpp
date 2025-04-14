#pragma once

#if defined(ESP32) || defined(ESP8266)
// This file requires the CNMAT OSC library
// Install it via the Arduino Library Manager: "OSC" by CNMAT
// Or via PlatformIO: pio lib install "CNMAT OSC"

#include <AH/Arduino-Wrapper.h>
#include <AH/Containers/Updatable.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending and receiving OSC messages
 */
class OSCInterface : public AH::Updatable<> {
  public:
    /**
     * @brief Virtual destructor
     */
    virtual ~OSCInterface() = default;

    /**
     * @brief Initialize the OSC connection
     */
    virtual void begin() override = 0;

    /**
     * @brief Update function to process incoming OSC messages
     */
    virtual void update() override = 0;
    
    /**
     * @brief Send an OSC message with a single float value
     * 
     * @param address OSC address pattern
     * @param value Float value to send
     * @return true if sent successfully, false otherwise
     */
    virtual bool sendOSC(const char* address, float value) = 0;

    /**
     * @brief Send an OSC message with multiple float values
     * 
     * @param address OSC address pattern
     * @param values Array of float values
     * @param size Number of values
     * @return true if sent successfully, false otherwise
     */
    virtual bool sendOSC(const char* address, const float* values, size_t size) = 0;
};

END_CS_NAMESPACE

#else
#error "OSC functionality is only available on ESP32 and ESP8266 platforms"
#endif
