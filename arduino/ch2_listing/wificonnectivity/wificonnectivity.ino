#include <ESP8266WiFi.h> //เรียกใช้ไลบรารีไวไฟ

const char* ssid = "your-ssid"; //SSID (Service Set Identifier) ชื่อของเครือข่ายไวไฟ
const char* password = "your-password"; //PASSWORD  รหัสผ่านของเครือข่าย

void setup() {
  Serial.begin(115200); //เริ่มส่งข้อความไปยังคอมพิวเตอร์ด้วยพอรต์ซีเรียล
  Serial.println();

  WiFi.begin(ssid, password); //เริ่มเชื่อมต่อเครือข่าย

  Serial.print("Connecting WiFi..");
  Serial.println();
  while (WiFi.status() != WL_CONNECTED) { //รอให้ไวไฟเขื่อมต่อ
    Serial.print("Attempting WiFi Connection");
    delay(500);
    Serial.print(".");
  }

  //ให้แสดงผลทางพอร์ตซีเรียล
  Serial.println();
  Serial.print("Connection Successful");
  Serial.println("");

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
}
