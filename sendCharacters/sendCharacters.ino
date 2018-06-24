/*

  Example of using the Arduino board to receive data (commands) from the computer.
  
  In our example, we want to turn on LED when Arduino receives 'H', and turn the LED off when Arduino receives 'L'

  Arduino can receive data via the serial monitor (and other mechanisms)

  Circuit:
    - LED from digital pin 13 to GND
  
*/


const int ledPin = 13; 
int incomingByte;     // Stores incoming serial data



void setup() {
  // Initialize serial communication 
  Serial.begin(9600);
  // Initialize the pin as output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // See if we have incoming serial data
  if (Serial.available() > 0) {
    // Read the oldest byte in the serial buffer
    incomingByte = Serial.read();
    if (incomingByte == 'H') {
      digitalWrite(ledPin, HIGH);
    }
    if (incomingByte == 'L') {
      digitalWrite(ledPin, LOW);
    }
  }
}
