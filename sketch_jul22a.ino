#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
//sensor pins
#define trig_pin 11 //analog input 1
#define echo_pin 12 //analog input 2
Servo servoMotor ;
//our L298N control pins
int distance, t, leftDistance = 0 , rightDistance = 0;
const int LeftMotorsForward = 3;
const int LeftMotorsBackward = 2;
const int RightMotorsForward = 4;
const int RightMotorsBackward = 5;
void setup() {
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(LeftMotorsForward, OUTPUT);
  pinMode(LeftMotorsBackward, OUTPUT);
  pinMode(RightMotorsBackward, OUTPUT);
  pinMode(RightMotorsForward, OUTPUT);
  servoMotor.attach(10);
  servoMotor.write(90);//angle 0 look right -- angle 180 look left
}
void ultrasonic() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  t = pulseIn(echo_pin, HIGH);
  distance = t / 57;
  delay(500);
}

void moveStop() {

  digitalWrite(RightMotorsForward, LOW);
  digitalWrite(LeftMotorsForward, LOW);
  digitalWrite(RightMotorsBackward, LOW);
  digitalWrite(LeftMotorsBackward, LOW);
}
void moveForward() {

  digitalWrite(LeftMotorsForward, HIGH);
  digitalWrite(RightMotorsForward, HIGH);

  digitalWrite(LeftMotorsBackward, LOW);
  digitalWrite(RightMotorsBackward, LOW);
}
void moveBackward() {
  digitalWrite(LeftMotorsBackward, HIGH);
  digitalWrite(RightMotorsBackward, HIGH);
  digitalWrite(LeftMotorsForward, LOW);
  digitalWrite(RightMotorsForward, LOW);

}
void turnRight() {
  digitalWrite(RightMotorsBackward, HIGH);
  digitalWrite(LeftMotorsForward, HIGH);
  digitalWrite(RightMotorsForward, LOW);
  digitalWrite(LeftMotorsBackward, LOW);
  delay (740);
  moveStop();
}
void turnLeft() {

  digitalWrite(RightMotorsForward, HIGH);
  digitalWrite(LeftMotorsBackward, HIGH);
  digitalWrite(RightMotorsBackward, LOW);
  digitalWrite(LeftMotorsForward, LOW);

  delay (740);
  moveStop();
}
void loop() {
  ultrasonic();

  delay(50);
  if (distance <= 25) {
    moveStop();
    delay(500);
    moveBackward();
    delay(500);
    moveStop();
    delay(500);
    servoMotor.write(0);
    ultrasonic();
    leftDistance = distance;
    delay(1000);
    servoMotor.write(180);
    ultrasonic();
    rightDistance = distance;
    delay(1000);
    servoMotor.write(90);
    delay(600);

    if (leftDistance > rightDistance) {
      turnLeft();
      delay(740);
      moveForward();
    }
    else {
      turnRight();
      delay(740);
      moveForward();
    }

  }
  else {
    moveForward();
  }
}
