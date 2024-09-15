// create a DynaServo class that inherit from Servo class and override attach function

#ifndef DYNASERVO_H
#define DYNASERVO_H

#include <Arduino.h>
#include <Servo.h>

#define FS 100
#define MAX_ACCEL 1800 // °/sec²
#define MAX_SPEED 180 // °/sec
#define MAX_V_US_FACTOR 10

class DynaServo : public Servo {
  private:
    static const int maxInstances = 10;
    int pin;
    int max_speed = 100;
    int speed_acc = 0;
    int current_us = 1500;
    int target_us = 1500;
    bool inverted = false;

  public:
    static DynaServo* instances[maxInstances];  // Static array to hold pointers to instances
    static int instanceCount;  // Number of active instances
    static bool timer_initialized;
    DynaServo();
    DynaServo(bool inverted);
    ~DynaServo();
    uint8_t attach(int pin);
    uint8_t attach(int pin, int max_speed);
    uint8_t attach(int pin, int max_speed, int min, int max);
    int move(int target);
    bool moving();
    uint8_t getTarget();
    void control_callback();


};

#endif