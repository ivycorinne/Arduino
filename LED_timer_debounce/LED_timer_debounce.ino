/*
// blink a led
// add a button to control the blink
// modify the program to keep the led on after button press

// graphical representation is available use
// serial plotter (Tools > Serial Plotter menu)

 problem: when the button is bouncing, Arduino sees a rapid sequence of on and off signals
 There are many techniques developed to do de-bouncing. Here, we will attempt to debounce using a timer

 solution: turn on and off an LED connected to the digital pin, without using the delay function. 
 This means other code can run at the same time without being interrupted by the LED code.

*/
const int led = 13;
const int button = 7;

int val = 0;      // store the state of the input pin
int old_val = 0;  // store previous value of 'val'
int state = 0;    // store the state of the led (0 = off, 1 = on)

// Generally use unsigned long for variables that hold time, because the value quickly become too large for an int to store
unsigned long lastDebounceTime = 0; // will store last time LED was updated
const long debounceTimer = 500; // interval for button pressed in milliseconds

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital led pin as an output:
  pinMode(led, OUTPUT);
  // initialize digital button pin as an input:
  pinMode(button, INPUT);
  // initalize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
}

// the loop function runs over and over again forever
void loop() {

  val = digitalRead(button);  // read the input value here and store it
  Serial.println(val);        // digitalRead() only reads '1' when button is pressed.
  
  // check if there was any change with new and improved if():
  if((val == HIGH) && (old_val == LOW)){
    
    unsigned long currentMillis = millis(); // Uses the Arduino clock

    // Next, check to see if the time has exceeded our threshold
    // (the difference between the current time and the last time we checked)
    if(currentMillis - lastDebounceTime > debounceTimer) {
      // save the last time the LED was on
      lastDebounceTime = currentMillis;

      state = 1 - state;
    }
  }

  old_val = val;             // val is now old, let's store it
  
  // check what state was captured by the button press
  if (state == 1){
  digitalWrite(led, HIGH);   // turn the LED on
  }
  else {
  digitalWrite(led, LOW);    // turn the LED off
  }
}








