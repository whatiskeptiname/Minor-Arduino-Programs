int data, count, tri;
void setup()
{
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(5, INPUT);

}

void loop()
{

  tri = digitalRead(5);
  data = analogRead(A0);

  if (tri == 0)
  {
    if (data < 800)
    {
      digitalWrite(12, HIGH);
      digitalWrite(10, LOW);
      count++;
      Serial.println("On the target: ");
      Serial.print(count);
      Serial.print(" times\n");
      delay(250);

    }
    else
    {
      Serial.println("Better luck next time");
    }
  }
  else
  {
    digitalWrite(12, LOW);
  }
}
