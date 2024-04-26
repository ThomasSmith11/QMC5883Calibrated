#ifndef QMC5883L_Compass
#define QMC5883L_Compass

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

class QMC5883L_Compass {
public:
  QMC5883L_Compass();
  struct rawReading {
    uint16_t x;
    uint16_t y;
    uint16_t z;
  };
  void calibrateCompass(int hardIron[3], float softIron[3][3]);
  void setDeclination();
  float getHeading();
  void setMode(uint8_t sampleMode, uint8_t outputDataRate, uint8_t fieldRange, uint8_t overSampleRate);
  rawReading getRawReading();
private:
  float declination;
  int hardIron[3];
  float softIron[3][3];

  rawReading data;
  
  void writeRegister(uint8_t reg, uint8_t val);
  float azimuth(int y, int x);
}

#endif
