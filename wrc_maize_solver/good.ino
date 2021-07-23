#define fthold 10
#define rthold 13
#define lthold 13


#define l1 10
#define l2 11
#define r1 12
#define r2 13


float front, right, left;
float t = 1045;
unsigned long stop_time;
unsigned long desired_time;
unsigned long desired_time_1;
unsigned long desired_time_2;
const int ena = 10;
const int enb = 11;
const int ena1 = 200;
const int ena2 = 130;




#include<Arduino.h>
//  Front US sensor.
const int trigPinf = 2; const int echoPinf = 6;

//  Right US sensor.
const int trigPinr = 8; const int echoPinr = 5;

//  Left US sensor.
const int trigPinl = 3; const int echoPinl = 9;




float frontdist()
{

  float gapfront;//how much gap is in front

  float lagnetimef;

  digitalWrite(trigPinf, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPinf, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPinf, LOW);


  lagnetimef = pulseIn(echoPinf, HIGH);

  gapfront = lagnetimef * 0.0344 / 2;



  // in one cm there are 29 microseconds.



  return gapfront;


}

//same can be done for left and right not using NewPing library

//  Returns the distance the wall to its right side
float rightdist()
{

  float gapright;
  float lagnetimer;

  digitalWrite(trigPinr, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinr, LOW);

  lagnetimer = pulseIn(echoPinr, HIGH);

  gapright = lagnetimer * 0.0344 / 2;

  return gapright;

}

//  Returns the distance of the wall to its left side
float leftdist() {

  float gapleft;
  float lagnetimel;

  digitalWrite(trigPinl, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPinl, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPinl, LOW);

  lagnetimel = pulseIn(echoPinl, HIGH);

  gapleft = lagnetimel * 0.0334 / 2;

  return gapleft;

}

// Main code here
// this is where lang lang begins






void stopit() {
  //bot stop garna k garnu parxa tyo lekh hai
  delay(400);
  analogWrite(ena, ena1);
  analogWrite(enb, ena2);
  digitalWrite(l1, LOW);

  digitalWrite(l2, LOW);

  digitalWrite(r1, LOW);

  digitalWrite(r2, LOW);
  Serial.print("Stoooooop");
}






void rotate_right() {
  //delay(30);
  //for(stop_time=0;stop_time<desired_time;stop_time=millis())
  //{
  analogWrite(ena, ena1);
  analogWrite(enb, ena2);
  digitalWrite(l1, LOW);
  digitalWrite(l2, HIGH);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  stopit();
  //}
  Serial.print("right chaliraxa\n");
}




void rotate_left() {

  //for(stop_time=0;stop_time<desired_time;stop_time=millis())
  //{
  analogWrite(ena, ena1);
  analogWrite(enb, ena2);
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  stopit();
  //}
  Serial.print("left chaliraxa\n");
}



void rotate_front() {

  //for(stop_time=0;stop_time<desired_time_2;stop_time=millis())
  //{
  analogWrite(ena, ena1);
  analogWrite(enb, ena2);
  digitalWrite(l1, HIGH);
  digitalWrite(l2, LOW);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  delay(600);
  //}
  Serial.print("U TURN chaliraxa\n");
}


void backward()
{

  analogWrite(ena, ena1);
  analogWrite(enb, ena2);
  digitalWrite(l1, HIGH);
  digitalWrite(l2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
  Serial.print("back chaliraxa\n");
  delay(100);

}




/* 300 by 150 cm ko boxa hunxa yeuta sq box 30x30 ko hunxa bot 15x15x10 roughly*/
void gofront()

{

  //  Moves forward adjusting its path

  float ldist1 = leftdist();

  float lconst = ldist1;


  while (ldist1 <= 4)

  {



    // Should turn a little to its right

    analogWrite(ena, 180);
    analogWrite(enb, 100);
    digitalWrite(4, LOW);

    digitalWrite(7, HIGH);

    digitalWrite(12, LOW);

    digitalWrite(13, LOW);

    //delay(t/65);

    //stop_time=millis();

    ldist1 = leftdist();

    if (abs(lconst - ldist1) >= 0.8 || (ldist1 >= 7.8)) {
      break;
    }

    //ali bot left tira gaa xa bhane ali right tira purauxa
    //hoping that dist betn wall and bot is 8

  }

  float rdist1 = rightdist();

  float rconst = rdist1;


  while (rdist1 <= 4)
  {

    // Should turn a little to its left

    analogWrite(ena, 180);
    analogWrite(enb, 100);
    rotate_left();

    //delay(t/65);

    //stop_time=millis();

    rdist1 = rightdist();

    if (abs(rconst - rdist1) >= 0.9) {
      break;
    }

  }


  if (leftdist() <= 4)
  {

    // Will move little to its left if its too far from the left wall

    analogWrite(ena, 180);
    analogWrite(enb, 100);
    rotate_left()

    //delay(t/30);

  }
  //agadi jane code
  //delay(30);
  analogWrite(ena, ena1);
  analogWrite(enb, ena2);
  rotate_forward();
  Serial.print("Agadi\n");
  delay(50); //MAY CHANGE
}
/*bool reached_end = false;

  bool fsensor= false;  // For the front US sensor.

  bool rsensor= false; // For the right US sensor.

  bool lsensor= false; // For the left US sensor.
*/


// Setting up the
void setup()
{

  desired_time = 600;
  //desired_time_1=50;
  desired_time_2 = 1400;

  //  US pins setup..
  pinMode (trigPinf, OUTPUT);
  pinMode (echoPinf, INPUT);
  pinMode (trigPinr, OUTPUT);
  pinMode (echoPinr, INPUT);
  pinMode (trigPinl, OUTPUT);
  pinMode (echoPinl, INPUT);


  //  Motor pins.
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);


  //initialization of motors
  analogWrite(ena, 200);
  analogWrite(enb, 100);
//  digitalWrite(4, LOW);
//  digitalWrite(7, HIGH);
//  digitalWrite(12, HIGH);
//  digitalWrite(13, LOW);

  Serial.begin(9600); //staartingg serial communication...9600 bits per second.


}



void loop()
{
  // Sabai basera lekhne code yesma

  front = frontdist();
  Serial.print("Front:");
  Serial.print( front );

  right = rightdist();
  Serial.print("    Right:");
  Serial.print( right );

  left = leftdist();
  Serial.print("    Left:");
  Serial.print( left );


  /*if(right<=rthold) rsensor = true; //rightwall closed

    if(left<=lthold) lsensor = true;//left closed

    if(front<=fthold) fsensor = true;//frontclosed
  */

  //various cases for direction
  //if(front=0)
  //{
  //  backward();
  //  delay(30);
  //}
  if (left <= lthold && right > rthold && front <= fthold)
  {

    rotate_right();
  }
  else if (left <= lthold && right > rthold && front > fthold)
  {
    gofront();
  }
  //else if(left>250 && right>250 && front>250)
  //{
  //  gofront();
  //}
  else if (left <= lthold && right <= rthold && front > fthold)
  {
    gofront();
  }

  else if (left > lthold && right <= rthold && front > fthold)
  {

    rotate_left();
  }
  else if (left > lthold && right > rthold && front > fthold)
  {

    rotate_left();
    //rotate_front();
  }
  else if (left <= lthold && right <= rthold && front <= fthold)
  {

    rotate_front();

  }
  else if (left > lthold && right <= rthold && front <= fthold)
  {

    rotate_left();
  }
  else if (left > lthold && right > rthold && front <= fthold)
  {

    rotate_left();
  }
  else if (front <= 4 && front >= 0 ) {

    backward();

  }


}
