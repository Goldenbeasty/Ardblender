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
  sensor.setAccelSensitivity(0); // 8g
  sensor.setGyroSensitivity(0);  // 500 degrees/s

  sensor.setThrottle();

  // set calibration values from calibration sketch.
  sensor.axe = -45;
  sensor.aye = 0.047;
  sensor.aze = -1.002;
  sensor.gxe = -0.921;
  sensor.gye = 2.512;
  sensor.gze = -0.355;

  // sensor.axe = -0.039;
  // sensor.aye = -0.924;
  // sensor.aze = -0.338;
  // sensor.gxe = -0.924;
  // sensor.gye = 2.688;
  // sensor.gze = -0.411;
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