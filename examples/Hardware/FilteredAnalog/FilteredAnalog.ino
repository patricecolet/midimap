#include <midimap.h>

// Create a filtered analog object on pin A0:
FilteredAnalog<10,      // Output precision in bits
               2,       // The amount of filtering
               uint16_t // The integer type for the calculations
               >
  analog = A0;

// If you want more filtering, you can increase the filter shift factor.
// The number of bits required for the intermediate calculations increases if
// you do so, so you have to use a larger type as well.
FilteredAnalog<10,      // Output precision in bits
               6,       // The amount of filtering
               uint32_t // The integer type for the calculations
               >
  moreFiltering = A0;

// If you don't care about the specific settings, and just want a
// default that works, you can use the following:
FilteredAnalog<> simpleAnalog = A0;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  // Select the correct ADC resolution
  FilteredAnalog<>::setupADC();
  // If you want, you can add mapping functions to invert the input, for example
  analog.invert();
}

void loop() {
  // Read the analog input every millisecond, and print if the value has changed
  static Timer<millis> timer = 1; // ms
  if (timer && analog.update())
    Serial.println(analog.getValue());

  // Explanation:
  //
  // analog.update() reads the analog input, applies the filters,
  // saves the value, and returns true if the value has changed.
  // You can then retreive the new value using analog.getValue().
  //
  // Timer is just a "Blink Without Delay" wrapper, it returns true
  // every time the specified amount of time has passed.
}