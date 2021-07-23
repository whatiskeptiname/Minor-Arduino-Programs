#define mA1 12   // A motor
#define mA2 11
#define mB1 10   // B motor
#define mB2 9
#define  trigPin 8    
#define  echoPin 7 
#define IR1 6 
#define IR2 5
long int dist,duration,IRs1,IRs2,data; 

void setup()
{
  pinMode(IR1, INPUT);
  pinMode(IR2,INPUT);
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin (9600);
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

  //read tx dataa
  data=Serial.read();
  
  // Read IR state
  
  IRs1=digitalRead(IR1);
  IRs2=digitalRead(IR2);  
  
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  
  duration = pulseIn(echoPin, HIGH);
  
  // convert the time into a distance
  
  dist = (duration/2)/29.1;
  
  Serial.print(dist);
  Serial.print(" cm IR state: ");
  Serial.print(IRs1);
  Serial.print(",");
  Serial.print(IRs2);
  Serial.println();
  delay(200);
}
void forward()
{
   digitalWrite(mA1, LOW);
   digitalWrite(mA2, HIGH);
   digitalWrite(mB1, HIGH);
   digitalWrite(mB2, LOW);
}
void backward()
{
   digitalWrite(mA1, HIGH);
   digitalWrite(mA2, LOW);
   digitalWrite(mB1, LOW);
   digitalWrite(mB2, HIGH);
}
void left()
{
   digitalWrite(mA1, HIGH);
   digitalWrite(mA2, LOW);
   digitalWrite(mB1, HIGH);
   digitalWrite(mB2, LOW);
}
void right()
{
   digitalWrite(mA1, LOW);
   digitalWrite(mA2, HIGH);
   digitalWrite(mB1, LOW);
   digitalWrite(mB2, HIGH);
}
void wait()
{
   digitalWrite(mA1, LOW);
   digitalWrite(mA2, LOW);
   digitalWrite(mB1, LOW);
   digitalWrite(mB2, LOW);
}
void AI() 
{
  sensor_check();

  if(IRs1||IRs2)
  {
    backward();
    delay(1000);
    right();
    delay(1000);
  }
  else
  {
    if(dist<=7)
    {
      backward();
    }
    else if(dist>=10&&dist<=12)
    {
      right();
    }
    else
    {
      forward();
    }
  } 
}

void manual() 
{
  sensor_check();

  switch(data)
  {
    case 1:
    forward();
    break;
    case 2:
    right();
    break;
    case 3:
    backward();
    break;
    case 4:
    left();
    break;
    deafult:
    wait();
    break;
  }
}

void loop()
{
    manual();
}

