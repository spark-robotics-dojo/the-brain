#ifndef GYRO_LIBRARY_H
#define GYRO_LIBRARY_H

#include <Arduino.h>
#include <MPU9250_asukiaaa.h>
#include <AFMotor.h>

// Define function prototypes
float getOmega(MPU9250_asukiaaa mpuObject, AF_DCMotor motor1, AF_DCMotor motor2, int leftIrSensor, int rightIrSensor);
float getDeltaT(int angle, float omega);

#endif