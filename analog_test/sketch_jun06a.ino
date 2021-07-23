void setup() {
  Serial.begin(9600);
  
  
}

void loop() {
  long data;
  data=analogRead(A5);
  Serial.println(A5);
  

}
