//Just for fun
#include <Servo.h>
Servo gs,gu;
int fun=2.5;
void setup()
{
  gs.attach(9);
  gu.attach(8);
  Serial.begin(9600);
}

void loop()
{
//inat();
time_to_fun();

}

void inat()
{
gs.write(0);
gu.write(0);
}
void time_to_fun()
{
gs.write(0);
gu.write(180);
delay(1000/fun);
gs.write(180);
gu.write(0);
delay(1000/fun);
}
