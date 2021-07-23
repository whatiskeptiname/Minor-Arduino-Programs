//This model is designed by susan ghimire of robotic club KEC, kalimati on June 28 2018.

#include <AFMotor.h>
#include <Servo.h>
#define trigPin 22
#define echoPin 24
#define buzzer 26

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servo1;
Servo servo2;
  
char input;
double duration, dist;
long dur;
void beep()
{
  tone(buzzer, 1000);
  delay(200);
  tone(buzzer, 900);
  delay(200);
}

void AI()
{
  forward();
  delay(1000);
  right();
  delay(500);
  forward();
  delay(100);
  right();
  delay(500);
  forward();
  delay(1000);
  left();
  delay(500);
  forward();
  delay(100);
  left();
  delay(500);
}

void forward()
{
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  servo1.write(0);
  servo2.write(0);
}

void backward()
{
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  servo1.write(90);
  servo2.write(90);
}

void right()
{
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  servo1.write(90);
  servo2.write(90);

}

void left()
{
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  servo1.write(90);
  servo2.write(90);

}

void wait()
{
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void sensor_check()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance

  dist = (duration / 2) / 29.1;
  //read tx dataa
  if (Serial2.available() > 0)
  {
    input = Serial2.read();
  }
  else
  {
    wait();
  }
  Serial.print(dist);
  Serial.print("   ");
  Serial.print(input);
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600); // baud rate
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo1.attach(10);
  servo2.attach(9);
}

void loop()
{
  sensor_check();

  servo1.write(90);
  servo2.write(90);

  if (dist <= 10)
  {
    beep();

    if (input == '3') {
    } else {
      wait();
    }
  }
  else
  {
    noTone(buzzer);


    switch (input)
    {
      case '0':
        wait();
        break;

      case '1':
        forward();
        break;

      case '2':
        right();
        break;

      case '3':
        backward();
        break;

      case '4':
        left();
        break;

      case 'b':
        servo1.write(0);
        servo2.write(0);
        break;

      case 'a':
        servo1.write(90);
        servo2.write(90);
        break;

      case '7':
        beep();
        break;

      case '8':
        noTone(buzzer);
        break;

      case '9':
        for (int i = 1; i <= 5; i++)
        {
          AI();
        }
        break;

deafult:
        wait();
        break;
    }
  }
}


