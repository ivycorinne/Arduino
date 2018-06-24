

/*

  analog input - potentiometer
  set brightness of led as specified by value of analog input

  analogRead() allows us to read the voltage applied to one of the analog pins

  analogRead() returns a number between 0 and 1023, which represents voltages between 0 and 5 volts
  (ie. 2.5v applied to pin A0, analogRead() returns 512)

  note: since we are reading a sensor, and we are not dependent on a switch, we don't need to debounce
  
*/

const int led = 9; 
const int button = 7;

int val = 0;             // store the state of the input pin

void setup() {                      
  pinMode(led, OUTPUT);
  // note: analog pins are automatically set as inputs
  Serial.begin(9600);
}

void loop() {
  val = analogRead(0);    // read input value and store it
  Serial.println(val);

  analogWrite(led, 255 - val/4); //specify brightness as val/4 (remembering sketch to fade an led) because analogRead() returns numbers up to 1023 and analogWrite() accepts a minimum of 255
  delay(10);
}




