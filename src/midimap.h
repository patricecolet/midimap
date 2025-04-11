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
#include <MIDI_Outputs/NoteButton.hpp>
#include <MIDI_Outputs/NoteButtonInverse.hpp>
#include <MIDI_Outputs/CCButton.hpp>
#include <MIDI_Outputs/PCButton.hpp>

#include <MIDI_Outputs/NotePotentiometer.hpp>
#include <MIDI_Outputs/NoteVelPotentiometer.hpp>
#include <MIDI_Outputs/NoteRelVelPotentiometer.hpp>
#include <MIDI_Outputs/PCPotentiometer.hpp>
#include <MIDI_Outputs/CPPotentiometer.hpp>
#include <MIDI_Outputs/KPPotentiometer.hpp>

#include <MIDI_Outputs/CCPotentiometer.hpp>
#include <MIDI_Outputs/CCPotentiometer14.hpp>
#include <MIDI_Outputs/PBPotentiometer.hpp>

#include <MIDI_Outputs/CCTouch.hpp>
#include <MIDI_Outputs/PBTouch.hpp>
#include <MIDI_Outputs/KPTouch.hpp>
#include <MIDI_Outputs/NoteTouch.hpp>
#include <MIDI_Outputs/NoteRelVelTouch.hpp>
#include <MIDI_Outputs/NoteVelTouch.hpp>

#include <MIDI_Outputs/Accelerometer3AxisSensor.hpp>

#include <MIDI_Outputs/NoteUltrasonicDistance.hpp>
#include <MIDI_Outputs/CCUltrasonic.hpp>
#include <MIDI_Outputs/KPUltrasonic.hpp>
#include <MIDI_Outputs/PBUltrasonic.hpp>
#include <MIDI_Outputs/CPUltrasonic.hpp>

// #include <MIDI_Outputs/VelostatNote.hpp>
#include <MIDI_Outputs/PiezoNoteSensor.hpp>

#include <MIDI_Outputs/QTouchNote.hpp>

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
#include <MIDI_Constants/Program_Change.hpp>

BEGIN_CS_NAMESPACE
#ifndef NO_USING_NAMESPACE_AH
USING_AH_NAMESPACE;
#endif
END_CS_NAMESPACE

#ifndef NO_USING_NAMESPACE_CS
USING_CS_NAMESPACE;
#endif

#define CONTROL_SURFACE_VERSION 10000