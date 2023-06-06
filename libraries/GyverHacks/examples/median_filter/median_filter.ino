#include "GyverHacks.h"

int val[3];
float val_f;
byte i;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (i > 1) i = 0;
  else i++;

  val[i] = analogRead(0);
  val_f = medianFilter(val[0], val[1], val[2]);
  Serial.println(val_f);
  delay(100);

}
