#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "Xiaomi 11i";
const char* password = "rhsx4212";

unsigned long channelID = 2743849;
const char* writeAPIKey = "6NZMT6H8YF7EKSPH";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to WiFi...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("!");
  }
  Serial.println("Connected to WiFi");
  
  ThingSpeak.begin(client);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');

    Serial.print("Received data: ");
    Serial.println(data);

    if (data.length() > 0) {
      float temperature, humidity, smoke;
      int red, green, blue;

      int commaIndex1 = data.indexOf(',');
      int commaIndex2 = data.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = data.indexOf(',', commaIndex2 + 1);
      int commaIndex4 = data.indexOf(',', commaIndex3 + 1);
      int commaIndex5 = data.indexOf(',', commaIndex4 + 1);
      temperature = data.substring(1, commaIndex1).toFloat();  
      humidity = data.substring(commaIndex1 + 1, commaIndex2).toFloat();  
      smoke = data.substring(commaIndex2 + 1, commaIndex3).toFloat();  
      red = data.substring(commaIndex3 + 1, commaIndex4).toInt();  
      green = data.substring(commaIndex4 + 1, commaIndex5).toInt();  
      blue = data.substring(commaIndex5 + 1).toInt();  

      Serial.print("Parsed Data - Temp: ");
      Serial.print(temperature);
      Serial.print(", Humidity: ");
      Serial.print(humidity);
      Serial.print(", Smoke: ");
      Serial.print(smoke);
      Serial.print(", Red: ");
      Serial.print(red);
      Serial.print(", Green: ");
      Serial.print(green);
      Serial.print(", Blue: ");
      Serial.println(blue);

      ThingSpeak.setField(1, temperature);
      ThingSpeak.setField(2, humidity);
      ThingSpeak.setField(3, smoke);
      ThingSpeak.setField(4, red);
      ThingSpeak.setField(5, green);
      ThingSpeak.setField(6, blue);

      int responseCode = ThingSpeak.writeFields(channelID, writeAPIKey);

      if (responseCode == 200) {
        Serial.println("Data sent to ThingSpeak successfully!");
      } else {
        Serial.println("Data sent to ThingSpeak successfully!");
      }
    } else {
      Serial.println("Error: No valid data received.");
    }
  }

  delay(1000);
}
