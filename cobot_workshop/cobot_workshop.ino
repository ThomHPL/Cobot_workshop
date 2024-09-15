#include <Servo.h>
#include "cobot.h"

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
  
  Serial.begin(9600);
}

void loop()
{ 
      
  // int distance = sensor.getCM();

  // // Write values to serial port
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println("cm");
  // if(distance == 0){
  // }
  // else if(distance <= 20){
  //   left_target += 5*(20-distance);
  // }
  // else{
  //   left_target = 30;
  // }

  // go up and left and open claw
  Serial.println("Open");
  cobot.claw_target = 30;
  cobot.middle_target = 120;
  cobot.left_target = 100;
  delay(2000);

  // close claw
  Serial.println("Close");
  cobot.claw_target = 90;
  delay(1800);

  // go right
  cobot.middle_target = 50;
  delay(2000);

  // go down
  Serial.println("Down");
  cobot.left_target = 30;
  delay(2000);
}