#include <ESP8266WiFi.h> //เรียกใช้ไลบรารีไวไฟ

const char* ssid = "your-ssid"; //SSID (Service Set Identifier) ชื่อของเครือข่ายไวไฟ
const char* password = "your-password"; //PASSWORD  รหัสผ่านของเครือข่าย

#define led 4 //gpio4 pin-4, d2

int value;

WiFiServer server(80);

void setup() {
  //เริ่มส่งข้อความไปยังคอมพิวเตอร์ด้วยพอรต์ซีเรียล
  Serial.begin(115200); 
  Serial.println();

  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  //เริ่มเชื่อมต่อเครือข่าย
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 

  Serial.print("Connecting WiFi..");
  Serial.println(ssid);
  Serial.println();

  //รอให้ไวไฟเขื่อมต่อ
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("Attempting WiFi Connection");
    delay(500);
    Serial.print(".");
  }

  //ให้แสดงผลทางพอร์ตซีเรียลมอนิเตอร์
  Serial.println();
  Serial.print("Connection Successful");
  Serial.println("");

  // Start the server
  server.begin();
  Serial.println("Server started");

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");

  client.setTimeout(5000); 

  String request = client.readStringUntil('\r');
  Serial.println("request: ");
  Serial.println(request);

  if (request.indexOf("/gpio4/0") != -1) {
    value = 0;
  } else if (request.indexOf("/gpio4/1") != -1) {
    value = 1;
  } else {
    Serial.println("invalid request");
    value = digitalRead(led);
  }

  digitalWrite(led, value);

  while (client.available()) {
    client.read();
  }

  //ส่ง request response ไปยังไคลเอ็นต์
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
  client.print("<!DOCTYPE HTML>\r\n<html>\r\n<head>");
  client.print("<meta charset=\"utf-8\">");
  client.print("\r\n<meta name=\"viewport\"  ");
  client.print("content=\"width=device-width, ");
  client.print("initial-scale=1.0\">");
  client.print("\r\n<TITLE>NodeMCU</TITLE></head><BODY>");
  client.print("<CENTER><br>\r\nLED (GPIO4):  ");
  client.print(value ? "ON" : "OF");
  client.print("<br><br><a href='http://");
  client.print(WiFi.localIP());
  client.print("/gpio4/1'><button>ON</button></a>");
  client.print("&nbsp;&nbsp;<a href='http://");
  client.print(WiFi.localIP());
  client.print("/gpio4/0'><button>OFF</button></a><br>");
  client.print("<br><br> HTTP Communication.</CENTER></BODY></html>");

  Serial.println("Disconnecting from client");
  
}
