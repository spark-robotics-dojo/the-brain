#include "gyro_library.h"
#include <MPU9250_asukiaaa.h>

#define MAX_ITERATIONS 100

//* ------------------------------- Calibration ---------------------------------------
float getOmega(MPU9250_asukiaaa mpuObject)
{
  // rotate the robot 360-degrees using the IR's to determine start and stop triggers.

  float omega = 0;
  bool stopTrigger = false;
  float angularVelocitySum = 0;
  float iterations = 0;
  float gY;

  // Start once triggered - we'll compute calibration time
  float startTime = millis();

  //* get angular velocity between start and stop events
  while (stopTrigger != true)
  {

    int result;

    // read the gyroscope from the MPU
    result = mpuObject.gyroUpdate();
    if (result == 0)
    {
      // read the angular velocity in the y-Axis
      gY = abs(mpuObject.gyroY());

      //! should be stopped by IR
      if (iterations < MAX_ITERATIONS)
      {
        angularVelocitySum += gY;
      }
      else
      {
        //! should be stopped by IR
        stopTrigger = true;
      }

      // increment iteration only when we successfully read from the MPU
      iterations += 1;
    }
    else
    {
      gY = 0;
    }

    // limit the number of times we read from MPU
    delay(100);
  }

  // get average angular velocity -> omega
  float angularVelocityAvg = abs(angularVelocitySum / iterations);
  omega = angularVelocityAvg;

  // Stop timer once triggered (stopTrigger = True)
  float stopTime = millis();

  // get change in time (in seconds)
  float deltaTime = stopTime - startTime;
  deltaTime = deltaTime / 1000; // convert milliseconds into seconds

  return omega;
}
