#pragma once

#include <MIDI_Senders/QTouchSender.hpp>

#if defined(ARDUINO_ARCH_SAMD) || defined(ESP32)
BEGIN_CS_NAMESPACE

/**
 * @brief   A class for sending **Polyphonic Aftertouch** messages based on an
 *          analog input from a **QTouch sensor**.
 *
 * This class reads analog input, applies filtering, and sends MIDI
 * **Polyphonic Aftertouch** (Poly Pressure) messages, making it ideal
 * for expressive MIDI controllers.
 */
class QTouchNote : public QTouchSender, public Updatable<> {
public:
  /**
   * @brief   Create a new **QTouchNote** object with the given QTouch pin,
   *          note number, and MIDI channel.
   *
   * @param   analogPin
   *          The analog input pin connected to QTouch.
   * @param   address
   *          The MIDI address containing the note and channel.
   * @param   TriggerValue
   *          The threshold where **Polyphonic Aftertouch** begins.
   * @param   MinNoteThreshold
   *          The minimum value required for the note to activate.
   */
  #ifdef ARDUINO_ARCH_SAMD
  QTouchNote(pin_t analogPin, MIDIAddress address, uint8_t TriggerValue, uint8_t MinNoteThreshold, oversample_t OVERSAMPLE, series_resistor_t RESISTOR, freq_mode_t FREQ_MODE)
    : QTouchSender(address, analogPin, TriggerValue, MinNoteThreshold, OVERSAMPLE, RESISTOR, FREQ_MODE) {}
  #elif defined(ESP32)
    QTouchNote(pin_t analogPin, MIDIAddress address, uint8_t TriggerValue, uint8_t MinNoteThreshold)
      : QTouchSender(address, analogPin, TriggerValue, MinNoteThreshold) {}
  #endif

  void begin() { QTouchSender::begin();}

  void update() { QTouchSender::update();}
};

END_CS_NAMESPACE
#endif


