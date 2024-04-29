#include <Wire.h>
#include <QMC5883LCompass.h>
 
QMC5883LCompass compass;
 
void setup() {
  Wire.begin();
  Serial.begin(9600);
  compass.initialize();
  compass.setMode(continuous, odr100, rng8, osr512);
}
 
void loop() {
  int heading = compass.azimuth();
  Serial.print("Predicted heading:");
  Serial.println(heading);
}
