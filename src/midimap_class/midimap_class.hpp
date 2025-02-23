
#pragma once
/** 
 * @brief   This class ensures initialization, updating, and interaction between
 *          all other classes, it's the glue that holds everything together.
 * 
 * @ingroup midimapModule
 */


//#include <AH/Containers/Updatable.hpp>
#include <AH/Hardware/FilteredAnalog.hpp>
#include <AH/Timing/MillisMicrosTimer.hpp>
//#include <Display/DisplayElement.hpp>
//#include <Display/DisplayInterface.hpp>
#include <MIDI_Interfaces/MIDI_Interface.hpp>
#include <Settings/SettingsWrapper.hpp>

BEGIN_CS_NAMESPACE

using AH::FilteredAnalog;
//using AH::NormalUpdatable;
using AH::Timer;
//using AH::Updatable;
