#pragma once

#include <MIDI_Senders/CCAccelerometerSender.hpp> // Use the new sender

BEGIN_CS_NAMESPACE

/**
 * @brief 3-axis accelerometer sensor with hysteresis filtering and MIDI output.
 * 
 * This class extends the `CCAccelerometerSender` to send MIDI messages based on 
 * 3-axis accelerometer data. It allows for dynamic control of MIDI parameters 
 * using accelerometer data for real-time interaction with your DAW.
 * 
 * The class supports three axes of movement: X, Y, and Z. Each axis corresponds 
 * to a different MIDI controller value, enabling you to map accelerometer 
 * movements to specific parameters in your DAW (e.g., volume, pitch, etc.).
 * 
 * The accelerometer data is filtered using hysteresis techniques to avoid sending 
 * too many messages for small changes in sensor values, providing smoother 
 * and more expressive control.
 * 
 * @note The sensor uses **hysteresis filtering** to smooth out small fluctuations 
 *       in sensor readings before sending MIDI messages.
 *
 * @see `CCAccelerometerSender` for details on how to map the accelerometer 
 *      data to MIDI controllers.
 */
class Accelerometer3AxisSensor : public CCAccelerometerSender, public Updatable<>
{
public:
    /**
     * @brief Constructor for Accelerometer3AxisSensor.
     * 
     * Initializes the sensor with the given MIDI addresses for the X, Y, 
     * and Z axes. These addresses will be used to send the accelerometer data 
     * as MIDI Control Change messages.
     * 
     * @param addressX MIDI address for the X-axis data.
     * @param addressY MIDI address for the Y-axis data.
     * @param addressZ MIDI address for the Z-axis data.
     */
    Accelerometer3AxisSensor(MIDIAddress addressX, MIDIAddress addressY, MIDIAddress addressZ, uint8_t range)
        : CCAccelerometerSender(addressX, addressY, addressZ, range) {}

    /// Initializes the accelerometer sensor and sets up the necessary communication.
    void begin() {
        CCAccelerometerSender::begin();
    }

    /// Updates the sensor readings and sends MIDI messages if necessary.
    /// This method filters the accelerometer data and transmits it as MIDI messages.
    void update() {
        CCAccelerometerSender::update();
    }
};

END_CS_NAMESPACE



