#include <Servo.h>
#include "cobot.h"
#include "DynaServo.h"

#include <DistanceSensor.h>

// Define pins
const int echoPin = 3;
const int trigPin = 2;

// Start the sensor
DistanceSensor sensor(trigPin, echoPin);

// create cobot instance
// Cobot cobot;
DynaServo middle, left, claw;
DynaServo right = DynaServo(true);

void setup() 
{ 
  // Init cobot with motor pins
  //cobot.init(11, 10, 9, 6);
  //cobot.home();
  claw.attach(6, 180);
  delay(200);
  middle.attach(11,80);
  delay(200);
  left.attach(10,100);
  delay(200);
  right.attach(9,100);
  delay(200);

  Serial.begin(9600);
  delay(1000);
}

void loop()
{ 
  // go up and left
  Serial.println("Open");
  claw.move(30);
  delay(200);
  middle.move(160);
  left.move(110);
  right.move(110);
  while(middle.moving()){
    delay(10);
  }
  delay(500);

  // close claw
  Serial.println("Close");
  claw.move(90);
  while(claw.moving()){
    delay(10);
  }
  delay(500);

  // go right
  middle.move(10);
  while(middle.moving()){
    delay(10);
  }

  // go down and open claw
  Serial.println("Down");
  left.move(30);
  right.move(30);
  while(right.moving()){
    delay(10);
  }
}