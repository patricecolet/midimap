/**
 * @file
 * @brief   The main header file that includes all midimap header files.
 *
 * @author  Patrice Colet
 * @date    2025-02-18
 */


#pragma once
#include <Arduino.h>
#include <AH/Arduino-Wrapper.h>
#include <Wire.h>

// ------------------------------- Main Logic ------------------------------- //
#include <midimap/midimap_class.hpp>

// ------------------------------ MIDI Outputs ------------------------------ //
#include <MIDI_Outputs/CCPotentiometer.hpp>
#include <MIDI_Outputs/CCPotentiometer14.hpp>
#include <MIDI_Outputs/PBPotentiometer.hpp>

#include <MIDI_Outputs/NoteButton.hpp>

#include <MIDI_Outputs/ChannelPressureSensor.hpp>
#include <MIDI_Outputs/PolyAftertouchSensor.hpp>

#include <MIDI_Outputs/Accelerometer3AxisSensor.hpp>
#include <MIDI_Outputs/CCUltrasonic.hpp>
#include <MIDI_Outputs/PBUltrasonic.hpp>
#include <MIDI_Outputs/VelostatNote.hpp>

#include <MIDI_Outputs/NoteButtonInverse.hpp>

#include <MIDI_Outputs/Bankable/CCSmartPotentiometer.hpp>

// ------------------------------- Selectors -------------------------------- //

#include <Selectors/IncrementDecrementSelector.hpp>

// ---------------------------- MIDI Interfaces ----------------------------- //
#include <MIDI_Interfaces/DebugMIDI_Interface.hpp>
#include <MIDI_Interfaces/USBMIDI_Interface.hpp>
#include <MIDI_Interfaces/BluetoothMIDI_Interface.hpp>

// ------------------------- Extended Input Output -------------------------- //
#include <AH/Hardware/ExtendedInputOutput/ExtendedInputOutput.hpp>

// ----------------------------- MIDI Constants ----------------------------- //

#include <MIDI_Constants/Control_Change.hpp>
#include <MIDI_Constants/Notes.hpp>


// ----------------------------- OSC interface ----------------------------- //
#if defined(ESP32) || defined(ESP8266)
#include <OSC_Interfaces/OSCWifi_Interface.hpp>

// ------------------------------ OSC Interfaces ------------------------------ //
#include <OSC_Interfaces/OSCInterface.hpp>
#include <OSC_Interfaces/OSCWifi_Interface.hpp>

// ------------------------------ OSC Senders -------------------------------- //
#include <OSC_Senders/OSCValueSender.hpp>
#include <OSC_Senders/OSCMultiValueSender.hpp>
#include <OSC_Senders/OSCMIDIChannelSender.hpp>
#include <OSC_Senders/OSCSysExSender.hpp>

// ------------------------------ OSC Outputs -------------------------------- //
#include <OSC_Outputs/OSCButton.hpp>
#include <OSC_Outputs/OSCEncoder.hpp>
#include <OSC_Outputs/MIDItoOSC_Converter.hpp>
#include <OSC_Outputs/OSCPotentiometer.hpp>
// ------------------------------ OSC Inputs -------------------------------- //

// ------------------------------ Network ------------------------------------ //
#include <Network/WiFiConnection.hpp>
#endif

BEGIN_CS_NAMESPACE
#ifndef NO_USING_NAMESPACE_AH
USING_AH_NAMESPACE;
#endif
END_CS_NAMESPACE

#ifndef NO_USING_NAMESPACE_CS
USING_CS_NAMESPACE;
#endif

#define CONTROL_SURFACE_VERSION 10000