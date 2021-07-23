
void printt()
{
  Serial.println("bikash wins");
}
int do_this(char func)
{
 func(); 
}
void setup() {
  Serial.begin(9600);
}

void loop() 
{
  do_this(printt());
}
