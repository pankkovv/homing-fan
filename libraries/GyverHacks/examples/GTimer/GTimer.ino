#include "GyverHacks.h"
GTimer myTimer;

void setup() {
  Serial.begin(9600);
  myTimer.setInterval(500);
}

void loop() {
  if (myTimer.isReady()) Serial.println("Timer!");
}
