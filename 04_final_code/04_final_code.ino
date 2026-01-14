// Program 3: reakcja na klik + Serial Monitor
// Przycisk: D2 -> przycisk -> GND (INPUT_PULLUP)

const int BTN_PIN = 2;

const unsigned long DEBOUNCE_MS = 30;
const unsigned long HOLD_MS     = 1000;

bool stableBtn = HIGH;
bool lastRawBtn = HIGH;
unsigned long lastDebounceTime = 0;

unsigned long pressStartTime = 0;
bool holdReported = false;

unsigned long clickCount = 0;

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial) { ; } // na UNO zwykle nic nie robi, ale nie szkodzi

  Serial.println("Start. Klikaj przycisk (D2 do GND).");
}

void loop() {
  // debounce
  bool raw = digitalRead(BTN_PIN);

  if (raw != lastRawBtn) {
    lastDebounceTime = millis();
    lastRawBtn = raw;
  }

  if (millis() - lastDebounceTime > DEBOUNCE_MS) {
    if (raw != stableBtn) {
      stableBtn = raw;

      if (stableBtn == LOW) {
        // wcisniecie
        pressStartTime = millis();
        holdReported = false;
      } else {
        // puszczenie => klik
        clickCount++;
        unsigned long dt = millis() - pressStartTime;

        Serial.print("CLICK #");
        Serial.print(clickCount);
        Serial.print("  press_ms=");
        Serial.print(dt);
        Serial.print("  t=");
        Serial.println(millis());
      }
    }
  }

  // raport HOLD gdy trzymany
  if (stableBtn == LOW && !holdReported) {
    if (millis() - pressStartTime >= HOLD_MS) {
      holdReported = true;
      Serial.print("HOLD (>");
      Serial.print(HOLD_MS);
      Serial.print(" ms)  t=");
      Serial.println(millis());
    }
  }
}
