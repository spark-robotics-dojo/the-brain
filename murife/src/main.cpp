#include <Arduino.h>
#include <MPU9250_asukiaaa.h>

// import the custom libraries
#include <obstacle_avoidance_library.h>
#include <motor_library.h>
#include <gyro_library.h>

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

AF_DCMotor LeftMotor(1, MOTOR12_8KHZ);
AF_DCMotor RightMotor(2, MOTOR12_8KHZ);
// AF_DCMotor motor3(3, MOTOR34_1KHZ);
// AF_DCMotor motor4(4, MOTOR34_1KHZ);

MPU9250_asukiaaa gyroSensor;
float calibrated_angular_velocity = 0;

// Essential Variables
int distance = 0;
int leftDistance;
int rightDistance;
boolean object;

float getOmega();

void setup()
{

  Serial.begin(115200);
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);

  Serial.println("\n+++++++++++++++++++++++ ROBOT CALIBRATION STARTED +++++++++++++++++++++++ ");

  Serial.println("\nCALIBRATION : MOTOR_SETTINGS");
  myservo.attach(10);
  // myservo.write(90);

  LeftMotor.setSpeed(200);
  LeftMotor.run(RELEASE);
  RightMotor.setSpeed(200);
  RightMotor.run(RELEASE);
  // motor3.setSpeed(200);
  // motor4.setSpeed(200);

  Serial.println("\nCALIBRATION : MPU9250, GET_OMEGA");
  // Initialize MPU9250
  gyroSensor.beginAccel();
  gyroSensor.beginGyro();
  gyroSensor.beginMag();

  // calibrated_angular_velocity = getOmega(gyroSensor, LeftMotor, RightMotor, irLeft, irRight);
  Serial.print("calibrated_angular_velocity, omega: ");
  Serial.println(calibrated_angular_velocity);

  Serial.println("\n+++++++++++++++++++++++ ROBOT CALIBRATION SUCCESS!!! +++++++++++++++++++++++ ");

  // Serial.println(getDeltaT(90, calibrated_angular_velocity));
}

void loop()
{
  // Serial.println(calibrated_angular_velocity);
  // obstacleAvoidanceAlgorithm(sonar, myservo, irLeft, irRight, rightDistance, leftDistance, object, motor1, motor2) // motor3, motor4);
  moveForward(LeftMotor, RightMotor);
}
