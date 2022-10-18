#include "maze_solving_library.h"
#include <obstacle_avoidance_library.h>
#include <motor_library.h>
#include <gyro_library.h>
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define exitMazeCount 7 // 6-th index
#define mazeExitDistance 10

// Maze direction representation
int mazeInterpretation[8] = {1, 2, 1, 2, 2, 1, 1, 2};

int turnCount = 0;
bool exitCondition = false;

// for non-blocking code.
// unsigned long previousDelayTimeInterval = millis();

// function prototypes
bool mazeTurn(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
bool mazeTurnRight(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
bool mazeTurnLeft(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
void mazeExit(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity, Servo servoObject, NewPing sonarObject);

void mazeSolvingAlgorithm(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity, Servo servoObject, NewPing sonarObject)
{

  bool turn = false;

  // could we get rid of the loop as this function will be called in the main loop??
  while (turn == false && exitCondition == false)
  {
    moveForward(motor1, motor2);

    // trigger turning if we approach the wall <Ultrasonic>
  }

  if (exitCondition == true)
  {
    mazeExit(motor1, motor2, angular_velocity, servoObject, sonarObject);
  }
  else
  {
    turn = mazeTurn(motor1, motor2, angular_velocity);
  }
}

bool mazeTurn(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity)
{

  int mazeAction = mazeInterpretation[turnCount];
  bool stillTurning = false;

  if (mazeAction == 1)
  {
    stillTurning = mazeTurnLeft(motor1, motor2, angular_velocity);
  }
  else
  {
    stillTurning = mazeTurnRight(motor1, motor2, angular_velocity);
  }

  turnCount += 1;

  // Set exit conditions
  if (turnCount == exitMazeCount)
  {
    exitCondition = true;
  }

  return stillTurning;
}

bool mazeTurnRight(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity)
{

  // delay time from Calibrated gyro
  int delayTime = getDeltaT(90, angular_velocity);

  // convert seconds into milliseconds
  delayTime = delayTime * 1000;

  // Turn
  moveRight(motor1, motor2);
  // blocking delay
  delay(delayTime);
  // stop
  Stop(motor1, motor2);

  return false; // return true while turning??

  // // non-blocking delay
  // unsigned long currentTime = millis();

  // if (currentTime - previousDelayTimeInterval > delayTime)
  // {
  //   previousDelayTimeInterval = currentTime;
  //   moveRight(motor1, motor2); // replace with stop??
  // }
}

bool mazeTurnLeft(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity)
{
  // delay time from Calibrated gyro
  int delayTime = getDeltaT(90, angular_velocity);

  // convert seconds into milliseconds
  delayTime = delayTime * 1000;

  // Turn
  moveLeft(motor1, motor2);
  // blocking delay
  delay(delayTime);
  // stop
  Stop(motor1, motor2);

  return false;
}

void mazeExit(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity, Servo servoObject, NewPing sonarObject)
{
  // look right
  checkRight(servoObject);

  // move forward
  moveForward(motor1, motor2);

  // if opening is found
  int distance = getDistance(sonarObject);

  if (distance > mazeExitDistance)
  {
    // stop
    Stop(motor1, motor2);

    // turn right
    mazeTurnRight(motor1, motor2, angular_velocity);

    // look forward
    checkForward(servoObject);

    // move forward
    moveForward(motor1, motor2);
  }

  // By this time, we are hopefully out of the maze and headed to the finish line.
  return;
}