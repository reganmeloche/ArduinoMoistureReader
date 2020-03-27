#include <SimpleTimer.h>
#include <Adafruit_seesaw.h>
#include <LiquidCrystal.h>

int timerId;
SimpleTimer timer;
Adafruit_seesaw ss;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  
int MOISTURE_POLL_MS = 3000;
int LOW_THRESHOLD = 500;
int HIGH_THRESHOLD = 1000;
  
void setup() {
  lcd.begin(16, 2);
  timerId = timer.setInterval(MOISTURE_POLL_MS, readMoisture);
  ss.begin(0x36);
  readMoisture();
}

void loop() {
  timer.run();
}

void readMoisture() {
    uint16_t value = ss.touchRead(0);
    lcd.clear();

    char *message = "I feel great!";
    if (value < LOW_THRESHOLD) {
      message = "I need a bath!";  
    }
    if (value > HIGH_THRESHOLD) {
      message = "I'm soaked!";  
    }
    lcd.begin(16, 2);
    lcd.print(message);
    lcd.setCursor(0, 1);
    lcd.print(value);
}
