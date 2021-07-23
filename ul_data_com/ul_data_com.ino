int const echo = 2;
int const trig = 3;
int dist,duration;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}
double distance()
{
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);
  //dist = duration * 0.034 / 2;
  return duration;
}
void loop()
{
  Serial.println(distance());
  delay(1000);
}
