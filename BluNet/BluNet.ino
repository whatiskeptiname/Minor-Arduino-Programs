#include<SoftwareSerial.h>
SoftwareSerial s1(2,3);
SoftwareSerial s2(4,5);

void setup()
{
  s2.begin(9600);
  s1.begin(9600);
}
void loop()
{
  if(s1.available())
  {
    s2.write(s1.read());
    //s2.println(s1.read());
  }
  if(s2.available())
  {
    s1.write(s2.read());
    //s1.println(s2.read());
  }
}
