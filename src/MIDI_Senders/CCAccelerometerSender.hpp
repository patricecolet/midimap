#pragma once

#include <AH/Hardware/MMA7660.h>
#include <midimap/midimap_class.hpp> // Include MIDI library
#include <Wire.h>
#include <AH/Filters/Hysteresis.hpp> // Include the hysteresis filter

BEGIN_CS_NAMESPACE

/**
 * @brief Sends MIDI Control Change messages based on 3-axis accelerometer data.
 * 
 * This class uses the MMA7660 accelerometer to read motion data along the X, Y, and Z axes. It maps the raw accelerometer 
 * readings to MIDI Control Change messages and applies a hysteresis filter to avoid sending frequent messages for small 
 * fluctuations in sensor data, ensuring smoother control. Each axis of movement is mapped to a separate MIDI controller.
 * 
 * The accelerometer readings are mapped to a 7-bit range (0-127) to be compatible with the MIDI standard. The hysteresis 
 * filter ensures that MIDI messages are sent only when the accelerometer values change significantly, reducing noise.
 * 
 * @note The hysteresis filter reduces the effective resolution of the sensor readings to 3 bits, helping with stability and 
 *       reducing unnecessary MIDI messages.
 */
class CCAccelerometerSender {
public:
    /**
     * @brief Constructor for CCAccelerometerSender.
     * 
     * Initializes the MIDI addresses for the X, Y, and Z axes, which will be used to send the corresponding MIDI 
     * Control Change messages based on the accelerometer data.
     * 
     * @param addressX MIDI address for the X-axis data.
     * @param addressY MIDI address for the Y-axis data.
     * @param addressZ MIDI address for the Z-axis data.
     */
    CCAccelerometerSender(MIDIAddress addressX, MIDIAddress addressY, MIDIAddress addressZ)
        : _addressX(addressX), _addressY(addressY), _addressZ(addressZ){}

    /// Initializes the accelerometer and prepares it for use.
    void begin() {
        accelerometer.init();
    }

    /**
     * @brief Updates the accelerometer readings and sends MIDI messages based on sensor data.
     * 
     * This method reads the accelerometer values (X, Y, and Z axes), maps them to MIDI range (0-127), 
     * applies hysteresis filtering, and sends MIDI Control Change messages if the values have changed 
     * significantly, as determined by the hysteresis filter.
     */
    void update() {
        int8_t x, y, z;
        accelerometer.getXYZ(&x, &y, &z); // Get accelerometer values

        // Map accelerometer values from raw range (-32 to 31) to MIDI range (0 to 127)
        uint8_t mappedX = map(x, -32, 31, 0, 127); 
        uint8_t mappedY = map(y, -32, 31, 0, 127); 
        uint8_t mappedZ = map(z, -32, 31, 0, 127); 

        // Apply hysteresis filter and send MIDI control change if the value changes
        if (hysteresisX.update(mappedX)) { 
            midimap.sendControlChange(_addressX, hysteresisX.getValue() << 3);
        }
        if (hysteresisY.update(mappedY)) { 
            midimap.sendControlChange(_addressY, hysteresisY.getValue() << 3);
        }
        if (hysteresisZ.update(mappedZ)) { 
            midimap.sendControlChange(_addressZ, hysteresisZ.getValue() << 3);
        }
    }

private:
    MIDIAddress _addressX, _addressY, _addressZ; ///< MIDI addresses for X, Y, and Z axes
    MMA7660 accelerometer; ///< Accelerometer object for reading sensor data
    Hysteresis<3, uint8_t, uint8_t> hysteresisX; ///< Hysteresis filter for X-axis 3 bits reduction
    Hysteresis<3, uint8_t, uint8_t> hysteresisY; ///< Hysteresis filter for Y-axis 3 bits reduction
    Hysteresis<3, uint8_t, uint8_t> hysteresisZ; ///< Hysteresis filter for Z-axis 3 bits reduction
};

END_CS_NAMESPACE

