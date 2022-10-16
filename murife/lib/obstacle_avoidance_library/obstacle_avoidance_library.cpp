#include "obstacle_avoidance_library.h"
#include <NewPing.h>
#include <Servo.h>
#include <motor_library.h>
#include <AFMotor.h>

void obstacleAvoidanceAlgorithm(NewPing sonarObject, Servo servoObject, int leftIrSensor, int rightIrSensor, int rightDistance, int leftDistance, boolean object, AF_DCMotor motor1, AF_DCMotor motor2) //AF_DCMotor motor3, AF_DCMotor motor4)
{
  // put your main code here, to run repeatedly:
  if (digitalRead(leftIrSensor) == 0 && digitalRead(rightIrSensor) == 0)
  {
    objectAvoid(sonarObject, servoObject, rightDistance, leftDistance, object, leftIrSensor, rightIrSensor, motor1, motor2); //motor3, motor4);
    // forward
  }
  else if (digitalRead(leftIrSensor) == 0 && digitalRead(rightIrSensor) == 1)
  {
    objectAvoid(sonarObject, servoObject, rightDistance, leftDistance, object, leftIrSensor, rightIrSensor, motor1, motor2); //motor3, motor4);
    Serial.println("TL");
    // leftturn
    moveLeft(motor1, motor2) //motor3, motor4);
  }
  else if (digitalRead(leftIrSensor) == 1 && digitalRead(rightIrSensor) == 0)
  {
    objectAvoid(sonarObject, servoObject, rightDistance, leftDistance, object, leftIrSensor, rightIrSensor, motor1, motor2mo); //tor3, motor4);
    Serial.println("TR");
    // rightturn
    moveRight(motor1, motor2); //motor3, motor4);
  }
  else if (digitalRead(leftIrSensor) == 1 && digitalRead(rightIrSensor) == 1)
  {
    // Stop
    Stop(motor1, motor2); //motor3, motor4);
  }
}

void objectAvoid(NewPing sonarObject, Servo servoObject, int rightDistance, int leftDistance, boolean object, int leftIrSensor, int rightIrSensor, AF_DCMotor motor1, AF_DCMotor motor2) //AF_DCMotor motor3, AF_DCMotor motor4)
{
  int distance = getDistance(sonarObject);
  if (distance <= 15)
  {
    // stop
    Stop(motor1, motor2); ///motor3, motor4);
    Serial.println("Stop");

    lookLeft(sonarObject, servoObject, leftDistance);
    lookRight(sonarObject, servoObject, rightDistance);
    delay(100);

    if (rightDistance <= leftDistance)
    {
      // left
      int object = true;
      turn(object, leftIrSensor, rightIrSensor, motor1, motor2); //motor3, motor4);
      Serial.println("moveLeft");
    }
    else
    {
      // right
      int object = false;
      turn(object, leftIrSensor, rightIrSensor, motor1, motor2); //motor3, motor4);
      Serial.println("moveRight");
    }
    delay(100);
  }
  else
  {
    // forward
    Serial.println("moveforward");
    moveForward(motor1, motor2); //motor3, motor4);
  }
}

int getDistance(NewPing sonarObject)
{
  delay(50);
  int cm = sonarObject.ping_cm();

  //! What does this mean / do ?
  if (cm == 0)
  {
    cm = 100;
  }

  return cm;
}

int lookLeft(NewPing sonarObject, Servo servoObject, int leftDistance)
{
  // look left
  //! Magic numbers need to be explained or defined at the top level
  servoObject.write(150);
  delay(500);
  leftDistance = getDistance(sonarObject);
  delay(100);
  servoObject.write(90);
  Serial.print("Left");
  Serial.print(leftDistance);

  //! Why delay after return statement??
  return leftDistance;
  delay(100);
}

int lookRight(NewPing sonarObject, Servo servoObject, int rightDistance)
{
  // look right
  //! Magic numbers need to be explained or defined at the top level
  servoObject.write(30);
  delay(500);
  rightDistance = getDistance(sonarObject);
  delay(100);
  servoObject.write(90);
  Serial.print(" ");
  Serial.print("Right");
  Serial.println(rightDistance);

  //! Why delay after return statement??
  return rightDistance;
  delay(100);
}