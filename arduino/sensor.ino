#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>

#include <dht11.h>
#include "NewPing.h"
#define TRIGGER_PIN D2
#define ECHO_PIN D3

#define MAX_DISTANCE 400  
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float mesafe = 0;

#define DHT11PIN D1

float sicaklik = 0.0 , nem=0.0;
dht11 DHT11;
int sayac = 0;

const char* ssid = "*********";
const char* password = "*******";
const char* host = "192.168.0.104";

void setup() 
{
  Serial.begin(9600);
  Serial.print("Erisim noktasi baslatiliyor...");
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println(""); 
  Serial.println("WiFi baglandi"); 
  Serial.println("IP: "); 
  Serial.println(WiFi.localIP());
}
void loop() 
{
    Serial.println(" sayac:"+String(sayac++));
    mesafe_olc();
    if( mesafe < 50 && mesafe > 10){
        sicaklik_olc();
        Serial.println("sicaklik: "+ String(sicaklik) +" Nem: "+ String(nem)+" Mesafe: "+ String(mesafe));
        post_request();
        delay(5000);
    }
    else{
        Serial.println("Mesafe uygun degil");
    }
  delay(1000);
}

void sicaklik_olc(){
    DHT11.read(DHT11PIN);
    sicaklik=DHT11.temperature;
    nem = DHT11.humidity;
    delay(200);
  }
void mesafe_olc(){
    mesafe = sonar.ping_cm();
    delay(200);
}

void post_request(){
  Serial.print("API baglantisi saglaniyor.. "); 
  Serial.println(host); 
  WiFiClient client; 
  const int httpPort = 3000; 
  if (!client.connect(host, httpPort)) 
  { 
  Serial.println("Baglanti hatasi"); 
  return; 
  } 
  String postData = "{\"humidity\":\""+ String(nem) +"\",\"temperature\":\""+ String(sicaklik)+"\",\"distance\":\""+ String(mesafe)+"\"}"; 
  String address = "http://192.168.0.104:3000/api/services"; 
  HTTPClient http; 
  http.begin(address); 
  http.addHeader("Content-Type", "application/json"); 
  auto httpCode = http.POST(postData); 
  Serial.println(httpCode);
  String payload = http.getString(); 
  Serial.println(payload);
  http.end();
  Serial.println("API baglantisi kapatildi");

}
