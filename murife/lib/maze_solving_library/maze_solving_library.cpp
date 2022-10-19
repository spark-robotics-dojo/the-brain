#include "maze_solving_library.h"
#include <obstacle_avoidance_library.h>
#include <motor_library.h>
#include <gyro_library.h>
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define exitMazeCount 7      // 6-th index
#define uTurnCount 4         // 3-rd index
#define uTurnExitDistance 40 // hard-coded distance to determine uTurn location
#define mazeExitDistance 15  // Defines the opening (exit of the maze)
#define distanceToWall 10    // determines distance to trigger turn event

// Maze direction representation
int mazeInterpretationOld[8] = {1, 2, 1, 2, 2, 1, 1, 2};
// new maze
int mazeInterpretation[8] = {1, 2, 2, 1, 1, 2, 1, 2};

// count the number of turns to determine position in the maze
int turnCount = 0;
bool exitCondition = false;
bool uTurnCondition = false;

// for non-blocking code.
// unsigned long previousDelayTimeInterval = millis();

// function prototypes
bool mazeTurn(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
bool mazeTurnRight(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
bool mazeTurnLeft(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity);
bool mazeUTurn(NewPing sonarObject, AF_DCMotor motor1, AF_DCMotor motor2);
void mazeExit(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity, Servo servoObject, NewPing sonarObject);

void mazeSolvingAlgorithm(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity, Servo servoObject, NewPing sonarObject)
{

  bool turn = false;

  // could we get rid of the loop as this function will be called in the main loop??
  while (turn == false && exitCondition == false && uTurnCondition == false)
  {
    moveForward(motor1, motor2);

    // trigger turning if we approach the wall <Ultrasonic>
    int distance = getDistance(sonarObject);
    if (distance < distanceToWall)
    {
      turn = true;
    }
  }

  // runs when we are at turn 5
  if (uTurnCondition == true)
  {
    mazeUTurn(sonarObject, motor1, motor2);
  }
  else
  {
    turn = mazeTurn(motor1, motor2, angular_velocity);
  }

  // runs when we are exiting the maze (final turn)
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

  // determines whether to turn left or right
  int mazeAction = mazeInterpretation[turnCount];
  // flag to ensure we've turned
  bool stillTurning = false;

  if (mazeAction == 1)
  {
    stillTurning = mazeTurnLeft(motor1, motor2, angular_velocity);
  }
  else
  {
    stillTurning = mazeTurnRight(motor1, motor2, angular_velocity);
  }

  // increase turnCount to mark turn as complete
  turnCount += 1;

  // Set UTurn conditions
  if (turnCount == uTurnCount)
  {
    uTurnCondition = true;
  }

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

bool mazeUTurn(NewPing sonarObject, AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity)
{

  int distance = getDistance(sonarObject);

  while (distance > uTurnExitDistance)
  {
    moveForward(motor1, motor2);
    // updated distance to wall
    distance = getDistance(sonarObject);
  }

  Stop(motor1, motor2);

  mazeTurnLeft(motor1, motor2, angular_velocity);

  // give back control to main mazeSolving algorithm.
  // accounts for the left turn above
  turnCount += 1;

  uTurnCondition = false;

  return false;
}

void mazeExit(AF_DCMotor motor1, AF_DCMotor motor2, float angular_velocity, Servo servoObject, NewPing sonarObject)
{
  // turn left (final turn)
  mazeTurn(motor1, motor2, angular_velocity);

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