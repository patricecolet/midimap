/**
 * This example demonstrates how to convert MIDI messages to OSC messages
 * and send them over WiFi.
 *
 * @boards  ESP32
 * 
 * Behavior
 * --------
 * 
 * - Connects to WiFi network
 * - Receives MIDI messages from USB MIDI
 * - Converts MIDI messages to OSC format
 * - Sends OSC messages to the specified IP address and port
 * 
 * OSC Message Format
 * -----------------
 * 
 * - Note messages: /midi/note/[channel] [note] [velocity]
 * - CC messages: /midi/cc/[channel]/[cc] [value]
 * - Pitch bend: /midi/pitchbend/[channel] [value]
 * - Channel pressure: /midi/pressure/[channel] [value]
 * - Program change: /midi/program/[channel] [program]
 * 
 * Written by Patrice Colet, 2025-04-06
 */

#include <midimap.h>

// WiFi network credentials
const char* ssid = "YourWiFiNetwork";
const char* password = "YourWiFiPassword";

// OSC destination
const char* oscIP = "192.168.1.100";
const uint16_t oscPort = 8000;

// Create a WiFi connection
WiFiConnection wifiConn(ssid, password);

// Create MIDI interfaces
USBMIDI_Interface midi;

// Create OSC interface
OSCWifi_Interface oscInterface(oscIP, oscPort);

// Create MIDI to OSC converter
MIDItoOSC_Converter midiToOsc(midi, oscInterface);

void setup() {
  Serial.begin(115200);
  
  // Initialize midimap
  midimap.begin();
  
  // Connect to WiFi
  wifiConn.begin();
  
  // Initialize MIDI interface
  midi.begin();
  
  // Initialize OSC interface
  oscInterface.begin();
  
  // Initialize converter
  midiToOsc.begin();
  
  Serial.println("MIDI to OSC converter started");
}

void loop() {
  // Update midimap
  midimap.loop();
  
  // Update WiFi connection
  wifiConn.update();
  
  // Update converter
  midiToOsc.update();
}
