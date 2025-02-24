/**
 * @file
 * @brief   The main header file that includes all midimap header files.
 *
 * @author  Patrice Colet
 * @date    2025-02-18
 */


#pragma once
#include <Arduino.h>

#include <MIDIUSB.h>

// ------------------------------- Main Logic ------------------------------- //
#include <midimap_class/midimap_class.hpp>

// ------------------------------ MIDI Outputs ------------------------------ //
#include <MIDI_outputs/CCPotentiometer.hpp>

#include <MIDI_outputs/NoteButton.hpp>

// ---------------------------- MIDI Interfaces ----------------------------- //
#include <MIDI_Interfaces/DebugMIDI_Interface.hpp>
#include <MIDI_Interfaces/USBMIDI_Interface.hpp>

// ------------------------- Extended Input Output -------------------------- //
#include <AH/Hardware/ExtendedInputOutput/ExtendedInputOutput.hpp>

// ----------------------------- MIDI Constants ----------------------------- //

#include <MIDI_Constants/Control_Change.hpp>

BEGIN_CS_NAMESPACE
#ifndef NO_USING_NAMESPACE_AH
USING_AH_NAMESPACE;
#endif
END_CS_NAMESPACE

#ifndef NO_USING_NAMESPACE_CS
USING_CS_NAMESPACE;
#endif

#define CONTROL_SURFACE_VERSION 10000