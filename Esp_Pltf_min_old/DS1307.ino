
// Gets the date and time from the ds1307 and prints result
void getDateDs1307() {
  // Reset the register pointer
  Wire.beginTransmission(clockAddress);
  Wire.write(byte(0x00));
  Wire.endTransmission();

  Wire.requestFrom(clockAddress, 7);

  // A few of these need masks because certain bits are control bits
  g_second     = bcdToDec(Wire.read() & 0x7f);
  g_minute     = bcdToDec(Wire.read());

  // Need to change this if 12 hour am/pm
  g_hour       = bcdToDec(Wire.read() & 0x3f);
  g_dayOfWeek  = bcdToDec(Wire.read());
  g_dayOfMonth = bcdToDec(Wire.read());
  g_day = g_dayOfMonth;
  g_month      = bcdToDec(Wire.read());
  g_year       = bcdToDec(Wire.read());
}

void setDateDs1307()
{
  // Use of (byte) type casting and ascii math to achieve result.
  /*second = (byte) ((Serial.read() - 48) * 10 + (Serial.read() - 48));
  minute = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  hour  = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  dayOfWeek = (byte) (Serial.read() - 48);
  dayOfMonth = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  month = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  year= (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));*/

  Wire.beginTransmission(clockAddress);
  Wire.write(byte(0x00));
  s_second = s_second | 0x80; // 7 бит 1 - старт часов
  Wire.write(decToBcd(s_second));  // 0 to bit 7 starts the clock
  Wire.write(decToBcd(s_minute));
  s_hour = s_hour & 0xBF; //6 бит 0 24 часовой режим
  Wire.write(decToBcd(s_hour));    // If you want 12 hour am/pm you need to set
  // bit 6 (also need to change readDateDs1307)
  Wire.write(decToBcd(s_dayOfWeek)); // день недели
  s_dayOfMonth = s_day;
  Wire.write(decToBcd(s_dayOfMonth));
  Wire.write(decToBcd(s_month));
  Wire.write(decToBcd(s_year));
  Wire.endTransmission();
}

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}
