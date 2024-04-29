#include <Arduino.h>
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <model.h>


QMC5883LCompass::QMC5883LCompass() {}

void QMC5883LCompass::initialize() {
  writeRegister(0x0B, 0x01);
  setMode(continuous, odr10, rng8, osr256);
}

void QMC5883LCompass::writeRegister(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(sensorAddress);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void QMC5883LCompass::setMode(uint8_t sampleMode, uint8_t outputDataRate, uint8_t fieldRange, uint8_t overSampleRate) {
  writeRegister(0x09, sampleMode | outputDataRate<<2 | fieldRange<<4 | overSampleRate<<6);
}

int QMC5883LCompass::azimuth() {
    data = getRawData();
    Eloquent::ML::Port::Model model;
    int features[3] = {data.x, data.y, data.z};
    return model.predict(features);
}


QMC5883LCompass::rawReading QMC5883LCompass::getRawData() {
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
  return data;
}
