//Living Room Monotoring
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN D6
#define DHTTYPE DHT11

const char* ssid = "your-ssid";
const char* password = "your-password";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;

const char* mqtt_client = "clientID";
const char* mqtt_username = "username";
const char* mqtt_password = "password";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

//char msg[100];
long lastMsg= 0;
int value = 0;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      //client.subscribe("@shadow/data/updated");
      client.subscribe("@msg/livingroom/temphum");
      Serial.print("Subscribe: ");
      Serial.println("@msg/livingroom/temphum");
      Serial.println();     
}
  else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println("try again in 5 seconds");
    delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived: [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
    for (int i = 0; i < length; i++) {
      message = message + (char)payload[i];
  }
  Serial.println(message);
}

const String getDhtJson() {
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  //String place = "Living room";

  String jsonDoc;
  StaticJsonDocument<128> sObjDoc;
  StaticJsonDocument<128> doc;
  sObjDoc["temp"] = temperature;
  sObjDoc["hum"] = humidity;
  //sObjDoc["room"] = place;
  doc["dht"] = sObjDoc;

  serializeJsonPretty(doc, jsonDoc);
  Serial.println("Message: ");
  serializeJsonPretty(doc, Serial); //serializeJsonPretty()
  Serial.println();
  //serializeJson(doc, Serial);
  Serial.println();
  return jsonDoc;
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  dht.begin();
}

void loop() {
  //String place = "Living Room";

  if (!client.connected()) {
    reconnect();
  }

  client.loop();
    long now = millis();
    if (now - lastMsg > 2000) {
      lastMsg = now;
      ++value;
      //String data = "{\"data\": {\"humidity\":" + String(humidity) 
                    //+ ", \"temperature\":" + String(temperature) 
                    //+ ", \"place\":" +String(place) + "}}";
      //Serial.print("data: ");
      //Serial.println(data);
      //data.toCharArray(msg, (data.length() + 1));
      //client.publish("@shadow/data/update", msg);
      //client.publish("@msg/livingroom/temphum", msg);
      
      Serial.println(getDhtJson());
      Serial.println("Message published");
      client.publish("@msg/livingroom/temphum", getDhtJson().c_str());
      
      Serial.println();
      }
  
  delay(1);

}
