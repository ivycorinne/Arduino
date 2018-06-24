// Worked with Shayan

int red = 13;
int yellow = 11;
int green = 9;
int incomingByte = 'g';
unsigned long lastTime = 0;  //will store last time LED was updated
boolean started = false;
unsigned long currentMillis  = 0;

void setup() {
 Serial.begin(9600);
 pinMode(red, OUTPUT);
 pinMode(yellow, OUTPUT);
 pinMode(green, OUTPUT);
}

void loop() {
 currentMillis = millis();
 if(Serial.available() > 0){
   incomingByte = Serial.read();
 }
 Serial.print("Incoming byte: ");
 Serial.println(incomingByte);
 switch(incomingByte){
   case 'g':
     {
     digitalWrite(green, HIGH);
     digitalWrite(red, LOW);
     digitalWrite(yellow, LOW);
     if(Serial.available() > 0){
     incomingByte = Serial.read();
     }
     if(currentMillis - lastTime > 3000){
       lastTime = currentMillis;
       incomingByte = 'y';
     }
     Serial.print("Current millis: ");
     Serial.println(currentMillis);
     Serial.print("Last time: ");
     Serial.println(lastTime);       
     break;
     }

   case 'y':
     {
     lastTime = currentMillis;
     digitalWrite(green, LOW);
     digitalWrite(yellow, HIGH);
     digitalWrite(red, LOW);
     delay(2500);
     lastTime = currentMillis;
     incomingByte = 'r';
     }

   case 'r':
     {digitalWrite(red, HIGH);
     digitalWrite(green, LOW);
     digitalWrite(yellow, LOW);
     if(Serial.available() > 0){
     incomingByte = Serial.read();
     }
     if(currentMillis - lastTime > 5500){
       lastTime = currentMillis;
       incomingByte = 'g';
     }
     break;
     }
   default:
     {incomingByte = 'g';
    }
 }

}

