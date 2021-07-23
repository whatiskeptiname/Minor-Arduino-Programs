#include <IRremote.h>

int hexa[20]={0};
IRsend irsend;
char data;

int RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;

void decthex(int temp)
{
  int quot;
  int i=0;
  while(quot!=0)
  {
  temp=quot%16;
    // to convert integer into character
    if(temp<10)
    {
      temp=temp+48;
    }
    else
    {
      temp=temp+55;
    }
    hexa[i++]=temp;
    quot=quot/16;
  }
}

long int arrtstr(int a[])
{
  int finalNumber;
  for (int i = 0; i < (sizeof(a)/sizeof(*a)); i++) {
    int num = a[i];
    if (num != 0) {
        while (num > 0) {
            finalNumber *= 10;
            num /= 10;
        }
        finalNumber += a[i];
    } else {
        finalNumber *= 10;
    }
    return finalNumber;
}
}
void sendd()
{
  
  decthex(results.value);

  long int code= arrtstr(hexa);

  for(int i=0;i<100;i++)lll
  {
  irsend.sendRaw(code, HEX, i);
  Serial.println(code);

  delay(100);
  }
  Serial.println("End of Test");
}
void receivee()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    if (results.value == 0x40BD28D7) Serial.println("Power button pressed");
    else if (results.value == 0x40BD30CF) Serial.println("Mute botton pressed");
    irrecv.resume(); // Receive the next value
  }
  delay(1000);
}

void setup()
{
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);

  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop()
{
  if (Serial.available() > 0)
  {
    data = Serial.read();
  }

  if (data == '0')
  {
    Serial.println("Receive mode");
    receivee();
  }

  if (data == '1')
  {
    Serial.println("send mode");
    sendd();
  }
}
