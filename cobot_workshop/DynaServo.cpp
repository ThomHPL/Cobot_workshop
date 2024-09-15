#include "DynaServo.h"

DynaServo* DynaServo::instances[DynaServo::maxInstances] = {nullptr};;  // Static array to hold pointers to instances
int DynaServo::instanceCount = 0;  // Number of active instances
bool DynaServo::timer_initialized = false;

ISR(TIMER2_COMPA_vect) {
  static bool first = true;
  if(first){
    first = false;
  }
  else{
    first = true;
    for(int i = 0; i < DynaServo::instanceCount; i++){
      DynaServo::instances[i]->control_callback();
    }
  }
}

void timer_init(){
  noInterrupts();
  TCCR2A = 0;           // Clear Timer/Counter Control Registers
  TCCR2B = 0;
  TCNT2 = 0;            // Initialize counter value

  // Set Timer2 for CTC mode with prescaler of 64
  TCCR2A |= (1 << WGM21);   // Set to CTC mode (Clear Timer on Compare Match)
  TCCR2B |= (1 << CS22)| (1 << CS21)| (1 << CS20);    // Set prescaler to 1024

  // Calculate and set the compare match register for 10ms
  OCR2A = 156;//This gives 100Hz

  // Enable Timer2 compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  interrupts();                              // turn interrupts back on
}

DynaServo::DynaServo(){
  if (instanceCount < maxInstances) {
    instances[instanceCount++] = this;  // Add the instance to the array
  }

  if(!timer_initialized){
    timer_init();
    timer_initialized = true;
  }
}

DynaServo::DynaServo(bool inverted){
  this->inverted = inverted;
  if (instanceCount < maxInstances) {
    instances[instanceCount++] = this;  // Add the instance to the array
  }

  if(!timer_initialized){
    timer_init();
    timer_initialized = true;
  }
}

DynaServo::~DynaServo() {
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

uint8_t DynaServo::attach(int pin){
  return this->attach(pin, MAX_SPEED, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}
uint8_t DynaServo::attach(int pin, int max_speed){
  return this->attach(pin, max_speed, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t DynaServo::attach(int pin, int max_speed, int min, int max){
  this->pin = pin;
  this->max_speed = max_speed;
  uint8_t ret = Servo::attach(pin, min, max);
  this->current_us = this->readMicroseconds();
  return ret;
}

int DynaServo::move(int target){
  if(inverted){
    target = map(target,0,180,180,0);
  }
  this->target_us = map(target,0,180,MIN_PULSE_WIDTH,MAX_PULSE_WIDTH);
  return this->target_us - this->current_us;
}

bool DynaServo::moving(){
  return !(this->target_us == this->current_us);
}

uint8_t DynaServo::getTarget()
{
  return map(this->target_us,MIN_PULSE_WIDTH,MAX_PULSE_WIDTH,0,180);
}

void DynaServo::control_callback(){
  this->current_us = this->readMicroseconds();
  int delta = target_us-current_us;
  if(delta <= 0){
    current_us -= max(delta,(MAX_V_US_FACTOR * this->max_speed )/(FS));
  }
  else{
    current_us += min(delta, (MAX_V_US_FACTOR * this->max_speed )/(FS));
  }
  this->writeMicroseconds(current_us);
  return current_us;
}