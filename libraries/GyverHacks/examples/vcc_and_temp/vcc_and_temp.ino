#include "GyverHacks.h"

void setup() {
  Serial.begin(9600);

  Serial.println(getVCC());         // напряжение питания в милливольтах
  setConstant(4610);                // пишем сюда реальное напряжение на 5V и GND в милливольтах
  Serial.println(getVCC());         // напряжение питания в милливольтах с правильной константой
  Serial.println(getVoltage(0));    // напряжение на аналоговом пине в мВ
  Serial.println(getTemp());        // температура ядра

}

void loop() {

}