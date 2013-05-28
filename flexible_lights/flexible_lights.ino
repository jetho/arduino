
/* Flexible lights.
   
   Connect 6 LEDs to Pins 8-13 and a potentiometer to analog Pin 0.
   A pushbutton connects through a pull-down resistor to Pin 7. 
   The potentiometer can be used to control the frequency of the LEDs,
   the pushbutton switches between running and random light modes.
*/


#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

int ledPin[] = {13, 12, 11, 10, 9, 8};
int potiPin = 0;
int buttonPin = 7;
int maxInterval = 512;
int minInterval = 20;
int buttonState = LOW;
int interval;
unsigned long prev;
int currentLed = random(NELEMS(ledPin));


void setup() {
  for(int i = 0; i < 6; i++)
    pinMode(ledPin[i], OUTPUT); 
  pinMode(buttonPin, INPUT);
  prev = millis();
}

int nextLed() {
  if(buttonState == HIGH)
    return random(NELEMS(ledPin));
  else
    return currentLed == (NELEMS(ledPin) - 1) ? 0 : (currentLed + 1);
}

int toggle(int i) {
  return !i;
}

void loop() {
  digitalWrite(ledPin[currentLed], HIGH);
  
  interval = map(analogRead(potiPin), 0, 1023, minInterval, maxInterval);
  if(digitalRead(buttonPin) == HIGH)
    buttonState = toggle(buttonState);
  
  if((millis() - prev) > interval) {
    prev = millis();
    digitalWrite(ledPin[currentLed], LOW);
    currentLed = nextLed();      
  }
}

