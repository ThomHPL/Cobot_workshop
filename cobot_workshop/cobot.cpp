#include "cobot.h"

Cobot::Cobot(){
  this->right = DynaServo(true);
}

// Method to initialize the cobot's pins and any other setup
void Cobot::init(int middle_pin, int left_pin, int right_pin, int claw_pin) {
  this->left.attach(left_pin,270);  // attaches the servo on pin 10 to the left object
  this->right.attach(right_pin,270);  // attaches the servo on pin 9 to the right object
  delay(200);

  this->middle.attach(middle_pin,270);  // attaches the servo on pin 11 to the middle object
  delay(200);

  this->claw.attach(claw_pin,720);  // attaches the servo on pin 6 to the claw object
  delay(200);
}

void Cobot::home() {
  this->left.move(90);
  this->right.move(90);
  this->middle.move(90);
  this->claw.move(25);
}

bool Cobot::moving() {
  return this->left.moving() || this->right.moving() || this->middle.moving() || this->claw.moving();
}