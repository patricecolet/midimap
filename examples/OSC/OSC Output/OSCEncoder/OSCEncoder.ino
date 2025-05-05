/** 
 * This example demonstrates using a rotary encoder to send OSC messages.
 *
 * @boards  ESP32
 * Connections
 * -----------
 * 
 * - D2: encoder pin A
 * - D3: encoder pin B
 * 
 * Behavior
 * --------
 * 
 * - When you rotate the encoder clockwise, the value increases
 * - When you rotate the encoder counter-clockwise, the value decreases
 * - The value is sent as a normalized float (0.0-1.0) via OSC
 * 
 * Mapping
 * -------
 * 
 * Create an UDP receive object on PureData on port 5000 and parse "/encoder" OSC address
 * 
 * Written by Patrice Colet, 2025-04-06
 */

#include <midimap.h> // Include the midimap library

// WiFi credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// Instantiate WiFi UDP connection for OSC
OSCWifi_Interface oscWifi {"192.168.1.1", 5000, ssid, password};

// Create an OSC value sender for the "/encoder" address
OSCValueSender oscSender {"/encoder"};

// Create an encoder that sends OSC messages
// Parameters: pinA, pinB, sender, interface, initialValue, increment, min, max
OSCEncoder encoder {2, 3, oscSender, oscWifi, 64, 1, 0, 127};

void setup() {
  Serial.begin(115200);
  midimap.begin(); // Initialize midimap
}

void loop() {
  midimap.loop(); // Update the midimap
}
