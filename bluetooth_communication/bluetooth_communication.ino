#define ena_pin 2
#define state 3
char data;
void setup() 
{
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 Serial.begin(9600);
 if(Serial.available()>0)
 {
  data=Serial.read();
 }

}

void loop() 
{
Serial.println(data);
digitalWrite(ena_pin,LOW);
digitalWrite(state,HIGH);
}
