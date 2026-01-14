// Sam debounce na klikniecie przycisku (bez LED)
// Przycisk: D2 -> przycisk -> GND (INPUT_PULLUP)
// Efekt: wypisuje "CLICK!" raz na kazde stabilne puszczenie przycisku

const int BTN_PIN = 2;

const unsigned long DEBOUNCE_MS = 30;

bool stableState = HIGH;      // pullup: HIGH = puszczony, LOW = wcisniety
bool lastRawState = HIGH;
unsigned long lastChangeTime = 0;

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial) { ; }
  Serial.println("Debounce click test: wcisnij i pusc przycisk.");
}

void loop() {
  bool raw = digitalRead(BTN_PIN);

  // wykryj zmiane surowego stanu i zapamietaj czas
  if (raw != lastRawState) {
    lastRawState = raw;
    lastChangeTime = millis();
  }

  // jesli od ostatniej zmiany minelo DEBOUNCE_MS, uznaj stan za stabilny
  if ((millis() - lastChangeTime) >= DEBOUNCE_MS) {
    if (raw != stableState) {
      stableState = raw;

      // klik liczymy na puszczeniu (powrot do HIGH)
      if (stableState == HIGH) {
        Serial.println("CLICK!");
      }
    }
  }
}
