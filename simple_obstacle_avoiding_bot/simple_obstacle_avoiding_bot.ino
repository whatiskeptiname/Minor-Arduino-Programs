int trigger_pin1 = 2;
int echo_pin1 = 3;

int trigger_pin2 = 12 ;
int echo_pin2 = 13;

int trigger_pin3 = 4;
int echo_pin3 = 5;

//right motor
int rm1 = 9;
int rm2 = 10;
int en1 = 11;

//left motor
int lm1 = 7;
int lm2 = 8;
int en2 = 6;

void setup()
{
  //front sensor
  pinMode(trigger_pin1, OUTPUT);
  pinMode(echo_pin1, INPUT);
  //left sensor
  pinMode(trigger_pin2, OUTPUT);
  pinMode(echo_pin2, INPUT);
  //right sensor
  pinMode(trigger_pin3, OUTPUT);
  pinMode(echo_pin3, INPUT);
  //right sensor
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(en1, OUTPUT);
  //left sensor
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(en2, OUTPUT);
  Serial.begin(9600);
}
double front_sensor()
{
  digitalWrite(trigger_pin1, LOW);
  delay(100);
  digitalWrite(trigger_pin1, HIGH);
  delay(10);
  digitalWrite(trigger_pin1, LOW);
  long duration1 = pulseIn(echo_pin1, HIGH);
  double distance1 = duration1 * 0.034 / 2;
  if (distance1 > 100) {
    distance1 = 0;
  }
  return distance1;
}
double left_sensor()
{
  digitalWrite(trigger_pin2, LOW);
  delay(100);
  digitalWrite(trigger_pin2, HIGH);
  delay(10);
  digitalWrite(trigger_pin2, LOW);
  long duration2 = pulseIn(echo_pin2, HIGH);
  double distance2 = duration2 * 0.034 / 2;
  if (distance2 > 100) {
    distance2 = 0;
  }
  return distance2;
}
double right_sensor()
{
  digitalWrite(trigger_pin3, LOW);
  delay(100);
  digitalWrite(trigger_pin3, HIGH);
  delay(10);
  digitalWrite(trigger_pin3, LOW);
  long duration3 = pulseIn(echo_pin3, HIGH);
  double distance3 = duration3 * 0.034 / 2;
  if (distance3 > 100) {
    distance3 = 0;
  }
  return distance3;
}
void right()
{
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  analogWrite(en1, 70);
  analogWrite(en2, 70);
  Serial.println("===============");
  Serial.println("RIGHT");
}
void left()
{
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  analogWrite(en1, 70);
  analogWrite(en2, 70);
  Serial.println("===============");
  Serial.println("LEFT");
}
void forward()
{
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  analogWrite(en1, 70);
  analogWrite(en2, 70);
  Serial.println("===============");
  Serial.println("FORWARD");
}
void backward()
{
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  analogWrite(en1, 70);
  analogWrite(en2, 70);
  Serial.println("===============");
  Serial.println("BACKWARD");
}
void stops()
{
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  analogWrite(en1, 0);
  analogWrite(en2, 0);

  Serial.println("===============");
  Serial.println("STOP");
}


void loop()
{
  double f = front_sensor();
  double l = left_sensor();
  double r = right_sensor();



  Serial.print("left: ");
  Serial.print(l);

  Serial.print("forward: ");
  Serial.print(f);


  Serial.print("right: ");
  Serial.println(r);
  Serial.println("____________________________________________");

  while (f<60 and f>30)
  {
    forward();
  }
  if (f < 30)
  {
    stops();
    delay(500);
    if (r > l)
    {
      right();
      delay(215);
    } else
    {
      left();
      delay(215);
    }
  } else if (l = 0 )
  {
    stops();
    delay(400);
    backward();
    delay(400);
  }
}
