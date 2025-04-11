#pragma once

#include <AH/Hardware/FilteredTouch.hpp>
#include <Def/Def.hpp>
#include <MIDI_Outputs/Abstract/MIDIOutputElement.hpp>

BEGIN_CS_NAMESPACE

/**
 * @brief   A class for capacitive touch sensors that send MIDI events.
 *
 * The touch input is filtered using adaptive baseline tracking with
 * multi-stage smoothing implemented in the FilteredTouch class.
 *
 * @see     FilteredTouch
 */
template <class Sender>
class MIDIFilteredTouch : public MIDIOutputElement
{
protected:
  /**
   * @brief   Construct a new MIDIFilteredTouch.
   *
   * @param   touchPin
   *          The ESP32 touch pin number (T0-T9).
   * @param   address
   *          The MIDI address to send to.
   * @param   sender
   *          The MIDI sender to use.
   */
  MIDIFilteredTouch(int touchPin, MIDIAddress address,
                    const Sender &sender)
      : FilteredTouch(touchPin), address(address), sender(sender) {}

public:
  void begin() final override
  {
    FilteredTouch.begin();
    FilteredTouch.resetToCurrentValue();
  }

  void update() final override
  {
    if (FilteredTouch.update())
    {
      int value = FilteredTouch.getValue();
    
    // Send the value to the MIDI sender
    sender.send(value, address);
    }
  }

  /// Get the MIDI address.
  MIDIAddress getAddress() const { return this->address; }
  /// Set the MIDI address.
  void setAddress(MIDIAddress address) { this->address = address; }

private:
  AH::FilteredTouch<Sender::precision()> FilteredTouch;
  MIDIAddress address;

public:
  Sender sender;
};

END_CS_NAMESPACE
