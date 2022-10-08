#include "motor_library.h"
#include <AFMotor.h>

void moveForward(AF_DCMotor motor1, AF_DCMotor motor2, AF_DCMotor motor3, AF_DCMotor motor4)
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward(AF_DCMotor motor1, AF_DCMotor motor2, AF_DCMotor motor3, AF_DCMotor motor4)
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void moveRight(AF_DCMotor motor1, AF_DCMotor motor2, AF_DCMotor motor3, AF_DCMotor motor4)
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveLeft(AF_DCMotor motor1, AF_DCMotor motor2, AF_DCMotor motor3, AF_DCMotor motor4)
{
  motor1.run(FORWARD);
  motor1.run(FORWARD);
  motor1.run(BACKWARD);
  motor1.run(BACKWARD);
}

void Stop(AF_DCMotor motor1, AF_DCMotor motor2, AF_DCMotor motor3, AF_DCMotor motor4)
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void turn(boolean object,int leftIrSensor, int rightIrSensor)
{
  if (object == false)
  {
    Serial.print("turn Right");
    moveLeft();
    delay(700);
    moveForward();
    delay(800);
    moveRight();
    delay(900);
    if (digitalRead(rightIrSensor) == 1)
    {
      loop();
    }
    else
    {
      moveForward();
    }
  }
  else
  {
    Serial.println("turn left");
    moveRight();
    delay(700);
    moveForward();
    delay(800);
    moveLeft();
    delay(900);
    if (digitalRead(leftIrSensor) == 1)
    {
      loop();
    }
    else
    {
      moveForward();
    }
  }
}