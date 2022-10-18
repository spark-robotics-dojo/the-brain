#include "gyro_library.h"
#include <MPU9250_asukiaaa.h>
#include <motor_library.h>
#include <AFMotor.h>

#define MAX_ITERATIONS 100

//* ------------------------------- Calibration ---------------------------------------
float getOmega(MPU9250_asukiaaa mpuObject, AF_DCMotor motor1, AF_DCMotor motor2, int leftIrSensor, int rightIrSensor)
{
  // rotate the robot 360-degrees using the IR's to determine start and stop triggers.

  float omega = 0;
  bool stopTrigger = false;
  float angularVelocitySum = 0;
  float iterations = 0;
  float gY;
  long delayInterval100 = 100;
  unsigned long previousTimeGyroLoop = millis();

  //! This is a Blocking Function!
  //? Is it really?
  moveRight(motor1, motor2);

  // Start timer once triggered - we'll compute calibration time
  while (digitalRead(leftIrSensor) != 1)
  {
  }

  float startTime = millis();
  int rightIRTriggerCount = 0;
  int leftIRTriggerCount = 0;

  //* get angular velocity between start and stop events
  while (stopTrigger != 1)
  {

    // Implemented non-blocking code.
    // The delay limits the number of times we read from MPU
    unsigned long currentTime = millis();

    if (currentTime - previousTimeGyroLoop > delayInterval100)
    {
      previousTimeGyroLoop = currentTime;
      int result;

      // read the gyroscope from the MPU
      result = mpuObject.gyroUpdate();
      if (result == 0)
      {
        // read the angular velocity in the y-Axis
        gY = abs(mpuObject.gyroY());

        angularVelocitySum += gY;

        // increment iteration only when we successfully read from the MPU
        iterations += 1;
      }
      else
      {
        gY = 0;
      }

      if (digitalRead(rightIrSensor) == 1)
      {
        rightIRTriggerCount += 1;
      }

      if (digitalRead(leftIrSensor) == 1)
      {
        leftIRTriggerCount += 1;
      }

      // Stop the calibration routine.
      if (rightIRTriggerCount == 2 && leftIRTriggerCount == 1)
      {
        // Stop the motors (robot)
        Stop(motor1, motor2);

        // break out of loop
        stopTrigger = 1;
      }
    }
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

float getDeltaT(int angle, float omega)
{
  // Used to get the time required to move the motors to rotate a given angle.

  float deltaT = angle / omega;

  return deltaT;
}