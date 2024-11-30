#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "your-ssid";
const char* password = "your-password";

const char* host = "www.httpbin.org";
int port = 80;

int temp = 25;
int hum = 50;

void setup(){
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting WiFi Connection");
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connection Successful");
  Serial.println("");
}

void loop(){
  WiFiClient client;
  Serial.printf("\nConnecting to %s ... ", host);
  if (client.connect(host, port)){
    Serial.println("connected");

    String url = "temperature=";
    url += String(temp);
    url += String("&humidity=");
    url += String(hum);

    client.print(String("POST /post") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "Content-Type: application/x-www-form-urlencoded\r\n" +
                 "Content-Length: " + url.length() + "\r\n" +
                 "\r\n" + url + 
                 "\r\n"
                );
    /** //Request sent     
    client.println("POST /post HTTP/1.1");
    client.println("Host: " + String(host) );
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(url.length());
    client.println();
    client.println(url);
    **/
    Serial.println("Request sent");
    Serial.println("Response: ");
    while (client.connected()){
      if (client.available()){
        //String line = client.readStringUntil('\n');
        //Serial.println(line);
        char c = client.read();
        Serial.write(c);
      }
    }
    client.stop();
    Serial.println("\nDisconnected");
  }
  else{
    Serial.println("connection failed!");
    client.stop();
  }
  delay(5000);
}
