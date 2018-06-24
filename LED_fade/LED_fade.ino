// analogWrite() expects a number btween 0 and 255

const int led = 13;
int i = 0;


void setup() {
  pinMode(led, OUTPUT);       // assign led to output in
}

void loop() {
  for (i = 0; i < 255; i++) {
    analogWrite(led, i);
    delay(10);
  }
  for (i = 255; i > 0; i--) {
    analogWrite(led, i);
    delay(10);
  }
}
