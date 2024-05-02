#include <Wire.h>
#include <QMC5883LCompass.h>
 
QMC5883LCompass compass;
 
void setup() {
  Wire.begin();
  Serial.begin(9600);
  compass.initialize();
  compass.setMode(continuous, odr50, rng8, osr512);
}
 
void loop() {
  while (!Serial.available()) {}
  String msg = Serial.readStringUntil('\n');
  if (msg == "send") {
    QMC5883LCompass::rawReading data = compass.getRawData();
    Serial.print(data.x);
    Serial.print(",");
    Serial.print(data.y);
    Serial.print(",");
    Serial.print(data.z);
    Serial.print(",");
    Serial.println(atan2(data.y, data.x));
  }
}