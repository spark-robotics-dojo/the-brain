#ifndef MAZE_SOLVING_LIBRARY_H
#define MAZE_SOLVING_LIBRARY_H

#include <Arduino.h>
#include <motor_library.h>
#include <gyro_library.h>
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

// Define function prototypes
// function prototypes
bool mazeTurn(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
bool mazeTurnRight(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
bool mazeTurnLeft(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
void mazeExit(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity, Servo servoObject, NewPing sonarObject);
bool mazeUTurn(NewPing sonarObject, AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
void mazeSolvingAlgorithm(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity, Servo servoObject, NewPing sonarObject);

#endif