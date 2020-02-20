#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

WiFiClient espClient;

// ------------- ULTRASONIC SENSORS -------------
#define ULTRASONIC_TRIG    16   // pin TRIG to D1
#define ULTRASONIC_ECHO    0   // pin ECHO to D2

int triggerDistance = 80; 

typedef struct {
  int dist; //Sensor Distance
} ultraSonic;

ultraSonic us;

const char* ssid = "University of Washington"; // Wifi network SSID
const char* password = ""; // Wifi network password

//String ip = "172.28.219.179"; // Sieg Master IP
//String api_token = "rARKEpLebwXuW01cNVvQbnDEkd2bd56Nj-hpTETB"; // Sieg Master API Token

String ip = "172.28.219.177"; // Red IP
String api_token = "Lht3HgITYDN-96UYm5mkJ4CEjKj20d3siYidcSq-"; // Red API Token

int number = 1;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  setup_ultrasonic();
  changeGroup(0, 10, "on", "false", "bri", "254", "hue", "40000", "sat", "200");
  Serial.println("lights off");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
      delay(1);
      Serial.print("WIFI Disconnected. Attempting reconnection.");
      setup_wifi();
      return; //End this loop cycle if WiFi disconnected
    }
   detectDistance();
//   if (us.dist < triggerDistance){
//    changeGroup(0, 10, "on", "true", "bri", "254", "hue", "40000", "sat", "200");
//   }
}

void detectDistance(){
   long duration, distance;
   digitalWrite(ULTRASONIC_TRIG, LOW);  
   delayMicroseconds(2); 
   digitalWrite(ULTRASONIC_TRIG, HIGH);
   delayMicroseconds(10); 
   digitalWrite(ULTRASONIC_TRIG, LOW);
   duration = pulseIn(ULTRASONIC_ECHO, HIGH);
   distance = (duration/2) / 29.1;
   Serial.print("1111111111 ------ Ultrasonic Distance: ");
   Serial.print(distance);
   Serial.println(" cm");
   us.dist = distance;
}

void setup_ultrasonic(){
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
}

void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("Connected to the WiFi network");
}
