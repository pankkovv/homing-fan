#include "GyverHacks.h"
GFilterRA analog0;

void setup() {
  Serial.begin(9600);

  analog0.setCoef(0.01);

  analog0.setStep(10);
}

void loop() {
  Serial.println(analog0.filteredTime(analogRead(0)));
}
