#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "DHT.h";

#define DHTPIN D6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "your-ssid";
const char* password = "your-password";

const char* host = "www.httpbin.org";
int port = 80;

WiFiClient client;

void setup(){
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting WiFi Connection");
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connection Successful");
  Serial.println("");

/**
  // Start the server
  server.begin();
  Serial.println("Server started");

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
**/

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop(){
  delay(2500);// ให้รอระหว่างวัดค่า
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  //ตรวจสอบถ้าอ่านผิดพลาดให้อ่านอีก
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String url = "?temp=";
  url += String(temp);
  url += String("&hum=");
  url += String(hum);
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port)) {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("POST /post") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Response:]");
    while (client.connected()) {
      if (client.available()) {
        //String line = client.readStringUntil('\n');
        //Serial.println(line);
        char c = client.read();
        Serial.write(c);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
    Serial.println();
  }
  else {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(50);

  Serial.print("Read Temperature as Celcius ");
  Serial.println("and Humidity as percent.");
   
  Serial.print(F("Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp);
  Serial.print(F("°C "));
  Serial.println();
  
  delay(5000);
}
