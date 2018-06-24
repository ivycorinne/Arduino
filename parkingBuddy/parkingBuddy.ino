#include <NewPing.h>

/*

 Requirements for parkingBuddy:

  1. Measure time/distance in inches and centimeters

  2. Provide Feedback
    - Monitor(Serial()) distance and pot sensor value
    - LED
        : Green 
            - High within range
            - Blink in proportion to sonar
        : Red
            - Blink proportional to sonar
            - High value when exceeded range
     - Pot to setup / config when to stop 

*/

// Placement of sensors
int potPin = 13;
int redLED = 8;
int greenLED = 12;
float limit = 30.48;
int warning = limit + 120;
boolean high = false;     // State value to flash an LED

#define TRIGGER_PIN  2   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4   // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {

 //Instantiation of variables
 int val, percent, inches, cm;

 inches = sonar.ping_in();                // Document the inches found through the ping
 cm = sonar.ping_cm();                    // Document the cm found through the ping
 val = analogRead(potPin);                // Read input value and store it
 percent = map(val, 0, 1023, 0, 100);     // Map the output for printing

 
 delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
 Serial.print("Ping: ");
 Serial.print(inches);
 Serial.print("in, ");         // Send ping, get distance in IN and print result (0 = outside set distance range)
 Serial.print(cm);              // Send ping, get distance in CM and print result (0 = outside set distance range)
 Serial.println("cm");

 Serial.println("POTENTIAMETER: ");     // Print the potentiameter values
 Serial.print("Percet: ");
 Serial.println(percent);

  // Test for a sonar value that is less than your “limit” value set by the potentiometer. Upon success, the red LED should be turned on.
 if (cm < limit) {
    Serial.println("WARNING: STOP");
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
 }

  // Test for a sonar value that falls below your “warning” value. Upon success, the green LED should flash.
 else if (cm < warning) {
    digitalWrite(redLED, LOW);
    Serial.println("Continue driving forward CAUTIOUSLY");
    if (!high) {
      digitalWrite(greenLED, HIGH);
      high = true;
    }
    else {
      digitalWrite(greenLED, LOW);
      high = false;
    }
 }

 // If the sonar value reads anything else, there is nothing to test; the green LED should be on.
 else {
    Serial.println("Continue driving forward");
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
 }
}
