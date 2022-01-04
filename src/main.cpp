#include <Arduino.h>
#include "GY521.h"

GY521 sensor(0x68);

uint32_t counter = 0;

String cmd;

void setup()
{
  Serial.begin(115200);
  // Serial.println(__FILE__);

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
  sensor.setAccelSensitivity(0);
  sensor.setGyroSensitivity(0);

  sensor.setThrottle();

  // set calibration values from calibration sketch.
  sensor.axe = -0.007;
  sensor.aye = 0.021;
  sensor.aze = -0.010;
  sensor.gxe = -0.774;
  sensor.gye = 2.583;
  sensor.gze = -0.718;
}

void loop()
{
  sensor.read();
  cmd = Serial.readStringUntil('\n');

  if (cmd == "x")
  {
    float roll = sensor.getRoll(); // x
    Serial.println(roll);
  }
  else if (cmd == "y")
  {
    float pitch = sensor.getPitch(); // y
    Serial.println(pitch);
  }
  else if (cmd == "z")
  {
    float yaw = sensor.getYaw(); // z
    Serial.println(yaw);
  }
}