#include <Arduino.h>
#include <Wire.h>
#include <QMC5883L_Compass.h>


QMC5883L_Compass::QMC5883L_Compass() {
  declination = 0;
  hardIron = { 0,0,0 };
  softIron = { { 1, 0, 0 },  { 0, 1, 0 }, { 0, 0, 1 } };
  writeRegister(0x0B, 0x01); //datasheet says to idk
  setMode(continuous, odr10, rng8, osr256);
}

void QMC5883L_Compass::calibrateCompass(int hard[3], float soft[3][3]) {
  hardIron = hard;
  softIron = soft;
}

void QMC5883L_Compass::writeRegister(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(sensorAddress);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission;
}

void QMC5883L_Compass::setMode(uint8_t sampleMode, uint8_t outputDataRate, uint8_t fieldRange, uint8_t overSampleRate) {
  writeRegister(0x09, sampleMode | outputDataRate<<2 | fieldRange<<4 | overSampleRate<<6);
}

void QMC5883L_Compass::updateData() {
  Wire.beginTransmission(sensorAddress);
  Wire.write(0x00);
  Wire.requestFrom(sensorAddress, 6);
  data.x = Wire.read();
  data.x |= Wire.read() << 8;
  data.y = Wire.read();
  data.y |= Wire.read() << 8;
  data.z = Wire.read();
  data.z |= Wire.read() << 8;
  Wire.endTransmission();
}

rawReading QMC5883L_Compass::getRawReading() {
  updateData();
  return data;
}

float QMC5883L_Compass::azimuth(int x, int y) {
  float azimuth = ()atan2(x,y) + declination) * 180.0/PI;
  return azimuth < 0?360 + azimuth:azimuth;
}

float QMC5883L_Compass::getHeading() {
  updateData();
  int tempx = data.x - hardIron[0];
  int tempy = data.y - hardIron[1];
  int tempz = data.z - hardIron[2];
  data.x = (softIron[0][0] * tempx) + (softIron[0][1] * tempy) + (softIron[0][2] * tempz);
  data.y = (softIron[1][0] * tempx) + (softIron[1][1] * tempy) + (softIron[1][2] * tempz);
  data.z = (softIron[2][0] * tempx) + (softIron[2][1] * tempy) + (softIron[2][2] * tempz);
  return azimuth(data.x, data.y);
}
