bool TimeArduino(byte s_hour, byte s_minute, byte s_second) {
  //устанавливает время в ардуино про
  Wire.beginTransmission(ArduinoAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x01));
  Wire.write(s_hour);
  Wire.write(s_minute);
  Wire.write(s_second);
  Wire.endTransmission();



  return true;
}


bool DigOut( byte pin , bool value) {
  //устанавливает pin  в значение value
  Wire.beginTransmission(ArduinoAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x02));
  Wire.write(pin + 1); // +1 что бы не было 0
  if (value) {
    Wire.write(0xF0); //это 1
  }
  else {
    Wire.write(0x0F);// а это 0 что бы не посылать 0x00
  }
  Wire.endTransmission();
  return true;
}

int DigInp(byte pin) {
  // считывае значение с pin
  // и возвращает его
  int retVal = -1;
  bool  fl_beg = false;

  Wire.beginTransmission(ArduinoAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x03));
  Wire.write(pin + 1); // +1 что бы не было 0
  Wire.endTransmission();
  Wire.requestFrom(ArduinoAddress, 2);   // request 2 bytes from slave device


  // A few of these need masks because certain bits are control bits
  if (2 <= Wire.available()) {
    byte c1     = Wire.read() ;
    byte c2     = Wire.read();

    String tmp = String(c1, HEX);
    Serial.println("c1 - " + tmp);
    tmp = String(c2, HEX);
    Serial.println("c2 - " + tmp);
  }
  /*

    // step 4: request reading from sensor
    Wire.requestFrom(112, 2);    // request 2 bytes from slave device #112

    // step 5: receive reading from sensor
    if (2 <= Wire.available()) { // if two bytes were received
      reading = Wire.read();  // receive high byte (overwrites previous reading)
      reading = reading << 8;    // shift high byte to be high 8 bits
      reading |= Wire.read(); // receive low byte as lower 8 bits
      Serial.println(reading);   // print the reading
    }
  */


  //
  //  if (2 <= Wire.available()) { // slave may send less than requested
  //    byte c = Wire.read(); // receive  byte
  //    String tmp = String((int)c, DEC);
  //    Serial.println("c1 - " + tmp);
  //    if (c == 0) {// начало передачи
  //      fl_beg = true;
  //    }
  //    c = Wire.read();
  //    tmp = String((int)c, DEC);
  //    Serial.println("c2 - " + tmp);
  //    if (fl_beg) {
  //      if (c == 0xf0)
  //        retVal = 1;
  //      else
  //        retVal = 0;
  //    }
  //
  //  }

  return retVal;
}

int AnalogInp(byte pin) {
  // считывае код ADC  с канала pin
  //и возвращает его
  int codADC = -1;
  int count = 0;
  byte b0;
  byte b1;
  bool fl_beg = false;

  Wire.beginTransmission(ArduinoAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x04));
  Wire.write(pin); //
  Wire.endTransmission();
  Wire.requestFrom(ArduinoAddress, 3);   // request 3 bytes from slave device

  while (Wire.available()) { // slave may send less than requested
    byte c = Wire.read(); // receive  byte

    if (fl_beg) {
      if (count == 1) {
        b1 = c; // второй байт
      }
      if (count == 0) {
        b0 = c; // первй байт
        count++;
      }
    }
    if (c == 0) {// начало передачи
      fl_beg = true;
    }
  }
  b1 = b1 & 0x0f; // сбросим старшие байты ADC 12 битный

  codADC = (unsigned int)b1;
  codADC = codADC << 8;
  codADC =  codADC + (unsigned int)b0;

  return codADC;
}

bool  AnalogOut(byte pin, byte value) {
  //Устаналивает pin канал DAC(шим)

  Wire.beginTransmission(ArduinoAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x05));
  Wire.write(pin + 1); // +1 что бы не было 0
  if (value == 0) // что бы не было 0 +1 хрен с ней с точностью
    value++;
  Wire.write(value  );//
  Wire.endTransmission();
  return true;
}

bool setPin(byte pin, byte digMode) {
  // устанавливает режим цифровой pin

  Wire.beginTransmission(ArduinoAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x06));
  Wire.write(pin + 1); // +1 что бы не было 0
  Wire.write(digMode + 1 ); //   +1 что бы не было 0
  Wire.endTransmission();
  return true;
}

