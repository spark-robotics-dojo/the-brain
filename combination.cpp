
#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

// hc-sr04 sensor
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define max_distance 50

// ir sensor
#define irLeft A0
#define irRight A1

// motor
#define MAX_SPEED 200
#define MAX_SPEED_OFFSET 20

Servo myservo;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, max_distance);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

int distance = 0;
int leftDistance;
int rightDistance;
boolean object;

// int (moveLeft(); moveRight(); Stop(); moveRight(); moveLeft(); lookRight(); lookLeft(); turn(); moveForward());
int moveLeft() ;
int moveRight() ;
int Stop() ;
int moveRight() ;
int moveLeft() ;
int lookRight() ;
int lookLeft() ;
int turn() ;
int moveForward() ;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  myservo.attach(10);
  myservo.write(90);

  motor1.setSpeed(120);
  motor2.setSpeed(120);
  motor3.setSpeed(120);
  motor4.setSpeed(120);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 0)
  {
    objectAvoid();
    // forward
  }
  else if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 1)
  {
    objectAvoid();
    Serial.println("TL");
    // leftturn
    moveLeft();
  }
  else if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 0)
  {
    objectAvoid();
    Serial.println("TR");
    // rightturn
    moveRight();
  }
  else if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 1)
  {
    // Stop
    Stop();
  }
}


void objectAvoid()
{
  distance = getDistance();
  if (distance <= 15)
  {
    // stop
    Stop();
    Serial.println("Stop");

    lookLeft();
    lookRight();
    delay(100);
    if (rightDistance <= leftDistance)
    {
      // left
      object = true;
      turn();
      Serial.println("moveLeft");
    }
    else
    {
      // right
      object = false;
      turn();
      Serial.println("moveRight");
    }
    delay(100);
  }
  else
  {
    // forward
    Serial.println("moveforward");
    moveForward();
  }
}
int getDistance()
{
  delay(50);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 100;
  }
  return cm;
}



int lookLeft()
{
  // look left
  myservo.write(150);
  delay(500);
  leftDistance = getDistance();
  delay(100);
  myservo.write(90);
  Serial.print("Left");
  Serial.print(leftDistance);
  return leftDistance;
  delay(100);
}


int lookRight()
{
  // lock right
  myservo.write(30);
  delay(500);
  rightDistance = getDistance();
  delay(100);
  myservo.write(90);
  Serial.print(" ");
  Serial.print("Right");
  Serial.println(rightDistance);
  return rightDistance;
  delay(100);
}
void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turn()
{
  if (object == false){
    Serial.print("turn Right");
    moveLeft();
    delay(700);
    moveForward();
    delay(800);
    moveRight();
    delay(900);
    if (digitalRead(irRight) == 1)
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
    if (digitalRead(irLeft) == 1)
    {
      loop();
    }
    else
    {
      moveForward();
    }
  }
}
void moveRight()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void moveLeft()
{
  motor1.run(FORWARD);
  motor1.run(FORWARD);
  motor1.run(BACKWARD);
  motor1.run(BACKWARD);
}
