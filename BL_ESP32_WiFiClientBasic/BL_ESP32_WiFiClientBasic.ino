#include <ETH.h>
#include <HTTPClient.h>

/*
    This sketch sends a message to a TCP server

*/

#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

const uint16_t port = 80;
const char * host = "192.168.43.41"; // ip or dns


const byte led = 13; //D13
const byte sw = 12; //D12
int state = LOW;

void setup()
{
  pinMode(sw, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  WiFiMulti.addAP("lan", "1234567890");

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);

  state = digitalRead(sw);
}


void loop()
{

  if ((WiFi.status() == WL_CONNECTED)) {

    HTTPClient http;

    //    if (digitalRead(sw) == HIGH) {
    //
    //      Serial.print("[HTTP] begin...\n");
    //      http.begin("http://192.168.43.41/sw");
    //
    //      Serial.print("[HTTP] GET...\n");
    //      int httpCode = http.GET();
    //      http.end();
    //
    //    }

    if (state != digitalRead(sw)) {
      state = digitalRead(sw);
      Serial.print("[HTTP] LED on...\n");
      if (state == HIGH) {
        http.begin("http://192.168.43.41/led_on");
      } else {
        http.begin("http://192.168.43.41/led_off");
      }
      int httpCode = http.GET();
      http.end();
    }
  }


  //  Serial.print("connecting to ");
  //  Serial.println(host);
  //
  //  // Use WiFiClient class to create TCP connections
  //  WiFiClient client;
  //
  //  if (!client.connect(host, port)) {
  //    Serial.println("connection failed");
  //    Serial.println("wait 5 sec...");
  //    delay(5000);
  //    return;
  //  }
  //
  //  // This will send the request to the server
  //  client.print("Send this data to server");
  //
  //  //read back one line from server
  //  String line = client.readStringUntil('\r');
  //  client.println(line);
  //
  //  Serial.println("closing connection");
  //  client.stop();
  //
  //  Serial.println("wait 5 sec...");
  //  delay(5000);
}
