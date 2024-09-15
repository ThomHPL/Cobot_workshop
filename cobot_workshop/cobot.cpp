#include "cobot.h"

// execute the callback with the timer 2 for every created instance of cobot
ISR(TIMER2_COMPA_vect) {
  static bool first = true;
  if(first){
    first = false;
  }
  else{
    first = true;
      for(int i = 0; i < Cobot::instanceCount; i++){
        Cobot::instances[i]->control_callback();
      }
  }
}

int servo_to_pos(Servo servo, int target){
  int target_us = map(target,0,180,MIN_PULSE_WIDTH,MAX_PULSE_WIDTH);
  int current = servo.readMicroseconds();
  int delta = target_us-current;
  if(delta <= 0){
    current -= max(delta,(MAX_V_US_FACTOR * MAX_V)/(FS));
  }
  else{
    current += min(delta, (MAX_V_US_FACTOR * MAX_V)/(FS));
  }
  servo.writeMicroseconds(current);
  return current;
}

void interrupt_init(){
  noInterrupts();
  TCCR2A = 0;           // Clear Timer/Counter Control Registers
  TCCR2B = 0;
  TCNT2 = 0;            // Initialize counter value

  // Set Timer2 for CTC mode with prescaler of 64
  TCCR2A |= (1 << WGM21);   // Set to CTC mode (Clear Timer on Compare Match)
  TCCR2B |= (1 << CS22)| (1 << CS21)| (1 << CS20);    // Set prescaler to 1024

  // Calculate and set the compare match register for 10ms
  OCR2A = 156;//This gives (100Hz )

  // Enable Timer2 compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  interrupts();                              // turn interrupts back on
}


// Initialize static members
Cobot* Cobot::instances[Cobot::maxInstances] = {nullptr};
int Cobot::instanceCount = 0;

Cobot::Cobot(){
  if (instanceCount < maxInstances) {
    instances[instanceCount++] = this;  // Add the instance to the array
  }
}

Cobot::~Cobot() {
  for (int i = 0; i < instanceCount; i++) {
      if (instances[i] == this) {
          // Shift remaining elements to the left
          for (int j = i; j < instanceCount - 1; j++) {
              instances[j] = instances[j + 1];
          }
          instances[instanceCount - 1] = nullptr;  // Clear the last entry
          instanceCount--;
          break;
      }
  }
}

// Method to initialize the cobot's pins and any other setup
void Cobot::init(int middle_pin, int left_pin, int right_pin, int claw_pin) {
  left.attach(left_pin);  // attaches the servo on pin 10 to the left object
  right.attach(right_pin);  // attaches the servo on pin 9 to the right object
  left.write(left_pos);
  right.write(right_pos);
  delay(200);

  middle.attach(middle_pin);  // attaches the servo on pin 11 to the middle object
  middle.write(middle_pos);
  delay(200);

  claw.attach(claw_pin);  // attaches the servo on pin 6 to the claw object
  claw.write(claw_pos);
  delay(200);
  interrupt_init();
}

void Cobot::home() {
  left_target = 90;
  right_target = 90;
  middle_target = 90;
  claw_target = 90;
}

void Cobot::control_callback(){
  left_pos = servo_to_pos(left, left_target);
  right_pos = servo_to_pos(right, map(left_target,0,180,180,0));
  middle_pos = servo_to_pos(middle,middle_target);
  claw_pos = servo_to_pos(claw,claw_target);
}
