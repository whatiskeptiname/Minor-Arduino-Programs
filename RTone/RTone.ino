/* This program generates a random tone */

void setup()
{ 
  /* Pins for buzzer output*/
  pinMode(3, OUTPUT);  
  pinMode(2, OUTPUT);

/* Gnd port can be used in place of port 3 */
  digitalWrite(3, LOW);
  Serial.begin(9600);
}

/* Function to play the tone generated randomly */
void play(int duration, int frequency, int n)
{
  for (int i = 0; i < n; i++);
  {
    tone(2, frequency, duration);
  }
}

void loop()
{
/* Random number is generated and fed to the tone function to generate a unique tone */
  int duration, frequency, n;
  randomSeed(analogRead(0));
  Serial.println(analogRead(0));
  duration = random(100, 3000);
  randomSeed(analogRead(0));
  Serial.println(analogRead(0));
  frequency = random(500, 10000);
  randomSeed(analogRead(0));
  Serial.println(analogRead(0));
  n = random(1, 10);

  play(duration, frequency, n);
}
