#define PARSE_AMOUNT 5
int intData[PARSE_AMOUNT];

#include "GParsingStream.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  parsingStream((int*)&intData);

  if (dataReady()) {
    for (byte i = 0; i < PARSE_AMOUNT; i++) {
      Serial.print(intData[i]); Serial.print(" ");
    }
    Serial.println();
  }
}
