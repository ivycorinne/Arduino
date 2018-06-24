
int i;
/*
  timer de-bounce

  When the pushbutton is bouncing, Arduino sees a rapid sequence of
  on and off signals.
  
  There are many techniques developed to do de-bouncing.
  Here, we will attempt to de-bounce using a timer.

  Turn on and off a LED connected to a digital pin, without using
  the delay() function.  This means that other code can run
  at the same time without being interrupted by the LED code.

  https://www.arduino.cc/en/Reference/Constants

*/

const int LED = 13;     // LED connected to digital pin 13
const int BUTTON = 7;   // pushbutton is connected to input pin 7

int val = 0;             // store the state of the input pin
int old_val = 0;         // stores previous value of 'val'
int state = 0;           // stores current state 0 = off and 1 = on
int hold = 0;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long lastDebounceTime = 0;     // will store last time LED was updated
const long debounceTimer = 500;           // interval for button press (milliseconds)


void setup() {                      
  pinMode(LED, OUTPUT);   // initialize digital pin 13 as output.
  pinMode(BUTTON, INPUT); // initialize pin 7 as input
  Serial.begin(9600);   
}

void loop() {
  val = digitalRead(BUTTON);    // read input value and store it
  Serial.println(val);          // only reads '1' when button is pressed 


  // check if there was any change
  if ((val == HIGH) && (old_val == LOW)) {

    // then start the clock
    unsigned long currentMillis = millis();
                                // insert this line here, which uses
                                // the Arduino clock. millis() returns
                                // how many milliseconds have passed since
                                // the board has been reset.
    

    // next, check to see if the time has exceeded our threshhold
    // (the difference between the current time and last time we checked)

    if (currentMillis - lastDebounceTime > debounceTimer) {
      // save the last time the LED was on
      lastDebounceTime = currentMillis;    
      state = 1 - state;
      // we removed the delay() function that was here...
    }
  }

  if ((val == HIGH) && (old_val == HIGH)) {

    // then start the clock
    unsigned long currentMillis = millis();
                                // insert this line here, which uses
                                // the Arduino clock. millis() returns
                                // how many milliseconds have passed since
                                // the board has been reset.
    

    // next, check to see if the time has exceeded our threshhold
    // (the difference between the current time and last time we checked)

    if (currentMillis - lastDebounceTime > debounceTimer) {
      // save the last time the LED was on
      lastDebounceTime = currentMillis;    
      hold = 1;
      // we removed the delay() function that was here...
    }
   }
  
  
  old_val = val;             // val is now old, let's store it
   
  // check whether input is HIGH (button pressed)
  if (state == 1) {
    digitalWrite(LED, HIGH); // turn the LED on 
  } 
  else if (hold == 1) {
    for (i = 0; i < 255; i++) {
      analogWrite(LED, i);
      delay(10);
    }
    for (i = 255; i > 0; i--) {
      analogWrite(LED, i);
      delay(10);
    }
      hold = 0;
  }
  else {
    digitalWrite(LED, LOW);  // turn the LED off
  }
}
