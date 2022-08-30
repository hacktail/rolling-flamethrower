//Servo correction


//libraries
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>

//motorshield objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *left = AFMS.getMotor(1);
Adafruit_DCMotor *right = AFMS.getMotor(2);
Servo turret;

//motorshield variables
const int leftDefaultSpeed = 238;
const int rightDefaultSpeed = 255;
const int servoPin = 10;

int rightSpeed = rightDefaultSpeed;
int leftSpeed = leftDefaultSpeed;

bool autoSlow = false;


//bluetooth variables
char blueToothVal = "S";
char lastValue;

//Ultrasonic sensor variables
const int pingPin = 7;
const int echoPin = 6;
long duration, cm;

//function for converting microseconds to centimeters
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}


//startup

void setup(){

    //start connections
    Serial.begin(115200);
    AFMS.begin();

    //set pinModes
    pinMode(pingPin, OUTPUT);
    pinMode(echoPin, INPUT);
    //attach servo
    turret.attach(servoPin);
    //return servo to starting possition (170)
    turret.write(180);

}

//main fucntion

void loop(){

//measure distance using ultrasonic sensor
digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
duration = pulseIn(echoPin, HIGH);

//convert microseconds to centimeters
cm = microsecondsToCentimeters(duration);

if (cm < 30 && autoSlow == true)
{
  leftSpeed = leftDefaultSpeed - 130;
  rightSpeed = rightDefaultSpeed - 130;
}
  else
  {
    leftSpeed = leftDefaultSpeed;
    rightSpeed = rightDefaultSpeed;
  }



//check if the serial port is available, if it is then it'll grab the value from the bluetooth transciever

if(Serial.available())
{
    blueToothVal=Serial.read();
}

//if serial connection isn't available then it'll retry to read it


    switch (blueToothVal)
{

//forward
case 'F':
    right->setSpeed(rightSpeed);
    left->setSpeed(leftSpeed);
    right->run(FORWARD);
    left->run(FORWARD);
    break;

//backward
case 'B':
    right->setSpeed(rightSpeed);
    left->setSpeed(leftSpeed);
    right->run(BACKWARD);
    left->run(BACKWARD);
    break;

//left
case 'L':
    right->setSpeed(rightSpeed);
    left->setSpeed(leftSpeed);
    right->run(FORWARD);
    left->run(BACKWARD);
    break;

//right
case 'R':
    right->setSpeed(rightSpeed);
    left->setSpeed(leftSpeed);
    right->run(BACKWARD);
    left->run(FORWARD);
    break;

//forward right
case 'G':
    right->setSpeed(rightSpeed);
    left->setSpeed(leftSpeed - 100);
    right->run(FORWARD);    
    left->run(FORWARD);
    break;

//forward left
case 'I':
    right->setSpeed(rightSpeed - 100);
    left->setSpeed(leftSpeed);
    right->run(FORWARD);
    left->run(FORWARD);
    break;

//backward right
case 'J':
    right->setSpeed(rightSpeed - 100);
    left->setSpeed(leftSpeed);
    right->run(BACKWARD);
    left->run(BACKWARD);
    break;
  
//backward left
case 'H':
    right->setSpeed(rightSpeed);
    left->setSpeed(leftSpeed - 100);
    right->run(BACKWARD);
    left->run(BACKWARD);
    break;

//stop
case 'S':
    right->run(RELEASE);
    left->run(RELEASE);
    break;

//Slow mode on
case 'X':
    autoSlow = true;
    break;

//slow mode off
case 'x':
    autoSlow = false;
    break;





//turret positions
case '1':
    turret.write(180);
    
    break;

case '2':
    turret.write(170);
    
    break;

case '3':
    turret.write(155);
    
    break;

case '4':
    turret.write(140);
    
    break;

case '5':
    turret.write(125);
    
    break;
  
case '6':
    turret.write(110);
    
    break;

case '7':
    turret.write(95);
    
    break;

case '8':
    turret.write(80);
    break;

case '9':
    turret.write(65);
    
    break;

case 'q':
    turret.write(50);
    
    break;
}

    }
