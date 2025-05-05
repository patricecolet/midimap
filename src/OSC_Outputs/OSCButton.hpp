#pragma once

#include <AH/Hardware/Button.hpp>
#include <AH/Containers/Updatable.hpp>
#include <OSC_Senders/OSCValueSender.hpp>
#include <OSC_Interfaces/OSC_Interface.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   Class for sending button state as OSC messages
 */
class OSCButton : public AH::Updatable<> {
  public:
    /**
     * @brief Constructor
     * 
     * @param pin Digital pin to read from
     * @param sender OSC value sender to use
     * @param oscInterface OSC interface to send through
     */
    OSCButton(pin_t pin, const OSCValueSender& sender, OSCInterface& oscInterface)
        : button(pin), sender(sender), oscInterface(oscInterface) {}
    
    /**
     * @brief Initialize the button
     */
    void begin() override {
        button.begin();
    }
    
    /**
     * @brief Update and send the button state if changed
     */
    void update() override {
        AH::Button::State state = button.update();
        
        if (state == AH::Button::Falling) {
            sender.send(1.0f, oscInterface);
        } else if (state == AH::Button::Rising) {
            sender.send(0.0f, oscInterface);
        }
    }
    
  private:
    AH::Button button;
    OSCValueSender sender;
    OSCInterface& oscInterface;
};

END_CS_NAMESPACE
