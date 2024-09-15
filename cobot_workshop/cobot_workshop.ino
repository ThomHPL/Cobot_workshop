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
Cobot cobot;
// DynaServo middle, left, claw;
// DynaServo right = DynaServo(true);

void setup() 
{ 
  // Init cobot with motor pins
  cobot.init(11, 10, 9, 6);
  cobot.home();
  
  Serial.begin(9600);
  delay(1000);
}

void loop()
{ 
  // go up and left
  Serial.println("Open");
  cobot.claw.move(30);
  delay(200);
  cobot.middle.move(160);
  cobot.left.move(110);
  cobot.right.move(110);
  while(cobot.moving()){
    delay(10);
  }
  delay(500);

  // close claw
  Serial.println("Close");
  cobot.claw.move(90);
  while(cobot.moving()){
    delay(10);
  }
  delay(500);

  // go right
  cobot.middle.move(10);
  while(cobot.moving()){
    delay(10);
  }

  // go down and open claw
  Serial.println("Down");
  cobot.left.move(30);
  cobot.right.move(30);
  while(cobot.moving()){
    delay(10);
  }
}