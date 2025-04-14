#pragma once

#include <AH/Hardware/FilteredAnalog.hpp>
#include <AH/Containers/Updatable.hpp>
#include <OSC_Senders/OSCValueSender.hpp>
#include <OSC_Interfaces/OSCInterface.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class for sending potentiometer values as OSC messages
 */
class OSCPotentiometer : public AH::Updatable<> {
  public:
    /**
     * @brief Constructor
     * 
     * @param pin Analog pin to read from
     * @param sender OSC value sender to use
     * @param oscInterface OSC interface to send through
     */
    OSCPotentiometer(pin_t pin, const OSCValueSender& sender, OSCWifi_Interface& oscInterface)
        : analog(pin), sender(sender), oscInterface(oscInterface) {}
    
    /**
     * @brief Initialize the potentiometer
     */
    void begin() override {
        // FilteredAnalog doesn't have a begin() method
        // The ADC is initialized by FilteredAnalog::setupADC() which is called in midimap.begin()
    }
    
    /**
     * @brief Update and send the potentiometer value if changed
     */
    void update() override {
        if (analog.update()) {
            // Get the raw value and normalize it to [0, 1]
            uint16_t rawValue = analog.getValue();
            // For 10-bit ADC (Arduino standard), max value is 1023
            float normalizedValue = static_cast<float>(rawValue) / 1023.0f;
            
            // Send the normalized value
            sender.send(normalizedValue, oscInterface);
        }
    }
    
    /**
     * @brief Get the current raw value
     * 
     * @return uint16_t Current raw value
     */
    uint16_t getValue() const {
        return analog.getValue();
    }
    
    /**
     * @brief Get the current normalized value [0, 1]
     * 
     * @return float Current normalized value
     */
    float getNormalizedValue() const {
        return static_cast<float>(analog.getValue()) / 1023.0f;
    }
    
  private:
    AH::FilteredAnalog<> analog;
    OSCValueSender sender;
    OSCWifi_Interface& oscInterface;
};

END_CS_NAMESPACE