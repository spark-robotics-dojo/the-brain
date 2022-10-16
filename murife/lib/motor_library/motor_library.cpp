#include "motor_library.h"
#include <AFMotor.h>

void moveForward(AF_DCMotor LeftMotor, AF_DCMotor RightMotor) //AF_DCMotor motor3, AF_DCMotor motor4)
{
  LeftMotor.run(FORWARD);
  RightMotor.run(FORWARD);
  //motor3.run(FORWARD);
  //motor4.run(FORWARD);
}

void moveBackward(AF_DCMotor LeftMotor, AF_DCMotor RightMotor) //AF_DCMotor motor3, AF_DCMotor motor4)
{
  LeftMotor.run(BACKWARD);
  RightMotor.run(BACKWARD);
  //motor3.run(BACKWARD);
  //motor4.run(BACKWARD);
}

void moveRight(AF_DCMotor LeftMotor, AF_DCMotor RightMotor) //AF_DCMotor motor3, AF_DCMotor motor4)
{
  LeftMotor.run(BACKWARD);
  RightMotor.run(BACKWARD);
  //motor3.run(FORWARD);
  //motor4.run(FORWARD);
}

void moveLeft(AF_DCMotor LeftMotor, AF_DCMotor RightMotor) //AF_DCMotor motor3, AF_DCMotor motor4)
{
  LeftMotor.run(FORWARD);
  RightMotor.run(FORWARD);
  //LeftMotor.run(BACKWARD);
  //LeftMotor.run(BACKWARD);
}

void Stop(AF_DCMotor LeftMotor, AF_DCMotor RightMotor) //AF_DCMotor motor3, AF_DCMotor motor4)
{
  LeftMotor.run(RELEASE);
  RightMotor.run(RELEASE);
  //motor3.run(RELEASE);
  //motor4.run(RELEASE);
}

void turn(boolean object, int leftIrSensor, int rightIrSensor, AF_DCMotor LeftMotor, AF_DCMotor RightMotor) //AF_DCMotor motor3, AF_DCMotor motor4)
{
  if (object == false)
  {
    Serial.print("turn Right");
    moveLeft(LeftMotor, RightMotor); //motor3, motor4);
    delay(700);
    moveForward(LeftMotor, RightMotor); //motor3, motor4);
    delay(800);
    moveRight(LeftMotor, RightMotor); //motor3, motor4);
    delay(900);
    if (digitalRead(rightIrSensor) == 1)
    {
      loop();
    }
    else
    {
      moveForward(LeftMotor, RightMotor) //motor3, motor4);
    }
  }
  else
  {
    Serial.println("turn left");
    moveRight(LeftMotor, RightMotor); //motor3, motor4);
    delay(700);
    moveForward(LeftMotor, RightMotor); //motor3, motor4);
    delay(800);
    moveLeft(LeftMotor, RightMotor); //motor3, motor4);
    delay(900);
    if (digitalRead(leftIrSensor) == 1)
    {
      loop();
    }
    else
    {
      moveForward(LeftMotor, RightMotor); //motor3, motor4);
    }
  }
}