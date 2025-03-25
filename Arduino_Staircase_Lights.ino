#define BOTTOM_BUTTON 2  // Bottom button (Pull-up)
#define TOP_BUTTON 3     // Top button (Pull-up)

#define NUM_LEDS 6
int ledPins[NUM_LEDS] = {4, 5, 6, 7, 8, 9};  // Stair LEDs
bool isOn = false;  // Track LED state
int lastDirection = 0;  // 1 = Bottom to Top, -1 = Top to Bottom

void setup() {
  pinMode(BOTTOM_BUTTON, INPUT_PULLUP);
  pinMode(TOP_BUTTON, INPUT_PULLUP);

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);  // Start with all LEDs OFF
  }
}

void loop() {
  if (digitalRead(TOP_BUTTON) == LOW) {
    delay(50);  // Debounce
    while (digitalRead(TOP_BUTTON) == LOW);  // Wait for release
    if (!isOn) {
      turnOnSequence(1);  // Turn ON from top to bottom
      lastDirection = 1;
    } else if (lastDirection == -1) {
      turnOffSequence(1);  // Turn OFF from bottom to top
      isOn = false;
    }
  }

  if (digitalRead(BOTTOM_BUTTON) == LOW) {
    delay(50);  // Debounce
    while (digitalRead(BOTTOM_BUTTON) == LOW);  // Wait for release
    if (!isOn) {
      turnOnSequence(-1);  // Turn ON from bottom to top
      lastDirection = -1;
    } else if (lastDirection == 1) {
      turnOffSequence(-1);  // Turn OFF from top to bottom
      isOn = false;
    }
  }
}

void turnOnSequence(int direction) {
  if (direction == 1) {  // Top to Bottom
    for (int i = NUM_LEDS - 1; i >= 0; i--) {
      digitalWrite(ledPins[i], HIGH);
      delay(200);
    }
  } else {  // Bottom to Top
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(200);
    }
  }
  isOn = true;
}

void turnOffSequence(int direction) {
  if (direction == 1) {  // Bottom to Top (Reverse of turning ON from Top to Bottom)
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(ledPins[i], LOW);
      delay(200);
    }
  } else {  // Top to Bottom (Reverse of turning ON from Bottom to Top)
    for (int i = NUM_LEDS - 1; i >= 0; i--) {
      digitalWrite(ledPins[i], LOW);
      delay(200);
    }
  }
}
