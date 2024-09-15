#include <Servo.h>
#include <Arduino.h>
#include "DynaServo.h"

#define FS 50
#define TS 20
#define MAX_V 40 // °/sec
#define MAX_V_US_FACTOR 10

// Define the Cobot class
class Cobot {
  private:
    int left_pin, right_pin, middle_pin, claw_pin;

  public:
    DynaServo middle, left, right, claw;
    Cobot();
    ~Cobot();
    void init(int middle_pin, int right_pin, int left_pin, int claw_pin);
    void home();
};