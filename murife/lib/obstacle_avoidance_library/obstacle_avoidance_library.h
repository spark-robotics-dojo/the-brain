#ifndef OBSTACLE_AVOIDANCE_LIBRARY_H
#define OBSTACLE_AVOIDANCE_LIBRARY_H

#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

// Define function prototypes
void obstacleAvoidanceAlgorithm(NewPing sonarObject, Servo servoObject, int leftIrSensor, int rightIrSensor, int rightDistance, int leftDistance, boolean object, AF_DCMotor LeftMotor, AF_DCMotor RightMotor); // AF_DCMotor motor3, AF_DCMotor motor4);

void objectAvoid(NewPing sonarObject, Servo servoObject, int rightDistance, int leftDistance, boolean object, int leftIrSensor, int rightIrSensor, AF_DCMotor LeftMotor, AF_DCMotor RightMotor); // AF_DCMotor motor3, AF_DCMotor motor4);

int getDistance(NewPing sonarObject);

int lookLeft(NewPing sonarObject, Servo servoObject, int leftDistance);

int lookRight(NewPing sonarObject, Servo servoObject, int rightDistance);

void checkRight(Servo servoObject);

void checkLeft(Servo servoObject);

void checkForward(Servo servoObject);

#endif