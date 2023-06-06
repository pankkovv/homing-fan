#define TIMEOUT 100
boolean _recievedFlag;
boolean _getStarted;
byte _index;
String _string_convert = "";

void parsingStream(int *incData) {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    if (_getStarted) {
      if (incomingByte != ' ' && incomingByte != ';') {
        _string_convert += incomingByte;
      } else {
        incData[_index] = _string_convert.toInt();
        _string_convert = "";
        _index++;
      }
    }
    if (incomingByte == '$') {
      _getStarted = true;
      _index = 0;
      _string_convert = "";
    }
    if (incomingByte == ';') {
      _getStarted = false;
      _recievedFlag = true;
    }
  }
}

void sendPacket(int *intData, uint8_t size) {
	byte n = size / sizeof(intData[0]);
	Serial.print('$');
	for (byte i = 0; i < n; i++) {
      Serial.print(intData[i]);
	  if (i < (n - 1)) Serial.print(" ");
    }
	Serial.println(';');
}

boolean dataReady() {
	if (_recievedFlag) {
		_recievedFlag = false;
		return true;
	} else {
		return false;
	}
}