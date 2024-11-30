int led = LOW;
long millisPrevious = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  long now = millis();
  if (now - millisPrevious >= 5000) {
      millisPrevious = now;
      if (led == LOW) {
      led = HIGH; 
    } else {
      led = LOW;  
    }
    digitalWrite(LED_BUILTIN, led);
  }

}
