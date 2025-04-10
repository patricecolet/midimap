#pragma once

#include "AH/Settings/NamespaceSettings.hpp"

#ifdef ARDUINO_ARCH_SAMD
#include <Adafruit_FreeTouch.h>
#endif

BEGIN_AH_NAMESPACE

/**
 * @brief Reads touch values from capacitive touch sensors.
 *
 * This class interfaces with touch sensors on different platforms (SAMD, ESP32)
 * and provides consistent readings with dynamic range calibration.
 */
class Touch {
public:
    /**
     * @brief Constructor for SAMD architecture.
     * 
     * @param pin The touch pin to read from.
     * @param oversample Oversampling setting for the touch sensor.
     * @param resistor Series resistor setting for the touch sensor.
     * @param freqMode Frequency mode setting for the touch sensor.
     */
    #ifdef ARDUINO_ARCH_SAMD
    Touch(pin_t pin, oversample_t oversample, series_resistor_t resistor, freq_mode_t freqMode)
        : _pin(pin), _oversample(oversample), _resistor(resistor), _freqMode(freqMode),
          _qtouch(pin, oversample, resistor, freqMode) {}
    #elif defined(ESP32)
    /**
     * @brief Constructor for ESP32 architecture.
     * 
     * @param pin The touch pin to read from.
     */
    Touch(pin_t pin) : _pin(pin) {}
    #endif

    /**
     * @brief Initializes the touch sensor.
     */
    void begin() {
        #ifdef ARDUINO_ARCH_SAMD
        _qtouch.begin();
        #endif
        // ESP32 touch pins don't need initialization
        
        // Initialize min/max values for dynamic range
        _minVal = 65535;
        _maxVal = 0;
    }

    /**
     * @brief Reads the raw touch value from the sensor.
     * 
     * @return Raw touch value.
     */
    uint16_t readRaw() {
        #ifdef ARDUINO_ARCH_SAMD
        return _qtouch.measure();
        #elif defined(ESP32)
        return touchRead(_pin);
        #else
        return 0; // Default for unsupported platforms
        #endif
    }

    /**
     * @brief Reads the touch value and maps it to a 7-bit MIDI value (0-127).
     * 
     * @return Mapped touch value (0-127).
     */
    uint8_t read() {
        uint16_t rawValue = readRaw();

        // Update min/max for dynamic range calibration
        if (rawValue < _minVal)
            _minVal = rawValue;
        if (rawValue > _maxVal)
            _maxVal = rawValue;

        // Map using dynamic range
        #ifdef ARDUINO_ARCH_SAMD
        return map(rawValue, _minVal, _maxVal, 0, 127);
        #elif defined(ESP32)
        return map(rawValue, 9000, 80000, 0, 127); // ESP32 specific range
        #else
        return 0; // Default for unsupported platforms
        #endif
    }

    /**
     * @brief Checks if the touch value exceeds a threshold.
     * 
     * @param threshold The threshold to compare against.
     * @return True if the touch value exceeds the threshold.
     */
    bool isPressed(uint8_t threshold) {
        return read() >= threshold;
    }

private:
    pin_t _pin;                  ///< Touch pin.
    uint16_t _minVal;            ///< Minimum value for dynamic range.
    uint16_t _maxVal;            ///< Maximum value for dynamic range.

    #ifdef ARDUINO_ARCH_SAMD
    oversample_t _oversample;    ///< Oversampling setting (SAMD only).
    series_resistor_t _resistor; ///< Series resistor setting (SAMD only).
    freq_mode_t _freqMode;       ///< Frequency mode setting (SAMD only).
    Adafruit_FreeTouch _qtouch;  ///< FreeTouch instance (SAMD only).
    #endif
};

END_AH_NAMESPACE
