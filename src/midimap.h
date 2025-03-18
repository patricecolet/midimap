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

#ifdef ESP32
    #include <USB.h>
    #include <USBMIDI.h>
#else
    #include <MIDIUSB.h>
#endif

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

#include <MIDI_Outputs/6-Capteurs.hpp>


// ---------------------------- MIDI Interfaces ----------------------------- //
#include <MIDI_Interfaces/DebugMIDI_Interface.hpp>
#include <MIDI_Interfaces/USBMIDI_Interface.hpp>

// ------------------------- Extended Input Output -------------------------- //
#include <AH/Hardware/ExtendedInputOutput/ExtendedInputOutput.hpp>

// ----------------------------- MIDI Constants ----------------------------- //

#include <MIDI_Constants/Control_Change.hpp>
#include <MIDI_Constants/Notes.hpp>

BEGIN_CS_NAMESPACE
#ifndef NO_USING_NAMESPACE_AH
USING_AH_NAMESPACE;
#endif
END_CS_NAMESPACE

#ifndef NO_USING_NAMESPACE_CS
USING_CS_NAMESPACE;
#endif

#define CONTROL_SURFACE_VERSION 10000