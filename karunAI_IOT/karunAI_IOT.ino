#include<ESP8266WiFi.h>
#define RELAY_IN1 3

int inByte;
char ssid[] = "wabbalabbadubdub";
char password[] = "ooooooop";

WiFiServer server(80);

void setup() {

  Serial.begin(115200);
  pinMode(RELAY_IN1, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print('.');

  }

  Serial.println("");
  Serial.println("WIFI CONNECTED");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.print("Server Started");

}

void loop() {

  WiFiClient wClient = server.available();
  if (!wClient) {
    return;
  }


  Serial.println("New Client");
  while (!wClient.available()) {
    delay(1);
  }

  String request = wClient.readStringUntil('\r');
  Serial.println(request);
  wClient.flush();

  delay(2000);
}
