/*
 lightFinder Algorithm:

 1. Find the balance
    Req: print to serial (for humans)
    Rval - Lval = Difference (it probably won't be zero*)
    *Define some offset at the top
    Circuit Note: The higher the resistor (10k) the higher the sensor values
    
 2. Calculate light source values
    Note: Must find a range of tolerance (Deadband, defined as a constant at the top -> define DEADBAND 20;
    If it moves outside of the 20, then start moving the servo's position  
   

 3. Send position to the servo

 
 */
#include <Servo.h>

#define DEADBAND 20    // to keep the servo from continuously trying to maintain a balance

// constant / variable / object setup
const int sensorPinL = A0;
const int sensorPinR = A1;
Servo myservo;        // create servo object to control a servo
int pos, center = 0;          // variable to store the servo position and the dead center
int difference = 0;


// sensor values
int sensorValueL = 0;         // the sensor value
int sensorValueR = 0;         // the sensor value

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  sensorValueL = analogRead(sensorPinL);
  sensorValueR = analogRead(sensorPinR);
}

void loop() {
  sensorValueR = analogRead(sensorPinR);
  sensorValueL = analogRead(sensorPinL);

  Serial.println(sensorValueR);
  Serial.print(sensorValueL);

  // create an offset variable to hold the difference between the two sensors
  // subtracting the offset from the sensor with higher readings should allow you to calculate dead-center for the light source
  if (sensorValueR > sensorValueL) {
    difference = sensorValueR - sensorValueL;
    center = (sensorValueR - difference) - sensorValueL;
  }
  else if (sensorValueR < sensorValueL) {
    difference = sensorValueL - sensorValueR;
    center = (sensorValueL - difference) - sensorValueR;
  }
  
  if (center > DEADBAND || center < DEADBAND) {         // move left and right of center, to keep the servo from continuously trying to maintain a balance
    pos = map(pos, 0, 1023, 0, 179);            // convert the difference between the sensor values into a position for the servo
    myservo.write(pos);           // write the position to the servo
  }
}
