/*
 * Demo sketch for video #143 www.youtube.com/ralphbacon
 * 
 * This is the built in Arduino method of detecting a touch and can
 * easily replace a push button switch.
 * 
 */

// Standard Arduino library for touch sensor
#include <CapacitiveSensor.h>

// Attach wire, foil, touch pad etc to pin 2
CapacitiveSensor sense = CapacitiveSensor(5, 2);
#define touchToggleLevel 1000

// Print out debugging messages to Serial Monitor?
bool isDebug = true;

#define ledPin 11

// ----------------------------------------------------------------------------
// One size fits all Serial Monitor debugging messages
// ----------------------------------------------------------------------------
template<typename T> void debugPrint(T printMe, bool newLine = false) {
  if (isDebug) {
    if (newLine) {
      Serial.println(printMe);
    }
    else {
      Serial.print(printMe);
    }
    Serial.flush();
  }
}

// -----------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// -----------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  // Autocallibrate every 10 seconds (default = 20?)
  sense.set_CS_AutocaL_Millis(10000);

  debugPrint("Setup complete.");
}

// ------------------------------------------------------------
// LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    LOOP    
// ------------------------------------------------------------
void loop() {

  if (doTouch()) {
    digitalWrite(ledPin,HIGH);
  } else {
    digitalWrite(ledPin,LOW);
  }  

}

// ----------------------------------------------------------------------------
// Detect whether the touch pad has been touched - will control on/off function
// ----------------------------------------------------------------------------
bool doTouch() {
  // Take several samples
  long signal = sense.capacitiveSensor(70);

  // Master ON-OFF switch (controlled by pretty cat collar touch pad)
  if (signal > touchToggleLevel) {
    debugPrint("Touch level: ");
    debugPrint(signal, true);

    // Return touch was detected
    return true;
  }

  // No touch detected
  return false;
}
