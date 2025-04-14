/** 
 * This example demonstrates sending button state as OSC messages.
 *
 * @boards  ESP32
 * Connections
 * -----------
 * 
 * - D2: momentary push button (to ground)
 * 
 * Behavior
 * --------
 * 
 * - When the button is pressed, a value of 1.0 is sent via OSC.
 * - When the button is released, a value of 0.0 is sent via OSC.
 * 
 * Mapping
 * -------
 * 
 * Create an UDP receive object on PureData on port 5000 and parse "/button" OSC address
 * 
 * Written by Patrice Colet, 2025-04-06
 */

#include <midimap.h> // Include the midimap library

// WiFi credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// Instantiate WiFi UDP connection for OSC
OSCWifi_Interface oscWifi {"192.168.1.1", 5000, ssid, password};

// Create an OSC value sender for the "/button" address
OSCValueSender oscSender {"/button"};

// Create a button that sends OSC messages
OSCButton button {2, oscSender, oscWifi};

void setup() {
  Serial.begin(115200);
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
