/** 
 * This example demonstrates converting MIDI messages to OSC with custom addresses.
 *
 * @boards  ESP32
 */

#include <midimap.h> // Include the midimap library

// WiFi credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// Target IP address and port for OSC messages
const char* targetIP = "192.168.1.100";
const uint16_t targetPort = 8000;

// Create MIDI interface
USBMIDI_Interface midi;

// Create OSC interface
OSCWifi_Interface oscWifi {targetIP, targetPort, ssid, password};

// Create MIDI to OSC converter
MIDItoOSC_Converter midiToOSC {midi, oscWifi};

void setup() {
  Serial.begin(115200);
  
  // Customize OSC addresses
  midiToOSC.setNoteOnAddress("/note/on/%d");
  midiToOSC.setNoteOffAddress("/note/off/%d");
  midiToOSC.setCCAddress("/control/%d/%d");
  
  // Initialize midimap
  midimap.begin();
  
  Serial.println("Custom MIDI to OSC converter started");
}

void loop() {
  midimap.loop(); // Update the midimap
}
