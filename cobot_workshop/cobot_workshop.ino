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
  Serial.println("Open");
  cobot.claw.move(30); // bouge la pince à 30°
  delay(200);

  // va en haut à gauche
  cobot.middle.move(160);
  cobot.left.move(110);
  cobot.right.move(110);
  while(cobot.moving()){
    delay(10); // Tant que le cobot bouge, on attend
  }
  delay(500);

  Serial.println("Close");
  cobot.claw.move(90); // bouge la pince à 90°
  while(cobot.moving()){
    delay(10);
  }
  delay(500);

  // va à droite
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