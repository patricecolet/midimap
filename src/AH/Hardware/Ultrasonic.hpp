#pragma once

#include <AH/Settings/NamespaceSettings.hpp>

BEGIN_AH_NAMESPACE
/**
 * @brief Reads distance values from an ultrasonic sensor.
 *
 * This class interfaces with an ultrasonic distance sensor using a single digital pin.
 * It measures the pulse duration and converts it to distance in millimeters.
 */
class Ultrasonic {
public:
    /**
     * @brief Constructor to initialize the ultrasonic sensor.
     * @param PinList The digital pin list connected to the sensor.
     */
    Ultrasonic(pin_t echo_pin, pin_t trigger_pin) : 
        _echo_pin(echo_pin), _trigger_pin(trigger_pin), _lastValidDistance(0) {}

    /**
     * @brief Initializes the sensor pin list.
     */
    void begin() {
        pinMode(_echo_pin, INPUT);
        pinMode(_trigger_pin, OUTPUT);
    }

    /**
     * @brief Reads the distance from the sensor.
     * @return Distance in millimeters (mm).
     */
    uint16_t readDistanceMM() {
        digitalWrite(_trigger_pin, LOW);
        delayMicroseconds(2);
        digitalWrite(_trigger_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trigger_pin, LOW);

        long duration = pulseIn(_echo_pin, HIGH, 30000); // Get pulse duration

        if (duration == 0) {
            return _lastValidDistance; // Return last good reading instead of 0
        }
        uint16_t distance = (duration / 2) * 0.343; // Convert to mm

        if (distance > 0 && distance < 4000){ // Filter out extreme values{
            _lastValidDistance = distance; // Save as last valid reading
        }

        return _lastValidDistance;
    }

private:
    pin_t _echo_pin;                  ///< Digital pin connected to the sensor.
    pin_t _trigger_pin;                  ///< Digital pin connected to the sensor.
    uint16_t _lastValidDistance; ///< Stores the last valid distance to avoid zero readings.
};

END_AH_NAMESPACE
