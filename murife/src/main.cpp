#include <Arduino.h>

// import the custom libraries
#include <obstacle_avoidance_library.h>

// ----------------------------- DEFINE PINS & ESSENTIAL VARIABLES ---------------------------------

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

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
//AF_DCMotor motor3(3, MOTOR34_1KHZ);
//AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Essential Variables
int distance = 0;
int leftDistance;
int rightDistance;
boolean object;

void setup()
{
  Serial.begin(9600);
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  myservo.attach(10);
  //myservo.write(90);

  //! Get rid of magic numbers by defining them elsewhere.
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  //motor3.setSpeed(200);
  //motor4.setSpeed(200);
}

void loop()
{

  obstacleAvoidanceAlgorithm(sonar, myservo, irLeft, irRight, rightDistance, leftDistance, object, motor1, motor2) //motor3, motor4);
}
