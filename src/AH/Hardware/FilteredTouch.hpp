#pragma once

#include <Arduino.h>
#include <AH/Settings/Warnings.hpp>
AH_DIAGNOSTIC_WERROR() // Enable errors on warnings

BEGIN_AH_NAMESPACE

#ifdef ESP32

/**
 * @brief A class for filtering capacitive touch sensor readings using adaptive 
 * baseline tracking with multi-stage smoothing.
 * 
 * @tparam Precision The precision of the output value (bit depth)
 */
template <uint8_t Precision = 7>
class FilteredTouch {
public:
    /// Constructor
    FilteredTouch(int touchPin) : touchPin(touchPin) {}

    /// Initialize the touch sensor
    void begin() {
        raw = touchRead(touchPin);
        smooth = raw;
        baseline = raw;
        mappedSmooth = 0;
        mappedValue = 0;
        lastUpdateTime = 0;
        initialized = true;
    }

    /// Reset the baseline to the current value
    void resetToCurrentValue() {
        if (!initialized)
            begin();
        raw = touchRead(touchPin);
        smooth = raw;
        baseline = raw;
        mappedSmooth = 0;
        mappedValue = 0;
    }

    /**
     * @brief Update the raw touch value if enough time has passed
     * 
     * @return true if the value changed and was updated, false otherwise
     */
    bool update() {
        if (!initialized)
            begin();

        // Check if enough time has passed since the last update
        unsigned long currentTime = millis();
        if (currentTime - lastUpdateTime < updateInterval) {
            return false; // Not enough time has passed
        }
        
        // Store the last update time
        lastUpdateTime = currentTime;
        
        int oldValue = mappedValue;
        
        // Read the raw touch value
        raw = touchRead(touchPin);
        
        return oldValue != getValue();
    }

    /// Get the current filtered value - calculations happen here
    int getValue() {
        // 1. Smoothing
        smooth = smooth * (1.0f - SMOOTH_COEF) + raw * SMOOTH_COEF;
        
        // 2. Delta calculation
        delta = smooth - baseline;
        if (delta < 0) delta = 0; // Clamp to 0
        
        // 3. Freeze baseline when hand is detected
        if (delta < baselineThreshold) { // Only update baseline when hand is far
            baseline = baseline * (1.0f - BASELINE_COEF) + smooth * BASELINE_COEF;
        }
        
        // 4. Normalize and curve delta
        float normDelta = constrain(delta / DELTA_MAX, 0.0f, 1.0f);
        float curvedDelta = pow(normDelta, 1.0f); // Exponential sensitivity
        
        // 5. Map to output range and smooth
        // Use the template parameter to determine the maximum output value
        float maxValue = (1 << Precision) - 1;
        float mappedRaw = curvedDelta * maxValue;
        mappedSmooth = mappedSmooth * (1.0f - MAPPED_SMOOTH_COEF) + mappedRaw * MAPPED_SMOOTH_COEF;
        mappedValue = round(mappedSmooth);
        
        #ifdef DEBUG_TOUCH
        Serial.print("Raw: "); Serial.print(raw);
        Serial.print("\tSmooth: "); Serial.print(smooth);
        Serial.print("\tBaseline: "); Serial.print(baseline);
        Serial.print("\tDelta: "); Serial.print(delta);
        Serial.print("\tMapped: "); Serial.println(mappedValue);
        #endif
        
        return mappedValue;
    }

    /// Get the raw touch value
    float getRawValue() const {
        return raw;
    }
    
    /// Set the update interval in milliseconds
    void setUpdateInterval(unsigned long interval) {
        updateInterval = interval;
    }

private:
    int touchPin;
    bool initialized = false;
    unsigned long lastUpdateTime = 0;
    
    // Use defined values if available, otherwise use defaults
    #ifndef TOUCH_UPDATE_INTERVAL
    unsigned long updateInterval = 50; // Default 50ms between updates (like delay(50))
    #else
    unsigned long updateInterval = TOUCH_UPDATE_INTERVAL;
    #endif

    // Configurable Parameters
    #ifndef TOUCH_SMOOTH_COEF
    const float SMOOTH_COEF = 0.95f;       // Slower response to raw = smoother signal
    #else
    const float SMOOTH_COEF = TOUCH_SMOOTH_COEF;
    #endif
    
    #ifndef TOUCH_BASELINE_COEF
    const float BASELINE_COEF = 0.01f;     // Baseline tracking speed
    #else
    const float BASELINE_COEF = TOUCH_BASELINE_COEF;
    #endif
    
    #ifndef TOUCH_DELTA_MAX
    const float DELTA_MAX = 4000.0f;       // Maximum expected delta value
    #else
    const float DELTA_MAX = TOUCH_DELTA_MAX;
    #endif
    
    #ifndef TOUCH_MAPPED_SMOOTH_COEF
    const float MAPPED_SMOOTH_COEF = 0.2f; // Smoothing for the final mapped output
    #else
    const float MAPPED_SMOOTH_COEF = TOUCH_MAPPED_SMOOTH_COEF;
    #endif
    
    #ifndef TOUCH_BASELINE_THRESHOLD
    float baselineThreshold = 100.0f; // Threshold for freezing baseline updates
    #else
    float baselineThreshold = TOUCH_BASELINE_THRESHOLD;
    #endif

    // Runtime Variables
    float raw = 0;
    float smooth = 0;
    float baseline = 0;
    float delta = 0;
    float mappedSmooth = 0;
    int mappedValue = 0;
};

#else
// Empty class for non-ESP32 platforms to avoid compilation errors
template <uint8_t Precision = 7>
class FilteredTouch {
public:
    FilteredTouch(int) {}
    void begin() {}
    void resetToCurrentValue() {}
    bool update() { return false; }
    int getValue() { return 0; }
    float getRawValue() const { return 0; }
    void setUpdateInterval(unsigned long) {}
};
#endif // ESP32

END_AH_NAMESPACE

AH_DIAGNOSTIC_POP()
