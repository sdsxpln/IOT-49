// Libraries
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Credentials
char ssid[] = "XXXXXX";     //  your network SSID (name)
char pass[] = "XXXXXX";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = {"iot.eclipse.org"};
int port = 1883;
char topic[] = {"XXXXXXXX/XXXXXXX"};
WiFiClient client;


void callback(char* topic, byte* payload, unsigned int length)
  {
  // Print payload
  String payloadContent = String((char *)payload);
  Serial.println("[INFO] Payload: " + payloadContent);
}

PubSubClient pubSubClient(server, 1883, callback, client);

void setup() {
  
  // Serial 
  Serial.begin(115200);

  // Attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    Serial.println(status);
    // Wait 10 seconds for connection:
    delay(30000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printWifiData();

   //Connect MQTT Broker
  Serial.println("[INFO] Connecting to MQTT Broker");
  if (pubSubClient.connect("arduinoClient1"))
  {
    Serial.println("[INFO] Connection to MQTT Broker Successful");

    pubSubClient.subscribe(topic);
    Serial.println("[INFO] Successfully Subscribed to MQTT Topic ");

    Serial.println("[INFO] Publishing to MQTT Broker");
    pubSubClient.publish(topic, "Test Message");
  }
  else
  {
    Serial.println("[INFO] Connection to MQTT Broker Failed");
  } 

}

void loop() {

  // Wait for messages from MQTT broker
  pubSubClient.loop();
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}

