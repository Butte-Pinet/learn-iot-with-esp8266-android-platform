#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "your-ssid";
const char* password = "your-password";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;

const char* mqtt_Client = "Node_MCU-Client";
const char* mqtt_username = "Node_MCU-ID-Token";
const char* mqtt_password = "Node_MCU-Secret";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg= 0;
int value = 0;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("@msg/greeting");
      Serial.print("Subscribe: ");
      Serial.println("@msg/greeting");
      
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
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  
    client.loop();
    long now = millis();
    if (now -lastMsg> 2000) {
      lastMsg= now;
      ++value;
      client.publish("@msg/greeting", "Hello NETPIE2020");
      Serial.print("Message publish: ");
      Serial.println("Hello NETPIE2020");
      }
  
  delay(1);
}
