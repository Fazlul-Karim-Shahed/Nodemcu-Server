#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>


DHT dht2(D5, DHT11);
// Adafruit_BMP085 bmp;

const char *ssid = "Shahed 2.4G";
const char *password = "20-43677-2";
// const int MQ_SENSOR_PIN = A0;
const int sensor_pin = A0;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println(WiFi.localIP());
  Serial.println("Connected to WiFi");

  //  if (!bmp.begin()) {
  //     Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  //     while (1) {}
  // }

}

void loop() {

  int temp = dht2.readTemperature();
  int hmd = dht2.readHumidity();
  // int gasLevel = analogRead(MQ_SENSOR_PIN);
  // int temp2 = bmp.readTemperature();
  // int pressure = bmp.readPressure();
  // int alt = bmp.readAltitude();
  // int seaPressure = bmp.readSealevelPressure();
  // int realAlt = bmp.readAltitude(101500);
  float moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );


  String apiURL = "http://192.168.0.103:4000/"; 
    // String apiURL = "https://nodemcu-server-2xr4c72hm-fazlul-karim-shahed.vercel.app/"; 


  WiFiClient client;
  HTTPClient http;

  http.begin(client, apiURL);
  // http.setTimeout(10000);  


  // Send the GET request and get the response
  // int httpResponseCode = http.GET();

  http.addHeader("Content-Type", "application/json");

  // Your POST data
// String postData = "{\"temperature\":" + String(temp) +
//                   ",\"temperature2\":" + String(temp2) +
//                   ",\"pressure\":" + String(pressure) + 
//                   ",\"altitude\":" + String(alt) +
//                   ",\"seaPressure\":" + String(seaPressure) +
//                   ",\"realAltitude\":" + String(realAlt) +
//                   ",\"humidity\":" + String(hmd) + 
//                   ",\"gasLevel\":" + String(gasLevel) + "}";

String postData = "{\"temperature\":" + String(temp) + 
                    ",\"humidity\":" + String(hmd) + 
                    ",\"moisture\":" + String(moisture_percentage) + "}";


  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    String payload = http.getString();
    Serial.println("Response payload:");
    Serial.println(payload);
  } else {
    Serial.print("HTTP Request failed. Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  delay(1000);
}




