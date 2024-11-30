#include <ESP8266WiFi.h>

const char* ssid = "your-ssid"; //SSID (Service Set Identifier) ชื่อของเครือข่ายไวไฟ
const char* password = "your-password"; //PASSWORD  รหัสผ่านของเครือข่าย

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");

  client.setTimeout(5000); 

  String req = client.readStringUntil('\r');
  Serial.println("request: ");
  Serial.println(req);

  while (client.available()) {
    client.read();
  }

  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<head>");
  client.print("<meta charset=\"utf-8\">");
  client.print("\r\n<meta name=\"viewport\"  ");
  client.print("content=\"width=device-width, ");
  client.print("initial-scale=1.0\">");
  client.print("\r\n<TITLE>NodeMCU</TITLE></head><BODY>");
  client.print("<CENTER><br>\r\nHello WiFi Server ");
  client.print("<br> HTTP Communication.</CENTER></BODY></html>");

  Serial.println("Disconnecting from client");
}
