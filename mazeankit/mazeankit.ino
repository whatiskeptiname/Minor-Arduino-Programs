
/*--Defination part for motor driver--*/

#define   ENA     11     //Enable pin A
#define   ENB     10        //Enable pin B
#define   INA1    12        //Input pin for right motor         
#define   INA2    13
#define   INB1    8       //Input pin for left motor
#define   INB2    9

/*--Defination part for ultrasonic sensor--*/

#define   E0      2         //Left most echo
#define   E1      3         //Centre one   echo
#define   E2      4         //Right most    echo
#define   T0      5         //Left most trigger
#define   T1      6         //Centre one   trigger
#define   T2      7         //Right most  trigger
int spee = 65;
int de = 100;
int threshold = 15;
int forward_threshold=10;
float value;
void forward() {
  //delay(de);
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);
  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW); 

  analogWrite(ENA, spee);
  analogWrite(ENB, spee);
}  
void backward() {
   //delay(de);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH); 

  analogWrite(ENA, spee);
  analogWrite(ENB, spee);
}  
void left() {
  delay(de);
  digitalWrite(INA1, HIGH); // right motor forward
  digitalWrite(INA2, LOW);
  digitalWrite(INB1, LOW);// left motor forward
  digitalWrite(INB2, LOW); 

  analogWrite(ENA, spee);
  analogWrite(ENB, spee);
  
  
 
}
void right() {
   delay(de);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW); 

  analogWrite(ENA, spee);
  analogWrite(ENB, spee);
}    
void rotate(){
  if(lDistance() <=10){
    
     digitalWrite(INA1, LOW);//right backward
     digitalWrite(INA2, HIGH);
     digitalWrite(INB1, HIGH);//left forward
     digitalWrite(INB2, LOW); 

     analogWrite(ENA, spee);
     analogWrite(ENB, spee);
     delay(500);
    
 }
  else if(rDistance() <=10){
     //delay(de);
     digitalWrite(INA1, HIGH);//right forward
     digitalWrite(INA2, LOW);
     digitalWrite(INB1, LOW);//left backward
     digitalWrite(INB2, HIGH); 

     analogWrite(ENA, spee);
     analogWrite(ENB, spee);
     delay(500);
  }
  else if(lDistance() <=10 && rDistance() <=10){
    backward();
  }
 
  
  }

float fDistance() {
  digitalWrite(T1, HIGH);
  delayMicroseconds(10);
  digitalWrite(T1, LOW);
  delayMicroseconds(5);
  value = pulseIn(E1, HIGH);
  return (value / 58.3);
} 
float lDistance() {
  digitalWrite(T0, HIGH);
  delayMicroseconds(10);
  digitalWrite(T0, LOW);
  delayMicroseconds(5);
  value = pulseIn(E0, HIGH);
  return  (value / 58.3);
  
} 
float rDistance() {
  digitalWrite(T2, HIGH);
  delayMicroseconds(10);
  digitalWrite(T2, LOW);
  delayMicroseconds(5);
  value = pulseIn(E2, HIGH);
  return  (value / 58.3);
}  

void setup(){
  pinMode (INA1, OUTPUT);
  pinMode (INA2, OUTPUT);
  pinMode (INB1, OUTPUT);
  pinMode (INB2, OUTPUT);
  //pinMode (ENA, OUTPUT);
  //pinMode (ENB, OUTPUT);
  pinMode (T0, OUTPUT);
  pinMode (T1, OUTPUT);
  pinMode (T2, OUTPUT);
  pinMode (E0, INPUT);
  pinMode (E1, INPUT);
  pinMode (E2, INPUT);
  Serial.begin(9600);
  }


void loop(){
   if(lDistance() >= threshold ){
    left();
    delay(500);
    forward();
 }
   else if(lDistance() <= threshold &&  fDistance() >=forward_threshold){
    forward();
     }
   else if(lDistance() <= threshold &&  fDistance() <=forward_threshold && rDistance() >=threshold){
    right();
    
  }
  else if(lDistance() <= threshold &&  fDistance() <=forward_threshold && rDistance() <=threshold){
    rotate();
    
 }
 else {
  backward();
  
 }

  Serial.print(lDistance());
  Serial.print("  ");
  Serial.print(fDistance());
  Serial.print("  ");
  Serial.println(rDistance());
  
}
