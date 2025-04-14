/** 
 * This example demonstrates sending potentiometer values as OSC messages.
 *
 * @boards  ESP32
 * Connections
 * -----------
 * 
 * - A0: wiper of a potentiometer
 * 
 * Connect the left terminal of the potentiometer to ground, and the right one
 * to V<sub>CC</sub>.
 * 
 * Behavior
 * --------
 * 
 * - When you turn the potentiometer, a value between 0 and 1 is sent via OSC.
 * 
 * Mapping
 * -------
 * 
 * Create an UDP receive object on PureData on port 5000 and parse "/potentiometer" OSC address
 * 
 * Written by Patrice Colet, 2025-04-06
 */

#include <midimap.h> // Include the midimap library

// WiFi credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// Instantiate WiFi UDP connection for OSC
OSCWifi_Interface oscWifi {"192.168.1.1", 5000, ssid, password};

// Create an OSC value sender for the "/potentiometer" address
OSCValueSender oscSender {"/potentiometer"};

// Create a potentiometer that sends OSC messages
OSCPotentiometer potentiometer {A0, oscSender, oscWifi};

void setup() {
  Serial.begin(115200);
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
