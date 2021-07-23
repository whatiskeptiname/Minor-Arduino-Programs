#include<AFMotor.h>

AF_DCMotor motor1(3);

void setup() {

motor1.setSpeed(255);

}

void loop() {
  // put your main code here, to run repeatedly:

motor1.run(FORWARD);

}
