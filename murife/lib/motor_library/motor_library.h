#ifndef MOTOR_LIBRARY_H
#define MOTOR_LIBRARY_H

#include <Arduino.h>
#include <AFMotor.h>

// Define function prototypes
void moveForward(AF_DCMotor motor1, AF_DCMotor motor2); //AF_DCMotor motor3, AF_DCMotor motor4);

void moveBackward(AF_DCMotor motor1, AF_DCMotor motor2); //AF_DCMotor motor3, AF_DCMotor motor4);

void moveRight(AF_DCMotor motor1, AF_DCMotor motor2); //AF_DCMotor motor3, AF_DCMotor motor4);

void moveLeft(AF_DCMotor motor1, AF_DCMotor motor2); //AF_DCMotor motor3, AF_DCMotor motor4);

void Stop(AF_DCMotor motor1, AF_DCMotor motor2); //AF_DCMotor motor3, AF_DCMotor motor4);

void turn(boolean object, int leftIrSensor, int rightIrSensor, AF_DCMotor motor1, AF_DCMotor motor2); //AF_DCMotor motor3, AF_DCMotor motor4);

#endif