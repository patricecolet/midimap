#pragma once

#include <MIDI_Senders/KeySender.hpp>
#include <MIDI_Interfaces/USBMIDI_Interface.hpp>
#include <MIDI_Outputs/Abstract/MIDIFilteredAnalog.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class to send MIDI aftertouch using a single SIG pin from an ultrasonic distance sensor.
 *
 * This class will read distance values from the ultrasonic sensor connected to a single digital pin (SIG).
 * It calculates the distance by measuring the pulse duration and sends MIDI channel pressure (aftertouch)
 * based on the measured distance.
 *
 * @ingroup MIDIOutputElements
 */

class AftertouchUltrasonic : public KeySender
{
public:
  AftertouchUltrasonic(pin_t pin, MIDIAddress address)
      : KeySender(address, pin) {}

  void begin() {
    KeySender::begin(); // Initialize pin for sensor
  }

  void update() 
  {
    KeySender::update(); // Update aftertouch value based on sensor
  }
};

END_CS_NAMESPACE
