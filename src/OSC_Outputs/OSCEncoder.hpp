#pragma once

#include <AH/Hardware/IncrementDecrementButtons.hpp>
#include <AH/Containers/Updatable.hpp>
#include <OSC_Senders/OSCValueSender.hpp>
#include <OSC_Interfaces/OSC_Interface.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class for sending encoder values as OSC messages
 */
class OSCEncoder : public AH::Updatable<> {
  public:
    /**
     * @brief Constructor
     * 
     * @param pinA First pin of the encoder
     * @param pinB Second pin of the encoder
     * @param sender OSC value sender to use
     * @param oscInterface OSC interface to send through
     * @param initialValue Initial value of the encoder
     * @param increment Value to increment/decrement by
     * @param minimum Minimum value
     * @param maximum Maximum value
     */
    OSCEncoder(pin_t pinA, pin_t pinB, 
               const OSCValueSender& sender, OSCInterface& oscInterface,
               int16_t initialValue = 0, int16_t increment = 1,
               int16_t minimum = 0, int16_t maximum = 127)
        : encoder(pinA, pinB), 
          sender(sender), 
          oscInterface(oscInterface),
          value(initialValue),
          increment(increment),
          minimum(minimum),
          maximum(maximum) {}
    
    /**
     * @brief Initialize the encoder
     */
    void begin() override {
        encoder.begin();
        // Send initial value
        sendValue();
    }
    
    /**
     * @brief Update and send the encoder value if changed
     */
    void update() override {
        int8_t delta = encoder.update();
        
        if (delta != 0) {
            // Update value with increment
            int16_t newValue = value + (delta * increment);
            
            // Constrain to range
            newValue = newValue < minimum ? minimum : newValue;
            newValue = newValue > maximum ? maximum : newValue;
            
            // Only send if value changed
            if (newValue != value) {
                value = newValue;
                sendValue();
            }
        }
    }
    
    /**
     * @brief Get the current value
     * 
     * @return Current value
     */
    int16_t getValue() const {
        return value;
    }
    
    /**
     * @brief Set the current value
     * 
     * @param newValue New value
     */
    void setValue(int16_t newValue) {
        // Constrain to range
        newValue = newValue < minimum ? minimum : newValue;
        newValue = newValue > maximum ? maximum : newValue;
        
        // Only send if value changed
        if (newValue != value) {
            value = newValue;
            sendValue();
        }
    }
    
  private:
    /**
     * @brief Send the current value as an OSC message
     */
    void sendValue() {
        // Normalize value to 0.0-1.0 range
        float normalizedValue = static_cast<float>(value - minimum) / (maximum - minimum);
        sender.send(normalizedValue, oscInterface);
    }
    
    AH::IncrementDecrementButtons encoder;
    OSCValueSender sender;
    OSCInterface& oscInterface;
    int16_t value;
    int16_t increment;
    int16_t minimum;
    int16_t maximum;
};

END_CS_NAMESPACE
