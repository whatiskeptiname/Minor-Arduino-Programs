#include"PPMReader.h"
#include<Servo.h>

int const ml1 = 7;
int const ml2 = 8;
int const mr1 = 9;
int const mr2 = 10;
int const pwm1 = 6;
int const pwm2 = 11;
Servo servo_1, servo_2;

int interruptPin = 2;
int channelAmount = 8;
int ch[8];
int servoPin1 = 3;
int servoPin2 = 5;
int pp1, pp2, pp3, pp4;
int servo1, servo2;
int var_maxPWM = 0, var_maxPWMTurn = 0;
boolean ch1_neutral = true, ch3_neutral =  true;

PPMReader ppm(interruptPin, channelAmount);

void setup()
{
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  servo_1.attach(servoPin1);
  servo_2.attach(servoPin2);

  Serial.begin(9600);
}

void loop()
{
  readPPMData();

  //  if (ch[7] < 1500)
  //  {
  if (ch[6] > 1500)
  {

    servo1 = map(ch[4], 1000, 2000, 90, 0);
    servo2 = map(ch[4], 1000, 2000, 90, 0);
    servo_1.write(servo1);
    servo_2.write(servo2);

    if (ch[7] > 1500)
    {
      servo_1.write(servo1);
      servo_2.write(servo2);
      delay(5);
      servo_1.write(servo1+20);
      servo_2.write(servo2+20);
      delay(5);
    }

    if (ch[5] < 1333)
    {
      var_maxPWM = 200;
      var_maxPWMTurn = 200;
      Serial.println("First Gear");
    }
    else if (ch[5] > 1334 && ch[5] < 1666)
    {
      var_maxPWM = 255;
      var_maxPWMTurn = 200;
      Serial.println("Second Gear");
    }
    else
    {
      var_maxPWM = 255;
      var_maxPWMTurn = 255;
      Serial.println("Third Gear");
    }

    if (ch[1] > 1485 && ch[1] < 1515)
    {
      ch1_neutral = true;
    }
    else if (ch[1] > 1515)
    {
      ch1_neutral = false;
      pp1 = abs(map(ch[1], 1500, 2000, 0, var_maxPWM));
      pp2 = abs(map(ch[1], 1500, 2000, 0, var_maxPWM));
      move_forward();
    }
    else if (ch[1] < 1485)
    {
      ch1_neutral = false;
      pp1 = abs(map(ch[1], 1000, 1500, var_maxPWM, 0));
      pp2 = abs(map(ch[1], 1000, 1500, var_maxPWM, 0));
      move_backward();
    }
    if (ch[3] > 1485 && ch[3] < 1515)
    {
      ch3_neutral = true;
    }
    else if (ch[3] > 1515)
    {
      ch3_neutral = false;
      pp3 = abs(map(ch[3], 1515, 2000, 0, var_maxPWMTurn ));
      pp4 = abs(map(ch[3], 1515, 2000, 0, var_maxPWMTurn ));
      move_left();
    }
    else if (ch[3] < 1515)
    {
      ch3_neutral = false;
      pp3 = abs(map(ch[3], 1000, 1485, var_maxPWMTurn , 0));
      pp4 = abs(map(ch[3], 1000, 1485, var_maxPWMTurn , 0));
      move_right();
    }
    if (ch1_neutral && ch3_neutral)
    {
      neutral();
    }
    int servo1 = map(ch[4], 1000, 2000, 90, 0);
    int servo22 = map(ch[4], 1000, 2000, 90, 0);
  }
  else
  {
    neutral();
  }
  //  }
  //  else
  //  {
  //    if (ch[6] >= 1500)
  //    {
  //      if (ch[5] < 1333)
  //      {
  //        var_maxPWM = 120;
  //        Serial.println("First Gear");
  //      }
  //      else if (ch[5] > 1334 && ch[5] < 1666)
  //      {
  //        var_maxPWM = 180;
  //        Serial.println("Second Gear");
  //      }
  //      else
  //      {
  //        var_maxPWM = 255;
  //        Serial.println("Third Gear");
  //      }
  //
  //      if (ch[1] > 1485 && ch[1] < 1515)
  //      {
  //        ch1_neutral = true;
  //      }
  //      else if (ch[1] > 1515)
  //      {
  //        ch1_neutral = false;
  //        pp1 = abs(map(ch[1], 1500, 2000, 0, var_maxPWM));
  //        pp2 = abs(map(ch[1], 1500, 2000, 0, var_maxPWM));
  //        move_forward();
  //      }
  //      else if (ch[1] < 1485)
  //      {
  //        ch1_neutral = false;
  //        pp1 = abs(map(ch[1], 1000, 1500, var_maxPWM, 0));
  //        pp2 = abs(map(ch[1], 1000, 1500, var_maxPWM, 0));
  //        move_backward();
  //      }
  //      if (ch[3] > 1485 && ch[3] < 1515)
  //      {
  //        ch3_neutral = true;
  //      }
  //      else if (ch[3] > 1515)
  //      {
  //        ch3_neutral = false;
  //        pp3 = abs(map(ch[3], 1515, 2000, 0, var_maxPWM ));
  //        pp4 = abs(map(ch[3], 1515, 2000, 0, var_maxPWM ));
  //        move_right();
  //      }
  //      else if (ch[3] < 1515)
  //      {
  //        ch3_neutral = false;
  //        pp3 = abs(map(ch[3], 1000, 1485, var_maxPWM , 0));
  //        pp4 = abs(map(ch[3], 1000, 1485, var_maxPWM , 0));
  //        move_left();
  //      }
  //      if (ch1_neutral && ch3_neutral)
  //      {
  //        neutral();
  //      }
  //      servo_1.write(map(ch[4], 1000, 2000, 180, 0));
  //      servo_2.write(map(ch[4], 1000, 2000, 180, 0));
  //    }
  //    else
  //    {
  //      neutral();
  //    }
  //  }
}

void readPPMData()
{
  for (int channel = 1; channel <= channelAmount; ++channel) {
    unsigned long value = ppm.latestValidChannelValue(channel, 0);
    ch[channel - 1] = value;
  }
}

void move_forward()
{
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  analogWrite(pwm1, pp1);
  analogWrite(pwm2, pp2);
  Serial.println("FORWARD");
}

void move_backward()
{
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  analogWrite(pwm1, pp1);
  analogWrite(pwm2, pp2);
  Serial.println("BACKWARD");
}

void move_left()
{
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  analogWrite(pwm1, pp3);
  analogWrite(pwm2, pp4);
  Serial.println("LEFT");
}

void move_right()
{
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  analogWrite(pwm1, pp3);
  analogWrite(pwm2, pp4);
  Serial.println("RIGHT");
}

void neutral()
{
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, LOW);
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  Serial.println("NEUTRAL");
}
