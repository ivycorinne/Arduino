
const int potPin = 0;
int redLED = 13;      
int yellowLED = 12;
int greenLED = 8;
int val = 0;


void setup() {                      
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  Serial.begin(9600);   
  
}

void loop() {
 
  int val;              // value from sensor
  int percent;          // mapped value
  
  val = analogRead(potPin);    // read input value and store it
  percent = map(val, 0, 1023, 0, 100);
                               // percent will range 0 to 100
  
  
  if (percent <= 33) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }

  else if (percent > 33 && percent <= 66) {
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
  }

  else {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  }
  Serial.println(percent);    // print out value of sensor
}
