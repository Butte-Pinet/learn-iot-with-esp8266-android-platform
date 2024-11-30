#include <ESP8266WiFi.h>
//#include <WiFiClient.h>

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
  while (WiFi.status() != WL_CONNECTED) {
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
  if (client.connect(host, port)) {
    Serial.println("connected");

    String url = "?temperature=";
    url += String(temp);
    url += String("&humidity=");
    url += String(hum);
    Serial.println("Sending a request");
    
    client.print(String("GET /get") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
                
    Serial.println("Request sent");
    Serial.println("Response: ");
    while (client.connected()){ // loop while the client's connected
      if (client.available()){ // if there are bytes to read from the client,
        String line = client.readStringUntil('\n');
        Serial.println(line);
        //char c = client.read();  // read a byte, then
        //Serial.write(c);         // print it out the serial monitor
      }
    }
    client.stop();
    Serial.println("\nDisconnected");
  }
  else{
    Serial.println("Connection failed!");
    client.stop();
  }
  delay(5000);
}
