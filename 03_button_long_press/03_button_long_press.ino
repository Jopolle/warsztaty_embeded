const int LED_PIN = 8;
const int BTN_PIN = 2;

const unsigned long DEBOUNCE_MS   = 30;
const unsigned long LONG_CLICK_MS = 700;

bool stableBtn = HIGH;
bool lastRawBtn = HIGH;
unsigned long lastDebounceTime = 0;

bool pressInProgress = false;
unsigned long pressStartTime = 0;

bool ledOn = false;
bool blinkMode = false;

unsigned long lastBlinkTime = 0;
const unsigned long BLINK_PERIOD_MS = 300;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
}

void handleShortClick() {
  ledOn = !ledOn;                 
}

void handleLongClick() {
  blinkMode = !blinkMode;       
}

void loop() {
  bool raw = digitalRead(BTN_PIN);

  if (raw != lastRawBtn) {
    lastDebounceTime = millis();
    lastRawBtn = raw;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    if (raw != stableBtn) {
      stableBtn = raw;
      if (stableBtn == LOW) {
        pressInProgress = true;
        pressStartTime = millis();
      } else {
        if (pressInProgress) {
          unsigned long pressTime = millis() - pressStartTime;
          pressInProgress = false;

          if (pressTime >= LONG_CLICK_MS) handleLongClick();
          else handleShortClick();
        }
      }
    }
  }


  if (!blinkMode) {
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
  } else {
    if (ledOn) {
      if (millis() - lastBlinkTime >= BLINK_PERIOD_MS) {
        lastBlinkTime = millis();
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      }
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
}
