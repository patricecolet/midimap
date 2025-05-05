// Define the pin connected to the relay
const int relayPin = 7;

void setup() {
  // Set the relay pin as an output
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Turn on the relay
  digitalWrite(relayPin, HIGH);
  delay(1000); // Wait for 1 second
  
  // Turn off the relay
  digitalWrite(relayPin, LOW);
  delay(1000); // Wait for 1 second
}
