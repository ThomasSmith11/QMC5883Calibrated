#ifndef QMC5883LCompass_h
#define QMC5883LCompass_h

#include <Arduino.h>

#define initialDataRegister 0x00
#define sensorAddress 0x0D

//sampling mode
#define single 0b00
#define continuous 0b01

//output data rate in hz
#define odr10 0b00
#define odr50 0b01
#define odr100 0b10
#define odr200 0b11

//field range in gauss
#define rng2 0b00
#define rng8 0b01

//over sample rate
#define osr512 0b00
#define osr256 0b01
#define osr128 0b10
#define osr64 0b11

class QMC5883LCompass {
public:
  QMC5883LCompass();

  struct rawReading {
    int16_t x;
    int16_t y;
    int16_t z;
  };

  void initialize();
  void setMode(uint8_t sampleMode, uint8_t outputDataRate, uint8_t fieldRange, uint8_t overSampleRate);
  rawReading getRawData();
  int azimuth();

private:
  rawReading data;
  void writeRegister(uint8_t reg, uint8_t val);
};

#endif

