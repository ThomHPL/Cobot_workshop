#include <Servo.h>
#include <Arduino.h>

#define FS 50
#define TS 1000/FS
#define MAX_V 40 // °/sec
#define MAX_V_US_FACTOR 10

int servo_to_pos(Servo servo, int target);


// Define the Cobot class
class Cobot {
  private:
    static const int maxInstances = 10;  // Maximum number of cobot instances allowed
    
    int left_pin, right_pin, middle_pin, claw_pin;
    
    Servo middle, left, right, claw;

    int left_pos = 90;
    int right_pos = 90;
    int middle_pos = 90;
    int claw_pos = 90;

    
    

  public:
    static Cobot* instances[maxInstances];  // Static array to hold pointers to instances
    static int instanceCount;  // Number of active instances
    
    int left_target = 90;
    int right_target = 90;
    int middle_target = 90;
    int claw_target = 90;

    Cobot();
    ~Cobot();
    void control_callback();
    void init(int middle_pin, int right_pin, int left_pin, int claw_pin);
    void home();
};